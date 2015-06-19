//This example is used to make an 8 button (NES like) remote game pad.  It tracks button-down
//and button-up information so that the games are playable.  Without tracking that stuff,
//your character would only have one level of jump.
//
//The other end of the link behaves like a USB keyboard and 'presses keys' for the emulator
//
//To use this example you will need to have the following connections:
//  4 buttons connected to pins 14 through 17, normally open, short to ground.
//  8 LEDs connected to pins 4 through 11, each with their own current limiting resistor
//  An Teensy 3.1 to XBee adapter board with XBee
//  An 2nd XBee connected to serial terminal (USB dongle with Tera Term for example)
//  The S-UART / UART1 switch set to S-UART for a software UART using the altSoftSerial library
//  
//  Load the sketch and press the buttons.  In the serial terminal the '0's change to '1's.
//  Press 1-8 on the keyboard in the terminal window.  The LEDs will illuminate.  Press enter or
//  any other key to clear the LEDs.

//Marshall@SparkFun Electronics, 2015


// Define pin locations
int led = 13;
int padLeftPin = 8;
int padRightPin = 9;
int padUpPin = 6;
int padDownPin = 7;
int btnStartPin = 2;
int btnSelectPin = 3;
int btnAPin = 5;
int btnBPin = 4;

  int newState = 1;
  int padLeftState = 1;
  int padRightState = 1;
  int padUpState = 1;
  int padDownState = 1;
  int btnStartState = 1;
  int btnSelectState = 1;
  int btnAState = 1;
  int btnBState = 1;
  int previousPadLeftState = 1;
  int previousPadRightState = 1;
  int previousPadUpState = 1;
  int previousPadDownState = 1;
  int previousBtnStartState = 1;
  int previousBtnSelectState = 1;
  int previousBtnAState = 1;
  int previousBtnBState = 1;
  
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial1.begin(9600);

  // Setup the pin directions
  pinMode(led, OUTPUT);     
  pinMode(padLeftPin, INPUT_PULLUP);
  pinMode(padRightPin, INPUT_PULLUP);
  pinMode(padUpPin, INPUT_PULLUP);
  pinMode(padDownPin, INPUT_PULLUP);
  pinMode(btnStartPin, INPUT_PULLUP);
  pinMode(btnSelectPin, INPUT_PULLUP);
  pinMode(btnAPin, INPUT_PULLUP);
  pinMode(btnBPin, INPUT_PULLUP);

}

// the loop routine runs over and over again forever:
void loop()
{
  //*******************************************************************//
  // Transmitting.  This section reads button states and builds a packet
  // that is shipped over the airwaves.  The basic packet has a start
  // char of ~, 9 user bytes, and terminates with a carriage return
  // "~000000000\r"

  //Get the states

  padLeftState = digitalRead(padLeftPin);
  if(previousPadLeftState != padLeftState)
  {
    previousPadLeftState = padLeftState;
    newState = 1;
  }
  padRightState = digitalRead(padRightPin);
  if(previousPadRightState != padRightState)
  {
    previousPadRightState = padRightState;
    newState = 1;
  }
  padUpState = digitalRead(padUpPin);
  if(previousPadUpState != padUpState)
  {
    previousPadUpState = padUpState;
    newState = 1;
  }
  padDownState = digitalRead(padDownPin);
  if(previousPadDownState != padDownState)
  {
    previousPadDownState = padDownState;
    newState = 1;
  }
  btnStartState = digitalRead(btnSelectPin);
  if(previousBtnStartState != btnStartState)
  {
    previousBtnStartState = btnStartState;
    newState = 1;
  }
  btnSelectState = digitalRead(btnStartPin);
  if(previousBtnSelectState != btnSelectState)
  {
    previousBtnSelectState = btnSelectState;
    newState = 1;
  }
  btnAState = digitalRead(btnAPin);
  if(previousBtnAState != btnAState)
  {
    previousBtnAState = btnAState;
    newState = 1;
  }
  btnBState = digitalRead(btnBPin);
  if(previousBtnBState != btnBState)
  {
    previousBtnBState = btnBState;
    newState = 1;
  }

  if( newState == 1 )
  {
    //Print the packet
    //Write the tilde to the XBee.  This signifies start of packet
    Serial1.write('~');

    Serial1.print(padLeftState);
    Serial1.print(padRightState);
    Serial1.print(padUpState);
    Serial1.print(padDownState);
    Serial1.print(btnStartState);
    Serial1.print(btnSelectState);
    Serial1.print(btnBState);
    Serial1.print(btnAState);

    // fill the rest of the packet with zeros
    Serial1.print('0');


    // Provide an end of line char for the interpreter to pick up on
    Serial1.write(0x0D);	 

    //Clear tne new state
    newState = 0; 
  }




  delay(10);        // delay in between reads for stability
}







