#ifndef POSE_CALLBACK_H
#define POSE_CALLBACK_H

#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

class PoseCallback
{
public:
    PoseCallback(rclcpp::Node::SharedPtr node);

    void updatePose();

    double getX() const;
    double getY() const;
    double getYaw() const;

private:
    rclcpp::Node::SharedPtr node_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;

    double x_, y_, yaw_;

    /*PoseCallback();

    void poseCallback(const nav_msgs::msg::Odometry::SharedPtr msg);

    double getX() const;
    double getY() const;
    double getYaw() const;

private:
    double robot_x_;
    double robot_y_;
    double robot_yaw_;*/
};

#endif
