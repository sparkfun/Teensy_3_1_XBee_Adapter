# Getting Started With The XBee And Teensy 3.1

## Introduction
When microcontroller power in a tight space is required, the Teensy 3.1/LC is a good place to get it.  When a decently ranged no-frills serial link is required, the XBee is the go-to.  The Teensy to XBee adapter board joins the two with easy, but how easy is it?  This tutorial will demonstrate the basics of using the adapter board.

This tutorial demonstrates:
* How to initialize Teensy 3.1/LC HW serial
* How to initialize Teensy 3.1 SW serial using softwareSerialAlt library
* The basics of packetizing data.
* How to make a simple controller that effects something far away
* How to build a wireless game controller for a computer.

### Materials Used

You will need a few components and tools to follow along with this tutorial. Here is what you will need:

-----------------------------------WISHLIST GOES HERE-----------------------------------

If you do not have specifically a 3.3V Arduino Pro, there are a number of ways to complete the walkthrough. In general, you will need:

* **Arduino or other microcontroller** -- You will need something that is capable of I<sup>2</sup>C and communicating back to the computer (e.g. [serial communications](tutorials/8)). The microcontroller needs to have a **3.3V I/O voltage** or you will have to use a level shifter. We are using the [3.3V Arduino Pro](https://www.sparkfun.com/products/10914), but the [3.3V Arduino Pro Mini](https://www.sparkfun.com/products/11114) would work as well.
* **Teensy 3.1/LC** -- If you are using a 5V Arduino, like the [Uno](https://www.sparkfun.com/products/11021) or [RedBoard](https://www.sparkfun.com/products/12757), you will need to use a level shifter, such as the [bi-directional logic level converter](https://www.sparkfun.com/products/12009).
* **Connectors** -- You will need to interface your microcontroller with the breakout board. [Male headers](https://www.sparkfun.com/products/116) are perfect if you're using a [breadboard](https://www.sparkfun.com/products/11026). Another option is to use [wire](https://www.sparkfun.com/products/11375) to connect the breakout board directly to the microcontroller.
* **Soldering tools** -- After you've picked a connector, you will need to solder it to the breakout board. A [simple soldering iron](https://www.sparkfun.com/products/9507) and some [solder](https://www.sparkfun.com/products/9163) should be all you need.

### Recommended Reading

Before getting started, there are a few concepts that you should be familiar with. If you haven't used a Teensy or XBee before, read these tutorials before continuing:

* [Teensy Quickstart](http://www.pjrc.com/teensy/first_use.html) - External link to PJRC, first powering of a Teensy
* [Teensyduino Software](http://www.pjrc.com/teensy/teensyduino.html) - External link to PJRC, using the Teensy with Arduino software
* [Exploring XBees and XCTU](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu) - Guide to configuring the XBees using the XBee tool XCTU
* [XBee Buying Guide](https://www.sparkfun.com/pages/xbee_guide) - Shows various XBee models including current consumption
use an Arduino to control the APDS-9960
* [Serial Terminal Basics](https://learn.sparkfun.com/tutorials/terminal-basics) - Lots of information about serial.  If you've only ever used the Arduino Serial monitor (or no terminal at all), this is a good resource.  It shows how to get serial terminals working on Mac, Linux, and Windows.


### Tools or materials required

* Soldering iron and flux core solder
* Spare wire
* X-acto or knife for cutting traces (possibly)
* Breadboard

### Software required
* Arduino IDE
* Teensyduino add-on
* AltSoftSerial library
* X-CTU

## Hardware Overview
Look at this picture!  *look at it...*

## Assembly
The basic methodology for developing with the Teensy and XBee goes like this:
* Determine how to power
* Connect the hardware
* Configure the XBees
* Establish serial over XBee (test all systems)
* Build and test the actual project

### Determine how the system is going to be powered
The XBee requires around 3.3v to operate depending on model.  The Teensy has an on-board regulator that outputs 3.3v which is perfect, but only for lower power radios.

Photo

*Powering from the Teensy's internal regulator*

This is the default configuration.  The internal regulator can supply about 100mA of current for 3.3v use, including what is consumed by the Teensy and things on the 3.3v rail. XBees up to 2mW (non-"pro" models) consume up to 40mA, so if you have a basic XBee this is probably the route for you.  Supply 3.7 to 5.5v (or USB power) and you're good to go.

Photo

*Powering the XBee from an external 3.3v regulator*

If you have a higher powered XBee, or more than 100mA of load on your 3.3v rail, you'll need to disconnect the XBee from the internal regulator and supply 3.3v from somewhere else.  A [Breadboard Power Supply Stick](https://www.sparkfun.com/products/13157) is a possible power source for this application.

In this case, switch the TNSY-EXT jumper to EXT, short the VIN-EXT_PWR jumper, and cut the trace between the Teensy's USB PWR jumper.  Now both the Teensy and XBee are powered from the ext power pins, so you'll need to provide power and plug in the USB if you want to reprogramming the device.

### Now that powering has been figured out, it's time to connect the teensy to the XBee.
The XBee sockets straight into the adapter.  It's good to go!
Neither the Teensy nor the adapter has have headers.  Here are some options for connecting the two.
* Solder headers into the teensy, and pins into the adapter (or visa-versa) - This is a good option because the two are easily seperable.  Note: the pair are quite thick in this configuration and the headers are difficult to remove.  If you *know* you'll be moving to an alternate connection scheme, it may be a good idea to test things with short flexible wires before locking things down.
* Solder short lengths of wire between the pins you wish to connect - this is a good idea if you know you'll be moving to some more permenent solution.  Also, only solder wires where you need, such as power, ground, TX, RX, and miscelanious GPIO.
* Solder the two boards directly together without pins or wires at all - This is an advanced technique but results in a very thin board stack.  Don't do this until you are 100% confidant in your design!  Verify first, then solder together.  Seperating the boards afterwards can destroy them.

### Connect Periphery Equipment
Use the outer holes to connect all manor of switches and sensors that you wish to read from the Teensy.  This tutorial makes a controller, so buttons and knobs are connected as shown in this diagram.

*Fritzing diagram showing wiring of the buttons for this example*

### Configure the XBees
The XBees are shipped with a default configuration (see XBee documentation).  Even if they work out of the box, you'll be using the default IDs and will be suseptable to unseen XBees interfering with your system (because some other designer had the similar thought, "I'm the only one here, why not use the default IDs.") Also, you can change other more advanced features once you're familiar with the concepts.

**The parameters used for this demo**
* ID/PAN ID = A5F1 - This can be any 16 bit hex value used to identify your network.  Make sure it is the same for both radios and unique in your area.  A5F1 was randomly chosen for this guide.  You can choose any ID for your network.
* Data rate = 9600
* Parity = N
* All others at factory default

**Configuring XBees with USB based explorers**

* Socket an XBee into the explorer matching the silkscreen orientation
* Plug the explorer into the USB port
* Open X-CTU
* Select your explorer's serial port
* Querry the XBee to make sure the drivers are working
* Read the configuration from the XBee
* Modify the parameters
* Write the new configuration to the XBee


Repeat this process so that both XBees have the new configuration.


### Power the System!
Apply (HOW MUCH VOLTAG?) to the system.  Does the (WHAT TURNS ON?)  Try running the blink sketch to determine if the Teensy is really powered and ready to recieve firmware.

## Firmware
### Theory
### Working with your serial ports
Difficulties arise while working with wireless devices because more than one serial port is in use.  Where Arduino allows you to simply load the serial monitor to talk to your code, be extra careful remembering which ports what device and which terminal are using.

For this example the computer is one party in the communication by using the XBee explorer.  Get this port open and communicating to the XBee explorer, then leave it alone.  It ushers bytes you type into it into the air, and prints whatever comes into it's antenna to your screen.  When the system is fully functional, this terminal will tell you what buttons are being pressed.

The Arduino serial monitor connects to the target over the USB cable.  This serial link isn't going to the XBee and won't be connected to anything when the controller is fully mobile, so may not have much use but it's important to remember that it exists, and to not confuse it with the other serial ports.  Actually, it can be usefull to get debugging information from your program while working with it.

The trickest serial link in this project is the one that goes from the Teensy to the XBee because we have little information about it.  If you have access to an oscilliscope the link can be probed, but in lieu of that all we get is a little blinking light we become thankful for.

### Test your serial and XBee configuration
*Two sketches are provided to ease bringing the XBees online.  They pass data between the XBee and the serial monitor using the HW UART or the SW UART 'AltSoftSerial'*

**teensy_3_1_xbee_UART1_example**

Set the adapter's serial switch to UART1.  Then, load and run the example.  Open the serial monitor.  Text entered in the serial monitor will be passed to the XBee, and come out the X-CTU (or other, I use Tera Term) serial monitor.  Typing in that terminal will send the text back to the Arduino serial monitor.  This tests the HW UART and XBee configurations

**teensy_3_1_xbee_SUART_example**

This sketch works much like the UART1 example but with the AltSoftSerial library, leaving the HW UART free to connect to other resources.  Set the adapter's switch to UART1 and run the sketch.  Text should be passed between the two serial terminals.

### Running the demo sketches

**teensy_3_1_xbee_buttons_and_leds_example**

This sketch demonstrates bi-directional communication and shows off operation that is more than just data echo.

**Connections**

* Attach buttons to pins 14-17 of the Teensy, and to ground.  The pins are pulled up inside the teensy and will float high until a button is depressed.
* Attach LEDs from pins 14-21 of the Teensy, through a current limiting resistor, to ground.  It's not so important to have all 8, 2 or 3 is enough to demonstrate the effect.

**Each time the loop() runs, the sketch**

* Converts button presses to an ascii repersentation
* Prints the button states to the Arduino serial monitor
* Transmits the button states as a series of ascii characters
* Checks for received data from the XBee.  If a number 1-8 is received, the associated LED on pins 14-21 is illuminated.  If any other character is received, all 8 LEDs are are switched off.

**teensy_3_1_xbee_gamepad_controller**

This sketch is used to create a NES style 8 button controller with D-pad, A, B, Start and Select.  It works similarly to the previous example in that it builds a packet of ascii characters that depict the state of the button and transmits them out the XBee.  It has an upgraded.  It's different in that the LED feedback and Arduino serial manager code has been removed, and button state information is now tracked.  This sketch checks the button states as fast as possible, and only sends an ascii packet out the XBee if the state of the buttons has changed.  This allows the XBee to not consume superflurious power if the controller is on battery power.

**Connections**

* Pin 2: Start button
* Pin 3: Select button
* Pin 4: B button
* Pin 5: A button
* Pin 6: Up button
* Pin 7: Down button
* Pin 8: Left button
* Pin 9: Right button
* Set switch to UART1

**teensy_3_1_xbee_gamepad_receiver**

This sketch causes the Teensy to behave like a USB keyboard.  It parses the data from the XBee and 'presses a key' in corrispondence with what key is being depressed on the controller.  When a controller button is pressed and held, the teensy acts like a keyboard with a key held down.  This allows the teensy to interface to a ROM emulator or game that has map-able keyboard input.

**Configuration**

* Set switch to UART1
* In the Arduino IDE, Select Tools -> USB type: -> Keyboard + Mouse + Joystick

After the sketch uploads your computer may have to go through a new device like detection.  When it is done, open a text editor and use the controller to send some XBee data to the receiver.  If everything is correct, numbers should be typed into the text editor.

This sketch was tested on windows 7 and mac OS 10.10.

## Conclusion

## Resources and Going Further

Going Further/Further Reading

