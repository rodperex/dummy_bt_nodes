#ifndef DUMMY_BT_NODES__BT_NODES__SUPPORT__EXECUTE_ACTION_HPP_
#define DUMMY_BT_NODES__BT_NODES__SUPPORT__EXECUTE_ACTION_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — generic task executor for any action not covered by other nodes.
/// Logs the action name and optional parameters. Returns SUCCESS.
/// Fails only if required input port 'action' is missing.
///
/// XML usage:
///   <ExecuteAction action="open_door" params="door=main_entrance"/>
///   <ExecuteAction action="pick_object" params="object=cup,speed=slow"/>
class ExecuteAction : public BT::SyncActionNode
{
public:
  ExecuteAction(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Generic dummy action executor for any task not covered by the specific nodes (e.g. open_door, pick_object, charge_battery, send_notification). Accepts an optional comma-separated key=value parameter string.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("action", "Name of the action to execute"),
      BT::InputPort<std::string>("params", "", "Optional key=value parameters (comma-separated)"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__SUPPORT__EXECUTE_ACTION_HPP_
