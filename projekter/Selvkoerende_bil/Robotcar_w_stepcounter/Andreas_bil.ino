
//2-hjulet køretøj med retlinjekorrektion ved at læse roterende encoders

#include <PID_v1.h>
#include <HUBeeBMDWheel.h>

HUBeeBMDWheel leftWheel;
HUBeeBMDWheel rightWheel;

//PID variables.  All doubles
double trackAdjustValue;
double trackSetpoint;
double trackError;

double Kp = 6;  //Bestemmer, hvor aggressivt PID reagerer på den aktuelle fejlmængde (Proportional)
double Ki = 4;  //Bestemmer, hvor aggressivt PID reagerer på fejl over tid (Integral)
double Kd = 1;  //Bestemmer, hvor aggressivt PID reagerer på fejlændringen (Derivat)

PID trackPID(&trackError, &trackAdjustValue, &trackSetpoint, Kp, Ki, Kd, DIRECT);

const byte rightFasterLED = 5;
const byte leftFasterLED = 7;
const byte equalSpeedLED = 6;

const byte forward = 1;
const byte reverse = 0;

const byte hard = 1;    //Hvilken type bremsning
const byte soft = 0;

double leftSpeed = 100;      //indledende hastigheder. Brug double til PID
double rightSpeed = 100;

volatile double leftCount =  0;
volatile double rightCount =  0;

void setup()
{
  Serial.begin(115200);
  attachInterrupt(1, updateLeftCount, CHANGE);
  attachInterrupt(0, updateRightCount, CHANGE);
  pinMode(rightFasterLED, OUTPUT);
  pinMode(leftFasterLED, OUTPUT);
  pinMode(equalSpeedLED, OUTPUT);
  leftWheel.setupPins(12, 13, 11);
  rightWheel.setupPins(9, 8, 10);
  leftWheel.setBrakeMode(hard);
  rightWheel.setBrakeMode(hard);
  leftWheel.setDirectionMode(reverse);
  rightWheel.setDirectionMode(reverse);
  trackAdjustValue = 0;
  trackSetpoint = 0;
  trackError = 0;
  trackPID.SetMode(AUTOMATIC);
  trackPID.SetSampleTime(200);
  trackPID.SetOutputLimits(-20, 20);
}

void loop()
{
  leftWheel.setMotorPower(leftSpeed);      //Indstil motorhastigheden til de aktuelle værdier
  rightWheel.setMotorPower(rightSpeed);
  trackError = rightCount - leftCount;
  if (trackPID.Compute()) //Sandt hvis PID er blevet udløst
  {
    rightSpeed += trackAdjustValue;
    leftCount = 0;
    rightCount = 0;
    if (trackError > 0)
    {
      digitalWrite(rightFasterLED, HIGH);
      digitalWrite(leftFasterLED, LOW);
      digitalWrite(equalSpeedLED, LOW);
    }
    else if (trackError < 0)
    {
      digitalWrite(rightFasterLED, LOW);
      digitalWrite(leftFasterLED, HIGH);
      digitalWrite(equalSpeedLED, LOW);
    }
    else
    {
      digitalWrite(rightFasterLED, LOW);
      digitalWrite(leftFasterLED, LOW);
      digitalWrite(equalSpeedLED, HIGH);
    }
  }
  Serial.println(trackAdjustValue);
}

void updateLeftCount()
{
  leftCount = leftCount + 1;
}

void updateRightCount()
{
  rightCount = rightCount + 1;
}
