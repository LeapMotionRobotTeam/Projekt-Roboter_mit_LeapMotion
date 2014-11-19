#include <SoftwareSerial.h>

SoftwareSerial Blt(11,12);

char input[100], momentaneZahl[37];
int indexWert, index;
float motorgas, motorlenk;

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
  Serial.println(input);
  Serial.println(motorgas);
  Serial.println(motorlenk);

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

