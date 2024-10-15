from sutsim_fixtures import devices
import pytest
import os

@pytest.fixture
def device_map():
    # Map simulated device instances to their shared object firmware paths
    return {
        "dev1": os.path.join(os.path.dirname(__file__), 'sim_artifacts', 'libfirmware.so'),
    }
