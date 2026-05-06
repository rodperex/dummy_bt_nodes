#include "dummy_bt_nodes/bt_nodes/interaction/extract.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

Extract::Extract(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Extract::tick()
{
  std::string interest;
  if (!getInput("interest", interest) || interest.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "Extract: missing required input 'interest'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'interest', received: '" + interest + "'",
      "bt_config_error");
  }

  std::string text;
  if (!getInput("text", text) || text.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "Extract: missing required input 'text'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'text', received: '" + text + "'",
      "bt_config_error");
  }

  const std::string dummy_result = "dummy_" + interest;
  setOutput("extracted_info", dummy_result);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] Extract: interest=\"%s\" from text=\"%s\" → \"%s\"",
      interest.c_str(), text.c_str(), dummy_result.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
