#pragma once

#include <Adafruit_NeoPixel.h>

void setup_neopixel();

void run_startup_animation(int time_ms, bool wifi_setup);

void animation_loop(bool button_pressed, ulong button_press_time);

void color_wipe(uint32_t c, int wait);

void sending_lights();