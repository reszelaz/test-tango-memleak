import time
import pickle
import threading

import tango
from tango.server import Device, attribute, command


class JobThread(threading.Thread):

    def __init__(self, dev=None):
        super(JobThread, self).__init__()
        self.dev = dev

    def run(self):
        i = 0
        while True:
            if self.dev._stopped:
                break
            print('In job; {} iteration'.format(i))
            self.dev.push_change_event("attr1",
                                  self.dev._fmt,
                                  self.dev._value,
                                  time.time(),
                                  tango.AttrQuality.ATTR_VALID)
            time.sleep(0.001)
            i += 1


class DeviceMemLeak(Device):

    attr1 = attribute(dtype=tango.CmdArgType.DevEncoded)
    
    def init_device(self):
        self.info_stream('In Python init_device method')
        self.set_state(tango.DevState.ON)
        self.set_change_event("attr1", True, False)
        self._stopped = False
        self._value = pickle.dumps(dict(index=0, value=1.23))
        self._fmt = "pickle"

    def read_attr1(self):
        return self._fmt, self._value

    @command
    def Start(self):
        self.info_stream('Starting...')
        self._stopped = False
        self._job_thread = JobThread(self)
        self._job_thread.start()

    @command
    def Stop(self):
        self.info_stream('Stopping...')
        self._stopped = True
        self._job_thread.join()


if __name__ == "__main__":
    DeviceMemLeak.run_server()