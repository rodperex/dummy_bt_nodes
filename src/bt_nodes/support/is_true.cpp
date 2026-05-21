#include "dummy_bt_nodes/bt_nodes/support/is_true.hpp"

namespace dummy_bt_nodes
{

IsTrue::IsTrue(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus IsTrue::tick()
{
  bool value = false;
  (void)getInput("value", value);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] IsTrue: value=%s -> forced SUCCESS", value ? "true" : "false");
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes