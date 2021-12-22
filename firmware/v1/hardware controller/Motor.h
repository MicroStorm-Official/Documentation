#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor
{
private:
    int _enablePin;
    int _inputA;
    int _inputB;
    int _speed = 0;
    bool _backward = false;

public:
    Motor(){}

    Motor(int enablePin, int inputA, int inputB)
    {
        _enablePin = enablePin;
        _inputA = inputA;
        _inputB = inputB;
    }

    void setup()
    {
        pinMode(_enablePin, OUTPUT);
        pinMode(_inputA, OUTPUT);
        pinMode(_inputB, OUTPUT);
    }

    void setSpeed(int speed)
    {
        _backward = speed < 0;
        if(_backward){
            _speed = speed * -1;
        }else{
            _speed = speed;
        }
        if(speed > 125){
            speed = 125;
        }
        // Serial.println("Motor speed updated");
        // delay(5000);
         if (_backward)
        {
            digitalWrite(_inputA, LOW);
            digitalWrite(_inputB, HIGH);
        }
        else
        {
            digitalWrite(_inputA, HIGH);
            digitalWrite(_inputB, LOW);
        }
    }

    void drive()
    {
        // Serial.println(String(_inputA) + ":" + String(_inputB) + ":" + String(_enablePin) + ":" + String(_speed));
       
        analogWrite(_enablePin, _speed);
    }
};

#endif