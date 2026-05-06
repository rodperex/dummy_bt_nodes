#ifndef DUMMY_BT_NODES__BT_NODES__SUPPORT__STOP_CURRENT_TASK_HPP_
#define DUMMY_BT_NODES__BT_NODES__SUPPORT__STOP_CURRENT_TASK_HPP_

#include <string>

#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition that checks whether the current task should be interrupted.
/// It reads the fixed blackboard key "stop_current_task" and returns:
///   - SUCCESS when the flag is true
///   - FAILURE when the flag is false or missing
class StopCurrentTask : public BT::ConditionNode
{
public:
  StopCurrentTask(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that checks whether the robot's current task should be stopped and control returned for replanning.";

  static BT::PortsList providedPorts()
  {
    return {};
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes

#endif  // DUMMY_BT_NODES__BT_NODES__SUPPORT__STOP_CURRENT_TASK_HPP_