#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDateTime>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // Datetime and frame update callback
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, [=]() {
        ui->QDT->setDateTime(QDateTime::currentDateTime());
        current_fps = frame_count;
        frame_count = 0;
    });
    updateTimer->start(1000);
    ui->QDT->setDateTime(QDateTime::currentDateTime());

    ui->PBAR_battery->setValue(0);

    // Rosnode slot
    ros_node = new RosNode(this);
    connect(ros_node, &RosNode::batteryPercentSig, this, &MainWidget::updateBatterySlot);
    connect(ros_node, &RosNode::imageReceivedSig, this, &MainWidget::updateCameraSlot);

    QPixmap pix(":/new/prefix1/top_bar_icon.png");
    if (!pix.isNull()) {
        QSize iconSize(33, 33);
        ui->QL_top_icon->setPixmap(pix.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->QL_top_icon->setFixedSize(iconSize);
    }

    // lift / vel initialize
    lift_state = 1;
    ui->L_lift_state_1->setStyleSheet("background-color: #FFD966; border: 1px solid grey; border-radius: 5px;");
    ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
    ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));

    clahe = cv::createCLAHE();
    clahe->setClipLimit(2.0);
    clahe->setTilesGridSize(cv::Size(8,8));
}


MainWidget::~MainWidget()
{
    delete ui;
}

// Update UI slots
void MainWidget::updateBatterySlot(double percentage) {
    double pbar_battery_avg;
    if (!battery_update) {
        filter.x = static_cast<float>(percentage);
        pbar_battery_avg = percentage;
        battery_update = 1;
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
    // raw_history.enqueue(percentage);
    // filtered_history.enqueue(pbar_battery_avg);
    // if (raw_history.size() > 100) {
    //     raw_history.dequeue();
    //     filtered_history.dequeue();
    // }
    // static int update_counter = 0;
    // update_counter++;
    // if (update_counter >= 10) {
    //     drawGraph();
    //     update_counter = 0; // 카운터 초기화
    // }
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

// /cmd_lift controll slots
void MainWidget::on_PB_lift_up_clicked()
{
    if (lift_state < lift_step.size() - 1) {
        lift_state++;
        ros_node->RunLiftPublisher(lift_step[lift_state]);
        this->setStateColor(lift_state);
    }
}

void MainWidget::on_PB_lift_stop_clicked()
{
    lift_state = 1;
    ros_node->RunLiftPublisher(lift_step[lift_state]);
    this->setStateColor(lift_state);
}


void MainWidget::on_PB_lift_down_clicked()
{
    if (lift_state > 0) {
        lift_state--;
        ros_node->RunLiftPublisher(lift_step[lift_state]);
        this->setStateColor(lift_state);
    }
}

// Lift UI update function
void MainWidget::setStateColor(int lift_state) {
    ui->L_lift_state_0->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_1->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_2->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_3->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_4->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_5->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    ui->L_lift_state_6->setStyleSheet("background-color: #F2F4F1; border: 1px solid grey; border-radius: 5px;");
    switch (lift_state) {
    case 0:
        ui->L_lift_state_0->setStyleSheet("background-color: #FF4340; border: 1px solid grey; border-radius: 5px;");
        break;
    case 1:
        ui->L_lift_state_1->setStyleSheet("background-color: #FFD966; border: 1px solid grey; border-radius: 5px;");
        break;
    case 2:
        ui->L_lift_state_2->setStyleSheet("background-color: #04EB84; border: 1px solid grey; border-radius: 5px;");
        break;
    case 3:
        ui->L_lift_state_3->setStyleSheet("background-color: #04EB84; border: 1px solid grey; border-radius: 5px;");
        break;
    case 4:
        ui->L_lift_state_4->setStyleSheet("background-color: #04EB84; border: 1px solid grey; border-radius: 5px;");
        break;
    case 5:
        ui->L_lift_state_5->setStyleSheet("background-color: #04EB84; border: 1px solid grey; border-radius: 5px;");
        break;
    case 6:
        ui->L_lift_state_6->setStyleSheet("background-color: #04EB84; border: 1px solid grey; border-radius: 5px;");
        break;
    }
}

// /cmd_vel control slots
void MainWidget::on_PB_arrow_up_clicked()
{
    if (linear_vel < 0.22) {
        linear_vel += 0.01;
        ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
        ros_node->RunTeleopPublisher(linear_vel, angular_vel);
    }
}

void MainWidget::on_PB_arrow_left_clicked()
{
    if (angular_vel > -1.8) {
        angular_vel -= 0.1;
        ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));
        ros_node->RunTeleopPublisher(linear_vel, angular_vel);
    }
}


void MainWidget::on_PB_arrow_stop_clicked()
{
    linear_vel = 0.0;
    angular_vel = 0.0;
    ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
    ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));
    ros_node->RunTeleopPublisher(linear_vel, angular_vel);
}


void MainWidget::on_PB_arrow_right_clicked()
{
    if (angular_vel < 1.8) {
        angular_vel += 0.1;
        ui->label_3->setText("Linear: " + QString::number(angular_vel, 'f', 1));
        ros_node->RunTeleopPublisher(linear_vel, angular_vel);
    }
}


void MainWidget::on_PB_arrow_down_clicked()
{
    if (linear_vel > -0.22) {
        linear_vel -= 0.01;
        ui->label_2->setText("Linear: " + QString::number(linear_vel, 'f', 2));
        ros_node->RunTeleopPublisher(linear_vel, angular_vel);
    }
}

// Keyboard Interrupts
void MainWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        ui->PB_arrow_up->setDown(true);
        this->on_PB_arrow_up_clicked();
        break;
    case Qt::Key_A:
        ui->PB_arrow_left->setDown(true);
        this->on_PB_arrow_left_clicked();
        break;
    case Qt::Key_S:
        ui->PB_arrow_stop->setDown(true);
        this->on_PB_arrow_stop_clicked();
        break;
    case Qt::Key_D:
        ui->PB_arrow_right->setDown(true);
        this->on_PB_arrow_right_clicked();
        break;
    case Qt::Key_X:
        ui->PB_arrow_down->setDown(true);
        this->on_PB_arrow_down_clicked();
        break;
    case Qt::Key_Q:
        ui->PB_lift_up->setDown(true);
        this->on_PB_lift_up_clicked();
        break;
    case Qt::Key_E:
        ui->PB_lift_down->setDown(true);
        this->on_PB_lift_down_clicked();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
void MainWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        ui->PB_arrow_up->setDown(false);
        // Slot함수 호출 필요
        break;
    case Qt::Key_A:
        ui->PB_arrow_left->setDown(false);
        break;
    case Qt::Key_S:
        ui->PB_arrow_stop->setDown(false);
        break;
    case Qt::Key_D:
        ui->PB_arrow_right->setDown(false);
        break;
    case Qt::Key_X:
        ui->PB_arrow_down->setDown(false);
        break;
    case Qt::Key_Q:
        ui->PB_lift_up->setDown(false);
        break;
    case Qt::Key_E:
        ui->PB_lift_down->setDown(false);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
