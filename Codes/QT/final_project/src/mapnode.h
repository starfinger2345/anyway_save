#ifndef MAPNODE_H
#define MAPNODE_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QObject>

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/msg/pose.hpp>
#include <std_srvs/srv/empty.hpp>

using namespace std::chrono_literals;
class MapNode : public QWidget
{
    Q_OBJECT
private:
    rclcpp::Node::SharedPtr node_map;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_pause;

public:
    double map_res = 0.05;
    double map_origin_x = 0.0;
    double map_origin_y = 0.0;
    int map_width = 0;
    int map_height = 0;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr sub_map;
    void MapSubCallbackFunc(nav_msgs::msg::OccupancyGrid::SharedPtr msg);
    geometry_msgs::msg::Point human_point;
    explicit MapNode(QWidget *parent = nullptr);
    ~MapNode();
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_point;
    void PointSubCallbackFunc(geometry_msgs::msg::Point::SharedPtr msg);
    geometry_msgs::msg::Pose getRobotPose();
    void pauseSlam();
    rclcpp::Node::SharedPtr getNode() { return node_map; };

signals:
    void batteryPercentSig(double percent);
    void pointReceivedSig(geometry_msgs::msg::Point point);
    void mapReceivedSig(nav_msgs::msg::OccupancyGrid::SharedPtr msg);

private slots:
};
#endif // MAPNODE_H
