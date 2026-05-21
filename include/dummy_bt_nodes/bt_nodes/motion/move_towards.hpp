#ifndef DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_TOWARDS_HPP_
#define DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_TOWARDS_HPP_

#include <string>

#include "behaviortree_cpp/action_node.h"
#include "rclcpp/rclcpp.hpp"

namespace dummy_bt_nodes
{

class MoveTowards : public BT::StatefulActionNode
{
public:
  MoveTowards(const std::string & name, const BT::NodeConfig & conf);

  BT::NodeStatus onStart() override;
  BT::NodeStatus onRunning() override;
  void onHalted() override;

  static constexpr const char * node_description =
    "Action that simulates moving the robot towards a target frame using linear and angular velocity control. Always returns RUNNING and never completes by itself.";

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<std::string>("target_frame", "target", "Target TF frame to move towards"),
      BT::InputPort<std::string>("base_frame", "base_link", "Base TF frame of the robot"),
      BT::InputPort<double>("goal_distance", 1.0, "Desired distance from target (m)"),
      BT::InputPort<double>("max_linear_speed", 0.5, "Maximum linear speed (m/s)"),
      BT::InputPort<double>("max_angular_speed", 1.0, "Maximum angular speed (rad/s)"),
      BT::InputPort<std::string>("cmd_vel_topic", "/cmd_vel", "Command velocity topic"),
      BT::InputPort<double>("linear_kp", 1.0, "Linear PID proportional gain"),
      BT::InputPort<double>("linear_ki", 0.0, "Linear PID integral gain"),
      BT::InputPort<double>("linear_kd", 0.2, "Linear PID derivative gain"),
      BT::InputPort<double>("angular_kp", 1.0, "Angular PID proportional gain"),
      BT::InputPort<double>("angular_ki", 0.0, "Angular PID integral gain"),
      BT::InputPort<double>("angular_kd", 0.3, "Angular PID derivative gain")
    };
  }

private:
  rclcpp::Node::SharedPtr node_;
};

}  // namespace dummy_bt_nodes

#endif  // DUMMY_BT_NODES__BT_NODES__MOTION__MOVE_TOWARDS_HPP_