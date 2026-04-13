#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition — simulates checking whether a target is detected.
/// Always returns SUCCESS (dummy). Fails only if 'target' port is missing.
/// Optionally writes the detected entity's name to 'detected_frame' so
/// downstream nodes (e.g. NavigateTo) can navigate to it.
///
/// XML usage:
///   <IsDetected target="person_1" detected_frame="{customer_location}"/>
class IsDetected : public BT::ConditionNode
{
public:
  IsDetected(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether a target entity is currently detected by the perception system. Always returns true.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target", "Target entity name or frame id"),
      BT::OutputPort<std::string>("detected_frame", "Writes the detected entity name to the blackboard (same as 'target')."),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
