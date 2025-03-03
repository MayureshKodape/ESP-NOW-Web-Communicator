# ESP-NOW-Web-Communicator
ESP-NOW Web Messenger enables wireless communication between two ESP32s using ESP-NOW in half-duplex mode. One ESP32 hosts a web page with a user input field and send button to transmit messages, while the second ESP32 receives and processes them. Ideal for remote control, IoT, and real-time data exchange without Wi-Fi or internet.

Important point:- Now protocol is only used,for Esp microntroller.

Theory Part:-
1)Esp-32 is a wireless communication protocol devloped by Espressit(Esp 32, Esp 8266).
2)It allows multiple Esp32 devices to communicate directly with each other without WIFI or BLUETOOT.
->No wifi Required.
->Low power Consumtion.
->BroadCast & peer to peer :- You can send the message to one or mutiple devices at once
->secure communication :- Support encrpytion using AES-CCM

Technical Things;-
1)Device communication using their MAC Adresses.
2)One device can act as a controller(Master) or just peer
3)Message are small, typically up to 250 bytes

Settings UP ESP-Now communication
1)Initialize the ESP-NOW Library
2)Add a peer (another ESP device)using ESP-NOW
3)Sending and receving data using ESP-NOW funtions.

Data Transmission Modes
1)One to One communication
2)Broadcast one to many communication

ESP-NOW vs WIFI vs Bluetoot
1) ESP_NOW :- Best for low-power , fast ,direct communication
2) Wifi :- Best for internet based Communication
3) bluetoot:- Best for Short-Ranges Pairing with Smartphones

Typicaly Range of ESP-NOW 
1)Indoors :- 30 - 50 meter's
2)Outdoor :- ~100 - 200 meter's
3)With Extra Anteena :- Over 500 meters

project:-
ESP-NOW-WEB-Communicator
->In this project we are using NOW protocol for communication between esp32 microcontroller(ESP32_WROOM (Sender) and Esp32 Dev(Receiver)) and it is half-duplex.

Step 1) :- First have the mac address of Esp32 (its Half-duplex so only, Receiver side mac addresses is required)
This below code gives mac address of esp microcontroller(every MAC - Address is unique of each ESP32)

#include <WiFi.h>
#include <esp_wifi.h>void readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial.println("Failed to read MAC address");
  }
}void setup(){
  Serial.begin(115200);  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();
}void loop(){}

step 2) In sender side code add the receiver MAC addres 
              uint8_t peerMacAddress[] = {0x94, 0x09, 0x7e, 0x4e, 0x85, 0x08};
Add the Id (ssid) and Password (password) of Wifi
              const char* ssid = "WIFI_Name";
              const char* password = "Password";
step 3) Flash the code 
       Result :-    Connected
                 Ip = xx:xx:xx:xx:xx
step 4) Take the receiving ip and put it in Browser
       -> it will open the web-webpage (The Wifi you have given to Esp-Microcontroller , use same wifi to your Browser(Pc,Mobile,etc...))
step 5) Flash the receiving-code in another Esp32(to receiving the message from the sender)

  You are good to goo...
  Send the message from the web-browser and receving the data 

