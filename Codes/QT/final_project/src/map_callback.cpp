#include "map_callback.h"
#include <QColor>

MapCallback::MapCallback()
    : map_width_(0),
    map_height_(0),
    map_resolution_(0.0),
    map_origin_x_(0.0),
    map_origin_y_(0.0)
{
}

void MapCallback::mapCallback(
    const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
    map_width_ = msg->info.width;
    map_height_ = msg->info.height;
    map_resolution_ = msg->info.resolution;
    map_origin_x_ = msg->info.origin.position.x;
    map_origin_y_ = msg->info.origin.position.y;

    map_image_ = QImage(map_width_, map_height_, QImage::Format_RGB888);

    for (int y = 0; y < map_height_; ++y)
    {
        for (int x = 0; x < map_width_; ++x)
        {
            int i = x + (map_height_ - y - 1) * map_width_;
            int8_t value = msg->data[i];

            QColor color;

            if (value == -1)
                color = QColor(128,128,128);
            else if (value == 0)
                color = QColor(255,255,255);
            else
                color = QColor(0,0,0);

            map_image_.setPixelColor(x, y, color);
        }
    }
}

QImage MapCallback::getMapImage() const { return map_image_; }
int MapCallback::getWidth() const { return map_width_; }
int MapCallback::getHeight() const { return map_height_; }
double MapCallback::getResolution() const { return map_resolution_; }
double MapCallback::getOriginX() const { return map_origin_x_; }
double MapCallback::getOriginY() const { return map_origin_y_; }
