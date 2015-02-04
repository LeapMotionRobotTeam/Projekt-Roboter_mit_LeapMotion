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
int u;


void setup() {
  
  pinMode(directionA, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(speedA, OUTPUT);
  pinMode(speedB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  
  Blt.begin(9600);
  
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
  
  
  
  bewegung();
  
  delay(200);
  
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

void bewegung(){
  
  
  u = map(motorgas, 100, 200, 80, 255);
  
  int z = map(motorlenk, 0, 99, 80, 120);
  int y = map(motorlenk, 0, 99, 150, 130);
  int x = map(motorlenk, 101, 200, 130, 150);
  int c = map(motorlenk, 101, 200, 120, 80);
  
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
      Motor1Vor(u);
      Motor2Vor(u);
    }
    else if(motorlenk < 100)
    {
      Motor1Vor(z);
      Motor2Vor(y);
    }
    else if(motorlenk > 100)
    {
      Motor1Vor(x);
      Motor2Vor(c);
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
      Motor1Back(z);
      Motor2Back(y);
    }
    else if(motorlenk > 100)
    {
      Motor1Back(x);
      Motor2Back(c);
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

