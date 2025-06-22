#include "mbed.h"
#include "ESPRobot.h"

// Sensor analog pin assignment
AnalogIn IrSensor_F(PC_1); // RED wire A4
AnalogIn IrSensor_R(PA_0); // Blue wire A2
AnalogIn IrSensor_L(PA_4); // Orange wire A0

// Serial communication using UART
Serial pc(USBTX, USBRX, 9600); // Serial Communication Initialization (TX, RX, Baud rate)

// Bluetooth Serial 
Serial bluetooth(PA_9, PA_10); // TX, RX (assuming UART pins)

// TIMER FOR INTERRUPT 
Ticker timer;

// Volatile boolean variables to indicate movement update flags
volatile bool updateMovement1 = false;
volatile bool updateMovement2 = false;
volatile bool updateMovement3 = false;
volatile bool updateMovement4 = false;
volatile bool updateMovement5 = false;
volatile bool updateMovement6 = false;
volatile bool updateMovement7 = false;
volatile bool updateMovement8 = false;
volatile bool mode = false;

// Variables to store sensor values
 float IR_val_F = 0.0;
 float IR_val_R = 0.0;
 float IR_val_L = 0.0;

 float Thrsh = 18.0; // Distance threshld (cm)
 
 char recv;   // Variable to store bluetooth received data
 
// Instantiation of robot object of the class ESPRobot
ESPRobot robot(PB_10, PB_4, PB_3, PB_5, PA_8, PC_7);

// ISR Prototyping
 void Do_MovementISR();


int main()
{
  
   // Attach the Do_MovementISR function to the timer interrupt
    timer.attach(&Do_MovementISR, 0.0001); // Set timer interval to 0.0001 seconds

    while(1){
        // Read sensor data
        IR_val_F = (7.4f / IrSensor_F.read()); // Read Front sensor
        IR_val_R = (7.4f / IrSensor_R.read()); // Read Right sensor
        IR_val_L = (7.4f / IrSensor_L.read()); // Read Left sensor

        // Conditions to check location of the object
        if (IR_val_R > Thrsh  &&  IR_val_F > Thrsh  &&  IR_val_L < Thrsh){ // If objected detected in Left

              updateMovement1 = true;

        }

        if (IR_val_R > Thrsh  &&  IR_val_F < Thrsh  &&  IR_val_L > Thrsh){ // If objected detected in Front, 

            updateMovement2 = true;

        }

        if (IR_val_R > Thrsh  &&  IR_val_F < Thrsh  &&  IR_val_L < Thrsh){ // If objected detected in Front, Left

              updateMovement3 = true;

        }

        if (IR_val_R < Thrsh  &&  IR_val_F > Thrsh  &&  IR_val_L > Thrsh){ // If objected detected in Right,

            updateMovement4 = true;

        }

        if (IR_val_R < Thrsh  &&  IR_val_F > Thrsh  &&  IR_val_L < Thrsh){ // If objected detected in Right, Left

            updateMovement5 = true;

        }

        if (IR_val_R < Thrsh  &&  IR_val_F < Thrsh  &&  IR_val_L > Thrsh){ // If objected detected in Front, Right

            updateMovement6 = true;

        }

        if (IR_val_R < Thrsh  &&  IR_val_F < Thrsh  &&  IR_val_L < Thrsh){ // If objected detected in Front, Right, Left

          updateMovement7 = true;

        }

        else{

          updateMovement8 = true;   // Object not found

        }

      // Check if data is readable form bluetooth
      // If yes, change the mode   
        if (bluetooth.readable()) {
              mode = true ;
        }

      // IF MODE IS CHANGED TO TRUE, GO TO BLUETOOTH CONTROL MODE
        while(mode){
        recv = bluetooth.getc();   // bluetooth reading

        bluetooth.printf("Received character from Bluetooth: %c\n", recv);
        switch (recv){
            
            case 'a' :                     // control command Forward
                updateMovement8 = true;
            break;

            case 's' :                     // control command Left
                robot.Curve_Left();
            break;

            case 'd' :                     // control command Right
                robot.Curve_Right();
            break;

            case 'f' :                     // control command Stop
                updateMovement7 = true;   
            break;

            case 'z' :                     // control command Back
                robot.Move_Back();
            break;

            case 'w' :                     // control command auto to manual or vice versa
                mode = false ;                 // IF MODE IS CHANGED TO FALSE, GO TO AUTONOMOUS CONTROL MODE

            }
        }
    }
}


// Interrupt Service Routine
void Do_MovementISR(){
    
    // Execute movement based on flags set by external events
    if (updateMovement1) {
      robot.Turn_Right(); 
      updateMovement1 = false; // Reset the flag
      }

    if (updateMovement2) {
      robot.Turn_Left(); 
      updateMovement2 = false; // Reset the flag
      }

    if (updateMovement3) {      
      robot.Turn_Right(); 
      updateMovement3 = false; // Reset the flag
      }

    if (updateMovement4) {
      robot.Turn_Left(); 
      updateMovement4 = false; // Reset the flag
      }

    if (updateMovement5) {
      robot.Move_Forward();   
      updateMovement5 = false; // Reset the flag
      }

    if (updateMovement6) {
      robot.Turn_Left(); 
      updateMovement6 = false; // Reset the flag
      }

    if (updateMovement7) {
      robot.Stop();
      updateMovement7 = false; // Reset the flag
      } 

    if(updateMovement8){
      robot.Move_Forward(); 
      updateMovement8 = false; // Reset the flag
      }

}