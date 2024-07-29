
#include <Arduino.h>
#include <AceButton.h>
#include <Wire.h>
#include <uoaWifi.h>
#include <neopixelAnimation.h>
#include <database.h>

using namespace ace_button;


const int BUTTON_PIN = 7;
const int LED_PIN = LED_BUILTIN;

bool button_pressed = 0;
uint button_pressed_start = 0;

AceButton button(BUTTON_PIN);

void handleEvent(AceButton* /* button */, uint8_t eventType, uint8_t buttonState) {

  // Print out a message for all events.
  Serial.print(F("handleEvent(): eventType: "));
  Serial.print(AceButton::eventName(eventType));
  Serial.print(F("; buttonState: "));
  Serial.println(buttonState);

  // Control the LED only for the Pressed and Released events.
  // Notice that if the MCU is rebooted while the button is pressed down, no
  // event is triggered and the LED remains off.
  switch (eventType) {
    case AceButton::kEventPressed:
      digitalWrite(LED_PIN, HIGH);
      button_pressed = true;
      button_pressed_start = millis();

      break;
    case AceButton::kEventReleased:
      digitalWrite(LED_PIN, LOW);
      button_pressed = false;

      uint pressTime = millis() - button_pressed_start;
      Serial.print("Button was pressed for ");
      Serial.print(pressTime);
      Serial.println("ms");

      sendToDB(pressTime);
      break;
  }
}

void setup() {
    Serial.begin(115200);

    setup_neopixel();
    run_startup_animation(1000, false); // Hold on 1s for serial to initialize
    

    Serial.println();
    setupWifi();
    run_startup_animation(1000, true); // Let user know wifi is connected

    // initialize built-in LED as an output
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Button uses the built-in pull up register.
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    ButtonConfig* buttonConfig = button.getButtonConfig();
    buttonConfig->setEventHandler(handleEvent);

    // Check if the button was pressed while booting
    if (button.isPressedRaw()) {
      Serial.println("setup(): button was pressed while booting");
    }
}
void loop() {
    checkWifi();
    animation_loop(button_pressed, button_pressed_start - millis());
    delay(100);
}