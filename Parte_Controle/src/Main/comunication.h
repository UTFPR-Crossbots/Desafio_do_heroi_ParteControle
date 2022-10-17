
#include <Main/config.h>

#include <esp_now.h>
#include <WiFi.h>



//58:BF:25:32:F9:FC
uint8_t mobilePartAddress[] = PARTE_MOVEL;

bool statusMsg = false;
bool failSend = false ;

typedef struct struct_message {
 
  int PwmRight;
  int PwmLeft;
 
} struct_message;

// Create a struct_message called myData
struct_message infoMotor;

esp_now_peer_info_t peerInfo;

void debug(int left_pwm, int right_pwm){
    Serial.print(" |LEFT: ");
    Serial.print(left_pwm);
    Serial.print(" |RIGHT : ");
    Serial.print(right_pwm);
    Serial.println("");
}
// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  statusMsg = (status == ESP_NOW_SEND_SUCCESS);
  failSend = !statusMsg;
  statusMsg ? digitalWrite(LED_BUILD_IN,LOW) : digitalWrite(LED_BUILD_IN,HIGH);


}
 
void ComSetup() {

 
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    digitalWrite(LED_BUILD_IN,HIGH);
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, mobilePartAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to conect");
    digitalWrite(LED_BUILD_IN,HIGH);
    return;
  }
}
 
bool ComLoop(int PwmLeft, int PwmRight ) {

  
  //debug(PwmLeft,PwmRight);

  // Set values to send
  infoMotor.PwmLeft = PwmLeft;
  infoMotor.PwmRight = PwmRight;
 
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(mobilePartAddress, (uint8_t *) &infoMotor, sizeof(infoMotor));
   
  if (result != ESP_OK) {
   digitalWrite(LED_BUILD_IN,HIGH);
  }

  
  return result == ESP_OK ; 
}
