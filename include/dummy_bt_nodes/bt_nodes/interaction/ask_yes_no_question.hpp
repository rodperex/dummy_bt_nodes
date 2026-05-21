#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_YES_NO_QUESTION_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_YES_NO_QUESTION_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates asking the user for a yes/no question.
/// Returns SUCCESS if the user confirms (YES), FAILURE otherwise.
/// 
/// The default simulated response is "YES". To simulate a "NO" response,
/// provide a "default_answer" input port set to "false".
///
/// XML usage (default YES):
///   <AskYesNoQuestion question="Are you sure?" confirmed="{user_confirmed}"/>
///
/// XML usage (simulate NO):
///   <AskYesNoQuestion question="Are you sure?" default_answer="false" confirmed="{user_confirmed}"/>
class AskYesNoQuestion : public BT::SyncActionNode
{
public:
  AskYesNoQuestion(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Simulates asking the user a yes/no question. Returns SUCCESS if the user confirms (YES), FAILURE otherwise.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("question", "Confirmation prompt to show the user (required)"),
      BT::OutputPort<bool>("confirmed", "User confirmation result (true for YES, false for NO)"),
      BT::InputPort<std::string>("default_answer", "true", "Simulated answer: 'true' for YES (SUCCESS) or 'false' for NO (FAILURE)"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__ASK_YES_NO_QUESTION_HPP_
