#include <NeopixelAnimation.h>
#define CLEAR_COLOUR 0, 0, 0
#define WHITE_COLOUR 255, 255, 255
#define RED_COLOUR 255, 10, 10
#define GREEN_COLOUR 10, 255, 10

#define STANDBY_COLOUR 20, 12, 10

constexpr int NEOPIXEL_PIN = 16;
constexpr int LED_COUNT = 24;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup_neopixel() {
    strip.begin();
    strip.setBrightness(100);
    strip.clear();
    strip.show();
}

void run_startup_animation(int time_ms, bool wifi_setup) {
    uint32_t cycle_colour = wifi_setup ? strip.Color(STANDBY_COLOUR) : strip.Color(RED_COLOUR);

    Serial.println("Running startup animation");
    color_wipe(cycle_colour, time_ms);
    Serial.println("Finished startup animation");

}

void animation_loop(bool button_pressed, ulong button_press_time) {
    ulong max_press = 2500;
    ulong blink_speed = 400;

    strip.setBrightness(255);

    if (!button_pressed) {
        strip.fill(strip.Color(STANDBY_COLOUR));
        strip.show();
        return;
    }

    if (button_press_time > max_press) {
        int blink_toggle = (button_press_time - max_press) % blink_speed;
        float brightness = blink_toggle / (float)blink_speed;
        strip.setBrightness(brightness*255);
        strip.fill(strip.Color(WHITE_COLOUR));

        strip.show();
        return;
    }

    float percent_press = (float)button_press_time / max_press;
    int num_leds = (int)(percent_press * LED_COUNT);

    Serial.println(percent_press);

    strip.fill(strip.Color(STANDBY_COLOUR));
    for (int i = 0; i < num_leds; i++) {
        strip.setPixelColor(i, strip.Color(WHITE_COLOUR));
    }


    strip.show();
}

void sending_lights() {
    strip.fill(strip.Color(GREEN_COLOUR));
    strip.show();
}

void color_wipe(uint32_t c, int wait) {
    int pixel_groups = (int)strip.numPixels() / 2;

    int delay_per_pixel = wait / pixel_groups;
    for (uint16_t i = 0; i < pixel_groups; i++) {
        delay(delay_per_pixel);
        strip.setPixelColor(i, c);
        strip.setPixelColor(i+pixel_groups, c);
        strip.show();
    }
}
