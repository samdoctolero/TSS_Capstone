//Macros::
//#define SEND_TO_XBEE 'X';
//#define SEND_TO_PI 'P';
#include <SoftwareSerial.h>

#define RX_PIN  3 
#define TX_PIN  2

//Structures
struct Bus
{
  int Route;
  int NumOfStops;
  Bus * next;
};

struct ShelterNode
{
  String ID;
  ShelterNode * next;  
};
//Global Variables
SoftwareSerial XBee(RX_PIN,TX_PIN);
Bus * bus;
ShelterNode * prevShelter;
String myID;

//Functions:
void ShowData()
{
  //Serial.println("Showing data");
  Bus * b = bus;
  while(b != NULL)
  {
    Serial.print("Bus Route: ");Serial.println(b->Route);
    b = b->next;  
  }  

  ShelterNode * s = prevShelter;
  while(s != NULL)
  {
    Serial.print("Shelter ID: ");Serial.println(s->ID);
    s = s->next;  
  }

  Serial.print("My ID: ");Serial.println(myID);
}
void StoreToShelterInfo(String ID)
{
  ShelterNode * temp = new ShelterNode;
  temp->ID = ID;
  temp->next = NULL;
  if(prevShelter == NULL)
  {
    prevShelter = temp;
    return;
  }
  //look for the end of the list and store there
  ShelterNode * hold = prevShelter;
  while(hold->next != NULL)
  {
     hold = hold->next;
  }
  hold->next = temp;
}
void StoreToBusInfo(int num)
{
  Bus * temp =  new Bus;
  temp->Route = num;
  temp->NumOfStops = 0;
  temp->next = NULL;
  //look for the end of the list and store there
  if(bus == NULL)
  {
    bus = temp;
    return;
  }
  Bus * hold = bus;
  while(hold->next != NULL)
  {
    hold = hold->next;
  }
  hold->next = temp;
}

void InitializeGlobalVariables()
{
  while(true)
  {
    if(Serial.available()> 0)
    { break;}
  }
  //Serial.println("Broken out of the loop");
        //delay(1000);
        //The data stream will come in a huge list
        //Data format: 
        // SRxxxRxxxRxxxPxxxxPxxxxPxxxxMxxxxX
        //R = bus routes
        //P = previous shelter IDs to accept
        //M = this shelter's ID
        //S = starting character
        //X = ending character
        //Always 3 characters every after R and 4 characters every after P and M
        String rawData = Serial.readString();
        if(rawData[0] != 'S')
        {
          Serial.println('-');
          return;  
        }
        //Split the data into the correct pieces
        //Start with bus routes;
        for(int i = 1;i < rawData.length()-1;i++)
        {
          if(rawData[i] == 'R')
          {
            String substr = rawData.substring(i+1,i+4);
            int num = substr.toInt();
            StoreToBusInfo(num);
          }
          if(rawData[i] == 'P')
          {
            String id = rawData.substring(i+1,i+5);
            StoreToShelterInfo(id);
          }
          if(rawData[i] == 'M')
          {
             myID = rawData.substring(i+1,i+5);
          }
        } 
        Serial.println("+++"); 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  InitializeGlobalVariables();
  XBee.begin(9600);
  delay(1);
  digitalWrite(13,LOW);
  //Serial.flush();
  //ShowData(); //Test to see if the data grabbed are correct
}

void loop() 
{
   //Raspberry pi will not do the communication algorithm.
   //It will merely display the information

   //Local xbee will grab and transmit data
   //When we get data from xbee, process it and send it to the other xbees,
   //then send the processed data to the Pi
   /*
   if (XBee.available()>0)
   {
     int route = 0;
     int num = 0;
     if(XBeeReceived(route,num))
     {
        SendToXbee(route,num);
        SendToPi(route,num);
     }
   }
   */
   Serial.println("Hello World");
   delay(1);
}
bool XBeeReceived(int &route, int &num)
{
  //XBee data received format:
  //
  String rawData = "";
  while(XBee.available() > 0)
  {
    char t = XBee.read();
    rawData += t;
  }
  if(rawData[0] != 'S')
  {
    //If message has the wrong starting byte then do NOT send anything
    return false;  
  }
  //Extract the message
  
}

void SendToXbee(int route, int num)
{
  
}

void SendToPi(int route, int stopsAway)
{
  //Data format to send:
  //AxxxBxxxN
  //A = starting data string
  //First three x's are for the bus route
  //B = separate bus route and number of stops away
  //Second set of x's are for number of stops away
  //N = end of stream
  //------------------------------------------------
  //Start of algorithm:
  /*
  Bus * b = bus;
  while(b->Route != route)
  {
    b = b->next;  
  }
  */
  String bRoute = "";
  String nStops = "";
  if(route < 10)
  {
    bRoute = "00";
  }
  else//(route >= 10 && route < 100)
  {
    bRoute = "0";  
  }

  if(stopsAway < 10)
  {
    nStops = "0";
  }

  bRoute += route;
  nStops += stopsAway;
  String msg = "A" + bRoute + "B" + nStops + "N";
  Serial.println(msg);
}

