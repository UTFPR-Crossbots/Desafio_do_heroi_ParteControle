
#include <Main/config.h>

// ref https://en.wikipedia.org/wiki/Differential_wheeled_robot
//turn linear ang angular speed in the speed for left and right motors 

float cinematic_left(float linear, float angular,float gain){
  
  return gain*(linear + angular*(L/2));
}

//return right wheel speed in radians/sec 
float cinematic_right(float linear, float angular, float gain){
 
  return gain*(linear - angular*(L/2));
}