#include "dummy_bt_nodes/bt_nodes/perception/is_facing.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsFacing::IsFacing(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsFacing::tick()
{
  std::string target_frame;
  if (!getInput("target_frame", target_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsFacing: missing required input 'target_frame'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'target_frame'",
      "bt_config_error");
  }

  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);

  double angle_threshold = 0.5;
  getInput("angle_threshold", angle_threshold);

  double timeout = 0.5;
  getInput("timeout", timeout);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsFacing: target_frame=\"%s\", base_frame=\"%s\", angle_threshold=%.3f rad, timeout=%.2f s -> true",
      target_frame.c_str(), base_frame.c_str(), angle_threshold, timeout);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
