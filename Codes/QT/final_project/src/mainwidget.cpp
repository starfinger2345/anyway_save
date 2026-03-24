#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDateTime>
#include <thread>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    // , node_(rclcpp::Node::make_shared("qt_map_viewer"))
    // , pose_callback_(node_)
{
    ui->setupUi(this);

    ui->S_lift_state->setRange(1104, 2346);
    ui->S_lift_state->setValue(lift_angle);
    ui->LB_lift_state->setText(QString::number(lift_angle));
    linear_vel = 0.0;
    angular_vel = 0.0;
    btn_state.vel_up = false;
    btn_state.vel_down = false;
    btn_state.vel_left = false;
    btn_state.vel_right = false;

    // Datetime and frame update callback
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, [=]() {
        ui->QDT->setDateTime(QDateTime::currentDateTime());
        current_fps = frame_count;
        frame_count = 0;
    });
    updateTimer->start(1000);
    ui->QDT->setDateTime(QDateTime::currentDateTime());

    on_checkTimer = new QTimer(this);
    on_checkTimer->setSingleShot(true);
    connect(on_checkTimer, &QTimer::timeout, this, &MainWidget::handleTimeout);

    liftTimer = new QTimer(this);
    connect(liftTimer, &QTimer::timeout, this, &MainWidget::increaseValue);
    liftTimer->start(250);

    ui->PBAR_battery->setValue(0);

    // Rosnode slot
    ros_node = new RosNode(this);
    map_node = new MapNode(this);
    connect(ros_node, &RosNode::batteryPercentSig, this, &MainWidget::updateBatterySlot);
    connect(ros_node, &RosNode::imageReceivedSig, this, &MainWidget::updateCameraSlot);
    connect(ros_node, &RosNode::peopleReceivedSig, this, &MainWidget::updatePeopleSlot);
    connect(map_node, &MapNode::mapReceivedSig, this, &MainWidget::updateMapSlot);
    connect(map_node, &MapNode::pointReceivedSig, this, &MainWidget::updateHumanPoseSlot);
    connect(ros_node, &RosNode::joyLiftUpSig, this, [=](bool pressed) {
        btn_state.lift_up = pressed;
    });
    connect(ros_node, &RosNode::joyLiftDownSig, this, [=](bool pressed) {
        btn_state.lift_down = pressed;
    });
    QPixmap pix(":/new/prefix1/top_bar_icon.png");
    if (!pix.isNull()) {
        QSize iconSize(33, 33);
        ui->QL_top_icon->setPixmap(pix.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->QL_top_icon->setFixedSize(iconSize);
    }
    // ui->L_lift_state_1->setStyleSheet("background-color: #FFD966; border: 1px solid grey; border-radius: 5px;");
    ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
    ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));

    clahe = cv::createCLAHE();
    clahe->setClipLimit(2.0);
    clahe->setTilesGridSize(cv::Size(8,8));
    width = -1;
    height = -1;

    robot_raw = QPixmap(":/new/prefix1/robot.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ping_raw = QPixmap(":/new/prefix1/top_bar_icon.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    lbl_robot_icon = new QLabel(ui->QL_map);
    lbl_robot_icon->setPixmap(robot_raw);
    lbl_robot_icon->setFixedSize(30, 30);
    lbl_robot_icon->setAttribute(Qt::WA_TranslucentBackground);
    lbl_robot_icon->hide();

    lbl_ping_icon = new QLabel(ui->QL_map);
    lbl_ping_icon->setPixmap(ping_raw);
    lbl_ping_icon->setFixedSize(30, 30);
    lbl_ping_icon->setAttribute(Qt::WA_TranslucentBackground);
    lbl_ping_icon->hide();

    ros_thread_ = std::thread([this]() {
        rclcpp::spin(ros_node->getNode());
    });

    map_thread_ = std::thread([this]() {
        rclcpp::spin(map_node->getNode());
    });
}

MainWidget::~MainWidget()
{
    delete ui;
    if (ros_thread_.joinable()) ros_thread_.join();
    if (map_thread_.joinable()) map_thread_.join();
}

