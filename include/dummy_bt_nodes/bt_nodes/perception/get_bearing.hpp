#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_BEARING_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_BEARING_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action - simulates computing bearing to a target frame.
/// Fails only if required input port 'target_frame' is missing.
///
/// XML usage:
///   <GetBearing target_frame="person" bearing="{bearing_to_person}"/>
class GetBearing : public BT::SyncActionNode
{
public:
  GetBearing(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates calculating the bearing to a target TF frame and writes it to the blackboard.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "Target TF frame to calculate bearing to"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame for reference"),
      BT::InputPort<double>("timeout", 0.5, "Maximum TF wait/staleness threshold in seconds"),
      BT::OutputPort<double>("bearing", "Calculated bearing angle in radians"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__GET_BEARING_HPP_
