#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <esp_now.h>

// Replace with your network credentials
const char* ssid = "Mayuresh";
const char* password = "okokokok";


//esp32 dev mac
//ESP32 Board MAC Address: 94:b9:7e:4e:85:08
//esp32 wroom
//ESP32 Board MAC Address: ac:15:18:d7:9a:5c

// ESP-NOW peer MAC address (Replace with ESP32 (2) MAC address)
uint8_t peerMacAddress[] = {0x94, 0xb9, 0x7e, 0x4e, 0x85, 0x08};

AsyncWebServer server(80);

// Structure to hold message data
typedef struct Message {
    char text[32];
} Message;

esp_now_peer_info_t peerInfo;

// Callback for ESP-NOW data sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Message Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent" : "Failed");
}

// Send ESP-NOW message function
void sendMessage(const char* msg) {
    Message message;
    strncpy(message.text, msg, sizeof(message.text));
    esp_now_send(peerMacAddress, (uint8_t *) &message, sizeof(message));
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi (Station Mode)
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
      Serial.println("\nConnected to Wi-Fi!");
      Serial.print("ESP32 IP Address: ");
      Serial.println(WiFi.localIP()); 
      
    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed!");
        return;
    }

    // Register send callback
    esp_now_register_send_cb(OnDataSent);

    // Add peer
    memcpy(peerInfo.peer_addr, peerMacAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    // Web Server Setup
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<html><body>";
        html += "<h2>ESP32 Web Page</h2>";
        html += "<button onclick=\"sendData('Esp32 Kem cho?Majama chu!')\">Send</button>";
        html += "<input type='text' id='userInput' placeholder='Type message'>";
        html += "<button onclick=\"sendUserInput()\">Send Input</button>";
        html += "<script>";
        html += "function sendData(msg) { fetch('/send?message=' + msg); }";
        html += "function sendUserInput() { var userText = document.getElementById('userInput').value; fetch('/send?message=' + userText); }";
        html += "</script>";
        html += "</body></html>";
        request->send(200, "text/html", html);
    });

    server.on("/send", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("message")) {
            String message = request->getParam("message")->value();
            sendMessage(message.c_str());
            request->send(200, "text/plain", "Message Sent: " + message);
            
        }
    });

    server.begin();
}

void loop() {
    // No need to do anything here, everything is handled in callbacks
}
