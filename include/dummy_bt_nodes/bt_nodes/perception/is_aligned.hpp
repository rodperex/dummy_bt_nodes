#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_ALIGNED_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_ALIGNED_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition - simulates checking if the robot is aligned with a target frame.
/// Returns SUCCESS in dummy mode if required inputs are present.
///
/// XML usage:
///   <IsAligned target_frame="person" angle_threshold="0.5"/>
class IsAligned : public BT::ConditionNode
{
public:
  IsAligned(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether the robot is aligned with a target TF frame within an angular threshold.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "Target TF frame to check"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame for reference"),
      BT::InputPort<double>("angle_threshold", 0.5, "Alignment threshold in radians"),
      BT::InputPort<double>("timeout", 0.5, "Maximum TF wait/staleness threshold in seconds"),
      BT::OutputPort<std::string>("direction", "Bearing direction to align with target ('left' or 'right')"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_ALIGNED_HPP_
