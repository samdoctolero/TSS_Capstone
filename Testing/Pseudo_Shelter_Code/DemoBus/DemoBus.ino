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
  if(Serial.available()){
    if(Serial.read() == '1'){
      XBee.println("b00an");  
      Serial.println("Sending: b00an");
    }
    else {
      XBee.println("b06bn");  
      Serial.println("Sending: b06bn");
    }
  }

}

String hexToStr()
{
    String rawData = Serial.readString();
    String hexStr = "";

    Serial.println(rawData);
    for(int i = 0;i<rawData.length() - 1;i+=2)
    {
      String str = rawData.substring(i,i+2); //grab two characters at a time
      long hex = strtol(&str[0],NULL,16);
      char ch = hex;
      hexStr += ch;
    }
    Serial.print("Original Hex: ");Serial.println(hexStr);
    return hexStr;
}

