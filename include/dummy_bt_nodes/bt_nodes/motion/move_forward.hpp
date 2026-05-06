#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_FORWARD_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_FORWARD_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action - simulates moving the robot forward at a given speed.
/// Returns SUCCESS immediately (dummy). Never fails.
///
/// XML usage:
///   <MoveForward speed="0.3"/>
class MoveForward : public BT::SyncActionNode
{
public:
  MoveForward(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates moving the robot forward with a given linear speed.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<double>("speed", 0.5, "Forward speed in m/s"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_FORWARD_HPP_
