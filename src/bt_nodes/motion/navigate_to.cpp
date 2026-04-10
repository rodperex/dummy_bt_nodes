#include "dummy_bt_nodes/bt_nodes/motion/navigate_to.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

NavigateTo::NavigateTo(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus NavigateTo::tick()
{
  std::string target;
  if (!getInput("target", target)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "NavigateTo: missing required input 'target'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'target'");
  }

  double x = 0.0, y = 0.0;
  getInput("x", x);
  getInput("y", y);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] NavigateTo: target=\"%s\" (x=%.2f, y=%.2f)", target.c_str(), x, y);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
