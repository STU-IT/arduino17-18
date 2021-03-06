/*  
  Robot Car with Speed Sensor Demonstration
  RobotCarSpeedSensorDemo.ino
  Demonstrates use of Hardware Interrupts
  to control motors on Robot Car
  
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/
 
// Constants for Interrupt Pins
// Change values if not using Arduino Uno
 
const byte MOTOR_A = 3;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2;  // Motor 1 Interrupt Pin - INT 0 - Left Motor
 
// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different
 
// Constant for wheel diameter
const float wheeldiameter = 66.15; // Wheel diameter in millimeters, change if different
 
// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;
 
 
// Motor A
 
int enA = 10;
int in1 = 9;
int in2 = 8;
 
// Motor B
 
int enB = 11;
int in3 = 12;
int in4 = 13;
 
// Interrupt Service Routines
 
// Motor A pulse count ISR
void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 
 
// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}
 
// Function to convert from centimeters to steps
int CMtoSteps(float cm) {
 
  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10.0; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step
  
  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)

  Serial.print("f_result: ");
  Serial.print(f_result);
  Serial.println();
   
  Serial.print("result: ");
  Serial.print(result);
  Serial.println();
  
  return result;  // End and return result
 
}
 
// Function to Move Forward
void MoveForward(int steps, int mspeed) 
{
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero
  
  // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  int lastCountA = 0;
  int lastCountB = 0;
  int deltaA = 0;
  int deltaB = 0;

  float ratio = 1;

  float speedA = 0;
  float speedB = 0;

  
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {

    deltaA = counter_A - lastCountA;
    deltaB = counter_B - lastCountB;

    if (deltaB > 0)
    {
      ratio = float(deltaA) / float(deltaB);
    }

    if (ratio > 1)
    {
      speedA = mspeed * (1 / ratio);
      speedB = mspeed;
    }
    else
    {
      speedA = mspeed;
      speedB = mspeed * ratio;
    }
  
    if (steps > counter_A) {
      analogWrite(enA, speedA);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, speedB);
    } else {
      analogWrite(enB, 0);
    }

    lastCountA = counter_A;
    lastCountB = counter_B;
    
///////
    Serial.print("Counter_A: ");
    Serial.print(counter_A);
    Serial.print(",  ");

    Serial.print("deltaA: ");  Serial.print(deltaA);   Serial.print(",  ");
    Serial.print("speedA: ");  Serial.print(speedA);   Serial.print(",  ");
    

    Serial.print("Counter_B: ");
    Serial.print(counter_B);
    Serial.print(" ");

    Serial.print("deltaB: ");  Serial.print(deltaB);   Serial.print(",  ");
    Serial.print("speedB: ");  Serial.print(speedB);   Serial.print(",  ");
    
    Serial.print("ratio: ");  Serial.print(ratio);   Serial.print(",  ");
    
    Serial.println();
///////
  
}


  
///////
    Serial.print("Counter_A: ");
    Serial.print(counter_A);
    Serial.print(",  ");

    Serial.print("Counter_B: ");
    Serial.print(counter_B);
    Serial.print(" ");
    
    Serial.println();
///////
  

  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 
 
}
 
// Function to Move in Reverse
void MoveReverse(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 
  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   // Go in reverse until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
    }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 
 
}
 
// Function to Spin Right
void SpinRight(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 
  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
   }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 
 
}
 
// Function to Spin Left
void SpinLeft(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 0);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 0);
    }
  }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 
 
}
 
void setup() 
{

  Serial.begin(250000); //Set Serial Communication
  
  // Attach the Interrupts to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High

  Serial.print("intA: ");
  Serial.print( digitalPinToInterrupt (MOTOR_A));
  Serial.print("intB: ");
  Serial.print( digitalPinToInterrupt (MOTOR_B));

  Serial.println();
  
} 
 
 
void loop()
{

  // Test Motor Movement  - Experiment with your own sequences here  
  
  MoveForward(CMtoSteps(200), 120);  // Forward half a metre at 255 speed  // NU 30 cm
  delay(1500);  // Wait one second

  //MoveReverse(CMtoSteps(30), 120);  // Forward half a metre at 255 speed  // NU 30 cm
  //delay(1000);  // Wait one second

  /*
  MoveReverse(10, 255);  // Reverse 10 steps at 255 speed
  delay(1000);  // Wait one second
  MoveForward(10, 255);  // Forward 10 steps at 150 speed
  delay(1000);  // Wait one second
  MoveReverse(CMtoSteps(25.4), 200);  // Reverse 25.4 cm at 200 speed
  delay(1000);  // Wait one second
  SpinRight(20, 255);  // Spin right 20 steps at 255 speed
  delay(1000);  // Wait one second
  SpinLeft(60, 255);  // Spin left 60 steps at 175 speed
  delay(1000);  // Wait one second
  MoveForward(1, 255);  // Forward 1 step at 255 speed
  delay(1000);

  MoveForward(CMtoSteps(10), 200); // 10 cm frem

  delay(10000); // stop i 10 sec
  */
  // Put whatever you want here!
 
  
}
