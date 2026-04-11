#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__SPIN_SEARCH_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__SPIN_SEARCH_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates spinning in place to search for targets.
/// Logs the spin and always succeeds (real node returns RUNNING indefinitely).
///
/// XML usage:
///   <SpinSearch angular_speed="0.5"/>
class SpinSearch : public BT::SyncActionNode
{
public:
  SpinSearch(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates making the robot spin in place to search for targets.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<float>("angular_speed", 0.5f, "Angular speed in rad/s"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__SPIN_SEARCH_HPP_
