#include "dummy_bt_nodes/bt_nodes/motion/move_towards.hpp"

namespace dummy_bt_nodes
{

MoveTowards::MoveTowards(const std::string & name, const BT::NodeConfig & conf)
: BT::StatefulActionNode(name, conf)
{
  node_ = config().blackboard->get<rclcpp::Node::SharedPtr>("node");
}

BT::NodeStatus MoveTowards::onStart()
{
  std::string target_frame = "target";
  std::string base_frame = "base_link";
  std::string cmd_vel_topic = "/cmd_vel";
  double goal_distance = 1.0;
  double max_linear_speed = 0.5;
  double max_angular_speed = 1.0;
  double linear_kp = 1.0;
  double linear_ki = 0.0;
  double linear_kd = 0.2;
  double angular_kp = 1.0;
  double angular_ki = 0.0;
  double angular_kd = 0.3;

  getInput("target_frame", target_frame);
  getInput("base_frame", base_frame);
  getInput("goal_distance", goal_distance);
  getInput("max_linear_speed", max_linear_speed);
  getInput("max_angular_speed", max_angular_speed);
  getInput("cmd_vel_topic", cmd_vel_topic);
  getInput("linear_kp", linear_kp);
  getInput("linear_ki", linear_ki);
  getInput("linear_kd", linear_kd);
  getInput("angular_kp", angular_kp);
  getInput("angular_ki", angular_ki);
  getInput("angular_kd", angular_kd);

  if (goal_distance < 0.0 || max_linear_speed <= 0.0 || max_angular_speed <= 0.0) {
    if (node_) {
      RCLCPP_ERROR(
        node_->get_logger(),
        "[DUMMY] MoveTowards invalid params: goal_distance=%.2f max_linear=%.2f max_angular=%.2f",
        goal_distance, max_linear_speed, max_angular_speed);
    }
    return BT::NodeStatus::RUNNING;
  }

  if (node_) {
    RCLCPP_INFO(
      node_->get_logger(),
      "[DUMMY] MoveTowards: target_frame=%s base_frame=%s goal_distance=%.2f max_linear=%.2f max_angular=%.2f cmd_vel_topic=%s linear_pid=[%.2f, %.2f, %.2f] angular_pid=[%.2f, %.2f, %.2f]",
      target_frame.c_str(), base_frame.c_str(), goal_distance, max_linear_speed, max_angular_speed,
      cmd_vel_topic.c_str(), linear_kp, linear_ki, linear_kd, angular_kp, angular_ki, angular_kd);
  }

  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus MoveTowards::onRunning()
{
  return BT::NodeStatus::RUNNING;
}

void MoveTowards::onHalted()
{
  if (node_) {
    RCLCPP_INFO(node_->get_logger(), "[DUMMY] MoveTowards halted");
  }
}

}  // namespace dummy_bt_nodes