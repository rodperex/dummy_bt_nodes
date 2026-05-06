#include "dummy_bt_nodes/bt_nodes/interaction/speak_enum.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

#include <cctype>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace dummy_bt_nodes
{

namespace
{

std::string trim_copy(const std::string & value)
{
  std::size_t start = 0;
  while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
    ++start;
  }
  std::size_t end = value.size();
  while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
    --end;
  }
  return value.substr(start, end - start);
}

bool resolve_blackboard_template(
  const std::string & raw,
  const BT::Blackboard::Ptr & blackboard,
  std::string & resolved,
  std::string & error)
{
  resolved.clear();
  bool saw_placeholder = false;
  std::size_t pos = 0;

  while (pos < raw.size()) {
    const std::size_t open = raw.find('{', pos);
    if (open == std::string::npos) {
      resolved += raw.substr(pos);
      break;
    }

    resolved += raw.substr(pos, open - pos);
    const std::size_t close = raw.find('}', open + 1);
    if (close == std::string::npos) {
      error = "unmatched '{' in text template: '" + raw + "'";
      return false;
    }

    const std::string key = trim_copy(raw.substr(open + 1, close - open - 1));
    if (key.empty()) {
      error = "empty blackboard key in text template: '" + raw + "'";
      return false;
    }

    try {
      resolved += blackboard->get<std::string>(key);
    } catch (const std::exception & e) {
      error = "blackboard key '" + key + "' unavailable in text template: " + e.what();
      return false;
    }

    saw_placeholder = true;
    pos = close + 1;
  }

  if (!saw_placeholder) {
    error = "template contains no blackboard placeholders";
    return false;
  }
  return true;
}

bool resolve_blackboard_list_expression(
  const std::string & raw,
  const BT::Blackboard::Ptr & blackboard,
  std::string & resolved,
  std::string & error)
{
  const char sep = (raw.find(';') != std::string::npos) ? ';' : ',';

  std::vector<std::string> tokens;
  std::stringstream ss(raw);
  std::string token;
  while (std::getline(ss, token, sep)) {
    std::string key = trim_copy(token);
    if (key.empty()) {
      continue;
    }
    if (!key.empty() && key.front() == '{') {
      key.erase(key.begin());
    }
    if (!key.empty() && key.back() == '}') {
      key.pop_back();
    }
    key = trim_copy(key);
    if (!key.empty()) {
      tokens.push_back(key);
    }
  }

  if (tokens.empty()) {
    error = "no tokens found in list expression: '" + raw + "'";
    return false;
  }

  resolved.clear();
  for (std::size_t i = 0; i < tokens.size(); ++i) {
    const auto & key = tokens[i];
    try {
      if (i > 0) {
        resolved += std::string(1, sep);
      }
      resolved += blackboard->get<std::string>(key);
    } catch (const std::exception & e) {
      error = "blackboard key '" + key + "' unavailable in list expression: " + e.what();
      return false;
    }
  }

  return !resolved.empty();
}

}  // namespace

SpeakEnum::SpeakEnum(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus SpeakEnum::tick()
{
  std::string list;
  if (!getInput("list", list) || list.empty()) {
    // BT.CPP doesn't resolve expressions like "{a},{b}" as a single input.
    // Resolve placeholders manually for this common generation pattern.
    std::string raw_list;
    auto input_it = config().input_ports.find("list");
    if (input_it != config().input_ports.end()) {
      raw_list = input_it->second;
    }

    if (!raw_list.empty()) {
      std::string resolved_list;
      std::string resolve_error;
      if ((resolve_blackboard_template(raw_list, config().blackboard, resolved_list, resolve_error) ||
        resolve_blackboard_list_expression(raw_list, config().blackboard, resolved_list, resolve_error)) &&
        !resolved_list.empty())
      {
        list = resolved_list;
      } else if (node_) {
        RCLCPP_WARN(
          node_->get_logger(),
          "SpeakEnum: could not resolve list template '%s': %s",
          raw_list.c_str(), resolve_error.c_str());
      }
    }
  }

  if (list.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SpeakEnum: missing required input 'list'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'list', received: '" + list + "'",
      "bt_config_error");
  }

  std::string separator = ",";
  getInput("separator", separator);
  std::string language = "en";
  getInput("language", language);

  // Split list by separator
  std::vector<std::string> items;
  std::string token;
  std::istringstream ss(list);
  while (std::getline(ss, token, separator[0])) {
    if (!token.empty()) {
      items.push_back(token);
    }
  }

  if (items.empty()) {
    if (node_) {
      RCLCPP_ERROR(node_->get_logger(), "SpeakEnum: no items found in 'list'");
    }
    return bt_failure(config(), registrationName(), "no items found in 'list'");
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
