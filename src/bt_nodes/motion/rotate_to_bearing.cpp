#include "dummy_bt_nodes/bt_nodes/motion/rotate_to_bearing.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

#include <algorithm>
#include <cctype>

namespace dummy_bt_nodes
{

RotateToBearing::RotateToBearing(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus RotateToBearing::tick()
{
  std::string bearing;
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

  std::string normalized = bearing;
  std::transform(
    normalized.begin(), normalized.end(), normalized.begin(),
    [](unsigned char c) {return static_cast<char>(std::tolower(c));});

  if (normalized != "left" && normalized != "right") {
    if (node_) {
      RCLCPP_ERROR(
        node_->get_logger(),
        "RotateToBearing: invalid 'bearing' value '%s' (expected 'left' or 'right')",
        bearing.c_str());
    }
    return bt_failure(
      config(), registrationName(),
      "invalid input 'bearing' (expected 'left' or 'right')",
      "bt_config_error");
  }

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] RotateToBearing: bearing=\"%s\", angular_speed=%.2f rad/s",
      normalized.c_str(), angular_speed);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
