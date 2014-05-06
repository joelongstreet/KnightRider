// Config
int wheelRadius = 35; // in millimeters
int hallEffect = 2; // the pin number of the hall effect sensor


// Calculated via config
float wheelCirc = wheelRadius*2*3.14;


void setup(){
  Serial.begin(9600);
  pinMode(hallEffect, INPUT);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(5, HIGH);
}


int lastEffectState = 0;
unsigned long speedTimer = millis();

int nextKitLight = 6;
int kitDirection = 0;

void loop(){

  if(digitalRead(hallEffect) == HIGH){
    if(lastEffectState == LOW){
      // Calculate Kilometers Per Hour everytime we sense
      // a trigger of the hall effect switch
      unsigned long currentMillis = millis();
      unsigned long millisElapsed = currentMillis - speedTimer;

      float kph = (wheelCirc/millisElapsed)*3.6;

      speedTimer = currentMillis;
      lastEffectState = 1;
      Serial.println(kph);

      // Do the "KIT" Effect
      if(kitDirection == 0){
        digitalWrite(nextKitLight, HIGH);
        if(nextKitLight != 3){
          digitalWrite(nextKitLight-1, LOW);
        } else{
          digitalWrite(4, LOW);
        }

        nextKitLight++;

        if(nextKitLight >= 8){
          nextKitLight = 6;
          kitDirection = -1;
        }
      } else{
        digitalWrite(nextKitLight, HIGH);
        digitalWrite(nextKitLight+1, LOW);
        nextKitLight--;

        if(nextKitLight <= 3){
          nextKitLight = 3;
          kitDirection = 0;
        }
      }
    }
  } else {
    lastEffectState = 0;
  }
}
