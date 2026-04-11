# dummy_bt_nodes

ROS 2 package that provides a set of **dummy BehaviorTree.CPP action/condition nodes** for high-level testing of the planning and execution pipeline (e.g. `behavior_architecture` + `llm_planner` + `llm_bt_builder`) without requiring any real hardware or external services.

Every node **only logs what it would do** and always returns `SUCCESS`. The only exception is when a required input port is missing, in which case the node returns `FAILURE` and writes a structured message to the blackboard key `bt_last_failure` so that the LLM plan orchestrator can replan accordingly.

---

## Package contents

```
dummy_bt_nodes/
├── include/dummy_bt_nodes/
│   ├── bt_failure.hpp          # bt_failure() helper + description registry
│   ├── bt_load_descriptions.hpp# utility to load descriptions from YAML
│   └── bt_nodes/
│       ├── interaction/        # Speak, Listen, Confirm, Ask
│       ├── motion/             # NavigateTo, Follow, Wait
│       ├── perception/         # IsDetected, SetTarget
│       └── support/            # ExecuteAction
├── src/bt_nodes/               # corresponding .cpp implementations
├── node_descriptions/
│   └── dummy_bt_nodes.yaml     # descriptions consumed by llm_bt_builder RAG
└── CMakeLists.txt / package.xml
```

The package builds a single shared library **`libdummy_bt_nodes_plugin.so`** that can be loaded dynamically by any BehaviorTree.CPP factory.

---

## Available nodes

### Interaction

| Node | Type | Required ports | Output ports |
|---|---|---|---|
| `Speak` | Action | `text` (string) | — |
| `Listen` | Action | — | `speech` (string) |
| `Confirm` | Action | `text` (string) | `confirmed` (string: `"true"`) |
| `Ask` | Action | `question` (string) | `answer` (string) |

### Motion

| Node | Type | Required ports | Optional ports |
|---|---|---|---|
| `NavigateTo` | Action | `target` (string) | `x` (double), `y` (double) |
| `Follow` | Action | `target` (string) | — |
| `Wait` | Action | — | `seconds` (double, default `1.0`) |

### Perception

| Node | Type | Required ports |
|---|---|---|
| `IsDetected` | Condition | `target` (string) |
| `SetTarget` | Action | `target` (string) |

### Support

| Node | Type | Required ports | Optional ports |
|---|---|---|---|
| `ExecuteAction` | Action | `action` (string) | `params` (string, comma-separated `key=value`) |

---

## Return values

All nodes return `SUCCESS` after logging the action. A node returns `FAILURE` only when a **required** input port is missing, in which case it writes a structured diagnostic to the blackboard key `bt_last_failure`:

```
node: Speak; description: Dummy action that logs the text it would speak.; failure: missing required input port 'text'
```

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
