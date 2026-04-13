#ifndef DUMMY_BT_NODES__BT_NODES__PERCEPTION__SET_TARGET_HPP_
#define DUMMY_BT_NODES__BT_NODES__PERCEPTION__SET_TARGET_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates configuring the perception system to look for a target.
/// Fails only if required input port 'target' is missing.
///
/// XML usage:
///   <SetTarget target="person"/>
class SetTarget : public BT::SyncActionNode
{
public:
  SetTarget(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates configuring the perception system to search for a specific target class.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target", "Target class or entity to search for"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__PERCEPTION__SET_TARGET_HPP_
