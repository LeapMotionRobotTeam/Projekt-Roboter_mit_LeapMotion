#include <SoftwareSerial.h>// import the serial library

SoftwareSerial BT(11, 12); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (BT.available()){
BluetoothData=BT.read();
   if(BluetoothData=='1'){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   Serial.println("LED ON!");
   }
  if (BluetoothData=='0'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   Serial.println("LED Off!");
  }
}
delay(100);// prepare for next data ...
}
