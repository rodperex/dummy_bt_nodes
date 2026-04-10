#include "dummy_bt_nodes/bt_nodes/perception/is_detected.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

IsDetected::IsDetected(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsDetected::tick()
{
  std::string target;
  if (!getInput("target", target)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "IsDetected: missing required input 'target'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'target'");
  }

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] IsDetected: target=\"%s\" → true", target.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
