#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_DISTANCE_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_DISTANCE_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action - simulates computing distance to a target frame.
/// Fails only if required input port 'target_frame' is missing.
///
/// XML usage:
///   <GetDistance target_frame="person" distance="{distance_to_person}"/>
class GetDistance : public BT::SyncActionNode
{
public:
  GetDistance(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates calculating the distance to a target TF frame and writes it to the blackboard.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "Target TF frame to calculate distance to"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame for reference"),
      BT::InputPort<double>("timeout", 0.5, "Maximum TF wait/staleness threshold in seconds"),
      BT::OutputPort<double>("distance", "Calculated distance in metres"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_DISTANCE_HPP_
