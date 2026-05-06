#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_WITHIN_DISTANCE_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_WITHIN_DISTANCE_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy condition - simulates checking if the robot is within distance to a target frame.
/// Returns SUCCESS in dummy mode if required inputs are present.
///
/// XML usage:
///   <IsWithinDistance target_frame="person" distance_threshold="1.0"/>
class IsWithinDistance : public BT::ConditionNode
{
public:
  IsWithinDistance(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether the robot is within a distance threshold to a target TF frame.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "Target TF frame to check"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame for reference"),
      BT::InputPort<double>("distance_threshold", 1.0, "Distance threshold in metres"),
      BT::InputPort<double>("timeout", 0.5, "Maximum TF wait/staleness threshold in seconds"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_WITHIN_DISTANCE_HPP_
