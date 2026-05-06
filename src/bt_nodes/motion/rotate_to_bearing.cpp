#include "dummy_bt_nodes/bt_nodes/motion/rotate_to_bearing.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

RotateToBearing::RotateToBearing(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus RotateToBearing::tick()
{
  double bearing = 0.0;
  if (!getInput("bearing", bearing)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "RotateToBearing: missing required input 'bearing'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'bearing'",
      "bt_config_error");
  }

  double angular_speed = 0.5;
  getInput("angular_speed", angular_speed);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] RotateToBearing: bearing=%.3f rad, angular_speed=%.2f rad/s",
      bearing, angular_speed);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
