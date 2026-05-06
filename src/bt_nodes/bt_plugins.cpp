#include "behaviortree_cpp/bt_factory.h"
#include "dummy_bt_nodes/bt_failure.hpp"

#include "dummy_bt_nodes/bt_nodes/interaction/speak.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/listen.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/yesno.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/ask.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/speak_enum.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/extract.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/is_available.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/navigate_to.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/get_nav_location.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/follow.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/follow_dynamic.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/move_forward.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/rotate_to_bearing.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/spin_search.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/wait.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/get_bearing.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/get_distance.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/is_detected.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/is_facing.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/is_within_distance.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/set_target.hpp"
#include "dummy_bt_nodes/bt_nodes/support/set_ros2_param.hpp"
#include "dummy_bt_nodes/bt_nodes/support/stop_current_task.hpp"

BT_REGISTER_NODES(factory)
{
  // Interaction
  factory.registerNodeType<dummy_bt_nodes::Speak>("Speak");
  dummy_bt_nodes::bt_register_node_description("Speak", dummy_bt_nodes::Speak::node_description);
  factory.registerNodeType<dummy_bt_nodes::Listen>("Listen");
  dummy_bt_nodes::bt_register_node_description("Listen", dummy_bt_nodes::Listen::node_description);
  factory.registerNodeType<dummy_bt_nodes::YesNo>("YesNo");
  dummy_bt_nodes::bt_register_node_description("YesNo", dummy_bt_nodes::YesNo::node_description);
  factory.registerNodeType<dummy_bt_nodes::Ask>("Ask");
  dummy_bt_nodes::bt_register_node_description("Ask", dummy_bt_nodes::Ask::node_description);
  factory.registerNodeType<dummy_bt_nodes::SpeakEnum>("SpeakEnum");
  dummy_bt_nodes::bt_register_node_description("SpeakEnum", dummy_bt_nodes::SpeakEnum::node_description);
  factory.registerNodeType<dummy_bt_nodes::Extract>("Extract");
  dummy_bt_nodes::bt_register_node_description("Extract", dummy_bt_nodes::Extract::node_description);
  factory.registerNodeType<dummy_bt_nodes::IsAvailable>("IsAvailable");
  dummy_bt_nodes::bt_register_node_description("IsAvailable", dummy_bt_nodes::IsAvailable::node_description);

  // Motion
  factory.registerNodeType<dummy_bt_nodes::NavigateTo>("NavigateTo");
  dummy_bt_nodes::bt_register_node_description("NavigateTo", dummy_bt_nodes::NavigateTo::node_description);
  factory.registerNodeType<dummy_bt_nodes::GetNavLocation>("GetNavLocation");
  dummy_bt_nodes::bt_register_node_description("GetNavLocation", dummy_bt_nodes::GetNavLocation::node_description);
  factory.registerNodeType<dummy_bt_nodes::Follow>("Follow");
  dummy_bt_nodes::bt_register_node_description("Follow", dummy_bt_nodes::Follow::node_description);
  factory.registerNodeType<dummy_bt_nodes::FollowDynamic>("FollowDynamic");
  dummy_bt_nodes::bt_register_node_description("FollowDynamic", dummy_bt_nodes::FollowDynamic::node_description);
  factory.registerNodeType<dummy_bt_nodes::MoveForward>("MoveForward");
  dummy_bt_nodes::bt_register_node_description("MoveForward", dummy_bt_nodes::MoveForward::node_description);
  factory.registerNodeType<dummy_bt_nodes::RotateToBearing>("RotateToBearing");
  dummy_bt_nodes::bt_register_node_description("RotateToBearing", dummy_bt_nodes::RotateToBearing::node_description);
  factory.registerNodeType<dummy_bt_nodes::SpinSearch>("Spin");
  dummy_bt_nodes::bt_register_node_description("Spin", dummy_bt_nodes::SpinSearch::node_description);
  factory.registerNodeType<dummy_bt_nodes::Wait>("Wait");
  dummy_bt_nodes::bt_register_node_description("Wait", dummy_bt_nodes::Wait::node_description);

  // Perception
  factory.registerNodeType<dummy_bt_nodes::IsDetected>("IsDetected");
  dummy_bt_nodes::bt_register_node_description("IsDetected", dummy_bt_nodes::IsDetected::node_description);
  factory.registerNodeType<dummy_bt_nodes::GetBearing>("GetBearing");
  dummy_bt_nodes::bt_register_node_description("GetBearing", dummy_bt_nodes::GetBearing::node_description);
  factory.registerNodeType<dummy_bt_nodes::GetDistance>("GetDistance");
  dummy_bt_nodes::bt_register_node_description("GetDistance", dummy_bt_nodes::GetDistance::node_description);
  factory.registerNodeType<dummy_bt_nodes::IsFacing>("IsFacing");
  dummy_bt_nodes::bt_register_node_description("IsFacing", dummy_bt_nodes::IsFacing::node_description);
  factory.registerNodeType<dummy_bt_nodes::IsWithinDistance>("IsWithinDistance");
  dummy_bt_nodes::bt_register_node_description("IsWithinDistance", dummy_bt_nodes::IsWithinDistance::node_description);
  // Backward-compatible alias for older trees.
  factory.registerNodeType<dummy_bt_nodes::IsDetected>("IsTargetDetected");
  dummy_bt_nodes::bt_register_node_description("IsTargetDetected", dummy_bt_nodes::IsDetected::node_description);
  factory.registerNodeType<dummy_bt_nodes::SetTarget>("SetPerceptionTarget");
  dummy_bt_nodes::bt_register_node_description("SetPerceptionTarget", dummy_bt_nodes::SetTarget::node_description);

  // Support
  factory.registerNodeType<dummy_bt_nodes::SetRos2Param>("SetRos2Param");
  dummy_bt_nodes::bt_register_node_description("SetRos2Param", dummy_bt_nodes::SetRos2Param::node_description);
  factory.registerNodeType<dummy_bt_nodes::StopCurrentTask>("StopCurrentTask");
  dummy_bt_nodes::bt_register_node_description("StopCurrentTask", dummy_bt_nodes::StopCurrentTask::node_description);
}
