#include "dummy_bt_nodes/bt_nodes/interaction/is_available.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsAvailable::IsAvailable(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsAvailable::tick()
{
  std::string available_items;
  std::string items;
  if (!getInput("available_items", available_items)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsAvailable: missing required input 'available_items'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'available_items', received: '" + available_items + "'",
      "bt_config_error");
  }

  if (!getInput("items", items)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsAvailable: missing required input 'items'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'items', received: '" + items + "'",
      "bt_config_error");
  }


  setOutput("unavailable_items", std::string{});
  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] IsAvailable: assuming all requested items are available (available_items=\"%s\", items=\"%s\")",
      available_items.c_str(), items.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
