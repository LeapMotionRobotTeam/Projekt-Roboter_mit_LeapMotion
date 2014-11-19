int vor;          //Variable zum vorwärts fahren
int linksrechts;  //Variable zum links und rechts Fahren

void setup(){
   Serial.begin(9600);  
 }

void loop(){   
  
  ausgeben();    //gibt einen zufälligen Code aus
  delay(1000);
}
/*
Hier wird eine Zufallszahl (Ganzzahl) generiert, welche
für das vorwärts-fahren gebraucht wird.
*/
int zufallsZahlZumVorFahren(){ 
   vor = random(0, 100); //der Variable vor wird eine Zufallszahl zwischen 0 und 100 zugewiesen
   return vor;           //vor wird zurückgegeben
}

/*
Hier wird eine Zufallszahl (Ganze Zahl) generiert, welche
für das links-und-rechts-fahren gebraucht wird.
*/
int zufallsZahlZumLinksRechtsFahren(){
    linksrechts = random(0, 200); //der Variable linksrechts wird ein Zufallswert zwischen 0 und 200 zugewiesen
    return linksrechts;           // linksrechts wird zurückgegeben
}

void ausgeben(){
    Serial.print(zufallsZahlZumVorFahren());          //hier wird die Zufallszahl zum Vorwärtsfahren auf dem Serial Monitor ausgegeben
    Serial.print("a");                                //Das Trennzeichen 'a' wird gesetzt/ausgegeben
    Serial.print(zufallsZahlZumLinksRechtsFahren());  //hier wird die Zufallszahl zum Links und Rechts fahren auf dem Serial Monitor ausgegeben
    Serial.print("\n");
}
