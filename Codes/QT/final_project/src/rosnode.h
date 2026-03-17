#ifndef ROSNODE_H
#define ROSNODE_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QObject>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/int32.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/msg/pose.hpp>
#include <std_srvs/srv/empty.hpp>
#include <sensor_msgs/msg/joy.hpp>

using namespace std::chrono_literals;
class RosNode : public QWidget
{
    Q_OBJECT
private:
    geometry_msgs::msg::Twist msg_twist;
    rclcpp::Node::SharedPtr node_teleop;
    QTimer* pQTimer;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_pause;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy;
    int current_lift_idx = 1;
    bool axis_6_reset = true;
    const std::vector<int> lift_step_values = {2350, 2048, 1888, 1728, 1568, 1408, 1248};
public:
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_map;
    void MapSubCallbackFunc(nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    geometry_msgs::msg::Point human_point;
    explicit RosNode(QWidget *parent = nullptr);

    void JoySubCallbackFunc(const sensor_msgs::msg::Joy::SharedPtr msg);
    ~RosNode();
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_teleop;
    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr sub_battery;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_image;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_point;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pub_point;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_lift;
    void RunTeleopPublisher(double, double);
    void BatterySubCallbackFunc(sensor_msgs::msg::BatteryState::SharedPtr);
    void ImageSubCallbackFunc(sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void PointSubCallbackFunc(geometry_msgs::msg::Point::SharedPtr msg);
    void RunLiftPublisher(int angle);
    void RunPointPublisher(float, float);
    geometry_msgs::msg::Pose getRobotPose();
    void pauseSlam();

signals:
    void batteryPercentSig(double percent);
    void imageReceivedSig(QImage img);
    void pointReceivedSig(geometry_msgs::msg::Point point);
    void mapReceivedSig(nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    void joyLiftUpSig(bool pressed);
    void joyLiftDownSig(bool pressed);

private slots:
    void OnTimerCallbackFunc();
};

#endif // ROSNODE_H
