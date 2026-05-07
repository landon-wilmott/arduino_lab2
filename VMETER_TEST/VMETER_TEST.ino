#include "Arduino.h"

#define V_METER A1

#define LED_6 10
#define LED_7 11
#define LED_8 12

// set up different led values;
#define FULL_CHARGE 0
#define MEDIUM_CHARGE 1
#define LOW_CHARGE 2
#define NO_CHARGE 3

#define FULL 4.5



// voltage value
int LedLightAction = 0;
int LedLightDetection = 0;

float getPinVoltage(int pin) {
  //This function can be used for many different tasks in the labs
  //Study this line of code to understand what is going on!!
  //What does analogRead(pin) do?
  //Why is (float) needed?
  //Why divide by 1024?
  //Why multiply by 5?
  return 5 * (float)analogRead(pin) / 1024;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(V_METER, INPUT);
  
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(getPinVoltage(V_METER));
  Serial.print("\n");

  fsmVoltagePerception();
  fsmVoltageDetection();
  fsmVoltageAction();
}


void fsmVoltagePerception(){
  float pinValue = getPinVoltage(V_METER);
  if(pinValue > (.9 * FULL)) {
    LedLightDetection = FULL_CHARGE;
  } else if (pinValue > (.8 * FULL)){
    LedLightDetection = MEDIUM_CHARGE;
  } else if (pinValue > (.7 * FULL)){
    LedLightDetection = LOW_CHARGE;
  } else {
    LedLightDetection = NO_CHARGE;
  }
}
void fsmVoltageDetection(){
  switch(LedLightDetection){
    case 0:
     LedLightAction = 3;
     break;
     
    case 1:
     LedLightAction = 2;
     break;
     
    case 2:
     LedLightAction = 1;
     break;

    case 3:
     LedLightAction = 0;
     break;

    default:
     LedLightAction = 0;
  }
}

void fsmVoltageAction(){
  switch(LedLightAction){
    case 3:
     doTurnLedOn(LED_6);
     doTurnLedOn(LED_7);
     doTurnLedOn(LED_8);
     break;
     
    case 2:
     doTurnLedOff(LED_6);
     doTurnLedOn(LED_7);
     doTurnLedOn(LED_8);
     break;
     
    case 1:
     doTurnLedOff(LED_6);
     doTurnLedOff(LED_7);
     doTurnLedOn(LED_8);
     break;

    case 0:
     doTurnLedOff(LED_6);
     doTurnLedOff(LED_7);
     doTurnLedOff(LED_8);
     break;

    default:
     doTurnLedOff(LED_6);
     doTurnLedOff(LED_7);
     doTurnLedOff(LED_8);
     break;
  }
}


// Function to turn LED on
void doTurnLedOn(int led_pin)
{
  digitalWrite(led_pin, HIGH);
}

// Function to turn LED off
void doTurnLedOff(int led_pin){
  digitalWrite(led_pin, LOW);
}
