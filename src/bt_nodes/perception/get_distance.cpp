#include "dummy_bt_nodes/bt_nodes/perception/get_distance.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

GetDistance::GetDistance(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus GetDistance::tick()
{
  std::string target_frame;
  if (!getInput("target_frame", target_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "GetDistance: missing required input 'target_frame'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'target_frame'",
      "bt_config_error");
  }

  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);

  double timeout = 0.5;
  getInput("timeout", timeout);

  const double dummy_distance = 1.0;
  setOutput("distance", dummy_distance);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] GetDistance: target_frame=\"%s\", base_frame=\"%s\", timeout=%.2f s -> distance=%.2f m",
      target_frame.c_str(), base_frame.c_str(), timeout, dummy_distance);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
