#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <RH_ASK.h>
#include <SPI.h>
#include<string.h>

RH_ASK driver;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
String s1;

void setup()
{
    Serial.begin(9600);
    if(!mag.begin()||!driver.init() )
  {
    exit(0);
  }
}

void loop()
{
    uint8_t buf[10];
    uint8_t buflen = sizeof(buf);
   if (driver.recv(buf, &buflen)) // Non-blocking
    {
        sensors_event_t event; 
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;
  if(heading < 0)
    heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI; 
  s1=String(headingDegrees);
  int inde = s1.indexOf('.');
  inde+=3;
  String x = s1.substring(0,inde);
      String s=(char*)buf;  
      int index = s.indexOf(' '); 
      String c = s.substring(0,index);
      index++;
      String l = s.substring(index,s.length());
      if ((c.toInt()-10)<=x.toInt()<=(c.toInt()+10)){
        Serial.println(l);
      }
      
       
   }
}
