#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__NAVIGATE_TO_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__NAVIGATE_TO_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates navigating to a named location or coordinates.
/// Fails only if required input port 'target' is missing.
///
/// XML usage (by name):
///   <NavigateTo target="kitchen"/>
/// XML usage (by coordinates):
///   <NavigateTo target="living_room" x="1.5" y="2.0"/>
class NavigateTo : public BT::SyncActionNode
{
public:
  NavigateTo(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates navigating the robot to a named location or to map coordinates.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target", "Destination name or frame"),
      BT::InputPort<double>("x", 0.0, "X coordinate (optional)"),
      BT::InputPort<double>("y", 0.0, "Y coordinate (optional)"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__NAVIGATE_TO_HPP_
