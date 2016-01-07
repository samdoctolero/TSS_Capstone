/*****************************************************************
XBee_Serial_Passthrough.ino

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(3, 2); // RX, TX

//Shelter: S1
//Shelter ID: 0x0001
//Shelter Next ID: 0x0002
//Shelter Bus Route: 0x0A (10)
//Shelter Previous ID: 0x0005

//Global variables:
//Bus to Shelter: b0
int busRoute = 10;
String prevShelterID = "0003";
String shelterID = "0003";

//Function Prototypes
//void Send();
//void Shelter2Shelter(String str);
//void Bus2Shelter(String str);
//void Receive();
//void splitData(String str);


void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  { // If data comes in from serial monitor, send it out to XBee
    busIn();
  }
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
    //Serial.write(XBee.read());
    String data = "";
    if(processData(data) != 0)
    {
      Serial.println(data);
    }
  }
}

void busIn()
{
    //Purpose: Emulated a bus passing through a shelter
    //String rawData = Serial.readString();
    String msg = "";

    if (busRoute != Serial.parseInt())
    {
      Serial.println("Not valid bus number.");
    }
    else
    {
      String busNum_hex = String(busRoute, HEX);
      if (busRoute < 16)
      {
        busNum_hex = "0"+ busNum_hex;
      }
    
      msg += "s0" + busNum_hex + "03" + "0005" + "n";

      Serial.print("Incoming Message from bus: ");
      Serial.println(msg);
      XBee.print(msg);
    }
}

int processData(String &msg)
{
    //Purpose: Recieve data from a shelter (Xbee) and parse the info

    String rawData = "";
    char t = XBee.read();
    while (t != 'n' && XBee.available())
    {
      rawData += t;
      Serial.print(t);
      t = XBee.read();
    }

    if(rawData.length() != 10)
    {
      return -1;
    }

    if(rawData.substring(0,2) == "s0" && rawData.substring(2,4) == String(busRoute, HEX) && rawData.substring(6) == prevShelterID)
    {
      Serial.println("Good");
      return 0;
    }
    else if(rawData.substring(0,2) != "s0")
    {
      msg = "Parsed data did not originate from shelter.";
      return -1;
    }
    else if(rawData.substring(2,4) != String(busRoute, HEX))
    {
      msg = "Not a valid bus route";
      return -1;
    }
    else if(rawData.substring(6) == prevShelterID)
    {
      msg = "Data did not originate from a valid shelter source";
      return -1;
    }
    else
    {
      msg = "ITS AN ERROR! PANIC";
      return -1;
    }
}

