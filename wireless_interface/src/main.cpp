#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <httpToSerial.h>
#include "secrets.h"
#include <LittleFS.h>

// small helper function to get the size of an array at compile time
// without this, we would have to pass the size of the routes array manually
// to the HttpToSerial constructor
template <size_t N>
static constexpr size_t arrSize(PassthroughRoute (&)[N]) {
    return N;
}

const char* motorParameters[] = {"motor", "coord"};
PassthroughRoute routes[] = {
    PassthroughRoute("/motorq", "motor?"),
    std::move(*PassthroughRoute::makeRoute("/motor", "motor", motorParameters))
};


HttpToSerial httpToSerial(
    Serial, 9600, 80,
    "esp8266",
    ACCESS_USERNAME, ACCESS_PASSWORD,
    routes,
    arrSize(routes)
);

void setup() {
    Serial.begin(9600);
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    // clear console
    //Serial.println("\x1b[1;1H\x1b[3J\x1b[1J\x1b[1;1H");
    File file = LittleFS.open("splash.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();

    Serial.println(F("Setup started"));
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int retries = 0;
    const int maxRetries = 30;
    while ((WiFi.status() != WL_CONNECTED) && (retries < maxRetries)) {
        retries++;
        delay(500);
        Serial.print(".");
        wl_status_t status = WiFi.status();
        if(status == WL_CONNECT_FAILED) {
            Serial.println(F("Connection failed!"));
        } else if (status == WL_NO_SSID_AVAIL) {
            Serial.println(F("SSID not available!"));
        }
    }
    Serial.println();
    if (retries > maxRetries-1) {
        Serial.println(F("WiFi connection FAILED"));
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("WiFi connected!"));
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
    Serial.println(F("Setup ready"));
    Serial.flush();
    Serial.end();
    Serial.setTimeout(3000);
    httpToSerial.start();
    Serial.swap();
}

void loop() {
    httpToSerial.loop();
}
