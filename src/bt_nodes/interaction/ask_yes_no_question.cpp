#include "dummy_bt_nodes/bt_nodes/interaction/ask_yes_no_question.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

AskYesNoQuestion::AskYesNoQuestion(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus AskYesNoQuestion::tick()
{
  std::string text;
  (void)getInput("question", text);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] AskYesNoQuestion: \"%s\" -> forced SUCCESS", text.c_str());
  }

  setOutput("confirmed", true);
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
