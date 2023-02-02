#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <sensor_msgs/PointCloud2.h>
#include <string>
using namespace std;

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
// void callback(const sensor_msgs::PointCloud2ConstPtr &msg);

ros::Publisher pub;
void callback(const sensor_msgs::PointCloud2ConstPtr &msg)
{
    printf("Cloud: width = %d, height = %d\n", msg->width, msg->height);
    pub.publish(*msg);
    // cout << to_string( msg->data.back()) ;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "sub_pcl");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("points2", 1, callback);
    pub = nh.advertise<PointCloud>("points_output", 1);
    ros::spin();
}