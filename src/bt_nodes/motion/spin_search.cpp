#include "dummy_bt_nodes/bt_nodes/motion/spin_search.hpp"
#include "dummy_bt_nodes/bt_failure.hpp"

namespace dummy_bt_nodes
{

SpinSearch::SpinSearch(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus SpinSearch::tick()
{
  float angular_speed = 0.5f;
  getInput("angular_speed", angular_speed);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] SpinSearch: spinning at %.2f rad/s", angular_speed);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
