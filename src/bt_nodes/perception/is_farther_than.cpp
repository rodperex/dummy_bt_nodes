#include "dummy_bt_nodes/bt_nodes/perception/is_farther_than.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsFartherThan::IsFartherThan(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsFartherThan::tick()
{
  std::string target_frame;
  (void)getInput("target_frame", target_frame);

  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);

  double distance_threshold = 1.0;
  getInput("distance_threshold", distance_threshold);

  double timeout = 0.5;
  getInput("timeout", timeout);

  const double dummy_distance = 1.0;

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsFartherThan: target_frame=\"%s\", base_frame=\"%s\", distance_threshold=%.2f m, timeout=%.2f s -> %s (distance=%.2f m)",
      target_frame.c_str(), base_frame.c_str(), distance_threshold, timeout,
      "forced failure",
      dummy_distance);
  }
  return bt_failure(config(), registrationName(), "NO_REAL_FAILURE");
}

}  // namespace dummy_bt_nodes
