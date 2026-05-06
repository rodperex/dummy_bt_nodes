#include "dummy_bt_nodes/bt_nodes/perception/is_within_distance.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsWithinDistance::IsWithinDistance(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsWithinDistance::tick()
{
  std::string target_frame;
  if (!getInput("target_frame", target_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsWithinDistance: missing required input 'target_frame'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'target_frame'",
      "bt_config_error");
  }

  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);

  double distance_threshold = 1.0;
  getInput("distance_threshold", distance_threshold);

  double timeout = 0.5;
  getInput("timeout", timeout);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsWithinDistance: target_frame=\"%s\", base_frame=\"%s\", distance_threshold=%.2f m, timeout=%.2f s -> true",
      target_frame.c_str(), base_frame.c_str(), distance_threshold, timeout);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
