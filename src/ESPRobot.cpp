//********************************************************************************************************//
//**This custom library is designed by Walid Bouzidi (SID - 14054035) and Paras Mahajan (SID - 14324134)**//
//********************************************************************************************************//

#include "mbed.h"
#include "ESPRobot.h"

ESPRobot::ESPRobot(PinName Rwheel, PinName Lwheel, PinName IN_1, PinName IN_2, PinName IN_3, PinName IN_4)
    : rightWheel(Rwheel), leftWheel(Lwheel), in1(IN_1), in2(IN_2), in3(IN_3), in4(IN_4), timePeriod(0.1) {}

// timePeriod variable indicates time period of PWM wave.
// Percentage duty cycle values are used for PWM pins.
// Motor direction is controlled by setting in1, in2, in3 and in4 pins of H-bridge driver.

// Method fucntion declaration for the class.
void ESPRobot::Move_Forward() {
    in1.write(0); 
    in3.write(0); 
    in2.write(1); 
    in4.write(1);
    rightWheel.period(timePeriod);
    rightWheel.write(0.90);
    leftWheel.period(timePeriod);
    leftWheel.write(0.90);
}

void ESPRobot::Stop() {
    in1.write(0); 
    in3.write(0); 
    in2.write(0); 
    in4.write(0);
    rightWheel.period(timePeriod);
    rightWheel.write(0.90);
    leftWheel.period(timePeriod);
    leftWheel.write(0.90);
}

void ESPRobot::Turn_Left() {
    in1.write(0); 
    in3.write(1); 
    in2.write(1); 
    in4.write(0); 
    rightWheel.period(timePeriod);
    rightWheel.write(0.90);
    leftWheel.period(timePeriod);
    leftWheel.write(0.90);
}

void ESPRobot::Turn_Right() {
   in1.write(1); 
    in3.write(0); 
    in2.write(0); 
    in4.write(1);
    rightWheel.period(timePeriod);
    rightWheel.write(0.90);
    leftWheel.period(timePeriod);
    leftWheel.write(0.90);
}

void ESPRobot::Curve_Right() {
    in1.write(0); 
    in3.write(0); 
    in2.write(1); 
    in4.write(1);
    rightWheel.period(timePeriod);
    rightWheel.write(0.30);
    leftWheel.period(timePeriod);
    leftWheel.write(0.80);
}
void ESPRobot::Curve_Left() {
    in1.write(0); 
    in3.write(0); 
    in2.write(1); 
    in4.write(1);
    rightWheel.period(timePeriod);
    rightWheel.write(0.80);
    leftWheel.period(timePeriod);
    leftWheel.write(0.30);
}

void ESPRobot::Move_Back() {
    in1.write(1); 
    in3.write(1); 
    in2.write(0); 
    in4.write(0);
    rightWheel.period(timePeriod);
    rightWheel.write(0.90);
    leftWheel.period(timePeriod);
    leftWheel.write(0.90);
}