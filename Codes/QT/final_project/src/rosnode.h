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
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using namespace std::chrono_literals;
class RosNode : public QWidget
{
    Q_OBJECT
private:
    geometry_msgs::msg::Twist msg_twist;
    rclcpp::Node::SharedPtr node_teleop;
    QTimer* pQTimer;
public:
    explicit RosNode(QWidget *parent = nullptr);
    ~RosNode();
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_teleop;
    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr sub_teleop;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_image;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_lift;
    void RunTeleopPublisher(double, double);
    void BatterySubCallbackFunc(sensor_msgs::msg::BatteryState::SharedPtr);
    void ImageSubCallbackFunc(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void RunLiftPublisher(int anngle);

signals:
    void batteryPercentSig(double percent);
    void imageReceivedSig(QImage img);
private slots:
    void OnTimerCallbackFunc();
};

#endif // ROSNODE_H
