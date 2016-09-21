#include <DHT11.h>

#include <SoftwareSerial.h>

#define DHT11PIN 2
#define RESISTOR A0

DHT11 dht11(DHT11PIN);

SoftwareSerial mySerial(10, 11); // RX, TX

String command;
void setup()
{
  pinMode(4,OUTPUT);
  
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for Leonardo only
}
Serial.println("Conectado al Bluetooth!");
// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
mySerial.println("Conecado a la pc");
}
void loop() // run over and over
{
/*if (mySerial.available())
Serial.write(mySerial.read());*/
if (Serial.available())
mySerial.write(Serial.read());

if(mySerial.available()>0){
  command=mySerial.readString();
  command.toLowerCase();
  Serial.println(command);
}

if(command == "on"){
   digitalWrite(4,HIGH);
}

if(command == "off"){
   digitalWrite(4,LOW);
}

if(command == "sensor"){
 int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();
             mySerial.print("Temperatura: ");
             mySerial.print(temp);
             mySerial.print(" Humedad: ");
             mySerial.print(hum);
             mySerial.println();
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
             mySerial.println();
             mySerial.print("Error Num :");
             mySerial.print(err);
             mySerial.println();
          }
       delay(1000);            //Recordad que solo lee una vez por segundo
}

if(command == "light"){
   int sensorValue = analogRead(RESISTOR);
   Serial.print("La luz es: ");
   Serial.println(sensorValue, DEC);
   mySerial.print("La luz es: ");
   mySerial.println(sensorValue, DEC);
}

command ="";
}

