#include "dummy_bt_nodes/bt_nodes/interaction/speak.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

Speak::Speak(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Speak::tick()
{
  std::string text;
  if (!getInput("text", text)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "Speak: missing required input 'text'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'text'");
  }

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] Speak: \"%s\"", text.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
