#include <Wire.h>

#define PWMa 7
#define PWMb 5
#define PWMc 8
#define PWMd 6

#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on SPI bus 0 and chip select pin 10
MPU9250 IMU(SPI,4);
int status;
void setup(){
  Wire.begin(0x07);

  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}
void turn(int ang){
  float sum = 0;
  float x = 0;
  float angle = 0;
  float reading = 0;

  while (x < ang){
 
    IMU.readSensor();
    reading = IMU.getGyroZ_rads(),6;
    Serial.println(reading);
    if (reading >= 0.2 || reading <= -0.2){
      float adjread; 
      adjread = reading * 0.25;
      sum = sum + adjread;
      //angle = sum * 0.01;
      angle = sum * (180/(3.141592654));
      x = x + angle;
      
    }
    Serial.println(x);
    Serial.println("");
    delay(250);
    if (reading >= -0.2 && reading <= 0.2){
      sum = 0;
      x = 0;
      angle = 0; 
    }
    if (x >= ang || x <= (-1*ang)){
      break;
    }
  }
  Serial.println("Turned");
  return 1;

}
int instruction;
void receiveEvent(){

  instruction = Wire.read();
  

}

void loop(){
  Serial.println(instruction);
  if(instruction == 1){
    Serial.println(instruction);
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    turn(90);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
  }
  if(instruction == 2){
    Serial.println(instruction);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, HIGH);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, HIGH);
    turn(-90);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
  }  
  if(instruction == 3){
    Serial.println(instruction);
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    turn(180);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
  }
  if(instruction == 4){
    Serial.println(instruction);
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    turn(360);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
  }


  if(instruction >= 10){
    Serial.println(instruction);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, HIGH);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    int timefor = (instruction / 10) * 1000;
    delay(timefor);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
    
  }

   if(instruction < 0){
    Serial.println(instruction);  
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, HIGH);
    int timerev = (instruction / -10) * 1000;
    delay(timerev);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(10);
    instruction = 0;
    
  }
}
