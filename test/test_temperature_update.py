import sutsim as simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.initSim("device", firmware_lib_path)

    temperatures = [25.5, 26.5, 27.5, 28.5, 29.5]
    for temp in temperatures:
        # Set the temperature
        simulator.setSutDataFloat("device.temperature_sensor.temperature", temp)

        # Run the firmware tick
        simulator.runTick()

        # Get the temperature
        assert simulator.getSutDataFloat("device.temperature_sensor.temperature") == temp

    simulator.setSutDataFloat("device.temperature_sensor.overTemperatureThreshold", 100.0)
    simulator.runTick()
    assert simulator.getSutDataFloat("device.temperature_sensor.overTemperatureThreshold") == 100.0
