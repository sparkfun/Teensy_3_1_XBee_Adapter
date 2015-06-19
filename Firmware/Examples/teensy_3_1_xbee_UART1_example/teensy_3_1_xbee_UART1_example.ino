//Serial test using the hardware uart on pins 0/1 (UART1).
//Connect an XBee and Teensy 3.1 to the adapter board
//Connect an XBee to a serial terminal of your choice (USB dongle for example)
//
//Characters sent out the XBee terminal go:
// Onto the airwaves -> into UART1 RX -> out the serial monitor
//
//Characters sent out the serial monitor go:
// Out the UART1 TX pin -> onto the airwaves -> out the SBee serial terminal
//
//Be sure to select UART1 on the adapter board's switch for HW serial
//
//Marshall@SparkFun Electronics, 2015



void setup()
{
  //Begin serial monitor port
  Serial.begin(9600);
  //Begin HW serial
  Serial1.begin(9600);

}

void loop()
{
  // Take data received from the serial monitor and pass it to the HW UART
  if(Serial.available())
  {
    Serial1.print(Serial.read(), BYTE);
  }

  // Take data received from the HW UART and pass it to the serial monitor
  if(Serial1.available())
  {
    Serial.print(Serial1.read(), BYTE);
  }
  
  //Wait to reduce serial load
  delay(5);
}

