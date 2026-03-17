#include "pose_callback.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/utils.h>

PoseCallback::PoseCallback(rclcpp::Node::SharedPtr node)
    : node_(node),
    tf_buffer_(node_->get_clock()),
    tf_listener_(tf_buffer_)
{
}

void PoseCallback::updatePose()
{
    try
    {
        auto transform = tf_buffer_.lookupTransform(
            "map",          // 목표 프레임
            "base_link",    // 로봇 프레임
            tf2::TimePointZero);

        x_ = transform.transform.translation.x;
        y_ = transform.transform.translation.y;

        yaw_ = tf2::getYaw(transform.transform.rotation);
    }
    catch (tf2::TransformException & ex)
    {
        RCLCPP_WARN(node_->get_logger(), "TF error: %s", ex.what());
    }
}
double PoseCallback::getX() const
{
    return x_;
}

double PoseCallback::getY() const
{
    return y_;
}

double PoseCallback::getYaw() const
{
    return yaw_;
}

/*
PoseCallback::PoseCallback()
    : robot_x_(0.0),
    robot_y_(0.0),
    robot_yaw_(0.0)
{
}

void PoseCallback::poseCallback(
    const nav_msgs::msg::Odometry::SharedPtr msg)
{
    robot_x_ = msg->pose.pose.position.x;
    robot_y_ = msg->pose.pose.position.y;

    tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);

    tf2::Matrix3x3 m(q);
    double roll, pitch;
    m.getRPY(roll, pitch, robot_yaw_);
}

double PoseCallback::getX() const { return robot_x_; }
double PoseCallback::getY() const { return robot_y_; }
double PoseCallback::getYaw() const { return robot_yaw_; }
*/
