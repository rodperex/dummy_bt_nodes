#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_DYNAMIC_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_DYNAMIC_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates following a person with dynamic speed/distance adjustments.
/// Logs the target frame and always succeeds.
///
/// XML usage:
///   <FollowDynamic target_frame="person_1" min_distance="1.0"/>
class FollowDynamic : public BT::SyncActionNode
{
public:
  FollowDynamic(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates following a person with dynamic speed and distance adjustments.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "target", "Target TF frame to follow"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame"),
      BT::InputPort<float>("min_distance", 1.0f, "Desired following distance in metres"),
      BT::InputPort<bool>("succeed_on_reach", false, "Return SUCCESS when target is reached"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__FOLLOW_DYNAMIC_HPP_
