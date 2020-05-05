# Test to reproduce Tango memleak while push_event

The architecture is as following. We have one DS called `DeviceMemLeak` which
exports one device of the `DeviceMemLeak` class with:
* one attribute `attr1` of `DevEncoded` type
* two commands: `Start` and `Stop`

The `Start` command starts a thread which pushes change events on `attr1`
at high rate. The `Stop` command stops that thread.

In order to reproduce the problem:
1. Register in Tango Database one `DeviceMemLeak` DS with instance name `test`
   with one device of `DeviceMemLeak` class, with the following name:
    `test/devicememleak/1`.
    ```console
    tango_admin --add-server DeviceMemLeak/test DeviceMemLeak test/devicememleak/1    
    ```
2. Start DeviceServer:
   ```console
   python3 DeviceMemLeak.py test
   ```
3. Start a trend with the DS process RSS memory (use the correct pid) e.g.:
   ```console
   taurus tpg trend "eval:@psutil.*/Process(<pid>).memory_info().rss"
   ```
4. Start itango3 and execute:
   ```python
   d = DeviceProxy("test/devicememleak/1")
   d.Start()
   ```
# C++ example

In `cpp` folder, you will find a C++ Device server able to push events for attr1 DevEncoded attribute.
This C++ device server does not seem to suffer from this memory leak.
- It provides a `PushEncodedEvent` command to push a change event for `attr1` attribute.
- The `Start` command starts a thread which will push change events for `attr1` attribute.
- The `Stop` command stops the thread.
- You can use the ThreadSleepTimeMs Device property to tune the thread sleeping time between 2 event pushes (default = 1ms).

To compile it, simply generate a Makefile with Pogo from DeviceMemLeak.xmi file and type `make` in the cpp directory.

Here is an example of the compilation commands you could use if you don't want to generate the Makefile with Pogo (you might need to define TANGO_HOME environment variable to point to your Tango install prefix path):

```
g++  -g -D_DEBUG -D_REENTRANT -W -I .  -I../include -I$TANGO_HOME/include/tango -I/usr/local/include  -std=c++11  -Dlinux -c DeviceMemLeak.cpp -o obj/DeviceMemLeak.o
g++  -g -D_DEBUG -D_REENTRANT -W -I .  -I../include -I$TANGO_HOME/include/tango -I/usr/local/include -std=c++11  -Dlinux -c DeviceMemLeakClass.cpp -o obj/DeviceMemLeakClass.o
g++  -g -D_DEBUG -D_REENTRANT -W -I .  -I../include -I$TANGO_HOME/include/tango -I/usr/local/include -std=c++11  -Dlinux -c DeviceMemLeakStateMachine.cpp -o obj/DeviceMemLeakStateMachine.o
g++  -g -D_DEBUG -D_REENTRANT -W -I .  -I../include -I$TANGO_HOME/include/tango -I/usr/local/include -std=c++11  -Dlinux -c ClassFactory.cpp -o obj/ClassFactory.o
g++  -g -D_DEBUG -D_REENTRANT -W -I .  -I../include -I$TANGO_HOME/include/tango -I/usr/local/include -std=c++11  -Dlinux -c main.cpp -o obj/main.o
g++ ./obj/DeviceMemLeak.o ./obj/DeviceMemLeakClass.o ./obj/DeviceMemLeakStateMachine.o   ./obj/ClassFactory.o ./obj/main.o -L$TANGO_HOME/lib -L/usr/local/lib -ltango -lomniDynamic4 -lCOS4 -lomniORB4 -lomnithread -lzmq -ldl -lpthread -lstdc++ -o bin/DeviceMemLeak
```

Of course, you might need to adapt these compilation commands to fit your ZMQ, omniORB and Tango installation.