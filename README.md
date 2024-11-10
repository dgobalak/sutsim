
# SUTSim

SUTSim is a simulation framework for validating baremetal or RTOS-based firmware off-target. Here are the main features:
- Supports signal injection at any layer of the firmware, eliminating hardware dependencies (sensors, data storage, etc.)
- Supports signal monitoring at any layer of the firmware, allowing users to monitor what the firmware is doing at any given timestep
- Supports a Python abstraction for writing automated regression tests that validate system-level behaviour

Take a look at the examples in the repo for more info on the framework's capabilities.

## Getting Started
### SUTSim Development
See our [dev environment setup instructions](https://github.com/dgobalak/sutsim/blob/main/docs/dev_setup.md).

### Integrating into new project
See our [project integration guide](https://github.com/dgobalak/sutsim/blob/main/docs/new_project.md) for a general overview of how you can integrate sutsim into an existing firmware codebase.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
