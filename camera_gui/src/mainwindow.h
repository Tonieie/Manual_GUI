#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

//ros
#include "ros/ros.h"
#include "ros/master.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <std_msgs/Bool.h>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public Q_SLOTS:
    void on_Exit_clicked();
    void spinRos();

protected:
   Q_SLOT void setImageMsg1(const sensor_msgs::ImageConstPtr&);
   Q_SLOT void setImageMsg2(const sensor_msgs::ImageConstPtr&);
   Q_SLOT void setImageMsg3(const sensor_msgs::ImageConstPtr&);
   Q_SLOT void setImageMsg4(const sensor_msgs::ImageConstPtr&);
   Q_SIGNAL void newImageMsg1(const sensor_msgs::ImageConstPtr&);
   Q_SIGNAL void newImageMsg2(const sensor_msgs::ImageConstPtr&);
   Q_SIGNAL void newImageMsg3(const sensor_msgs::ImageConstPtr&);
   Q_SIGNAL void newImageMsg4(const sensor_msgs::ImageConstPtr&);

/*/private slots: Note if you want to create function from mainwindow.ui delete
 * private slots and put them with public QSLOTS
 * */

    
private slots:
    static QImage toImageShare(const sensor_msgs::ImageConstPtr &msg) {
       using namespace sensor_msgs::image_encodings;
       QImage::Format format = {};
       if (msg->encoding == RGB8 || msg->encoding == BGR8)
          format = QImage::Format_RGB888;
       else if (msg->encoding == RGBA8 || msg->encoding == BGRA8)
          format = QImage::Format_RGBA8888_Premultiplied;
       else if (msg->encoding == MONO8)
          format = QImage::Format_Grayscale8;
       else
          return {};
       QImage img(msg->data.data(), msg->width, msg->height, format);
       if (msg->encoding == BGR8 || msg->encoding == BGRA8)
          img = std::move(img).rgbSwapped();
       return img;
    }

    void on_start_btn_clicked();

private:
    Ui::MainWindow *ui;
   ros::Subscriber sub_cam1,sub_cam2,sub_cam3,sub_cam4;
   ros::Publisher pub_;
    QTimer* timer;
    std_msgs::Bool control_status;
};
Q_DECLARE_METATYPE(sensor_msgs::ImageConstPtr)

#endif // MAINWINDOW_H
