#include "dummy_bt_nodes/bt_nodes/interaction/speak_enum.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

#include <sstream>
#include <vector>

namespace dummy_bt_nodes
{

SpeakEnum::SpeakEnum(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus SpeakEnum::tick()
{
  std::string text;
  if (!getInput("text", text) || text.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SpeakEnum: missing required input 'text'");
    }
    return bt_failure(config(), registrationName(), "missing required input 'text'");
  }

  std::string separator = ",";
  getInput("separator", separator);
  std::string language = "en";
  getInput("language", language);

  // Split text by separator
  std::vector<std::string> items;
  std::string token;
  std::istringstream ss(text);
  while (std::getline(ss, token, separator[0])) {
    if (!token.empty()) {
      items.push_back(token);
    }
  }

  if (items.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SpeakEnum: no items found in 'text'");
    }
    return bt_failure(config(), registrationName(), "no items found in 'text'");
  }

  // Build enumeration string
  std::string spoken;
  const std::string conjunction = (language == "es") ? " y " : " and ";
  if (items.size() == 1) {
    spoken = items[0];
  } else {
    for (size_t i = 0; i < items.size() - 1; ++i) {
      spoken += items[i];
      if (i < items.size() - 2) {spoken += ", ";}
    }
    spoken += conjunction + items.back();
  }

  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] SpeakEnum: \"%s\"", spoken.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
