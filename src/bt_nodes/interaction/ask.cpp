#include "dummy_bt_nodes/bt_nodes/interaction/ask.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

Ask::Ask(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Ask::tick()
{
  std::string question;
  if (!getInput("question", question)) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "Ask: missing required input 'question'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'question'");
  }

  const std::string dummy_answer = "dummy answer";
  setOutput("answer", dummy_answer);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] Ask: \"%s\" → answer=\"%s\"", question.c_str(), dummy_answer.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
