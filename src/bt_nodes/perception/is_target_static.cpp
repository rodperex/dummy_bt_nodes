#include "dummy_bt_nodes/bt_nodes/perception/is_target_static.hpp"

#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsTargetStatic::IsTargetStatic(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsTargetStatic::tick()
{
  std::string target_frame = "target";
  getInput("target_frame", target_frame);

  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);

  double min_static_time_sec = 5.0;
  getInput("min_static_time_sec", min_static_time_sec);

  double position_epsilon = 0.05;
  getInput("position_epsilon", position_epsilon);

  double timeout = 0.5;
  getInput("timeout", timeout);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsTargetStatic: Checking if target_frame=\"%s\" is static (from base_frame=\"%s\") with min_static_time_sec=%.2f s, position_epsilon=%.3f m, timeout=%.2f s -> SUCCESS (dummy always accepts)",
      target_frame.c_str(), base_frame.c_str(), min_static_time_sec, position_epsilon, timeout);
  }

  // Dummy always succeeds - just simulate the check
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
