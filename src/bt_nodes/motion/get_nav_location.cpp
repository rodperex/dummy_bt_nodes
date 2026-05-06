#include "dummy_bt_nodes/bt_nodes/motion/get_nav_location.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

GetNavLocation::GetNavLocation(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus GetNavLocation::tick()
{
  std::string location_description;
  if (!getInput("location_description", location_description) || location_description.empty()) {
    if (node_) {
      RCLCPP_ERROR(
        node_->get_logger(),
        "GetNavLocation: missing required input 'location_description'");
    }
    return bt_failure(
      config(), registrationName(),
      "missing required input 'location_description', received: '" + location_description + "'",
      "bt_config_error");
  }

  const std::string dummy_frame = "dummy_frame";
  setOutput("location_frame", dummy_frame);

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] GetNavLocation: location_description=\"%s\" → frame=\"%s\"",
      location_description.c_str(), dummy_frame.c_str());
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
