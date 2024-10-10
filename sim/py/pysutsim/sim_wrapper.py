import sutsim

class SimWrapper:
    def __init__(self, device_map):
        """
        Initialize the SimWrapper with a dictionary of devices and their corresponding firmware paths.
        """
        self.devices = {}
        for device_name, firmware_path in device_map.items():
            # Initialize each device with its firmware path
            sutsim.initSim(device_name, firmware_path)
            self.devices[device_name] = firmware_path

    def __getitem__(self, device_name):
        # Check if the device exists in the initialized list
        if device_name not in self.devices:
            raise KeyError(f"Device '{device_name}' not found.")
        return SimDevice(device_name)


class SimDevice:
    def __init__(self, device_name):
        self.device_name = device_name

    def __getitem__(self, tag):
        full_key = f"{self.device_name}.{tag}"
        return sutsim.getSutData(full_key)

    def __setitem__(self, tag, value):
        full_key = f"{self.device_name}.{tag}"
        sutsim.setSutData(full_key, value)

    def run_once(self):
        sutsim.runTick()
    
    def run_for(self, num_ticks):
        for _ in range(num_ticks):
            self.run_once()
