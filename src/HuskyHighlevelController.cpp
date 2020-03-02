#include "husky_highlevel_controller/HuskyHighlevelController.hpp"
#include <cmath>

namespace husky_highlevel_controller {

    HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle &nodeHandle) :
            nodeHandle_(nodeHandle) {
        nodeHandle.getParam("/husky_highlevel_controller/husky/topic_name", topic_name);
        nodeHandle.getParam("/husky_highlevel_controller/husky/queue_size", queue_size);
        ROS_INFO_STREAM(topic_name << " " << queue_size);

        laser_msg = nodeHandle.subscribe(topic_name, queue_size, &HuskyHighlevelController::laserScanMsg, this);

        vel_pub = nodeHandle.advertise<geometry_msg::Twist_msg>("/cmd_vel", 10);
    }

    HuskyHighlevelController::~HuskyHighlevelController() {
    }

    void HuskyHighlevelController::laserScanMsg(const sensor_msgs::LaserScan &msg) {

        auto len = msg.ranges.size();

        for (auto i = 0; i < len; i++) {
            if (min == INFINITY) {
                min = msg.ranges[i];
            }
            if (msg.ranges[i] < min) {
                min = msg.ranges[i];
                min_i = i;
            }
            ROS_INFO_STREAM("Minimum laser reading: " << min);
        }

        pillar_angle = -0.875 + 1.5 * pi / 720 * min_i;

        cmd_vel_command.linear.x = speed;
        cmd_vel_command.angular.z = 0.5 * (0-(pillar_angle-pi/2);

        vel_pub.publish(cmd_vel_command);
    }

} /* namespace */
