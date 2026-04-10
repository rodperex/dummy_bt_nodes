#include "dummy_bt_nodes/bt_nodes/interaction/confirm.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

Confirm::Confirm(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Confirm::tick()
{
  std::string text;
  if (!getInput("text", text)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "Confirm: missing required input 'text'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'text'");
  }

  setOutput("confirmed", std::string("true"));

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] Confirm: \"%s\" → confirmed=true", text.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
