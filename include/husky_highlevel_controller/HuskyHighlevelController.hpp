#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <string>

#define pi 3.14159265349

using std::string;

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
    class HuskyHighlevelController {
    public:
        /*!
         * Constructor.
         */
        HuskyHighlevelController(ros::NodeHandle &nodeHandle);

        /*!
         * Destructor.
         */
        virtual ~HuskyHighlevelController();

    private:
        ros::NodeHandle nodeHandle_;
        ros::Subscriber laser_msg;
        ros::Publisher vel_pub;

        void laserScanMsg(const sensor_msgs::LaserScan &msg);

        int queue_size;
        string topic_name;

        float min = INFINITY;
        auto min_i = 0;
        float pillar_angle = pi / 2;
        float speed = 2;

        geometry_msg::Twist cmd_vel_command;
    };

} /* namespace */
