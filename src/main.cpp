
#include <Arduino.h>
#include <Wire.h>

#include <uoaWifi.h>

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println();
  setupWifi();
}
void loop() {
  checkWifi();
  Serial.print("Wifi live!");
  delay(2000);
}