#include "dummy_bt_nodes/bt_nodes/interaction/listen.hpp"

namespace dummy_bt_nodes
{

Listen::Listen(const std::string & name, const BT::NodeConfig & conf)
: BT::SyncActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus Listen::tick()
{
  int timeout;
  getInput("timeout", timeout);

  const std::string dummy_speech = "dummy transcribed speech";
  setOutput("speech", dummy_speech);

  if (node_) {
    RCLCPP_INFO(node_->get_logger(),
      "[DUMMY] Listen: heard \"%s\" (timeout=%dms)", dummy_speech.c_str(), timeout);
  }
  return BT::NodeStatus::SUCCESS;
}

}  // namespace dummy_bt_nodes
