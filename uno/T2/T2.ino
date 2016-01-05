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
String BusID = "";
String BusRoute = "";
String str = "";
bool msgRx = false;

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
  //if (Serial.available())
  //{ // If data comes in from serial monitor, send it out to XBee
  //  XBee.write(Serial.read());
  //}
  
  /*
   * Shelter to Shelter Message Format:
   * SIxxxxRxxxN
   * 
   * Bus to Shelter Message Format:
   * BIxxxxRxxxN
  */
  if(XBee.available())
  {
    char t;
    do
    {
      t = XBee.read();
      if (msgRx == false){msgRx = true;}
      str = str + t;
    }
    while(t!= 'N');
    if(msgRx == true)
    {
      //Choose whether it is a S-S or B-S
      if(str[0] == 'S'){Serial.println("Shelter to Shelter");}
      else if(str[0] == 'B'){Serial.println("Bus to Shelter");}
      else{Serial.println("Error. Not a correct message");}
      Serial.println(str);
      msgRx = false;
      str = "";
    }
   }
}

void ShelterToShelter()
{
  char t = XBee.read(); //read 'I' character
  Serial.println(t);
  while(XBee.available())
  {
    t = XBee.read();
    Serial.println(t);
    if (t == 'N'){break;}
    if(t == 'R')
    {
      BusRoute = BusRoute + t;
    }
    else
    {
       BusID = BusID + t;
    }
  }
  Serial.print("Bus ID: ");Serial.println(BusID);BusID = "";
  Serial.print("Bus Route: ");Serial.println(BusRoute);BusRoute = "";
}

void BusToShelter()
{
  
}

