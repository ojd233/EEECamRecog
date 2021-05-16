#include <Wire.h>

#define PWMa 7
#define PWMb 5
#define PWMc 8
#define PWMd 6

int trig = 9;
int echo =10;

int gled = 11;
int yled = 12;
int rled = 13;

void setup() {
  Serial.begin(9600);
  Wire.begin(0x07);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(gled, OUTPUT);
  pinMode(yled, OUTPUT);
  pinMode(rled, OUTPUT);

  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

int distanceSense(){
  float dist, dur;
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  dur = pulseIn(echo,HIGH);
  dist = (dur/2) /29.1;
  return dist;
}

int LEDScale(int dist){
  if(dist >= 30){
    digitalWrite(gled,LOW);
    digitalWrite(yled,LOW);
    digitalWrite(rled,LOW);
  }
  
  if(dist >= 15 && dist < 30){
    digitalWrite(gled,HIGH);
    digitalWrite(yled,LOW);
    digitalWrite(rled,LOW);
  }

  if(dist < 15 && dist >= 7){
    digitalWrite(gled,HIGH);
    digitalWrite(yled,HIGH);
    digitalWrite(rled,LOW);
  }

  if(dist < 7){
    digitalWrite(gled,HIGH);
    digitalWrite(yled,HIGH);
    digitalWrite(rled,HIGH);
  }
  
}

void requestEvent(){
  int distance;
  distance = distanceSense();
  byte i2carray[1];
  //i2carray[0] = (distance >> 8) & 0xFF;
  //i2carray[1] = distance & 0xFF;
  i2carray[0] = distance;
  Wire.write(i2carray, 1);

}

void receiveEvent(){
  int M;
  M = Wire.read();
  if (M == 0){
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
  }
  if (M == 1){
    digitalWrite(PWMa, HIGH);
    analogWrite(PWMb, -100);
    digitalWrite(PWMc, LOW);
    analogWrite(PWMd, 100);
  }
  if (M == 2){
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, HIGH);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
  }

  
}
void loop() {
  int distance;
  distance = distanceSense();
  LEDScale(distance);
  //Serial.println("LD:");
  //Serial.print(distance);
  //String dist = String(distance);
  //Serial.println(distance);

}
