#include "dummy_bt_nodes/bt_nodes/support/set_ros2_param.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

SetRos2Param::SetRos2Param(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus SetRos2Param::tick()
{
  std::string node_name, param_name, param_value;

  if (!getInput("node_name", node_name) || node_name.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SetRos2Param: missing required input 'node_name'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'node_name'");
  }
  if (!getInput("param_name", param_name) || param_name.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SetRos2Param: missing required input 'param_name'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'param_name'");
  }
  if (!getInput("param_value", param_value)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SetRos2Param: missing required input 'param_value'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'param_value'");
  }

  std::string param_type = "string";
  getInput("param_type", param_type);

  setOutput("success", true);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] SetRos2Param: %s/%s = %s (%s)",
      node_name.c_str(), param_name.c_str(), param_value.c_str(), param_type.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
