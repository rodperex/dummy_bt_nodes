#include "dummy_bt_nodes/bt_nodes/interaction/yesno.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

YesNo::YesNo(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus YesNo::tick()
{
  std::string text;
  if (!getInput("text", text)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "YesNo: missing required input 'text'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'text', received: '" + text + "'",
      "bt_config_error");
  }

  setOutput("confirmed", std::string("true"));

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] YesNo: \"%s\" -> confirmed=true", text.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
