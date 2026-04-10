#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates asking the user a question and getting an answer.
/// Writes a placeholder string to the output port 'answer'.
/// Fails only if required input port 'question' is missing.
///
/// XML usage:
///   <Ask question="What is your name?" answer="{user_answer}"/>
class Ask : public BT::SyncActionNode
{
public:
  Ask(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that simulates asking the user an open-ended question and capturing their answer.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("question", "Question to ask the user"),
      BT::OutputPort<std::string>("answer", "User's answer"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_HPP_
