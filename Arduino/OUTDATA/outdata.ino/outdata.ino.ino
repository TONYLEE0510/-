#include <SoftwareSerial.h>
#include "DHT.h"


#define DHTPIN 2
#define DHTTYPE DHT22
int measurePin = A0;
int ledPower = 12;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 DHT dht(DHTPIN,DHTTYPE);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
    dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()){
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  int a = map(getdust(),8,133,10,1000);
    char b[] = "";
    sprintf(b,"%03d",a);
    String tx="";
    tx+='$';
    tx+=b;
    tx+=',';
    tx+=h;
    tx+=',';
    tx+=t;
    tx+='*';
    Serial.println(tx);
/*
  Serial.print("Dust:");
  Serial.println(b);
   Serial.print("Humid:");
  Serial.println(h);
  Serial.print("Temp:");
  Serial.println(t);
  */
  }

}

int getdust(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (3.3 / 1024);
  dustDensity = 100 * calcVoltage - 0.1;
  return(dustDensity);
}
