#include "dummy_bt_nodes/bt_nodes/support/execute_action.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

ExecuteAction::ExecuteAction(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus ExecuteAction::tick()
{
  std::string action;
  if (!getInput("action", action)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "ExecuteAction: missing required input 'action'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'action'");
  }

  std::string params;
  getInput("params", params);

  if (node_) {
    if (params.empty()) {
      RCLCPP_INFO(node_->get_logger(), "[DUMMY] ExecuteAction: action=\"%s\"", action.c_str());
    } else {
      RCLCPP_INFO(node_->get_logger(),
        "[DUMMY] ExecuteAction: action=\"%s\" params=\"%s\"", action.c_str(), params.c_str());
    }
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
