#pragma once

#include <WiFi.h>

#if __has_include("esp_eap_client.h")
#include "esp_eap_client.h"
#else

#include "esp_wpa2.h"
#endif


void setupWifi();

void checkWifi();