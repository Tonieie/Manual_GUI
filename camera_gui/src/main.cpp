#include <QtGui>
#include <QApplication>
#include "ros/ros.h"
#include "mainwindow.h"


int main(int argc, char **argv) {
    QApplication a(argc, argv);
    ros::init(argc, argv, "camera_gui_node");
//  cv::namedWindow("view",CV_WINDOW_AUTOSIZE);
  // cv::startWindowThread();
//  cv::waitKey(1);

    MainWindow w;
//    w.setWindowState(Qt::WindowFullScreen);
    w.show();

    qDebug() << "main";

    return a.exec();

}

