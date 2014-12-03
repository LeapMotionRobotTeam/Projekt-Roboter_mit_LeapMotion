int vor;
int linksrechts;


void setup(){
 Serial.begin(9600);  
}

void loop(){
  
  ausgeben();  
  delay(3000);
}

int zufallsZahlZumVorFahren(){ 
   vor = random(0, 100); //der Variable vor wird eine Zufallszahl zwischen 0 und 100 zugewiesen
   return vor;           //vor wird zurückgegeben
}

int zufallsZahlZumLinksRechtsFahren(){
    linksrechts = random(0, 200); //der Variable linksrechts wird ein Zufallswert zwischen 0 und 200 zugewiesen
    return linksrechts;           // linksrechts wird zurückgegeben
}

void ausgeben(){
    Serial.print(zufallsZahlZumVorFahren());          //hier wird die Zufallszahl zum Vorwärtsfahren auf dem Serial Monitor ausgegeben
    Serial.print("a");                                //Das Trennzeichen 'a' wird gesetzt/ausgegeben
    Serial.print(zufallsZahlZumLinksRechtsFahren());  //hier wird die Zufallszahl zum Links und Rechts fahren auf dem Serial Monitor ausgegeben
    
    Serial.print(" Vorwaertsfahren mit ");
    Serial.print(vor);                            //Zufallszahl zum vorwärtsfahren wird ausgegeben
    Serial.print("%");                           // in %
    Serial.print(" und");
    if(linksrechts >= 0 && linksrechts < 100)    //Bedingung: wenn Zahl zwischen 0 und 99 ist
    {
      Serial.print(" nach links fahren!");  //soll am Serial Monitor ausgegeben werden, dass nach links gefahren werden soll
    }else if(linksrechts > 100 && linksrechts <= 200)  //Bedingung: wenn Zahl zwischen 101 und 200 ist
    {
       Serial.print (" nach rechts fahren!");   //soll am Serial Monitor ausgegeben werden, dass nach rechts gefahren werden soll
    }
    if(linksrechts == 100)                     //Bedingung: falls zufällig generierte Zahl 100 ist
    {
        Serial.print(" geradeaus fahren!");   //soll am Serial Monitor ausgegeben werden, dass geradeausgefahren werden soll
    }
    Serial.print("\n");
}
