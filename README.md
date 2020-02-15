# Radio-synced LED controllers

## Hardware requirements

* Microcontroller: [Anarduino MiniWireless RFM69-W-915](http://www.anarduino.com/miniwireless/). 
* Programmer: Any **5V** USB-FTDI bridge with the DTR pin exposed (I used SparkFun's [FTDI Basic Breakout](https://www.sparkfun.com/products/9716) while working on it)

## Project setup

1. Install [Visual Studio Code](https://code.visualstudio.com/download)
1. Install the [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension from VSCode's Marketplace (Ctrl+P, then `ext install platformio.platformio-ide`)
1. Restart VSCode, give it time to update itself, then use PlatformIO's "Open Project" to load the project (it will automatically download and install the needed compiler toolchain)
1. Follow any prompts from PlatformIO to ensure that your PC is able to communicate with the AVR programmer
1. Plug the FTDI programmer into the board to be programmed, _then_ connect the programmer to the PC
1. From PlatformIO's sidebar panel, under "Project Tasks", select "Build" to compile, or "Upload" to compile and then program the board. You should see output like this:
```
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [========= ]  92.4% (used 1893 bytes from 2048 bytes)
Flash: [======    ]  59.6% (used 19210 bytes from 32256 bytes)
Configuring upload protocol...
AVAILABLE: arduino
CURRENT: upload_protocol = arduino
Looking for upload port...
Auto-detected: /dev/ttyUSB0
Uploading .pio/build/miniwireless/firmware.hex
```

> #### ⚠️ If you see an error that reads the following:
> ```
> avrdude: stk500_recv(): programmer is not responding
> avrdude: stk500_getsync() attempt 1 of 10: not in sync: resp=0x00
> ```
> Then your programmer is not getting an answer from the chip it's trying to program. Ensure that it's plugged all the way in, **and isn't connected backwards**. _Most_ boards have protection against reverse polarity, including these Anarduino ones, but not all engineers are fond of idiot-proofing things.

