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
  bool stop_requested = false;

  try {
    stop_requested = config().blackboard->get<bool>("stop_current_task");
  } catch (const std::exception &) {
    stop_requested = false;
  }

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] StopCurrentTask: blackboard.stop_current_task=%s -> %s",
      stop_requested ? "true" : "false",
      stop_requested ? "stop requested" : "continue current task");
  }

  return stop_requested ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

}  // namespace dummy_bt_nodes