#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QQueue>
#include <QResizeEvent>
#include "rosnode.h"

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

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void setStateColor(int lift_state);

private slots:
    void on_PB_lift_up_clicked();
    void on_PB_lift_stop_clicked();
    void on_PB_lift_down_clicked();

    void updateBatterySlot(double percentage);
    void updateCameraSlot(QImage img);

    void on_PB_arrow_up_clicked();

    void on_PB_arrow_left_clicked();

    void on_PB_arrow_stop_clicked();

    void on_PB_arrow_right_clicked();

    void on_PB_arrow_down_clicked();

private:
    Ui::MainWidget *ui;
    QTimer *updateTimer;
    RosNode *ros_node;
    double battery_prev;
    int lift_state = 1;
    float linear_vel;
    float angular_vel;
    KalmanFilter filter{0.001f, 0.1f, 100.0f};
    cv::Ptr<cv::CLAHE> clahe;
    int battery_update = 0;
    int frame_count = 0;
    QElapsedTimer fps_timer;
    double current_fps = 0.0;
    const QList<int> lift_step = {2350, 2048, 1888, 1728, 1568, 1408, 1248};

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};
#endif // MAINWIDGET_H
