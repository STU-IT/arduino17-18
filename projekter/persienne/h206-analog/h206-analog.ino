
int PinOut = A0; //Set assign digital pin 2
int myDelay = 50;
int val;
 
void setup()
{
Serial.begin(9600); //Set Serial Communication
pinMode(PinOut, INPUT); //Set as INPUT
Serial.println("14CORE | Opto Interrupter Analog Out Test Code");
Serial.println("-----------------------------------------------");
}
 
void loop(){
 val = analogRead(PinOut);
 //Serial.print("Sensor Value:");
 Serial.println(val);
 delay(myDelay);
}

