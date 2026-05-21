#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__ROTATE_TO_BEARING_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__ROTATE_TO_BEARING_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action - simulates rotating to a target bearing.
/// Fails only if required input port 'bearing' is missing.
///
/// XML usage:
///   <RotateToBearing bearing="left" angular_speed="0.6"/>
class RotateToBearing : public BT::SyncActionNode
{
public:
  RotateToBearing(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates rotating the robot in place to face a target bearing angle.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("bearing", "Target bearing direction ('left' or 'right')"),
      BT::InputPort<double>("angular_speed", 0.5, "Angular speed in rad/s"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__ROTATE_TO_BEARING_HPP_
