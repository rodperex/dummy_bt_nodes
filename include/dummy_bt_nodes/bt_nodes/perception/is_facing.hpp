#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FACING_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FACING_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition - simulates checking if the robot is facing a target frame.
/// Returns SUCCESS in dummy mode if required inputs are present.
///
/// XML usage:
///   <IsFacing target_frame="person" angle_threshold="0.5"/>
class IsFacing : public BT::ConditionNode
{
public:
  IsFacing(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether the robot is facing a target TF frame within an angular threshold.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "Target TF frame to check"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame for reference"),
      BT::InputPort<double>("angle_threshold", 0.5, "Facing threshold in radians"),
      BT::InputPort<double>("timeout", 0.5, "Maximum TF wait/staleness threshold in seconds"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FACING_HPP_
