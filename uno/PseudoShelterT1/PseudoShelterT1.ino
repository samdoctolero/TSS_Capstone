#include <SoftwareSerial.h>

//Macros
#define THIS_ID_A 0x00
#define THIS_ID_B 0xFF
#define _S 'a' //Shelter to shelter character
#define _B 'b' //Bus to shelter character
#define NUMHEXDATA 14

//Global variables:
SoftwareSerial XBee(3,2); 
uint8_t busIDa = 0x00;
uint8_t busIDb = 0x00;
uint8_t busRoute = 0x00;
uint8_t numStops = 0x00;
uint8_t prevShelterIDa = 0x00;
uint8_t prevShelterIDb = 0x00;

//Function Prototypes
void Send();
void Shelter2Shelter(String str);
void Bus2Shelter(String str);
void Receive();
void splitData(String str);
//String hexTostring(String data);

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(XBee.available()){Receive();}
}

void Receive(){
  int hexCount = 0;
  String hexData = "";
  //Format: 0x#######d
  while(hexCount <= NUMHEXDATA)
  {
      char t = XBee.read();
      //Serial.println(t);
      hexData = hexData + String(byte(t),HEX);
      //byte b = byte(t);
      //Serial.println(b,HEX);
      hexCount+=2; //1 bytes or 2 hex digits in one character
  }
  XBee.flush();
  Serial.print("Raw Data: 0x");Serial.println(hexData);
  splitData(hexData);
  if(hexData[0] == _S){Shelter2Shelter(hexData);}
  else if(hexData[0] == _B){Bus2Shelter(hexData);}
  else{Serial.println("Error. Not a valid message");}
}

void Shelter2Shelter(String str)
{
  //XBee.println(str);  
}

void Bus2Shelter(String str)
{
  Serial.println(str);  
}

void splitData(String str)
{
    //_ _ II II RR NN S  S  S  S
    //0 1 2345 67 89 10 11 12 13
    //hexStr = "";
    busIDa = (uint8_t)strtol(&(str.substring(2,4))[0],NULL,16);
    busIDb = (uint8_t)strtol(&(str.substring(4,6))[0],NULL,16);
    busRoute = (uint8_t)strtol(&(str.substring(6,8))[0],NULL,16);
    numStops = (uint8_t)strtol(&(str.substring(8,10))[0],NULL,16);
    prevShelterIDa = (uint8_t)strtol(&(str.substring(10,12))[0],NULL,16);
    prevShelterIDb = (uint8_t)strtol(&(str.substring(12,14))[0],NULL,16);

    /*
    Serial.println(busID,HEX);
    Serial.println(busRoute,HEX);
    Serial.println(numStops,HEX);
    Serial.println(prevShelterID,HEX);Serial.println();

    Serial.println(busID);
    Serial.println(busRoute);
    Serial.println(numStops);
    Serial.println(prevShelterID);Serial.println();
  */

  numStops++;
  char bIDa = busIDa;
  char bIDb = busIDb;
  char bRoute = busRoute;
  char nStops = numStops;
  char sIDa = THIS_ID_A;
  char sIDb = THIS_ID_B;

  //Serial.println(bIDa);
  //Serial.println(bIDb);
  //Serial.println(bRoute);
  //Serial.println(nStops);
  //Serial.println(sIDa);
  //Serial.println(sIDb);

  String msg = ""+_S + '0';
  msg = msg + bIDa + bIDb + bRoute + nStops + sIDa + sIDb;

  //Serial.println(msg);
  //XBee.print(_S + '0' + bIDa + bIDb + bRoute + nStops + sIDa + sIDb);
  XBee.print(msg);
}

