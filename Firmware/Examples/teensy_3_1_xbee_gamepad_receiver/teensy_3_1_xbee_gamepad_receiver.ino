//Buttons to USB Keyboard Example
//
//You must select Keyboard from the "Tools > USB Type" menu
//
//This code decodes packets from a XBee gamepad controller
//sketch.  It behaves like a keyboard in that pressing and holding
//a button will make repeated characters appear.  It uses the
//Teensy functions Keyboard.press() and Keyboard.release() to do
//this.
//
//To test, get the gamepad running, open a text editor on your
//computer and press some game buttons.  Try holding one- the
//associated character should start repeating like it would if
//you held down a real keyboard key.

#define PACKET_LENGTH 10
#define START_SYMBOL '~'

char lastchar;
char packet[PACKET_LENGTH];
char lastPacket[PACKET_LENGTH];
char packetPending = 0;

char packet_ptr;

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

void setup()
{
  Serial1.begin(9600);
  pinMode(13, OUTPUT);
  
}

void loop()
{
  if (Serial1.available())
  {
    lastchar = Serial1.read();
    //look for packet start (START_SYMBOL)
    if( lastchar == START_SYMBOL )
    {
      //Flag that the packet needs to be serviced
      packetPending = 1;
      
      //Fill packet with null, reset the pointer
      for( int i = 0; i < PACKET_LENGTH; i++ )
      {
        packet[i] = 0;
      }
      //write the start char
      packet[0] = START_SYMBOL;
      //reset the pointer
      packet_ptr = 1;
    }
    else
    if( ( packet_ptr < PACKET_LENGTH ) && (packet_ptr > 0) )//check for room in the packet, and that the start char has been seen
    {
      //put the char in the packet
      packet[packet_ptr] = lastchar;
      //advance the pointer
      packet_ptr++;
      //turn on LED
    }
    else
    {
      //Just overwrite to the last position
      packet[PACKET_LENGTH - 1] = lastchar;
    }
  }
  
  //if the packet is full and the last char is LF or CR, *do something here*
  if((packetPending == 1) && ((packet_ptr == PACKET_LENGTH) && ((packet[PACKET_LENGTH - 1] == 0x0A) || (packet[PACKET_LENGTH - 1] == 0x0D))) )
  {
    digitalWrite(13, digitalRead(13)^1);
    //check for new data
    packetPending = 0;
    for(int k = 0; k < PACKET_LENGTH; k++)
    {
       if(packet[k] != lastPacket[k])
      {
        lastPacket[k] = packet[k];
        if(packet[k] == '1')
        {
          //Do off things
          Keyboard.release(48 + k);
        }
        if(packet[k] == '0')
        {
          //Do on things
          Keyboard.press(48 + k);
        }
      } 
    }
  }
  
}

