#include <SoftwareSerial.h>
SoftwareSerial Blt(4,7);

char input[100];
char delimiter[] = "AB";
char * ptr;
char momentaneZahl[37];
int indexWert, index;
int motorgas;
int motorlenk;
int zustandMotorLinks;
int zustandMotorRechts;


void setup() {
  
  Blt.begin(9600);
  Serial.begin(9600);
  

}

void loop() {
  
  indexWert = 0;
  
  while(Blt.available())
  {
    input[indexWert] = Blt.read();
    indexWert++;
  }
  
  // läuft bei ihm
  
  
  ptr = strtok(input, delimiter);
  
  motorgas = atoi(ptr);
  
  ptr = strtok(NULL, delimiter);
  
  motorlenk = atoi(ptr);
  
  
  
  test();
  
  delay(300);
  
  Serial.println(motorgas);
  Serial.println(motorlenk);
  
  
  
  

}


void test(){
  
  
  if( (motorgas >= 100) && (motorlenk == 100))
  {
    zustandMotorLinks = 1;
    Motor1Back();
    zustandMotorRechts = 1;
    Motor2Back();
    
  }else if((motorgas < 100 && motorgas >= 0) && (motorlenk == 100))
  {
      zustandMotorRechts = 0;
      Motor1Vor();
      zustandMotorLinks = 0;
      Motor2Vor();
  }
  
  if( (motorlenk >= 0) && (motorlenk < 100) )
  {
    zustandMotorLinks = 0;
    Motor1Back();
    zustandMotorRechts = 1;
    Motor2Vor();
    
    Serial.println("Motor left");
    
  }
  else
  if( (motorlenk <= 200) && (motorlenk > 100))
  {
    zustandMotorRechts = 0;
    Motor2Back();
    zustandMotorLinks = 1;
    Motor1Vor();
    
    Serial.println("Motor rechts");
    
  }
  
}


void Motor1Vor()
{
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  analogWrite(3, 255);
}


void Motor1Back()
{
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  analogWrite(3, 255);
}


void Motor2Vor()
{
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, 255);
}


void Motor2Back()
{
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(11, 255);  
}
