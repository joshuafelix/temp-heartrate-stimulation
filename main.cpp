#include <Arduino.h>

#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WiFiClient client;

// 🔴 REPLACE THESE
unsigned long channelNumber = 3306095;
const char* apiKey = "16EDTRYT93ZLU6U3";

#define TEMP_PIN 34
#define PULSE_PIN 35

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  ThingSpeak.begin(client);
}

void loop() {
  int tempVal = analogRead(TEMP_PIN);
  float temperature = map(tempVal, 0, 4095, 30, 45);

  int pulseVal = analogRead(PULSE_PIN);
  int bpm = map(pulseVal, 0, 4095, 60, 120);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | BPM: ");
  Serial.println(bpm);

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, bpm);

  ThingSpeak.writeFields(channelNumber, apiKey);

  Serial.println("Data sent to ThingSpeak!");

  delay(15000);
}
