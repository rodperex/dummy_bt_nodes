#include "behaviortree_cpp/bt_factory.h"
#include "dummy_bt_nodes/bt_failure.hpp"

#include "dummy_bt_nodes/bt_nodes/interaction/speak.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/listen.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/confirm.hpp"
#include "dummy_bt_nodes/bt_nodes/interaction/ask.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/navigate_to.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/follow.hpp"
#include "dummy_bt_nodes/bt_nodes/motion/wait.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/is_detected.hpp"
#include "dummy_bt_nodes/bt_nodes/perception/set_target.hpp"
#include "dummy_bt_nodes/bt_nodes/support/execute_action.hpp"

BT_REGISTER_NODES(factory)
{
  // Interaction
  factory.registerNodeType<dummy_bt_nodes::Speak>("Speak");
  dummy_bt_nodes::bt_register_node_description("Speak", dummy_bt_nodes::Speak::node_description);
  factory.registerNodeType<dummy_bt_nodes::Listen>("Listen");
  dummy_bt_nodes::bt_register_node_description("Listen", dummy_bt_nodes::Listen::node_description);
  factory.registerNodeType<dummy_bt_nodes::Confirm>("Confirm");
  dummy_bt_nodes::bt_register_node_description("Confirm", dummy_bt_nodes::Confirm::node_description);
  factory.registerNodeType<dummy_bt_nodes::Ask>("Ask");
  dummy_bt_nodes::bt_register_node_description("Ask", dummy_bt_nodes::Ask::node_description);

  // Motion
  factory.registerNodeType<dummy_bt_nodes::NavigateTo>("NavigateTo");
  dummy_bt_nodes::bt_register_node_description("NavigateTo", dummy_bt_nodes::NavigateTo::node_description);
  factory.registerNodeType<dummy_bt_nodes::Follow>("Follow");
  dummy_bt_nodes::bt_register_node_description("Follow", dummy_bt_nodes::Follow::node_description);
  factory.registerNodeType<dummy_bt_nodes::Wait>("Wait");
  dummy_bt_nodes::bt_register_node_description("Wait", dummy_bt_nodes::Wait::node_description);

  // Perception
  factory.registerNodeType<dummy_bt_nodes::IsDetected>("IsDetected");
  dummy_bt_nodes::bt_register_node_description("IsDetected", dummy_bt_nodes::IsDetected::node_description);
  factory.registerNodeType<dummy_bt_nodes::SetTarget>("SetTarget");
  dummy_bt_nodes::bt_register_node_description("SetTarget", dummy_bt_nodes::SetTarget::node_description);

  // Support
  factory.registerNodeType<dummy_bt_nodes::ExecuteAction>("ExecuteAction");
  dummy_bt_nodes::bt_register_node_description("ExecuteAction", dummy_bt_nodes::ExecuteAction::node_description);
}
