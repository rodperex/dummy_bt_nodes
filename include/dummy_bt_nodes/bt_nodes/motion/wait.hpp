#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__WAIT_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__WAIT_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates waiting for a number of seconds.
/// Returns SUCCESS immediately (dummy). Never fails.
///
/// XML usage:
///   <Wait seconds="3.0"/>
class Wait : public BT::SyncActionNode
{
public:
  Wait(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates waiting for a given number of seconds. Returns immediately without blocking.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<double>("seconds", 1.0, "Time to wait in seconds"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__WAIT_HPP_
