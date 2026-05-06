#include "dummy_bt_nodes/bt_nodes/motion/move_forward.hpp"

namespace dummy_bt_nodes
{

MoveForward::MoveForward(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus MoveForward::tick()
{
  double speed = 0.5;
  getInput("speed", speed);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] MoveForward: speed=%.2f m/s", speed);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
