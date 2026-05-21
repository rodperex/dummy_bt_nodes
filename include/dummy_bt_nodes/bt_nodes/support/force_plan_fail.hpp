#ifndef DUMMY_BT_NODES__BT_NODES__SUPPORT__FORCE_PLAN_FAIL_HPP_
#define DUMMY_BT_NODES__BT_NODES__SUPPORT__FORCE_PLAN_FAIL_HPP_

#include <string>

#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Signals the orchestrator that the current plan must be restarted from the
/// beginning. The node writes the special code "FORCED_FAILURE" to the
/// blackboard key bt_last_failure_code so the orchestrator can distinguish
/// this hard restart from a normal step failure or a NO_REAL_FAILURE.
///
/// Typical use: wrap in a RetryUntilSuccessful (or a counter idiom) so that
/// after N failed attempts at a particular sub-goal the BT emits this node,
/// causing the orchestrator to loop the whole plan back to step 0 without
/// consuming a replan slot.
class ForcePlanFail : public BT::ConditionNode
{
public:
  ForcePlanFail(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Always returns FAILURE and writes FORCED_FAILURE to bt_last_failure_code so "
    "the orchestrator restarts plan execution from step 0 (reusing already-generated "
    "BTs). Use this node when the current sub-goal is definitively unachievable under "
    "the current plan and the mission must restart from the beginning "
    "(e.g. after N failed appointment-validation attempts).";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("fail_message", "Human-readable reason for the forced plan restart (optional).")
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes

#endif  // DUMMY_BT_NODES__BT_NODES__SUPPORT__FORCE_PLAN_FAIL_HPP_
