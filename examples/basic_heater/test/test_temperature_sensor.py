import pytest

def test_temperature_sensor_reads(devices):    
    devices["thermal_ecu"]["temperature_sensor.status"] = 1
    assert devices["thermal_ecu"]["temperature_sensor.status"] == 1
    devices.run_for(5)
    
    devices["thermal_ecu"]["temperature_sensor.temperature"] = 5.0
    devices.run_for(20)
    assert devices["thermal_ecu"]["pwm.freq.ch1"] == 1000
    
    devices["thermal_ecu"]["temperature_sensor.temperature"] = 55.0
    devices.run_for(20)
    assert devices["thermal_ecu"]["pwm.freq.ch1"] == 0    
