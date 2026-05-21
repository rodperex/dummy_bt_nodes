#include "dummy_bt_nodes/bt_nodes/support/stop_current_task.hpp"

#include <exception>

namespace dummy_bt_nodes
{

StopCurrentTask::StopCurrentTask(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus StopCurrentTask::tick()
{
  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] StopCurrentTask: forced SUCCESS");
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes