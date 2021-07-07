#include <ros/ros.h>
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"

class JoySub
{
    public:
        JoySub();

    private:
        ros::NodeHandle nh;
        ros::Subscriber sub_;
        ros::Publisher pub_;
        void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);
        
        std_msgs::Float32 foo;
};

JoySub::JoySub()
{
    sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &JoySub::joyCallback,this);
    pub_ = nh.advertise<std_msgs::Float32>("joy_listen",1);
}

void JoySub::joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
    foo.data = msg->axes[0];
    pub_.publish(foo); 
    ROS_INFO("I heard something : [%f]",foo.data);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy_listener_node");
  JoySub joySub;

  ros::spin();
}