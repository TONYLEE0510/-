int one=3;
int two=4;
char data;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(one,OUTPUT);
pinMode(two,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


if(Serial.available())
{
 
  data=Serial.read();
  data=Serial.print(data);
  delay(1000);
  


  if(data=='1')
  {
    digitalWrite(one,HIGH);
    digitalWrite(two,HIGH);
  }
  else
  {
    digitalWrite(one,LOW);
    digitalWrite(two,LOW); 
  }
}

}
