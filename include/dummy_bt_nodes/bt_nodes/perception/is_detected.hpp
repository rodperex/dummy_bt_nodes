#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition — simulates checking whether a target is detected.
/// Always returns SUCCESS (dummy). Fails only if 'target' port is missing.
///
/// XML usage:
///   <IsDetected target="person_1"/>
class IsDetected : public BT::ConditionNode
{
public:
  IsDetected(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy condition that simulates checking whether a target entity is currently detected by the perception system. Always returns true.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target", "Target entity name or frame id"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
