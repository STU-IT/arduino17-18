// connect motor controller pins to Arduino digital pins
// motor one
int enA = 11;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 10;
int in3 = 7;
int in4 = 6;

// joystick
int joyXpin = A0;
int joyYpin = A1;


void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(joyXpin, OUTPUT);
  pinMode(joyYpin, OUTPUT);

  Serial.begin(9600);
}

void driveForwards(int speed)
{
  // turn on motor A
//    Serial.println("starter motor A");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed, possible range 0~255
  analogWrite(enA, speed);
  // turn on motor B
//    Serial.println("starter motor B");
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed, possible range 0~255
  analogWrite(enB, speed);
}

void driveBackwards(int speed)
{
  // turn on motor A
//    Serial.println("starter motor A");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed, possible range 0~255
  analogWrite(enA, speed);
  // turn on motor B
//    Serial.println("starter motor B");
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed, possible range 0~255
  analogWrite(enB, speed);
}

void stop()
{
  // now turn off motors
//    Serial.println("stopper begge");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void loop()
{
  int x = analogRead(joyXpin);
  int y = analogRead(joyYpin);

Serial.println(y);

  if (y < 2)
  {
    driveForwards(180);
  } else if (y > 5)
  {
    driveBackwards(180);
  }

  else 
  {
    stop();
  }
  
}
