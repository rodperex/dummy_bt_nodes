#ifndef DUMMY_BT_NODES__BT_NODES__SUPPORT__SET_ROS2_PARAM_HPP_
#define DUMMY_BT_NODES__BT_NODES__SUPPORT__SET_ROS2_PARAM_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates setting a parameter on a ROS 2 node.
/// Logs the node/param/value and always succeeds.
/// Fails only if required input ports 'node_name', 'param_name', or 'param_value' are missing.
///
/// XML usage:
///   <SetRos2Param node_name="/my_node" param_name="speed" param_value="1.0" success="{ok}"/>
class SetRos2Param : public BT::SyncActionNode
{
public:
  SetRos2Param(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates setting a parameter on a ROS 2 node.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("node_name", "Name of the ROS 2 node"),
      BT::InputPort<std::string>("param_name", "Parameter name"),
      BT::InputPort<std::string>("param_value", "Parameter value"),
      BT::InputPort<std::string>("param_type", "string", "Parameter type (string, int, double, bool)"),
      BT::OutputPort<bool>("success", "Whether the operation succeeded"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__SUPPORT__SET_ROS2_PARAM_HPP_
