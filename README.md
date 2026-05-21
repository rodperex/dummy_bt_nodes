# dummy_bt_nodes

ROS 2 package that provides a set of **dummy BehaviorTree.CPP action/condition nodes** for high-level testing of the planning and execution pipeline (e.g. `behavior_architecture` + `llm_planner` + `llm_bt_builder`) without requiring any real hardware or external services.

Nodes are lightweight test doubles: they log the intended behavior, write expected outputs to blackboard ports when needed, and avoid hardware/service dependencies.

---

## Package contents

```
dummy_bt_nodes/
├── include/dummy_bt_nodes/
│   ├── bt_failure.hpp          # bt_failure() helper + description registry
│   ├── bt_load_descriptions.hpp# utility to load descriptions from YAML
│   └── bt_nodes/
│       ├── interaction/        # Speak, Listen, YesNo, Ask, SpeakEnum, Extract, IsAvailable
│       ├── motion/             # NavigateTo, GetNavLocation, Follow, FollowDynamic, MoveForward, RotateToBearing, Spin, Wait
│       ├── perception/         # IsDetected, GetBearing, GetDistance, IsAligned, IsInRange, SetPerceptionTarget
│       └── support/            # SetRos2Param, StopCurrentTask
├── src/bt_nodes/               # corresponding .cpp implementations
├── node_descriptions/
│   └── dummy_bt_nodes.yaml     # descriptions consumed by llm_bt_builder RAG
└── CMakeLists.txt / package.xml
```

The package builds a single shared library **`libdummy_bt_nodes_plugin.so`** that can be loaded dynamically by any BehaviorTree.CPP factory.

---

## Available nodes

### Interaction

| Node | Type | Required input ports | Optional input ports | Output ports |
|---|---|---|---|---|
| `Speak` | Action | `text` (string) | — | — |
| `Listen` | Action | — | `timeout` (int, default `5000`) | `speech` (string) |
| `YesNo` | Action | `text` (string) | — | `confirmed` (string) |
| `Ask` | Action | `question` (string) | — | `answer` (string) |
| `SpeakEnum` | Action | `list` (string) | `separator` (string, default `,`), `language` (string, default `en`) | — |
| `Extract` | Action | `interest` (string), `text` (string) | — | `extracted_info` (string) |
| `IsAvailable` | Condition | `available_items` (string), `items` (string) | — | `unavailable_items` (string, optional) |

### Motion

| Node | Type | Required input ports | Optional input ports | Output ports |
|---|---|---|---|---|
| `NavigateTo` | Action | `target` (string) | `x` (double, default `0.0`), `y` (double, default `0.0`) | — |
| `GetNavLocation` | Action | `location_description` (string) | — | `location_frame` (string) |
| `Follow` | Action | `target` (string) | — | — |
| `FollowDynamic` | Action | — | `target_frame` (string, default `target`), `base_frame` (string, default `base_link`), `min_distance` (float, default `1.0`), `succeed_on_reach` (bool, default `false`) | — |
| `MoveForward` | Action | — | `speed` (double, default `0.5`) | — |
| `RotateToBearing` | Action | `bearing` (double) | `angular_speed` (double, default `0.5`) | — |
| `Spin` | Action | — | `angular_speed` (float, default `0.5`) | — |
| `Wait` | Action | — | `seconds` (double, default `1.0`) | — |

### Perception

| Node | Type | Required input ports | Optional input ports | Output ports |
|---|---|---|---|---|
| `IsDetected` | Condition | — | `target_frame` (string, default `target`), `base_frame` (string, default `base_link`), `timeout` (double, default `0.5`) | `detected_frame` (string) |
| `GetBearing` | Action | `target_frame` (string) | `base_frame` (string, default `base_link`), `timeout` (double, default `0.5`) | `bearing` (double) |
| `GetDistance` | Action | `target_frame` (string) | `base_frame` (string, default `base_link`), `timeout` (double, default `0.5`) | `distance` (double) |
| `IsAligned` | Condition | `target_frame` (string) | `base_frame` (string, default `base_link`), `angle_threshold` (double, default `0.5`), `timeout` (double, default `0.5`) | `direction` (string) |
| `IsInRange` | Condition | `target_frame` (string) | `base_frame` (string, default `base_link`), `distance_threshold` (double, default `1.0`), `timeout` (double, default `0.5`) | — |
| `SetPerceptionTarget` | Action | `target` (string) | — | — |

### Support

| Node | Type | Required input ports | Optional input ports | Output ports |
|---|---|---|---|---|
| `SetRos2Param` | Action | `node_name` (string), `param_name` (string), `param_value` (string) | `param_type` (string, default `string`) | `success` (bool) |
| `StopCurrentTask` | Condition | — | — | — |

Compatibility aliases registered by the plugin:

- `IsTargetDetected` -> same implementation as `IsDetected`
- `IsWithinDistance` -> same implementation as `IsInRange`

---

## Return values

Most nodes return `SUCCESS` after logging the action.

Nodes using `bt_failure(...)` return `FAILURE` when required inputs are missing, and write a structured diagnostic to blackboard key `bt_last_failure`:

```
node: Speak; description: Dummy action that logs the text it would speak.; failure: missing required input port 'text'
```

Important runtime exceptions:

- `StopCurrentTask` returns `SUCCESS` only if blackboard key `stop_current_task` is `true`; otherwise it returns `FAILURE`.
- `IsAvailable` currently returns `SUCCESS` when inputs are present (dummy behavior assumes availability).
- `Spin` returns `SUCCESS` in this package implementation.

This key is read by `LLMPlanOrchestrator` (from `behavior_architecture`) to feed the replanning service with an actionable failure reason.

---

## Building

```bash
colcon build --packages-select dummy_bt_nodes
source install/setup.bash
```

Dependencies: `rclcpp`, `behaviortree_cpp`.

---

## Using the plugin in another package

Load the plugin from your BehaviorTree.CPP factory:

```cpp
factory.registerFromPlugin("libdummy_bt_nodes_plugin.so");
```

Or declare it in a `behavior_architecture` YAML config:

```yaml
plugin_libraries:
  - "libdummy_bt_nodes_plugin.so"
```

The `node_descriptions/dummy_bt_nodes.yaml` file is installed under
`share/dummy_bt_nodes/node_descriptions/` and is auto-resolved by
`llm_bt_builder` when you set:

```yaml
bt_nodes_package: "dummy_bt_nodes"
```

---

## Utility headers

### `bt_failure.hpp`

Provides `bt_failure(cfg, registrationName(), "reason")` — a one-liner that writes to `bt_last_failure` and returns `BT::NodeStatus::FAILURE`. Also exposes the process-wide description registry populated at plugin load time.

### `bt_load_descriptions.hpp`

Alternative to the static `bt_register_node_description()` calls in `bt_plugins.cpp`. Reads descriptions directly from the YAML file, keeping the source of truth in one place. See the header for activation instructions.

---

## License

Apache License 2.0

## Author

Rodrigo Pérez-Rodríguez (rodrigo.perez@urjc.es)
