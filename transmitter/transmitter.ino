
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <RH_ASK.h>
#include <SPI.h>
#include<string.h>

RH_ASK driver;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
String s1,snd,lmt="90"; //Speed Limit

void setup(void) 
{
  Serial.begin(9600);
  if(!mag.begin()||!driver.init() )
  {
    exit(0);
  }
}
void loop(void) 
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
  snd=s1+" "+lmt;
    char tosend[snd.length() + 1];
    snd.toCharArray(tosend, sizeof(tosend));
    driver.send((uint8_t *)tosend, snd.length() + 1);
    driver.waitPacketSent();
  delay(500);
}
