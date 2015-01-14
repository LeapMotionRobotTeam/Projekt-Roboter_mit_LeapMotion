#include <SoftwareSerial.h>
SoftwareSerial Blt(4,7);

#define directionA 12
#define directionB 13
#define speedA 3
#define speedB 11
#define brakeA 9
#define brakeB 8

char input[100];
char delimiter[] = "AB"; // Trennzeichen
char * ptr;
char momentaneZahl[37];
int indexWert, index;
int motorgas;
int motorlenk;
int zustandMotorLinks;
int zustandMotorRechts;


void setup() {
  
  pinMode(directionA, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(speedA, OUTPUT);
  pinMode(speedB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  
  Blt.begin(9600);
  Serial.begin(9600);
  
  Init();

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

void Init()
{
  Motor1Vor(1);
  Motor2Vor(1);
  delay(500);
  Motor2Back(1);
  delay(200);
  Motor1Back(1);
  delay(200);
}

void test(){
  
  
  
  /*
  Wenn motorlenk genau 100 ist, soll Roboter geradeaus fahren 
  motorlenk < 100 --> nach links lenken
  motorlenk > 100 --> nach rechts lenken
  */
  // Roboter soll nach vorne fahren
  if(motorgas >= 100)
  {
    if(motorlenk == 100)
    {
      Motor1Vor(255);
      Motor2Vor(255);
    }
    else if(motorlenk < 100)
    {
      Motor1Back(0);
      Motor2Vor(100);
    }
    else if(motorlenk > 100)
    {
      Motor1Vor(100);
      Motor2Back(0);
    }
    
  } 
  // Roboter soll nach hinten fahren
  else if(motorgas < 100)
  {
    if(motorlenk == 100)
    {
      Motor1Back(100);
      Motor2Back(100);
    }
    else if(motorlenk < 100)
    {
      Motor1Back(0);
      Motor2Vor(100);
    }
    else if(motorlenk > 100)
    {
      Motor1Vor(100);
      Motor2Back(0);
    }
  }
  
}



void Motor2Vor(int v)
{
  digitalWrite(directionA, HIGH);
  digitalWrite(brakeA, LOW);
  analogWrite(speedA, v);
  
  //digitalWrite(12, HIGH);
  //digitalWrite(9, LOW);
  //analogWrite(3, 255);
}


void Motor2Back(int v)
{
  digitalWrite(directionA, LOW);
  digitalWrite(brakeA, LOW);
  analogWrite(speedA, v);
}


void Motor1Vor(int v)
{
  digitalWrite(directionB, HIGH);
  digitalWrite(brakeB, LOW);
  analogWrite(speedB, v);
}


void Motor1Back(int v)
{
  digitalWrite(directionB, LOW);
  digitalWrite(brakeB, LOW);
  analogWrite(speedB, v);  
}

