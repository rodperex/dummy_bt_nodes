#include "dummy_bt_nodes/bt_nodes/motion/follow_dynamic.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

FollowDynamic::FollowDynamic(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus FollowDynamic::tick()
{
  std::string target_frame = "target";
  getInput("target_frame", target_frame);
  std::string base_frame = "base_link";
  getInput("base_frame", base_frame);
  float min_distance = 1.0f;
  getInput("min_distance", min_distance);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] FollowDynamic: target_frame=\"%s\" base_frame=\"%s\" min_distance=%.2f",
      target_frame.c_str(), base_frame.c_str(), min_distance);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
