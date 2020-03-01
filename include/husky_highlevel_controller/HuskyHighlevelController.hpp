#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string>

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
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	void laserScanMsg(const sensor_msgs::LaserScan &msg);
	ros::Subscriber laser_msg;
	int queue_size;
	string topic_name;
};

} /* namespace */
