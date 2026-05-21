#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FARTHER_THAN_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FARTHER_THAN_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Condition that checks whether the robot is farther than a distance threshold from a target frame.
/// Returns SUCCESS when the robot is farther than the threshold and FAILURE otherwise.
///
/// XML usage:
///   <IsFartherThan target_frame="person" distance_threshold="1.0"/>
class IsFartherThan : public BT::ConditionNode
{
public:
  IsFartherThan(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Checks if robot-target distance is > distance_threshold. Returns SUCCESS while the robot is farther than the threshold and FAILURE once it is within range.";

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
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__IS_FARTHER_THAN_HPP_
