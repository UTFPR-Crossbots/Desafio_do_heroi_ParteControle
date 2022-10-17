#include <PS4Controller.h>
#include <Main/config.h>
int cmd_linear ;
int cmd_angular ;

void PS4setup() {
 
  PS4.begin(ESP_MAC);
 
}

int ps4Linear() {

  cmd_linear = 0;

  if(PS4.Square()){
    cmd_linear = PS4.LStickY();
  }
 
   return cmd_linear ;
  
}
int ps4Angular() {
  cmd_angular = 0;

  if(PS4.Square()){
    cmd_angular = PS4.LStickX();
  }
 
   return cmd_angular ;
  
}
 
bool ps4Connected(){
    return PS4.isConnected();
}

void debugPs4(){
    Serial.print("| Linear: ");
    Serial.print(cmd_linear);
    Serial.print("| Angular: ");
    Serial.print(cmd_angular);
    Serial.println("");

}