#include "rosnode.h"
using std::placeholders::_1;

RosNode::RosNode(QWidget *parent)
    : QWidget{parent}
{
    msg_twist = geometry_msgs::msg::Twist();
    rclcpp::init(0, nullptr);
    node_teleop = rclcpp::Node::make_shared("qt_node");
    pub_teleop = node_teleop->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    pub_lift = node_teleop->create_publisher<std_msgs::msg::Int32>("/cmd_lift", 10);
    pub_point = node_teleop->create_publisher<geometry_msgs::msg::Point>("/depth_request", 10);
    sub_battery = node_teleop->create_subscription<sensor_msgs::msg::BatteryState>(
        "/battery_state", 10, std::bind(&RosNode::BatterySubCallbackFunc, this, _1));
    sub_image = node_teleop->create_subscription<sensor_msgs::msg::CompressedImage>(
        "/image_out/compressed", 10, std::bind(&RosNode::ImageSubCallbackFunc, this, _1));
    sub_point = node_teleop->create_subscription<geometry_msgs::msg::Point>(
        "/point_out", 10, std::bind(&RosNode::PointSubCallbackFunc, this, _1));
    sub_map = node_teleop->create_subscription<nav_msgs::msg::OccupancyGrid>(
        "/map", rclcpp::QoS(rclcpp::KeepLast(1)).transient_local(),
        std::bind(&RosNode::MapSubCallbackFunc, this, std::placeholders::_1));
    sub_joy = node_teleop->create_subscription<sensor_msgs::msg::Joy>(
        "/joy", 10, std::bind(&RosNode::JoySubCallbackFunc, this, std::placeholders::_1));

    pQTimer = new QTimer(this);
    connect(pQTimer, &QTimer::timeout, this, &RosNode::OnTimerCallbackFunc);
    pQTimer->start(50);
    tf_buffer = std::make_shared<tf2_ros::Buffer>(node_teleop->get_clock());
    tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);
    client_pause = node_teleop->create_client<std_srvs::srv::Empty>("/slam_toolbox/pause_new_measurements");
}
RosNode::~RosNode() {
    rclcpp::shutdown();
    delete pQTimer;
}

void RosNode::ImageSubCallbackFunc(sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    try {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        if (cv_ptr->image.empty()) return;
        QImage qimg(cv_ptr->image.data,
                    cv_ptr->image.cols,
                    cv_ptr->image.rows,
                    cv_ptr->image.step,
                    QImage::Format_BGR888);
        emit imageReceivedSig(qimg.copy());
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(node_teleop->get_logger(), "Could not convert from '%s' to 'bgr8'.", msg->format.c_str());
    }
}
void RosNode::PointSubCallbackFunc (geometry_msgs::msg::Point::SharedPtr msg) {
    human_point.x = msg->x;
    human_point.y = msg->y;
    emit pointReceivedSig(human_point);
}
void RosNode::BatterySubCallbackFunc(sensor_msgs::msg::BatteryState::SharedPtr pmsg) {
    static int battery_update_count = 0;
    battery_update_count++;
    if (battery_update_count >= 40) {
        emit batteryPercentSig(pmsg->percentage);
        battery_update_count = 0;
    }
}
void RosNode::MapSubCallbackFunc(nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    emit mapReceivedSig(msg);
}

void RosNode::OnTimerCallbackFunc()
{
    rclcpp::spin_some(node_teleop);
}
void RosNode::RunTeleopPublisher(double linearX, double angularZ)
{
    msg_twist.linear.x = linearX;
    msg_twist.angular.z = angularZ;
    RCLCPP_INFO(node_teleop->get_logger(), "Sending velocity linear: %.2f angular: %.1f", linearX, angularZ);
    pub_teleop->publish(msg_twist);
}
void RosNode::RunLiftPublisher(int angle)
{
    std_msgs::msg::Int32 msg;
    msg.data = angle;
    RCLCPP_INFO(node_teleop->get_logger(), "Sending lift angle: %d", msg.data);
    pub_lift->publish(msg);
}
void RosNode::RunPointPublisher(float x, float y) {
    RCLCPP_INFO(node_teleop->get_logger(), "Sending depth request with point: (%.2f, %.2f)", x, y);
    human_point.x = x;
    human_point.y = y;
    pub_point->publish(human_point);
}

void RosNode::JoySubCallbackFunc(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    double lin_x = (std::abs(msg->axes[1]) > 0.25) ? msg->axes[1] * 0.22 : 0.0;
    double ang_z = (std::abs(msg->axes[0]) > 0.25) ? msg->axes[0] * 0.6 : 0.0;

    static double last_lin_x = 0.0;
    static double last_ang_z = 0.0;

    if (lin_x != last_lin_x || ang_z != last_ang_z) {
        RunTeleopPublisher(lin_x, ang_z);
        last_lin_x = lin_x;
        last_ang_z = ang_z;
    }

    float lift_input = msg->axes[6];
    static float last_lift_input = 0.0f;

    if (lift_input != last_lift_input) {
        if (lift_input > 0.5) {
            emit joyLiftUpSig(true);
            emit joyLiftDownSig(false);
        }
        else if (lift_input < -0.5) {
            emit joyLiftUpSig(false);
            emit joyLiftDownSig(true);
        }
        else {
            emit joyLiftUpSig(false);
            emit joyLiftDownSig(false);
        }

        last_lift_input = lift_input;
    }
}

geometry_msgs::msg::Pose RosNode::getRobotPose() {
    geometry_msgs::msg::Pose cur_pos;
    try {
        auto transform = tf_buffer->lookupTransform("map", "base_footprint", tf2::TimePointZero);
        cur_pos.position.x = transform.transform.translation.x;
        cur_pos.position.y = transform.transform.translation.y;
        cur_pos.orientation = transform.transform.rotation;
    } catch (tf2::TransformException &e) {
        RCLCPP_ERROR(node_teleop->get_logger(), "Could not transform map to base_footprint: %s", e.what());
    }
    return cur_pos;
}
void RosNode::pauseSlam() {
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    client_pause->async_send_request(request);
}
