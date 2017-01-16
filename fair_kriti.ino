#include <Wire.h>
#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;
void SpeedRun(byte Address ,int Speed){
  Wire.beginTransmission(Address);
  Wire.write(1);
  Wire.write(Speed  &0xff);
  Wire.write((Speed >> 8) & 0xff);
  Wire.endTransmission();
}


void SetMaxSpeed(byte Address,byte Speed)
{ Wire.beginTransmission(Address);
  Wire.write(0);
  Wire.write(Speed);
  Wire.write(0);
  Wire.endTransmission();
}



void SetDamping(byte Address,byte Damping){
  Wire.beginTransmission(Address);
  Wire.write(2);
  Wire.write(Speed);
  Wire.write(0);
  Wire.endTransmission();
  delay(500);
  }
  
  
void MoveAbs(byte Address,long Position){
  
  Wire.beginTransmission(Address);
  Wire.write(4);
  Wire.write(Position   & 0xff);
  Wire.write((Position >> 8) & 0xff);
  Wire.write((Position >> 32) & 0xff);
  Wire.write((Position >> 24) & 0xff);
  Wire.endTransmission();
}

void MoveRel(byte Address,long Position){
  
  Wire.beginTransmission(Address);
  Wire.write(8);
  Wire.write(Position   & 0xff);
  Wire.write((Position >> 8) & 0xff);
  Wire.write((Position >> 32) & 0xff);
  Wire.write((Position >> 24) & 0xff);
  Wire.endTransmission();
}


void joyCallback(const sensor_msgs::Joy& joy)
{
  int a;
  a = joy.axes[1];
  if (a > 0){
    digitalWrite(13,HIGH);}
  if (a < 0){
    digitalWrite(13,LOW);}  
}  

ros::Subscriber<sensor_msgs::Joy> sub("joy", joyCallback);
void setup(){
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(1);
}


