#define motorLinks 3
#define motorRechts 13
#define signalMotorLinks 4
#define signalMotorRechts 7
#define signal 5

int motorgas;          //Variable zum motorgaswärts fahren
int motorlenk;  //Variable zum links und rechts Fahren
int zustandMotorLinks;
int zustandMotorRechts;


void setup(){
   Serial.begin(9600);  
 }

void loop(){   
  
  
  
  test();  
  //int l = digitalRead(signalMotorLinks);
  //int r = digitalRead(signalMotorRechts);
  Serial.print("Vor oder Zurueck");
  Serial.print("\t");
  Serial.print(motorgas);
  Serial.print("\t");
  Serial.print(motorlenk);
  
  Serial.print(" "); 
  //Serial.print(zahl);
  Serial.print ("\n");
  
  Serial.print("Links: ");
  //Serial.print(l);
  Serial.print("\t");
  Serial.print(zustandMotorLinks);
  Serial.print("\n");
  Serial.print("Rechts: ");
  //Serial.print(r);
  Serial.print("\t");
  Serial.print(zustandMotorRechts);
  Serial.print("\n");
  
  Serial.print(" ");
  
  Serial.println("");
  delay(5000);
}
/*
Hier wird eine Zufallszahl (Ganzzahl) generiert, welche
für das motorgaswärts-fahren gebraucht wird.
*/
int zufallsZahlZummotorgasFahren(){ 
   motorgas = random(0, 100); //der Variable motorgas wird eine Zufallszahl zwischen 0 und 100 zugewiesen
   return motorgas;           //motorgas wird zurückgegeben
}

/*
Hier wird eine Zufallszahl (Ganze Zahl) generiert, welche
für das links-und-rechts-fahren gebraucht wird.
*/
int zufallsZahlZummotorlenkFahren(){
    motorlenk = (int)random(0, 200); //der Variable motorlenk wird ein Zufallswert zwischen 0 und 200 zugewiesen
    return motorlenk;           // motorlenk wird zurückgegeben
}

/*void ausgeben(){
    Serial.print(zufallsZahlZummotorgasFahren());          //hier wird die Zufallszahl zum motorgaswärtsfahren auf dem Serial Monitor ausgegeben
    Serial.print("a");                                //Das Trennzeichen 'a' wird gesetzt/ausgegeben
    Serial.print(zufallsZahlZummotorlenkFahren());  //hier wird die Zufallszahl zum Links und Rechts fahren auf dem Serial Monitor ausgegeben
    Serial.print("\n");
}*/

void test(){
  
  //zahl = (int)random(0, 200);
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
