#include <AltSoftSerial.h>
//To use this example you will need to have the following connections:
//  4 buttons connected to pins 14 through 17, normally open, short to ground.
//  8 LEDs connected to pins 4 through 11, each with their own current limiting resistor.
//  The sketch is intended to have leds with a common ground, though using a common power
//  will work invertedly.
//
//You will also need:
//  A Teensy 3.1 to XBee adapter board with XBee
//  A 2nd XBee connected to serial terminal (USB dongle with Tera Term for example)
//  The S-UART / UART1 switch set to S-UART for a software UART using the altSoftSerial library
//  
//Load the sketch and press the buttons.  In the serial terminal the '0's change to '1's.
//Press 1-8 on the keyboard in the terminal window.  The LEDs will illuminate.  Press enter or
//any other key to clear the LEDs.

//Marshall @ SparkFun Electronics, 2015.
  
  
// Define pin locations
int upleftButton = 14;
int uprightButton = 15;
int downleftButton = 16;
int downrightButton = 17;
int led1Pin = 4;
int led2Pin = 5;
int led3Pin = 6;
int led4Pin = 7;
int led5Pin = 8;
int led6Pin = 9;
int led7Pin = 10;
int led8Pin = 11;

AltSoftSerial altSerial;



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  altSerial.begin(9600);

  // Setup the pin directions
  pinMode(upleftButton, INPUT_PULLUP);
  pinMode(uprightButton, INPUT_PULLUP);
  pinMode(downleftButton, INPUT_PULLUP);
  pinMode(downrightButton, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  pinMode(led8Pin, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  //*******************************************************************//
  // Transmitting.  This section reads button states and builds a packet
  // that is shipped over the airwaves.  The basic packet has a start
  // char of ~, 9 user bytes, and terminates with a carriage return
  // "~000000000\r"
  
  int buttonState;

  //Write the tilde to the XBee.  This signifies start of packet
  altSerial.write('~');

  // read the input pin:
  buttonState = digitalRead(upleftButton);
  Serial.print("up left is ");
  // print out the state of the button to the serial monitor:
  Serial.println(buttonState);
  buttonState ^= 0x01;
  // write the value to the XBee packet
  altSerial.print(buttonState);

  // read the input pin:
  buttonState = digitalRead(uprightButton);
  // print out the state of the button to the serial monitor:
  Serial.print("up right is ");
  Serial.println(buttonState);
  buttonState ^= 0x01;
  // write the value to the XBee packet
  altSerial.print(buttonState);

  // read the input pin:
  buttonState = digitalRead(downleftButton);
  // print out the state of the button to the serial monitor:
  Serial.print("down left is ");
  Serial.println(buttonState);
  buttonState ^= 0x01;
  // write the value to the XBee packet
  altSerial.print(buttonState);

  // read the input pin:
  buttonState = digitalRead(downrightButton);
  // print out the state of the button to the serial monitor:
  Serial.print("down right is ");
  Serial.println(buttonState);
  buttonState ^= 0x01;
  // write the value to the XBee packet
  altSerial.print(buttonState);

  // fill the rest of the packet with zeros
  altSerial.print('0');
  altSerial.print('0');
  altSerial.print('0');
  altSerial.print('0');
  altSerial.print('0');
  // Proved an end of line char for the interpreter to pick up on
  altSerial.write(0x0D);

  //*******************************************************************//
  // Receiving.  This section check for new serial data and turns on an
  // LED that corresponds to a number key entered.  All other characters
  // including return, LF, CR, etc. cause all LEDs to be turned off.
  if (altSerial.available())
  {
    char c;
    c = altSerial.read();
    switch(c)
    {
    case '1':
      digitalWrite(4, 1);
      break;
    case '2':
      digitalWrite(5, 1);
      break;
    case '3':
      digitalWrite(6, 1);
      break;
    case '4':
      digitalWrite(7, 1);
      break;
    case '5':
      digitalWrite(8, 1);
      break;
    case '6':
      digitalWrite(9, 1);
      break;
    case '7':
      digitalWrite(10, 1);
      break;
    case '8':
      digitalWrite(11, 1);
      break;
    default:
      //Clear all pins on other keys
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
      digitalWrite(11, 0);
      break;

    }

  }


  delay(100);        // delay in between reads for stability
}





