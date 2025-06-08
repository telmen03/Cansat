#include <WiFi.h>
#include <esp_now.h>

// Replace with your receiver's MAC address
uint8_t broadcastAddress[] = {0x8C, 0x4F, 0x00, 0x3A, 0x13, 0x38};

// Structure to send data
typedef struct struct_message {
  int id;
  float temperature;
  float humidity;
} struct_message;

struct_message myData;

void setup() {
  Serial.begin(115200);

  // Set device as Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Callback on data sent
  esp_now_register_send_cb([](const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  });
}

void loop() {
  myData.id = 1;
  myData.temperature = random(20, 30);
  myData.humidity = random(40, 60);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(2000);
}
