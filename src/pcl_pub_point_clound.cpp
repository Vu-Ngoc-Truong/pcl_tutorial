#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pub_pcl");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<PointCloud >("points2", 1);

    int num_point = 30;

    PointCloud::Ptr msg(new PointCloud);
    msg->header.frame_id = "map";
    msg->height = 1;
    msg->width = num_point;
    for ( int x = 0 ; x< num_point ; x++ )
    {
        float x_coor = float(x)/10;
        msg->points.push_back(pcl::PointXYZ(x_coor, 1.0, 1.0));
    }
    // msg->points.push_back(pcl::PointXYZ(1.0, 2.0, 1.0));
    // msg->points.push_back(pcl::PointXYZ(1.0, 3.0, 1.0));

    ros::Rate loop_rate(4);
    while (nh.ok())
    {
        pcl_conversions::toPCL(ros::Time::now(), msg->header.stamp);
        pub.publish(*msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}
