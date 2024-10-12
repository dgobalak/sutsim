import pytest

def test_temperature_sensor_reads(devices):    
    devices["thermal_ecu"]["temperature_sensor.status"] = 1
    assert devices["thermal_ecu"]["temperature_sensor.status"] == 1
    
    devices["thermal_ecu"]["temperature_sensor.temperature"] = 100.0
    assert devices["thermal_ecu"]["temperature_sensor.temperature"] == 100.0
    
    devices.run_for(25)
    