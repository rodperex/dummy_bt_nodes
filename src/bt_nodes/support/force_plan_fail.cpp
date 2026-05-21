#include "dummy_bt_nodes/bt_nodes/support/force_plan_fail.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

#include <string>

namespace dummy_bt_nodes
{

ForcePlanFail::ForcePlanFail(const std::string & name, const BT::NodeConfig & conf)
: BT::ConditionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus ForcePlanFail::tick()
{
  std::string message = "ForcePlanFail triggered";
  getInput("fail_message", message);

  if (node_) {
    RCLCPP_WARN(
      node_->get_logger(),
      "ForcePlanFail: signalling FORCED_FAILURE — '%s'", message.c_str());
  }

  return bt_failure(config(), registrationName(), message, "FORCED_FAILURE");
}

}  // namespace dummy_bt_nodes
