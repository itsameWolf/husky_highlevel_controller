#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <cmath>

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
    nodeHandle.getParam("/husky_highlevel_controller/husky/topic_name", topic_name);
    nodeHandle.getParam("/husky_highlevel_controller/husky/queue_size", queue_size);
    ROS_INFO_STREAM(topic_name << " " << queue_size);
    laser_msg = nodeHandle.subscribe(topic_name, queue_size, &HuskyHighlevelController::laserScanMsg, this);
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

void HuskyHighlevelController::laserScanMsg(const sensor_msgs::LaserScan &msg)
{
    float min = INFINITY;
    auto len = msg.ranges.size();

    for (auto i = 0; i < len; i++)
    {
        if (min==INFINITY)
        {
            min = msg.ranges[i];
        }
        if (msg.ranges[i] < min)
        {
            min = msg.ranges[i];
        }
        ROS_INFO_STREAM("Minimum laser reading: "<<min);
    }
}

} /* namespace */
