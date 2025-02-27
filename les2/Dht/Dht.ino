#include <ArduinoJson.h>

JsonDocument doc;
char jsonOut[128];

void setup() {
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(115200);
}

void turnOffAll(){
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
}

void turnOn(int input, bool turnOff){
  if (turnOff == true){
    turnOffAll();  
  }
  digitalWrite(input, HIGH);
}

int getRandomPin(){
  int rndmNumber = random(3);
  Serial.println(String(rndmNumber));
  int returnedPin;

  if (rndmNumber == 0){
    returnedPin = D3;
  }else if (rndmNumber == 1){
    returnedPin = D5;
  }else if (rndmNumber == 2){
    returnedPin = D6;
  }

  return returnedPin;
}

void turnOnRandom(){
  turnOn(getRandomPin(), true);
}

void turnOnWhenLight(int input){
  if (input > 800){
    turnOn(D5, true);
  } else if (input > 900){
    turnOn(D6, true);
  }
}

void loop() {
  int ldr_value = analogRead(A0);
  CreateJSON(int(ldr_value));

  if (isDark(ldr_value) == true){
  Serial.println("dark" );
    turnOn(D3, false);
  } else {
    turnOffAll();
 // Serial.println("turnOffAll" );
  }

delay(100);
  //turnOnWhenLight(ldr_value);
}

bool isDark(int ldrValue){
  bool returnedBool;
  if (ldrValue < 750){
    returnedBool = true;
  } else {
    returnedBool = false;  
  }
  return returnedBool;
}

int lowest = 50;
int highest = 50;
void CreateJSON(int firstKey){
  doc["LDR"] = String(firstKey);
  doc["lowest"] = lowest;
  doc["highest"] = highest;

  if (firstKey < lowest){
    lowest = firstKey;
    doc["lowest"] = firstKey;
  }

  if (firstKey > highest){
    highest = firstKey;
    doc["highest"] = firstKey;
  }

  serializeJson(doc, jsonOut);
  serializeJson(doc, Serial);
  Serial.println();
}

 
