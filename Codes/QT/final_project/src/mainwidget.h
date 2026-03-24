#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>
#include <QQueue>
#include <QResizeEvent>
#include <QPixmap>
#include <QLabel>
#include "rosnode.h"
#include "mapnode.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

// KF
struct KalmanFilter {
    float x;
    float P;
    float Q;
    float R;
    float K;
    KalmanFilter(float q=0.001f, float r = 0.01f, float init_x = 0.0f)
        : x(init_x), P(1.0f), Q(q), R(r), K(0.0f) {}
};

struct BtnState {
    bool vel_up = false;
    bool vel_down = false;
    bool vel_left = false;
    bool vel_right = false;
    bool lift_up = false;
    bool lift_down = false;
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    // void setStateColor(int lift_state);
    void drawMap();
    void handleTimeout();
    void increaseValue();
    enum class SlamState {
        MAPPING,
        PAUSED
    };

private slots:
    void on_PB_arrow_stop_clicked();
    void on_PB_lift_stop_clicked();
    void on_PB_marker_clicked();

    void updateBatterySlot(double percentage);
    void updateCameraSlot(QImage img);
    void updatePeopleSlot(custom_interfaces::msg::People p);
    void updateMapSlot(nav_msgs::msg::OccupancyGrid::SharedPtr msg);

    void on_PB_return_clicked();
    void on_PB_pause_clicked();
    void on_PB_ping_clicked();

    void on_PB_arrow_up_pressed();
    void on_PB_arrow_up_released();
    void on_PB_arrow_left_pressed();
    void on_PB_arrow_left_released();
    void on_PB_arrow_right_pressed();
    void on_PB_arrow_right_released();
    void on_PB_arrow_down_pressed();
    void on_PB_arrow_down_released();
    void on_PB_lift_up_pressed();
    void on_PB_lift_up_released();
    void on_PB_lift_down_pressed();
    void on_PB_lift_down_released();
    void updateHumanPoseSlot(geometry_msgs::msg::Point p);


    void on_pushButton_clicked();

private:
    Ui::MainWidget *ui;
    QTimer *updateTimer;
    RosNode *ros_node;
    MapNode* map_node;
    QTimer* on_checkTimer;
    QTimer *liftTimer;
    double battery_prev;
    int lift_angle = 2048;
    float linear_vel;
    float angular_vel;
    KalmanFilter filter{0.001f, 0.1f, 100.0f};
    cv::Ptr<cv::CLAHE> clahe;
    int battery_update = 0;
    int point_update = 0;
    int frame_count = 0;
    float x, y, state;
    int width, height;
    QElapsedTimer fps_timer;
    double current_fps = 0.0;
    SlamState slam_state = SlamState::MAPPING;
    BtnState btn_state;
    geometry_msgs::msg::Point estimated_person_pos;
    bool is_person_estimated = false;
    QLabel* lbl_robot_icon;
    QLabel* lbl_ping_icon;
    QPixmap robot_raw;
    QPixmap ping_raw;

    std::thread ros_thread_;
    std::thread map_thread_;


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};
#endif // MAINWIDGET_H
