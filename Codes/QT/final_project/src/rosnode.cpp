#include "rosnode.h"
using std::placeholders::_1;

RosNode::RosNode(QWidget *parent)
    : QWidget{parent}
{
    msg_twist = geometry_msgs::msg::Twist();

    node_teleop = rclcpp::Node::make_shared("qt_node");
    pub_teleop = node_teleop->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    pub_lift = node_teleop->create_publisher<std_msgs::msg::Int32>("/cmd_lift", 10);
    pub_point = node_teleop->create_publisher<geometry_msgs::msg::Point>("/depth_request", 10);
    sub_battery = node_teleop->create_subscription<sensor_msgs::msg::BatteryState>(
        "/battery_state", 10, std::bind(&RosNode::BatterySubCallbackFunc, this, _1));
    sub_image = node_teleop->create_subscription<sensor_msgs::msg::CompressedImage>(
        "/image_out/compressed", 10, std::bind(&RosNode::ImageSubCallbackFunc, this, _1));
    sub_people = node_teleop->create_subscription<custom_interfaces::msg::People>(
        "/point_out", 10, std::bind(&RosNode::PeopleSubCallbackFunc, this, _1));
    sub_joy = node_teleop->create_subscription<sensor_msgs::msg::Joy>(
        "/joy", 10, std::bind(&RosNode::JoySubCallbackFunc, this, std::placeholders::_1));
    pub_dispenser = node_teleop->create_publisher<std_msgs::msg::Empty>("/dispenser_trigger", 10);
}
RosNode::~RosNode() {
    rclcpp::shutdown();
}
void RosNode::RunDispenserPublisher()
{
    auto msg = std_msgs::msg::Empty();
    RCLCPP_INFO(node_teleop->get_logger(), "Sending dispenser trigger signal...");
    pub_dispenser->publish(msg);
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
void RosNode::PeopleSubCallbackFunc (custom_interfaces::msg::People::SharedPtr msg) {
    int num_people = msg->people.size();
	people_points.people.clear();
    if (num_people == 0) return;
    else {
        for (int i = 0; i < num_people; i++) {
            people_points.people.insert(people_points.people.end(), msg->people[i]);
        }
        emit peopleReceivedSig(people_points);
    }

}
void RosNode::BatterySubCallbackFunc(sensor_msgs::msg::BatteryState::SharedPtr pmsg) {
    static int battery_update_count = 0;
    battery_update_count++;
    if (battery_update_count >= 40) {
        emit batteryPercentSig(pmsg->percentage);
        battery_update_count = 0;
    }
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
    geometry_msgs::msg::Point point;
	point.x = x;
	point.y = y;
    pub_point->publish(point);
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
