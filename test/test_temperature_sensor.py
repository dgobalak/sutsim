import sutsim as simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.initSim("device", firmware_lib_path)

    simulator.setSutDataFloat("device.temperature_sensor.temperature", 100.0)

    for _ in range(20):
        simulator.runTick()

    # # Get the temperature
    assert simulator.getSutDataFloat("device.temperature_sensor.temperature") == 100.0
