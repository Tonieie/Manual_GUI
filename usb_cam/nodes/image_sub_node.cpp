#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
     
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
//sensor_msgs::Image The message form passed by image in ROS
  try
  {
    cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    cvWaitKey(3);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_sub_node");
  ros::NodeHandle nh;
  cv::namedWindow("view",CV_WINDOW_AUTOSIZE);
  // cv::startWindowThread();
  cv::waitKey(1);
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);
  ros::spin();
     cv::destroyWindow("view"); //window
}
