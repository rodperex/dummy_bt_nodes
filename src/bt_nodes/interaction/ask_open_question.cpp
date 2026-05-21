#include "dummy_bt_nodes/bt_nodes/interaction/ask_open_question.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

AskOpenQuestion::AskOpenQuestion(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus AskOpenQuestion::tick()
{
  std::string question;
  if (!getInput("question", question)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "AskOpenQuestion: missing required input 'question'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'question', received: '" + question + "'",
      "bt_config_error");
  }

  const std::string dummy_answer = "dummy answer";
  setOutput("answer", dummy_answer);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] AskOpenQuestion: \"%s\" -> answer=\"%s\"", question.c_str(), dummy_answer.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
