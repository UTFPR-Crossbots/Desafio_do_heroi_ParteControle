#include <Arduino.h>

#define SERIAL_RATE 115200
#define PARTE_MOVEL {0x58, 0xBF, 0x25, 0x32, 0xF9, 0xFC} //get by get_mac.cpp in Example/ESP_NOW
#define REFRESH_RATE 100 //millis 
#define LED_BUILD_IN 2 //pinOut esp


// changed the mac that the control connects to to the mac to this esp (4dots)
#define ESP_MAC "58:BF:25:33:3A:38" //same information diferent format

#define PS4_CONTROLER 1 //switch between PS4 and MPU controler 
#define MPU 0

// info for the cinematic
#define RADIUS 10 //mili
#define L 0.90

//notes this code almost blow up the memory i had to ad board_build.partitions = huge_app.csv this line so it works 
//dont ask me questions about i dont know why works 