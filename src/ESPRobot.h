//********************************************************************************************************//
//**This custom library is designed by Walid Bouzidi (SID - 14054035) and Paras Mahajan (SID - 14324134)**//
//********************************************************************************************************//

#ifndef ESPROBOT_H
#define ESPROBOT_H

#include "mbed.h"

class ESPRobot {
public:
    ESPRobot(PinName Rwheel, PinName Lwheel, PinName IN_1, PinName IN_2, PinName IN_3, PinName IN_4);

    // Method prototyping
    void Move_Forward();
    void Curve_Left();
    void Curve_Right();
    void Turn_Right();
    void Turn_Left();
    void Stop();
    void Move_Back();

private:

    // Pin assignment
    PwmOut rightWheel;  // PWM pin for right wheel (PB_10 => D6)
    PwmOut leftWheel;   // PWM pin for left wheel (PB_4 => D5)
    DigitalOut in1;     // in1 direction pin (PB_3 => D3)
    DigitalOut in2;     // in2 direction pin (PB_5 => D4)
    DigitalOut in3;     // in3 direction pin (PA_8 => D7)
    DigitalOut in4;     // in4 direction pin (PC_7 => D9)
    // Variable declaration
    float timePeriod;   // Time period variable
};

#endif