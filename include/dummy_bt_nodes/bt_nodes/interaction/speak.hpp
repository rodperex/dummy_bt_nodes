#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — logs the text it would speak.
/// Fails only if required input port 'text' is missing.
///
/// XML usage:
///   <Speak text="Hello world"/>
///   <Speak text="{blackboard_key}"/>
class Speak : public BT::SyncActionNode
{
public:
  Speak(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that logs the text it would speak. Simulates TTS output without any service call.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("text", "Text to speak"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_HPP_
