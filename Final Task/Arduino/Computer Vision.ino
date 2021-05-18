#include <Wire.h>

#define PWMa 7
#define PWMb 5
#define PWMc 8
#define PWMd 6

void setup(){
  Serial.begin(9600);
  Wire.begin(0x07);

  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);
  Wire.onReceive(receiveEvent);
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
    delay(1000);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(1000);
    instruction = 0;
  }
  if(instruction == 2){
    Serial.println(instruction);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, HIGH);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, HIGH);
    delay(1000);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(1000);
    instruction = 0;
  }  
  if(instruction == 3){
    Serial.println(instruction);
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    delay(2000);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(1000);
    instruction = 0;
  }
  if(instruction == 4){
    Serial.println(instruction);
    digitalWrite(PWMa, HIGH);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, HIGH);
    digitalWrite(PWMd, LOW);
    delay(4000);
    digitalWrite(PWMa, LOW);
    digitalWrite(PWMb, LOW);
    digitalWrite(PWMc, LOW);
    digitalWrite(PWMd, LOW);
    delay(1000);
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
    delay(1000);
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
    delay(1000);
    instruction = 0;
    
  }
}
