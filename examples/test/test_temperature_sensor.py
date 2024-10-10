import sutsim
import pytest

def test_temperature_sensor_reads(suts):
    suts["device"].run_for(1)
    
    suts["device"]["temperature_sensor.status"] = 1
    assert suts["device"]["temperature_sensor.status"] == 1
    
    suts["device"]["temperature_sensor.temperature"] = 100.0
    assert suts["device"]["temperature_sensor.temperature"] == 100.0
    
    suts["device"].run_for(25)
    