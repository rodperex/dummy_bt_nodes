#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__GET_NAV_LOCATION_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__GET_NAV_LOCATION_HPP_

#include <string>
#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

/// Dummy action — simulates resolving a human-readable location description to a
/// navigation frame name.  Writes a placeholder frame string to 'location_frame'.
/// Fails only if the required input port 'location_description' is missing or empty.
///
/// XML usage:
///   <GetNavLocation location_description="{user_location}" location_frame="{nav_frame}"/>
class GetNavLocation : public BT::SyncActionNode
{
public:
  GetNavLocation(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus tick() override;

  static constexpr const char * node_description =
    "Action that resolves a human-provided location description to a known navigation frame "
    "in the map and writes it to 'location_frame'.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>(
        "location_description",
        "Description of the location to navigate to (required)"),
      BT::OutputPort<std::string>(
        "location_frame",
        "Navigation frame corresponding to the location description"),
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes
#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__GET_NAV_LOCATION_HPP_
