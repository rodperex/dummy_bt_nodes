#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__LISTEN_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__LISTEN_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates listening to the user.
/// Writes a placeholder string to the output port 'speech'.
/// Never fails (timeout port is optional).
///
/// XML usage:
///   <Listen speech="{heard_text}" timeout="5000"/>
class Listen : public BT::SyncActionNode
{
public:
  Listen(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates listening to the user and capturing their speech. Writes a placeholder string to the output port.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<int>("timeout", 5000, "Listening timeout in ms"),
      BT::OutputPort<std::string>("speech", "Transcribed speech"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__LISTEN_HPP_
