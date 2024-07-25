#include <WiFi.h>
#include "esp_wpa2.h" // Include the necessary header file for WPA2 Enterprise

// WiFi credentials
const char* ssid = "UoA-WiFi";
const char* identity = "username";  // e.g., your_username@domain.com
const char* password = "password";  // Also known as the PEAP password
const char* ca_cert = "";  // Optionally, add a CA cert in PEM format

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Disconnect any existing WiFi connection
  WiFi.disconnect(true);
  delay(1000);

  // Configuring the ESP32 to use WPA2 Enterprise
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  // WPA2 Enterprise configuration
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t*)identity, strlen(identity));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t*)identity, strlen(identity));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t*)password, strlen(password));

  // Optionally, you can add a CA certificate
  if (strlen(ca_cert) > 0) {
    esp_wifi_sta_wpa2_ent_set_ca_cert((uint8_t*)ca_cert, strlen(ca_cert) + 1);
  }

  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  if (esp_wifi_sta_wpa2_ent_enable(&config) != ESP_OK) {
    Serial.println("WPA2 Enterprise config failed");
    return;
  }

  WiFi.begin();

  // Attempt to connect to the WiFi network
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connection successful
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Add your main code here
}