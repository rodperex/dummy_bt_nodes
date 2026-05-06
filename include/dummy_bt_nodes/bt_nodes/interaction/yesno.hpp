#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__YESNO_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__YESNO_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates asking the user for confirmation.
/// Always succeeds and writes "true" to the output port 'confirmed'.
/// Fails only if required input port 'text' is missing.
///
/// XML usage:
///   <YesNo text="Are you sure?" confirmed="{user_confirmed}"/>
class YesNo : public BT::SyncActionNode
{
public:
  YesNo(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that simulates asking the user a yes/no question. Always confirms (writes 'true' to the output port).";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("text", "Confirmation prompt to show the user"),
      BT::OutputPort<std::string>("confirmed", "User confirmation result ('true'/'false')"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__YESNO_HPP_
