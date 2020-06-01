#include <AltSoftSerial.h>
//Serial test using the software uart on pins 20/21.
//Connect an XBee and Teensy 3.1 to the adapter board
//Connect an XBee to a serial terminal of your choice (USB dongle for example)
//
//Characters sent out the XBee terminal go:
// Onto the airwaves -> into S-UART RX -> out the serial monitor
//
//Characters sent out the serial monitor go:
// Out the S-UART TX pin -> onto the airwaves -> out the SBee serial terminal
//
//Be sure to select S-UART on the adapter board's switch for HW serial
//
//Marshall@SparkFun Electronics, 2015
  
  
AltSoftSerial altSerial;

void setup() {
  // initialize serial communication at 9600 bits per second:
  //Begin serial monitor port
  Serial.begin(9600);
  //Begin SW UART serial
  altSerial.begin(9600);

}

// the loop routine runs over and over again forever:
void loop() {
  // Take data received from the serial monitor and pass it to the HW UART
  if(Serial.available())
  {
    altSerial.write(Serial.read());
  }

  // Take data received from the HW UART and pass it to the serial monitor
  if(altSerial.available())
  {
    Serial.write(altSerial.read());
  }
  
  //Wait to reduce serial load
  delay(5);
}





