import sutsim
import pytest
from sutsim_device import SimDeviceManager

@pytest.fixture
def devices(device_map):
    yield SimDeviceManager(device_map)
