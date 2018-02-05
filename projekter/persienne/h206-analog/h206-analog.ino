
int PinOut = A0; //Set assign digital pin 2
int myDelay = 50;
int val;

int dPin1 = 2;
int dPin2 = 3;


void setup()
{
Serial.begin(9600); //Set Serial Communication
pinMode(PinOut, INPUT); //Set as INPUT
Serial.println("14CORE | Opto Interrupter Analog Out Test Code");
Serial.println("-----------------------------------------------");

pinMode(dPin1, INPUT);
pinMode(dPin2, INPUT);
}
 
void loop(){
  //val = analogRead(PinOut);
  val = digitalRead(PinOut);
  //Serial.print("Sensor Value:");
  
  //Serial.print("X: ");
  //Serial.print(val*2);
  //Serial.print(", ");
  
  Serial.print("Direct opto: ");
  Serial.print(val);
  
  int val1 = digitalRead(dPin1);
  int val2 = digitalRead(dPin2);

  Serial.print(", ");
  Serial.print("d1: ");
  Serial.print(val1);

  Serial.print(", ");
  Serial.print("d2: ");
  Serial.print(val2);

  Serial.println();
  
  delay(myDelay);
}

