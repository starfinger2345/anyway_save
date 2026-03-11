#include "rosnode.h"
using std::placeholders::_1;

RosNode::RosNode(QWidget *parent)
    : QWidget{parent}
{
    msg_twist = geometry_msgs::msg::Twist();
    rclcpp::init(0, nullptr);
    node_teleop = rclcpp::Node::make_shared("teleop_qt");
    pub_teleop = node_teleop->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    pub_lift = node_teleop->create_publisher<std_msgs::msg::Int32>("/cmd_lift", 10);
    sub_teleop = node_teleop->create_subscription<sensor_msgs::msg::BatteryState>(
        "/battery_state", 10, std::bind(&RosNode::BatterySubCallbackFunc, this, _1));
    sub_image = node_teleop->create_subscription<sensor_msgs::msg::CompressedImage>(
        "/image_out/compressed", 10, std::bind(&RosNode::ImageSubCallbackFunc, this, _1));

    pQTimer = new QTimer(this);
    connect(pQTimer, &QTimer::timeout, this, &RosNode::OnTimerCallbackFunc);
    pQTimer->start(50);
}
RosNode::~RosNode() {
    rclcpp::shutdown();
    delete pQTimer;
}

void RosNode::ImageSubCallbackFunc(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
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
void RosNode::BatterySubCallbackFunc(sensor_msgs::msg::BatteryState::SharedPtr pmsg) {
    static int battery_update_count = 0;
    battery_update_count++;
    if (battery_update_count >= 40) {
        emit batteryPercentSig(pmsg->percentage);
        battery_update_count = 0;
    }
}
