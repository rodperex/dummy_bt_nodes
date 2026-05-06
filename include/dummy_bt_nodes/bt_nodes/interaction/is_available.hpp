#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__IS_AVAILABLE_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__IS_AVAILABLE_HPP_

#include <string>
#include "behaviortree_cpp/condition_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Condition that checks whether requested items are available.
/// Returns SUCCESS only when every requested item exists in 'available_items'.
/// Returns FAILURE when at least one requested item is unavailable.
///
/// XML usage:
///   <IsAvailable available_items="item_1;item_2;item_3" items="item_1;item_4"/>
class IsAvailable : public BT::ConditionNode
{
public:
  IsAvailable(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Condition that simulates checking whether requested items are available.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("available_items", "Semicolon-separated list of available items"),
      BT::InputPort<std::string>("items", "Semicolon-separated list of requested items"),
      BT::OutputPort<std::string>("unavailable_items", "Semicolon-separated list of unavailable items (optional)"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__IS_AVAILABLE_HPP_
