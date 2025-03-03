#include <WiFi.h>
#include <esp_now.h>

// Structure to receive message
typedef struct Message {
    char text[64];
} Message;

// New ESP-NOW callback function
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
    Message receivedMessage;
    memcpy(&receivedMessage, incomingData, sizeof(receivedMessage));
    Serial.print("Received: ");
    Serial.println(receivedMessage.text);

}

void setup() {
    Serial.begin(115200);

    // Set device as Wi-Fi station
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed!");
        return;
    }
   

    // Register callback function with updated function signature
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // ESP-NOW works via callback, no need for code here
}
