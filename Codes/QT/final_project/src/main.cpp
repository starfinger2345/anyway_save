#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    rclcpp::init(0, nullptr);
    QApplication a(argc, argv);
    MainWidget w;
    w.showFullScreen();
    return a.exec();
}
