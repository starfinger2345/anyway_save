#include "mapnode.h"
using std::placeholders::_1;

MapNode::MapNode(QWidget *parent)
    : QWidget{parent}
{
    node_map = rclcpp::Node::make_shared("map_node");
    sub_point = node_map->create_subscription<geometry_msgs::msg::Point>(
        "/depth_response", 10, std::bind(&MapNode::PointSubCallbackFunc, this, _1));
    sub_map = node_map->create_subscription<nav_msgs::msg::OccupancyGrid>(
        "/map", rclcpp::QoS(rclcpp::KeepLast(1)).transient_local(),
        std::bind(&MapNode::MapSubCallbackFunc, this, std::placeholders::_1));
    tf_buffer = std::make_shared<tf2_ros::Buffer>(node_map->get_clock());
    tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);
    client_pause = node_map->create_client<std_srvs::srv::Empty>("/slam_toolbox/pause_new_measurements");
}
MapNode::~MapNode() {
    rclcpp::shutdown();
}

void MapNode::PointSubCallbackFunc (geometry_msgs::msg::Point::SharedPtr msg) {
    human_point.x = msg->x;
    human_point.y = msg->y;
    emit pointReceivedSig(human_point);
}
void MapNode::MapSubCallbackFunc(nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    map_width = msg->info.width;
    map_height = msg->info.height;
    map_res = msg->info.resolution;
    map_origin_x = msg->info.origin.position.x;
    map_origin_y = msg->info.origin.position.y;
    emit mapReceivedSig(msg);
}

geometry_msgs::msg::Pose MapNode::getRobotPose() {
    geometry_msgs::msg::Pose cur_pos;
    try {
        auto transform = tf_buffer->lookupTransform("map", "base_footprint", tf2::TimePointZero);
        cur_pos.position.x = transform.transform.translation.x;
        cur_pos.position.y = transform.transform.translation.y;
        cur_pos.orientation = transform.transform.rotation;
    } catch (tf2::TransformException &e) {
        RCLCPP_ERROR(node_map->get_logger(), "Could not transform map to base_footprint: %s", e.what());
    }
    return cur_pos;
}
void MapNode::pauseSlam() {
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    client_pause->async_send_request(request);
}
