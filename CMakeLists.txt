cmake_minimum_required(VERSION 3.8)
project(dummy_bt_nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_cpp REQUIRED)

set(dependencies
  rclcpp
  behaviortree_cpp
)

include_directories(include)

add_library(dummy_bt_nodes_plugin SHARED
  src/bt_nodes/interaction/speak.cpp
  src/bt_nodes/interaction/listen.cpp
  src/bt_nodes/interaction/yesno.cpp
  src/bt_nodes/interaction/ask.cpp
  src/bt_nodes/interaction/speak_enum.cpp
  src/bt_nodes/interaction/extract.cpp
  src/bt_nodes/interaction/is_available.cpp
  src/bt_nodes/motion/navigate_to.cpp
  src/bt_nodes/motion/get_nav_location.cpp
  src/bt_nodes/motion/follow.cpp
  src/bt_nodes/motion/follow_dynamic.cpp
  src/bt_nodes/motion/move_forward.cpp
  src/bt_nodes/motion/rotate_to_bearing.cpp
  src/bt_nodes/motion/spin_search.cpp
  src/bt_nodes/motion/wait.cpp
  src/bt_nodes/perception/get_bearing.cpp
  src/bt_nodes/perception/get_distance.cpp
  src/bt_nodes/perception/is_detected.cpp
  src/bt_nodes/perception/is_facing.cpp
  src/bt_nodes/perception/is_within_distance.cpp
  src/bt_nodes/perception/set_target.cpp
  src/bt_nodes/support/stop_current_task.cpp
  src/bt_nodes/support/set_ros2_param.cpp
  src/bt_nodes/bt_plugins.cpp
)
ament_target_dependencies(dummy_bt_nodes_plugin ${dependencies})
target_compile_definitions(dummy_bt_nodes_plugin PRIVATE BT_PLUGIN_EXPORT)

install(TARGETS dummy_bt_nodes_plugin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY node_descriptions/
  DESTINATION share/${PROJECT_NAME}/node_descriptions
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_libraries(dummy_bt_nodes_plugin)
ament_export_dependencies(${dependencies})

ament_package()
