#include "dummy_bt_nodes/bt_nodes/perception/is_detected.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsDetected::IsDetected(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsDetected::tick()
{
  std::string target_frame;
  std::string base_frame;
  double timeout = 0.5;

  if (!getInput("target_frame", target_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsDetected: missing required input 'target_frame'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'target_frame'",
      "bt_config_error");
  }

  if (!getInput("base_frame", base_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsDetected: missing required input 'base_frame'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'base_frame'",
      "bt_config_error");
  }

  getInput("timeout", timeout);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsDetected: target_frame=\"%s\" from base_frame=\"%s\" (timeout=%.2f s) -> true",
      target_frame.c_str(), base_frame.c_str(), timeout);
  }

  setOutput("detected_frame", target_frame);
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
