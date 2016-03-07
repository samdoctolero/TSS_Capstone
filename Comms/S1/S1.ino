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
int busRoute[] = {10};
String prevShelterID = "0005";
String shelterID = "0001"; 
String rawData = "";
int numStop = 0;

//Function Prototypes
//void Send();
//void Shelter2Shelter(String str);
//void Bus2Shelter(String str);
//void Receive();
//void splitData(String str);

String hexToStr();

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
  int check = 0;
  String msg = "";
  
  if (Serial.available())
  { // If data comes in from serial monitor, send it out to XBee
    check = busIn(msg);
    doCheck(check, msg, rawData);
    reset();
  }
  if (XBee.available())
  { // If data comes in from XBee, send it out to serial monitor
    //Serial.write(XBee.read());
    check = processData(msg);
    doCheck(check, msg, rawData);
    reset();
  }
}

int busIn(String &msg)
{
    //Purpose: Emulated a bus passing through a shelter
    decodeMessage("Serial");
    
    if(rawData.length() != 4)
    {
      return 1;
    }

    String bRoute = "";
    int found = 0;
    
    for (int i = 0; i < 2; i++)
    {
      bRoute = getBusRoute(i);
      if (bRoute == rawData.substring(2, 4))
      {
        found = 1;
        break;
      }
    }

    if (found == 0)
    {
        msg = "Not valid bus number.";
        return -1;
    }
    else if (rawData.substring(0, 2) != "b0")
    {
      msg = "Message did not originate from a bus.";
      return -1;
    }
    else
    {
      msg += "b0" + bRoute;
      msg = "Incoming Message from bus: ";
      
      return 0;
    }
}

int processData(String &msg)
{
    //Purpose: Recieve data from a shelter (Xbee) and parse the info
    decodeMessage("XBee");
    
    Serial.println("Incoming message from shelter: " + rawData);
    
    //if(rawData.length() != 10)
    //{
     // return 1;
    //}

    String bRoute = "";
    int found = 0;
    
    for (int i = 0; i < 2; i++)
    {
      bRoute = getBusRoute(i);
      if (bRoute == rawData.substring(4, 6))
      {
        found = 1;
        break;
      }
    }

    if (found == 0)
    {
        msg = "Not valid bus number.";
        return -1;
    }
    
    if(rawData.substring(2,4) == "s0" && rawData.substring(4,6) == bRoute && rawData.substring(8,12) == prevShelterID)
    {
      numStop = (int)strtol(&rawData.substring(6,8)[0],NULL,16); //Convert String HEX to int
      numStop++;

      //Create message to send to other shelters in a new function
      return 0;
    }
    else if(rawData.substring(2,4) != "s0")
    {
      msg = "Parsed data did not originate from shelter.";
      return -1;
    }
    else if(rawData.substring(8,12) != prevShelterID)
    {
      msg = "Data did not originate from a valid shelter source.";
      return -1;
    }
    else
    {
      msg = "ITS AN ERROR! PANIC!";
      return -1;
    }
}

void doCheck (int check, String msg, String data)
{
  if(check == -1)
  {
    Serial.println(msg);
  }
  else if(check == 0)
  {
    //Send to xbee
    send(data);
  }
  else if(check == 1)
  {
    Serial.println("Waiting for end character.");  
  }
  Serial.println();
}

void send(String data)
{
  String sendData = "s0";
  String _numStop = String(numStop, HEX);
  
  if (numStop < 16)
  {
    _numStop = "0" + _numStop;
  }
 
  sendData += data.substring(4,6) + _numStop + shelterID;
  Serial.println("Sending message to shelter: " + sendData);

  XBee.println(sendData + "n");
}

void reset()
{
  rawData = "";
  numStop = 0;
}

String getBusRoute(int i)
{
  String bRoute = "";
  if(busRoute[i] < 15)
  {
    bRoute = "0" + String(busRoute[i], HEX) ;
  }
  else
  {
    bRoute = String(busRoute[i], HEX);
  }
  return bRoute;
}

void decodeMessage(String type)
{
  char t;
  
  if (type == "Serial")
  {   
    while(rawData.length() < 5)
    {
      if (Serial.available())
      {
        t = Serial.read();
        if(t=='n' || t=='N')
        {
          break;
        }
      
        rawData += t;
      }
    }
  }
  else if (type == "XBee")
  {
    while(rawData.length() < 15)
    {
      if (XBee.available())
      {
        t = XBee.read();
        if(t=='n' || t=='N')
        {
          break;
        }
        rawData += t;
      }
    }
  }
}
