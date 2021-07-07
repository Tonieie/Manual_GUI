#include "mainwindow.h"
#include <ui_mainwindow.h>
//QT
#include "QMessageBox"
#include "QDebug"
#include "QProcess"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui (new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Manual Control GUI");

    qRegisterMetaType<sensor_msgs::ImageConstPtr>();

    connect(this, &MainWindow::newImageMsg1, this, &MainWindow::setImageMsg1);
    connect(this, &MainWindow::newImageMsg2, this, &MainWindow::setImageMsg2);
    connect(this, &MainWindow::newImageMsg3, this, &MainWindow::setImageMsg3);
    connect(this, &MainWindow::newImageMsg4, this, &MainWindow::setImageMsg4);

    ros::NodeHandle n;
    sub_cam1 = n.subscribe("/Channel1/cctv_cam1/image_raw", 1, &MainWindow::newImageMsg1, this);
    sub_cam2 = n.subscribe("/Channel2/cctv_cam2/image_raw", 1, &MainWindow::newImageMsg2, this);
    sub_cam3 = n.subscribe("/Channel3/cctv_cam3/image_raw", 1, &MainWindow::newImageMsg3, this);
    sub_cam4 = n.subscribe("/Channel4/cctv_cam4/image_raw", 1, &MainWindow::newImageMsg4, this);
    pub_ = n.advertise<std_msgs::Bool>("controlStatus",1);
    control_status.data = false;
    pub_.publish(control_status);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(spinRos()));
    timer->start(25);

    qDebug() << "Constructor OK";

}
MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "Destructor OK";
}

void MainWindow::spinRos()
{
//    qDebug() << "rosSpin";
    ros::spinOnce();
}

void MainWindow::setImageMsg1(const sensor_msgs::ImageConstPtr &msg) {
    qDebug() << "setImg1";
   auto img = toImageShare(msg);
   auto pix = QPixmap::fromImage(std::move(img));
   ui->label->setPixmap(pix);
}

void MainWindow::setImageMsg2(const sensor_msgs::ImageConstPtr &msg) {
    qDebug() << "setImg2";
   auto img = toImageShare(msg);
   auto pix = QPixmap::fromImage(std::move(img));
   ui->label_2->setPixmap(pix);
}

void MainWindow::setImageMsg3(const sensor_msgs::ImageConstPtr &msg) {
    qDebug() << "setImg3";
   auto img = toImageShare(msg);
   auto pix = QPixmap::fromImage(std::move(img));
   ui->label_3->setPixmap(pix);
}

void MainWindow::setImageMsg4(const sensor_msgs::ImageConstPtr &msg) {
    qDebug() << "setImg4";
   auto img = toImageShare(msg);
   auto pix = QPixmap::fromImage(std::move(img));
   ui->label_4->setPixmap(pix);
}

void MainWindow::on_Exit_clicked()
{
    control_status.data = false;
    pub_.publish(control_status);
    sleep(2); //make sure that msg has been sent
    qApp->exit();
}

void MainWindow::on_start_btn_clicked()
{
    control_status.data = !control_status.data;
    if(control_status.data)
    {
        ros::V_string node_list;
        if(ros::master::getNodes(node_list))
        {
            if (std::find(node_list.begin(), node_list.end(), "/turtle_joy") != node_list.end())
            {
                qDebug() << "Joy node found";
                control_status.data = true;
                ui->status_label->setText("Status : Running");
            }

            else
            {
                qDebug() << "no Joy node found";
                control_status.data = false;
                ui->status_label->setText("Status : No joy node found");
            }
        }
        else
        {
            qDebug() << "no node found";
            control_status.data = false;
            ui->status_label->setText("Status : Not running any node");
        }
    }
    else {
        ui->status_label->setText("Status : Stop");
    }


    pub_.publish(control_status);

}
