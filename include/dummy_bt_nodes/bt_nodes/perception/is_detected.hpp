#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition — simulates checking whether a target is detected.
/// Always returns SUCCESS (dummy). It mirrors the real node interface with
/// target_frame/base_frame/timeout and writes detected_frame = target_frame.
///
/// XML usage:
///   <IsDetected target_frame="person" detected_frame="{customer_location}"/>
class IsDetected : public BT::ConditionNode
{
public:
  IsDetected(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether a target TF frame is currently detected. Always returns true in dummy mode.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "target", "Target TF frame to check"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame"),
      BT::InputPort<double>("timeout", 0.5, "Time to wait for detection (seconds)"),
      BT::OutputPort<std::string>("detected_frame", "Writes the detected class/frame (same as 'target_frame') to the blackboard."),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_DETECTED_HPP_
