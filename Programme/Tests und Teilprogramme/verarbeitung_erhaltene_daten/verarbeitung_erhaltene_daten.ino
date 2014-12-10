#include <SoftwareSerial.h>

SoftwareSerial Blt(11,12);

char input[100], momentaneZahl[37];
int indexWert, index;
float motorgas, motorlenk;

#define motorLinks 3
#define motorRechts 13
#define signalMotorLinks 4
#define signalMotorRechts 7
#define signal 5

int zustandMotorLinks;
int zustandMotorRechts;


void setup()
{
  Serial.begin(9600);
  indexWert = 0;
  index = 0;
  Blt.begin(9600);
}

void loop()
{
  GetSollpositionen();
  
  test();
  
  Serial.println(input);
  Serial.print("Gas");
  Serial.print(motorgas);
  Serial.print("\t");
  Serial.print("Lenk");
  Serial.println(motorlenk);
  
  Serial.print("Links:");
  Serial.print("\t");
  Serial.print(zustandMotorLinks);
  Serial.print("\t");
  Serial.print("Rechts:");
  Serial.print("\t");
  Serial.print(zustandMotorRechts);

  delay(1000);
}

//liefert mir für A und B 0.0 zurück. Aber nur wenn ich die Ausgabe außerhalb der Methode mache
void GetSollpositionen()
{
  while(Blt.available())
  {
    input[indexWert] = Blt.read();
    indexWert++;
  }
  index=0;
  
  MomentaneZahlZuruecksetzen();
  if(input[index] == 'A')
  {
    index++;
    do
    {
      momentaneZahl[indexWert] = input[index];
      indexWert++;
      index++;
    }while(input[index] != 'B');
    motorgas = atof(momentaneZahl);
  }
  
  MomentaneZahlZuruecksetzen();
  if(input[index] == 'B')
  {
    index++;
    do
    {    
      momentaneZahl[indexWert] = input[index];
      indexWert++;
      index++;
    }while(index < sizeof(input));
    motorlenk = atof(momentaneZahl);
  }

}

void MomentaneZahlZuruecksetzen()
{
  for(int i = 0; i < sizeof(momentaneZahl); i++)
  {
    momentaneZahl[i] = '0';
  }
  indexWert = 0;
}

void test(){
  
  if( motorgas >= 100)
  {
  zustandMotorLinks = 1;
  digitalWrite(motorLinks, zustandMotorLinks);
  zustandMotorRechts = 1;
  digitalWrite(motorRechts, zustandMotorRechts);
  }else if(motorgas < 100 && motorgas >= 0)
  {
      zustandMotorRechts = 0;
      digitalWrite(motorRechts, zustandMotorRechts);
      zustandMotorLinks = 0;
      digitalWrite(motorLinks, zustandMotorLinks);
  }
  
  if( (motorlenk >= 0) && (motorlenk < 100) )
  {
  zustandMotorLinks = 0;
  digitalWrite(motorLinks, zustandMotorLinks);
  zustandMotorRechts = 1;
  digitalWrite(motorRechts, zustandMotorRechts);
  }
  else
  if( (motorlenk <= 200) && (motorlenk > 100))
  {
    zustandMotorRechts = 0;
    digitalWrite(motorRechts, zustandMotorRechts);
    zustandMotorLinks = 1;
    digitalWrite(motorLinks, zustandMotorLinks);
  }
  
}

