#include "dummy_bt_nodes/bt_nodes/perception/get_bearing.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

GetBearing::GetBearing(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus GetBearing::tick()
{
  std::string target_frame;
  if (!getInput("target_frame", target_frame)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "GetBearing: missing required input 'target_frame'");
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

  const double dummy_bearing = 0.0;
  setOutput("bearing", dummy_bearing);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] GetBearing: target_frame=\"%s\", base_frame=\"%s\", timeout=%.2f s -> bearing=%.3f rad",
      target_frame.c_str(), base_frame.c_str(), timeout, dummy_bearing);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
