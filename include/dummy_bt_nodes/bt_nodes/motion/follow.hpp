#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates following a target entity.
/// Fails only if required input port 'target' is missing.
///
/// XML usage:
///   <Follow target="person_1"/>
class Follow : public BT::SyncActionNode
{
public:
  Follow(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates making the robot follow a target entity (person, object, etc.).";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target", "Entity to follow (name or frame id)"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_HPP_
