import sutsim as simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.initSim("device", firmware_lib_path)

    # Set the temperature sensor data and verify it was set correctly
    simulator.setSutDataFloat("device.temperature_sensor.temperature", 100.0)
    simulator.getSutDataFloat("device.temperature_sensor.temperature") == 100.0
    
    for _ in range(25):
        simulator.runTick()
    