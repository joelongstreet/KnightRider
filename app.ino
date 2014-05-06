// Config
int wheelRadius = 35; // in millimeters
int hallEffect = 2; // the pin number of the hall effect sensor


// Calculated via config
float wheelCirc = wheelRadius*2*3.14;


void setup(){
  Serial.begin(9600);
  pinMode(hallEffect, INPUT);
}


int lastEffectState = 0;
unsigned long speedTimer = millis();

void loop(){

  // Calculate Kilometers Per Hour everytime we sense
  // a trigger of the hall effect switch
  if(digitalRead(hallEffect) == HIGH){
    if(lastEffectState == LOW){
      unsigned long currentMillis = millis();
      unsigned long millisElapsed = currentMillis - speedTimer;

      float kph = (wheelCirc/millisElapsed)*3.6;

      speedTimer = currentMillis;
      lastEffectState = 1;

      Serial.println(kph);
    }
  } else {
    lastEffectState = 0;
  }
}
