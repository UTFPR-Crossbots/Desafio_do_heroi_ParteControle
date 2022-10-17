
#include <Main/config.h>

#include <Main/comunication.h>
#include <Main/ps4.h>
#include <Main/cinematic.h>
#include <Main/tools.h>

//global 
int linear = 0 ;
int angular = 0;
int left_pwm = 0;
int right_pwm = 0;

bool comStatus = false;

int controlMode = PS4_CONTROLER;
// int controlMode =  MPU;


void debug(){
    Serial.print(" |right: ");
    Serial.print(right_pwm);
    Serial.print(" |left: ");
    Serial.print(left_pwm);
    Serial.println("");
}
void setup() {

  pinMode(OUTPUT,LED_BUILD_IN);
  digitalWrite(LED_BUILD_IN,LOW);

  // Init Serial Monitor
  Serial.begin(SERIAL_RATE);
  
  ComSetup();
  if(controlMode){
    PS4setup();
  }

}
 
void loop() {
  if(controlMode){

    if(ps4Connected){
      linear = ps4Linear();
      angular = ps4Angular();
    }
    else{
      Serial.println(" DISCONECTED ");
      linear = 0;
      angular = 0;
    }
    // debugPs4();
  }
  else{
    //conect here the mpu controls 
    Serial.println("MPU");
  }
    //maps the output from the controler (0-127 forward and backwards to pwm 10 bits)
    linear = map(linear,-127, 127,-1023,1023);
    angular = map(angular,-127, 127,-1023,1023);

    //turn linear and angular speeds to right and left motor speed 
    left_pwm = cinematic_left(linear,angular,2.0);
    right_pwm = cinematic_right(linear,angular,2.0);

    //satured so dosnt go over 1023 or under -1023 
    left_pwm = saturated(left_pwm,1023);
    right_pwm = saturated(right_pwm,1023);

    debug();
 
    //send to mobile part return if the com is okay -- i dont do anything with that 
    comStatus = ComLoop(left_pwm,right_pwm);

  delay(REFRESH_RATE);
}