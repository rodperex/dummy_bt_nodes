#ifndef DUMMY_BT_NODES__BT_NODES__INTERACTION__EXTRACT_HPP_
#define DUMMY_BT_NODES__BT_NODES__INTERACTION__EXTRACT_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates extracting a piece of information from a text via LLM.
/// Writes a placeholder string to the output port 'extracted_info'.
/// Fails only if required input ports 'interest' or 'text' are missing.
///
/// XML usage:
///   <Extract interest="order" text="{transcription}" extracted_info="{order}"/>
class Extract : public BT::SyncActionNode
{
public:
  Extract(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that extracts information of interest from a text using an LLM service.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("interest", "Information to extract (e.g. 'order', 'name')"),
      BT::InputPort<std::string>("text", "Source text to extract from"),
      BT::OutputPort<std::string>("extracted_info", "The extracted information"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__INTERACTION__EXTRACT_HPP_
