import sutsim

class SimDeviceManager:
    def __init__(self, device_map):
        self.devices = {}
        
        for device_name, firmware_path in device_map.items():
            sutsim.initSim(device_name, firmware_path)
            self.devices[device_name] = firmware_path

    def __getitem__(self, device_name):
        if device_name not in self.devices:
            raise KeyError(f"Device '{device_name}' not found.")
        return SimDevice(device_name)
    
    def run_once(self):
        sutsim.runTick()
    
    def run_for(self, num_ticks):
        for _ in range(num_ticks):
            sutsim.runTick()


class SimDevice:
    def __init__(self, device_name):
        self.device_name = device_name

    def __getitem__(self, tag):
        full_key = f"{self.device_name}.{tag}"
        return sutsim.getSutData(full_key)

    def __setitem__(self, tag, value):
        full_key = f"{self.device_name}.{tag}"
        sutsim.setSutData(full_key, value)