// Update UI slots
void MainWidget::updateBatterySlot(double percentage) {
    double pbar_battery_avg;
    on_checkTimer->start(3000);
    if (!battery_update) {
        filter.x = static_cast<float>(percentage);
        pbar_battery_avg = percentage;
        battery_update = 1;
        ui->L_onoff->setText("ON");
        ui->L_onoff->setStyleSheet(
            "QLabel {"
            "border: 1px solid grey;"
            "border-radius: 5px;"
            "text-align: center;"
            "background-color: #04EB84;"
            "}"
        );
    }
    else {
        // Prediction
        filter.P = filter.P + filter.Q;
        // Update
        filter.K = filter.P / (filter.P + filter.R);
        filter.x = filter.x + filter.K * (static_cast<float>(percentage) - filter.x);
        filter.P = (1.0f - filter.K) * filter.P;
        pbar_battery_avg = filter.x;
    }
    ui->PBAR_battery->setValue(static_cast<int>(pbar_battery_avg));
    ui->PBAR_battery->update();
}
void MainWidget::updateCameraSlot(QImage img) {
    if (img.isNull()) return;
    frame_count++;
    int total_width = img.width();
    int height = img.height();
    int single_width = total_width / 2;

    QImage webcam_img = img.copy(0, 0, single_width, height);
    QImage depth_img = img.copy(single_width, 0, single_width, height);

    cv::Mat depth_mat(height, single_width, CV_8UC3, (void*)depth_img.bits(), depth_img.bytesPerLine());
    cv::medianBlur(depth_mat, depth_mat, 3);
    cv::Mat lab;
    cv::cvtColor(depth_mat, lab, cv::COLOR_BGR2Lab);
    std::vector<cv::Mat> lab_planes;
    cv::split(lab, lab_planes);
    clahe->apply(lab_planes[0], lab_planes[0]);
    cv::merge(lab_planes, lab);
    cv::cvtColor(lab, depth_mat, cv::COLOR_Lab2BGR);
    if (width < 0) {
        width = depth_img.width();
        height = depth_img.height();
    }

    if (point_update) {
        int num_people = ros_node->people_points.people.size();
        for (int i = 0; i < num_people; i++) {
            custom_interfaces::msg::Person person = ros_node->people_points.people[i];
            int px = static_cast<int>(width * person.x);
            int py = static_cast<int>(height * person.y);
            QPainter painter_point(&depth_img);
            painter_point.setRenderHint(QPainter::Antialiasing);
            if (person.state > 1.5 && person.state < 2.5) {
                painter_point.setPen(QPen(Qt::red, 10));
                painter_point.setBrush(Qt::red);
            }

            else if (person.state > 0.5 && person.state < 1.5) {
                painter_point.setPen(QPen(Qt::blue, 10));
                painter_point.setBrush(Qt::blue);
            }
			else {
				continue;
			}
            painter_point.drawEllipse(QPoint(px, py), 3, 3);
            painter_point.end();
        }
    }

    ui->QL_depth_camera->setPixmap(QPixmap::fromImage(depth_img).scaled(
        ui->QL_depth_camera->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPainter painter(&webcam_img);
    painter.setPen(Qt::yellow);
    painter.setFont(QFont("Arial", 12, QFont::Bold));

    painter.drawText(15, 30, QString("FPS: %1").arg(current_fps));
    painter.end();


    ui->QL_omx_camera->setPixmap(QPixmap::fromImage(webcam_img).scaled(
        ui->QL_omx_camera->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWidget::updatePeopleSlot(custom_interfaces::msg::People p) {
    if (p.people.size() == 0) point_update = 0;
    else point_update = 1;
    x = p.people[0].x;
    y = p.people[0].y;
	state = p.people[0].state;
}
void MainWidget::updateMapSlot(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    int width = msg->info.width;
    int height = msg->info.height;
    double res = msg->info.resolution;
    double origin_x = msg->info.origin.position.x;
    double origin_y = msg->info.origin.position.y;

    double map_res = map_node->map_res;
    double map_origin_x = map_node->map_origin_x;
    double map_origin_y = map_node->map_origin_y;
    int map_height = map_node->map_height;

    QImage map_image(width, height, QImage::Format_RGB32);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = x + (height - 1 - y) * width;
            int val = msg->data[i];

            QRgb color;
            if (val == 0) color = qRgb(255, 255, 255);
            else if (val == 100) color = qRgb(0, 0, 0);
            else color = qRgb(150, 150, 150);

            map_image.setPixel(x, y, color);
        }
    }

    ui->QL_map->setPixmap(QPixmap::fromImage(map_image).scaled(
        ui->QL_map->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    double scale_factor = qMin((double)ui->QL_map->width() / width, (double)ui->QL_map->height() / height);
    int offset_x = (ui->QL_map->width() - qRound(width * scale_factor)) / 2;
    int offset_y = (ui->QL_map->height() - qRound(height * scale_factor)) / 2;

    auto robot_pos = map_node->getRobotPose();
    int robot_px = qRound((robot_pos.position.x - origin_x) / res);
    int robot_py = height - qRound((robot_pos.position.y - origin_y) / res);

    int ui_robot_x = qRound(robot_px * scale_factor) + offset_x;
    int ui_robot_y = qRound(robot_py * scale_factor) + offset_y;

    double qz = robot_pos.orientation.z;
    double qw = robot_pos.orientation.w;
    double ryaw = 2.0 * atan2(qz, qw);
    double degrees = ryaw * 180.0 / M_PI - 90.0;

    QTransform transform;
    transform.rotate(-degrees);
    QPixmap rotated_robot = robot_raw.transformed(transform, Qt::SmoothTransformation);

    lbl_robot_icon->setPixmap(rotated_robot);
    lbl_robot_icon->setFixedSize(rotated_robot.size());
    lbl_robot_icon->move(ui_robot_x - (rotated_robot.width() / 2),
                         ui_robot_y - (rotated_robot.height() / 2));
    lbl_robot_icon->show();
    lbl_robot_icon->raise();

    if (is_person_estimated) {
        int person_px = qRound((estimated_person_pos.x - map_origin_x) / map_res);
        int person_py = map_height - qRound((estimated_person_pos.y - map_origin_y) / map_res);

        int ui_person_x = qRound(person_px * scale_factor) + offset_x;
        int ui_person_y = qRound(person_py * scale_factor) + offset_y;

        lbl_ping_icon->move(ui_person_x - (lbl_ping_icon->width() / 2),
                            ui_person_y - (lbl_ping_icon->height() / 2));
        lbl_ping_icon->show();
        lbl_ping_icon->raise();
    } else {
        lbl_ping_icon->hide();
    }
}
void MainWidget::updateHumanPoseSlot(geometry_msgs::msg::Point p) {
    auto robot_pose = map_node->getRobotPose();
    double rx = robot_pose.position.x;
    double ry = robot_pose.position.y;
    double qz = robot_pose.orientation.z;
    double qw = robot_pose.orientation.w;
    double ryaw = 2.0 * atan2(qz, qw);

    double distance = p.x;
    double relative_yaw = p.y;

    estimated_person_pos.x = rx + distance * cos(ryaw - relative_yaw);
    estimated_person_pos.y = ry + distance * sin(ryaw - relative_yaw);

    is_person_estimated = true;
    qDebug() << "Ping! Person at: " << estimated_person_pos.x << ", " << estimated_person_pos.y;
}

// /cmd_lift controll slots
void MainWidget::on_PB_lift_stop_clicked()
{
    lift_angle = 2048;
    ros_node->RunLiftPublisher(lift_angle);
    ui->S_lift_state->setValue(lift_angle);
    ui->LB_lift_state->setText(QString::number(lift_angle));
}

// /cmd_vel control slots
void MainWidget::on_PB_arrow_up_pressed() { btn_state.vel_up = true; }
void MainWidget::on_PB_arrow_up_released() { btn_state.vel_up = false; }
void MainWidget::on_PB_arrow_left_pressed() { btn_state.vel_left = true; }
void MainWidget::on_PB_arrow_left_released() { btn_state.vel_left = false; }
void MainWidget::on_PB_arrow_right_pressed() { btn_state.vel_right = true; }
void MainWidget::on_PB_arrow_right_released() { btn_state.vel_right = false; }
void MainWidget::on_PB_arrow_down_pressed() { btn_state.vel_down = true; }
void MainWidget::on_PB_arrow_down_released() { btn_state.vel_down = false; }
void MainWidget::on_PB_lift_up_pressed() { btn_state.lift_up = true; }
void MainWidget::on_PB_lift_up_released() { btn_state.lift_up = false; }
void MainWidget::on_PB_lift_down_pressed() { btn_state.lift_down = true; }
void MainWidget::on_PB_lift_down_released() { btn_state.lift_down = false; }
void MainWidget::on_PB_arrow_stop_clicked()
{
    linear_vel = 0.0;
    angular_vel = 0.0;
    ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
    ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));
    ros_node->RunTeleopPublisher(linear_vel, angular_vel);
}

// Keyboard Interrupts
void MainWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        ui->PB_arrow_up->setDown(true);
        on_PB_arrow_up_pressed();
        break;
    case Qt::Key_A:
        ui->PB_arrow_left->setDown(true);
        on_PB_arrow_left_pressed();
        break;
    case Qt::Key_S:
        ui->PB_arrow_stop->setDown(true);
        this->on_PB_arrow_stop_clicked();
        break;
    case Qt::Key_D:
        ui->PB_arrow_right->setDown(true);
        on_PB_arrow_right_pressed();
        break;
    case Qt::Key_X:
        ui->PB_arrow_down->setDown(true);
        on_PB_arrow_down_pressed();
        break;
    case Qt::Key_Q:
        ui->PB_lift_up->setDown(true);
        on_PB_lift_up_pressed();
        break;
    case Qt::Key_E:
        ui->PB_lift_down->setDown(true);
        on_PB_lift_down_pressed();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
void MainWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        ui->PB_arrow_up->setDown(false);
        on_PB_arrow_up_released();
        break;
    case Qt::Key_A:
        ui->PB_arrow_left->setDown(false);
        on_PB_arrow_left_released();
        break;
    case Qt::Key_S:
        ui->PB_arrow_stop->setDown(false);
        break;
    case Qt::Key_D:
        ui->PB_arrow_right->setDown(false);
        on_PB_arrow_right_released();
        break;
    case Qt::Key_X:
        ui->PB_arrow_down->setDown(false);
        on_PB_arrow_down_released();
        break;
    case Qt::Key_Q:
        ui->PB_lift_up->setDown(false);
        on_PB_lift_up_released();
        break;
    case Qt::Key_E:
        ui->PB_lift_down->setDown(false);
        on_PB_lift_down_released();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void MainWidget::on_PB_return_clicked()
{
    return;
}
void MainWidget::on_PB_pause_clicked()
{
    if (slam_state == SlamState::MAPPING) {
        ui->PB_pause->setText("RESTART");
        slam_state = SlamState::PAUSED;
        map_node->pauseSlam();
    }
    else {
        ui->PB_pause->setText("STOP");
        slam_state = SlamState::MAPPING;
        map_node->pauseSlam();
    }
}
void MainWidget::handleTimeout() {
    battery_update = 0;
    ui->L_onoff->setText("OFF");
    ui->L_onoff->setStyleSheet(
        "QLabel {"
        "border: 1px solid grey;"
        "border-radius: 5px;"
        "text-align: center;"
        "background-color: rgb(242, 244, 241);"
        "}"
    );
}
void MainWidget::increaseValue() {
    // cmd_vel
    bool changed = false; // cmd_vel change check
    if (btn_state.vel_up && linear_vel < 0.22) {
        linear_vel += 0.01;
        changed = true;
    }
    if (btn_state.vel_down && linear_vel > -0.22) {
        linear_vel -= 0.01;
        changed = true;
    }
    if (btn_state.vel_left && angular_vel < 1.8) {
        angular_vel += 0.1;
        changed = true;
    }
    if (btn_state.vel_right && angular_vel > -1.8) {
        angular_vel -= 0.1;
        changed = true;
    }

    // cmd_lift
    if (btn_state.lift_up && lift_angle > 1149) {
        lift_angle -= 50;
        ros_node->RunLiftPublisher(lift_angle);
        // setStateColor(lift_angle);
        ui->S_lift_state->setValue(lift_angle);
        ui->LB_lift_state->setText(QString::number(lift_angle));
    }
    if (btn_state.lift_down && lift_angle < 2301) {
        lift_angle += 50;
        ros_node->RunLiftPublisher(lift_angle);
        // setStateColor(lift_angle);
        ui->S_lift_state->setValue(lift_angle);
        ui->LB_lift_state->setText(QString::number(lift_angle));
    }

    if (changed) {
        ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
        ui->label_3->setText("Angular: " + QString::number(angular_vel, 'f', 1));
        ros_node->RunTeleopPublisher(linear_vel, angular_vel);
    }
}

void MainWidget::on_PB_ping_clicked() {
	int num_people = ros_node->people_points.people.size();
	if (num_people == 0) return;
	for (int i = 0; i < num_people; i++) {
		if (ros_node->people_points.people[i].state > 1.5) {
			ros_node->RunPointPublisher(ros_node->people_points.people[i].x, ros_node->people_points.people[i].y);
			return;
		}
	}
}

void MainWidget::on_pushButton_clicked()
{
    close();
}

void MainWidget::on_PB_marker_clicked()
{
    ui->PB_marker->setEnabled(false);
    ros_node->RunDispenserPublisher();
    QTimer::singleShot(2000, this, [=]() {
        ui->PB_marker->setEnabled(true);
    });
}