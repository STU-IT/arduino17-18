#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <StepperMotor.h>
#include <EEPROM.h>

const int stepsPerRevolution = 4105;
const int stepperSpeed = 1;

StepperMotor myStepper(10, 11, 12, 13);

//digital
/*
const int redLed = 2;
const int yellowLed = 3;
const int greenLed = 4;
*/
const int setOpenValPin = 5;
const int setCloseValPin = 6;
const int openComplite = 7;
const int closeComplite = 8;
const int setValPin = 9;
//analog
const int closeLevelPin = 3;
const int lcdPin1 = 5; //never in use
const int lcdPin2 = 4; //never in use
const int lightReadPin = 0;
//other values
const long MAX = 35000;//MAX: 40000
const long MIN = -40000;

const bool User = true;

int lightLevel;
int closeLevel = 970;
long stepsTaken = 0;
bool resetHaveBeenPress = false;
bool useConfig = false;
//dont write to lcd if lcd already have written
bool lcdPerfect = false;
bool lcdOpen = false;
bool lcdClose = false;

LiquidCrystal_I2C lcd(0x27 ,20 ,4);

void setup() 
{
  //EEPROM.write(0, 0);
  Serial.begin(9600);
  
  pinMode(setOpenValPin, INPUT);
  pinMode(setCloseValPin, INPUT);
  pinMode(openComplite, INPUT);
  pinMode(closeComplite, INPUT);
  pinMode(setValPin, INPUT);
  myStepper.setStepDuration(stepperSpeed);

  byte closeLVL = EEPROM.read(0);
  closeLevel = closeLVL * 10;
  
  lcd.init();
  lcd.init();

  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Starting");
}

void loop() 
{ 
  int temp;
  //open to you don want more light
  if(digitalRead(setOpenValPin) == true)
  {
    if(stepsTaken < MAX)
    {
      resetHaveBeenPress = true;
      useConfig = true;
    
      myStepper.step(1000);
      stepsTaken += 1000;

      //Serial.print("stepsTaken: ");

      temp = round((stepsTaken / (MAX *1.0)) * 100);

      Serial.print("stepsTaken: ");
      Serial.println(stepsTaken);

      Serial.print("MAX:");
      Serial.println(MAX);
      
      Serial.print("stepsTaken / MAX = ");
      Serial.println(stepsTaken / MAX);

      Serial.print("(stepsTaken / MAX) * 10000 = ");
      Serial.println((stepsTaken / MAX) * 10000);
      
      lcd.clear();
      lcd.print("Window is ");
      lcd.print(temp);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("open");

      //Serial.println(stepsTaken);
      //Serial.println(temp);
      
      delay(50);
    }
  }
  else if(digitalRead(setCloseValPin) == true)
  {
    if(stepsTaken > 0)
    {
      resetHaveBeenPress = true;
      useConfig = true;
      
      myStepper.step(-1000);
      stepsTaken -= 1000;

      //Serial.print("stepsTaken: ");

      temp = round((stepsTaken / (MAX * 1.0)) * 100);

      lcd.clear();
      lcd.print("Window is ");
      lcd.print(temp);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("open");

      //Serial.println(stepsTaken);
      //Serial.println(temp);
      
      delay(50);
    }
  }
  else if(digitalRead(setValPin) == true)
  {
    lcd.clear();
    
    if(useConfig == true)
    {
      lcd.print("Light config");
      lcd.setCursor(0, 1);
      lcd.print("saved");
      
      useConfig = false;
      closeLevel = analogRead(closeLevelPin);
      
      EEPROM.write(0, round(closeLevel/10));
      Serial.print("SetValButton ");
      delay(1500);
    }
    else
    {
      lcd.print("Auto mode");
      delay(1500);
    }
    resetHaveBeenPress = false;
  }
  else if(digitalRead(openComplite) == true)
  {
    resetHaveBeenPress = true;
    
    lcd.clear();
    lcd.print("Opening");
    lcd.setCursor(0, 1);
    lcd.print("in prograss");
    
    Serial.println("openComplite");
    myStepper.step(MAX - stepsTaken);
    
    lcd.clear();
    lcd.print("Opening");
    lcd.setCursor(0, 1);
    lcd.print("complite");
    
    stepsTaken = MAX;
  }
  else if(digitalRead(closeComplite) == true)
  {
    resetHaveBeenPress = true;

    lcd.clear();
    lcd.print("Closeing");
    lcd.setCursor(0, 1);
    lcd.print("in prograss");
    
    Serial.println("closeComplite");
    myStepper.step(-stepsTaken);

    lcd.clear();
    lcd.print("Closeing");
    lcd.setCursor(0, 1);
    lcd.print("complite");
    
    stepsTaken = 0;
  }
  
  if(resetHaveBeenPress == false)
  {
    lightLevel = analogRead(lightReadPin);
    Serial.print("lightLevel ");
    Serial.println(lightLevel);
    Serial.print("closeLevel ");
    Serial.println(closeLevel);
    Serial.print("stepsTaken ");
    Serial.println(stepsTaken);
    
    if(lightLevel > closeLevel && stepsTaken > 0)//bigger then zero. its starts on closed (0)
    {
      if(!lcdClose)
      {
        lcdClose = true;
        lcdOpen = false;
        lcdPerfect = false;
        
        lcd.clear();
        lcd.print("Closeing");
      }
      
      Serial.println("closeing");
      
      myStepper.step(-1000);
      stepsTaken -= 1000;
      
      delay(50);
      Serial.print("steps ");
      Serial.println(stepsTaken);
  }
    else if(lightLevel < closeLevel - 30 && stepsTaken < MAX)
    {
      if(!lcdOpen)
      {
        lcdClose = false;
        lcdOpen = true;
        lcdPerfect = false;
        
        lcd.clear();
        lcd.print("Opening");
      }
      
      Serial.println("opening");

      myStepper.step(1000);
      stepsTaken += 1000;
      
      delay(50);
      Serial.print("steps ");
      Serial.println(stepsTaken);
    }
    else
    {
      if(!lcdPerfect)
      {
        lcdClose = false;
        lcdOpen = false;
        lcdPerfect = true;
        
        lcd.clear();
        lcd.print("Perfect");
      }
    }
  }
}
