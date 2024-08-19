#include "uoaWifi.h"

int counter = 0;

void setupWifi() {
    Serial.print("Connecting to network: ");
    Serial.println(WIFI_SSID);
    Serial.print("Username:");
    Serial.println(WIFI_USERNAME);
    WiFi.disconnect(true);  // disconnect form wifi to set new wifi connection
    WiFi.mode(WIFI_STA);    // init wifi mode
#if __has_include("esp_eap_client.h")
    esp_eap_client_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));	 // provide identity
    esp_eap_client_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));	 // provide username
    esp_eap_client_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));	 // provide password
    esp_wifi_sta_enterprise_enable();
#else
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME));  // provide identity
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME));  // provide username --> identity and username is same
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)WIFI_PASSWORD, strlen(WIFI_PASSWORD));  // provide password
    esp_wifi_sta_wpa2_ent_enable();
#endif
    WiFi.begin(WIFI_SSID);  // connect to wifi
    while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
	counter++;
	if (counter >= 60) {  // after 30 seconds timeout - reset board
	    ESP.restart();
	}
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address set: ");
    Serial.println(WiFi.localIP());  // print LAN IP
}

void checkWifi() {
    if (WiFi.status() == WL_CONNECTED) {	 // if we are connected to Eduroam network
	counter = 0;				 // reset counter
    } else if (WiFi.status() != WL_CONNECTED) {	 // if we lost connection, retry
	Serial.println("WiFi connection lost, retrying...");
	WiFi.begin(WIFI_SSID);
    }
    while (WiFi.status() != WL_CONNECTED) {  // during lost connection, print dots
	delay(500);
	Serial.print(".");
	counter++;
	if (counter >= 60) {  // 30 seconds timeout - reset board
	    ESP.restart();
	}
    }
}