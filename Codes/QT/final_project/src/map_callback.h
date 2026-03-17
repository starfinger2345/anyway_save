#ifndef MAP_CALLBACK_H
#define MAP_CALLBACK_H

#include <nav_msgs/msg/occupancy_grid.hpp>
#include <QImage>

class MapCallback
{
public:
    MapCallback();

    void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);

    QImage getMapImage() const;

    int getWidth() const;
    int getHeight() const;
    double getResolution() const;
    double getOriginX() const;
    double getOriginY() const;

private:
    QImage map_image_;

    int map_width_;
    int map_height_;
    double map_resolution_;
    double map_origin_x_;
    double map_origin_y_;
};

#endif
