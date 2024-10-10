import sutsim
import pytest

def test_temperature_sensor_reads(suts):
    suts["device"]["temperature_sensor.temperature"] = 100.0
    assert suts["device"]["temperature_sensor.temperature"] == 100.0
    
    for _ in range(25):
        sutsim.runTick()
    