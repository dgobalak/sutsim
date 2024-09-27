import simulator
import pytest
import os

def test_data_types():
    # Path to the firmware shared library
    firmware_lib_path = os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so')

    # Initialize the simulator
    simulator.init_simulator(firmware_lib_path)

    # Set different types of values (no type strings needed)
    simulator.set_sut_data_float("temperature_sensor.temperature", 25.5)  # float
    simulator.set_sut_data_uint32("temperature_sensor.overTemperatureThreshold", 1)

    # Run the firmware tick
    simulator.run_tick()

    # Get and assert values (automatically detects type)
    assert simulator.get_sut_data_float("temperature_sensor.temperature") == 25.5
    assert simulator.get_sut_data_uint32("temperature_sensor.overTemperatureThreshold") == 1
