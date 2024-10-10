from sutsim_fixtures import suts
import pytest
import os

@pytest.fixture
def device_map():
    # Dictionary to map device names to their firmware paths
    return {
        "device": os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so'),
        # Add more devices and their respective firmware paths here if needed
    }
