#ifndef Module_h
#define Module_h

#include <Arduino.h>

// #define SerialCallback void (*_callback)(byte*, unsigned int length)
#define SerialCallback void (*_callback)(String data)

class Module
{

private:
    SerialCallback;
    char _buffer[100];
    int _bufferIndex = 0;

public:
    Module() {}

    void begin(long baudrate)
    {
        Serial.begin(baudrate);
        clear();
    }

    void setCallback(SerialCallback)
    {
        this->_callback = _callback;
    }

    int available()
    {
        return Serial.available();
    }

    void listen()
    {
        if (Serial.available())
        {
            _buffer[_bufferIndex++] = Serial.read();
            if (_buffer[_bufferIndex - 1] == '\n' && _buffer[_bufferIndex - 2] == '\r')
            {
                String dataString = "";
                for (int i = 0; i < _bufferIndex - 1; i++)
                {
                    dataString += _buffer[i];
                }
                _callback(dataString);
                clear();
            }
            else if (_bufferIndex > 60)
            {
                clear();
            }
        };
    }

    void clear()
    {
        for (int i = 0; i < _bufferIndex; i++)
        {
            if(i >= 100){
                break;
            }
            _buffer[i] = 0;
        }
        _bufferIndex = 0;
    }

    void write(int val)
    {
        Serial.write(val);
    }

    void printString(String val)
    {
        Serial.println(val);
    }
};

#endif
