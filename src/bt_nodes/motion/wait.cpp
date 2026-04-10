#include "dummy_bt_nodes/bt_nodes/motion/wait.hpp"

namespace dummy_bt_nodes
{

Wait::Wait(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Wait::tick()
{
  double seconds = 1.0;
  getInput("seconds", seconds);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] Wait: %.1f seconds", seconds);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
