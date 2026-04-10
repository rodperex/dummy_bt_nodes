#include "dummy_bt_nodes/bt_nodes/perception/set_target.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

SetTarget::SetTarget(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus SetTarget::tick()
{
  std::string target;
  if (!getInput("target", target)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SetTarget: missing required input 'target'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'target'");
  }

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] SetTarget: target=\"%s\"", target.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
