#include <SoftwareSerial.h>
SoftwareSerial Blt(11,12);

#define motorLinks 3
#define motorRechts 13

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
  
  Serial.print("Input:    ");
  Serial.println(input);
  
  ptr = strtok(input, delimiter);
  
  motorgas = atoi(ptr);
  
  ptr = strtok(NULL, delimiter);
  
  motorlenk = atoi(ptr);
  
  test();
  
  delay(500);
  
  
  
  Serial.println();
  
  
  
  

}


void test(){
  
  
  if( motorgas >= 100)
  {
    zustandMotorLinks = 1;
    digitalWrite(motorLinks, zustandMotorLinks);
    zustandMotorRechts = 1;
    digitalWrite(motorRechts, zustandMotorRechts);
    
    Serial.println("Motor vor");
    
  }else if(motorgas < 100 && motorgas >= 0)
  {
      zustandMotorRechts = 0;
      digitalWrite(motorRechts, zustandMotorRechts);
      zustandMotorLinks = 0;
      digitalWrite(motorLinks, zustandMotorLinks);
      
      Serial.println("Motor zuruck");
      
  }
  
  if( (motorlenk >= 0) && (motorlenk < 100) )
  {
    zustandMotorLinks = 0;
    digitalWrite(motorLinks, zustandMotorLinks);
    zustandMotorRechts = 1;
    digitalWrite(motorRechts, zustandMotorRechts);
    
    Serial.println("Motor left");
    
  }
  else
  if( (motorlenk <= 200) && (motorlenk > 100))
  {
    zustandMotorRechts = 0;
    digitalWrite(motorRechts, zustandMotorRechts);
    zustandMotorLinks = 1;
    digitalWrite(motorLinks, zustandMotorLinks);
    
    Serial.println("Motor rechts");
    
  }
  
}
