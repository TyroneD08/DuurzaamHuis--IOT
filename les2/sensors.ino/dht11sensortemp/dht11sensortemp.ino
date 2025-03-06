#include "DHT.h"
#include <ArduinoJson.h> 
#define DHTTYPE DHT11

uint8_t DHTPin = D7;
DHT dht(DHTPin, DHTTYPE);

float Temperature, Humidity, HeatIndex;

void setup() {
  Serial.begin(9600); // Start de seriële communicatie
}

void loop() {
  ReadDHT11();
  delay(6000); // Wacht 6 seconden voordat de sensor opnieuw wordt uitgelezen
  
  int ldrValue = analogRead(A0);
  JsonDocument doc;
  doc["temperature"] = Temperature;
  doc["humidity"] = Humidity;
  doc["light"] = ldrValue;

  serializeJson(doc, Serial);
  Serial.println();

  delay(2000); 
  
}

void ReadDHT11() {
  float temperature = round(dht.readTemperature() * 10) / 10;
  float humidity = round(dht.readHumidity() * 10) / 10;
  float heatIndex = round(dht.computeHeatIndex(temperature, humidity, false) * 10) / 10;

  if (isnan(temperature) || isnan(humidity) || isnan(heatIndex)) {
    Serial.println("DHT11 sensor error");
  } else {
    Temperature = temperature;
    Humidity = humidity;
    HeatIndex = heatIndex;

    Serial.print("Temp: " + String(Temperature) + " C");
    Serial.print("  Humidity: " + String(Humidity) + " %");
    Serial.println("  HeatIndex: " + String(HeatIndex));
  }

}
