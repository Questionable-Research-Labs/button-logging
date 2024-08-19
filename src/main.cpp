
#include <Arduino.h>
#include <Bounce2.h>
#include <Wire.h>
#include <database.h>
#include <neopixelAnimation.h>
#include <uoaWifi.h>

const int BUTTON_PIN = 14;
const int LED_PIN = LED_BUILTIN;

bool button_pressed = 0;
uint button_pressed_start = 0;

// INSTANTIATE A Button OBJECT FROM THE Bounce2 NAMESPACE
Bounce2::Button button = Bounce2::Button();

void setup() {
    Serial.begin(115200);

    setup_neopixel();
    run_startup_animation(1000, false);	 // Hold on 1s for serial to initialize

    // initialize built-in LED as an output
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println();
    setupWifi();
    run_startup_animation(1000, true);	// Let user know wifi is connected

    // Button uses the built-in pull up register.
    button.attach(BUTTON_PIN, INPUT_PULLUP);
    button.interval(25);
    button.setPressedState(LOW);

    // Check if the button was pressed while booting
    if (button.read() == LOW) {
      Serial.println("setup(): button was pressed while booting");
    }
}
void loop() {
    checkWifi();
    animation_loop(button_pressed, millis() - button_pressed_start);
    button.update();

    if (!button.changed()) {
      return;
    }

    if (button.pressed()) {
      digitalWrite(LED_PIN, HIGH);
      button_pressed = true;
      button_pressed_start = millis();

      Serial.println("Button was pressed");

    } else if (button.released()) {
      digitalWrite(LED_PIN, LOW);
      button_pressed = false;

      uint pressTime = millis() - button_pressed_start;
      Serial.print("Button was pressed for ");
      Serial.print(pressTime);
      Serial.println("ms");
      
      sending_lights();
      sendToDB(pressTime);
    }
}