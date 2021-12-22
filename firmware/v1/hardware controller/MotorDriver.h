#ifndef MOTORDRIVER_h
#define MOTORDRIVER_h

#include "Motor.h"

class MotorDriver
{

    
private:
    Motor motors[2];
public:
    MotorDriver(int enableAPin, int inputA1, int inputA2, int enableBpin, int inputB1, int inputB2){
        motors[0] = Motor(enableAPin, inputA1, inputA2);
        motors[1] = Motor(enableBpin, inputB1, inputB2);
    }

    void setup(){
        for (int i = 0; i < 2; i++)
        {
            motors[i].setup();
        }
    }

    void set(int index, int speed){
        motors[index].setSpeed(speed);

        // Serial.println("set motor " + String(index) + " Speed " + String(speed) );
    }

    void loop(){
        for (int i = 0; i < 2; i++)
        {
            motors[i].drive();
        }
        
    }
    
};



#endif