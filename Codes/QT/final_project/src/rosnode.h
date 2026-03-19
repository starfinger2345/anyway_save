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
#include <geometry_msgs/msg/point.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <sensor_msgs/msg/joy.hpp>

using namespace std::chrono_literals;
class RosNode : public QWidget
{
    Q_OBJECT
private:
    geometry_msgs::msg::Twist msg_twist;
    rclcpp::Node::SharedPtr node_teleop;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy;
    bool axis_6_reset = true;
public:
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
    rclcpp::Node::SharedPtr getNode() { return node_teleop; };

signals:
    void pointReceivedSig(geometry_msgs::msg::Point point);
    void batteryPercentSig(double percent);
    void imageReceivedSig(QImage img);
    void joyLiftUpSig(bool);
    void joyLiftDownSig(bool);

private slots:
};

#endif // ROSNODE_H
