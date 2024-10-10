import sutsim
import pytest
from sim_wrapper import SimWrapper

@pytest.fixture
def suts(device_map):
    """
    Fixture to set up the simulator with the provided device map.
    """
    return SimWrapper(device_map)
