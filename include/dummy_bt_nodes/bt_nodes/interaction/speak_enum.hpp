#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_ENUM_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_ENUM_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — enumerates a list of items and logs them as if spoken via TTS.
/// Splits 'text' by 'separator' and joins with a natural-language conjunction.
/// Fails only if required input port 'text' is missing or contains no items.
///
/// XML usage:
///   <SpeakEnum text="coffee,tea,water" separator="," language="en"/>
class SpeakEnum : public BT::SyncActionNode
{
public:
  SpeakEnum(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Dummy action that enumerates and speaks a list of items using TTS with proper conjunction.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("text", "Items to speak, separated by separator"),
      BT::InputPort<std::string>("separator", ",", "Item separator (default: ',')"),
      BT::InputPort<std::string>("language", "en", "Language for final conjunction: 'en' or 'es'"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__SPEAK_ENUM_HPP_
