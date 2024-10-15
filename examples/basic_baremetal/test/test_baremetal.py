import pytest

def test_baremetal(devices):    
    devices.run_for(10)
