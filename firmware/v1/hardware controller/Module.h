#ifndef Module_h
#define Module_h

#include <Arduino.h>
#include <NeoSWSerial.h>


#define SerialCallback void (*_callback)(char*, unsigned int)


class Module
{

private:
    NeoSWSerial _module; 
    byte _buffer[256];
    int _bufferIndex =0;
    bool useCallback = false;
    bool hasData = false;

protected:
    SerialCallback;
public:
    Module(int rx, int tx){
        _module = NeoSWSerial(rx,tx);
    }

    void begin(long baudrate){
        _module.begin(baudrate);
        clear();
    }

    int read(){
        if(_module.available() > 0){
           return _module.read();
        }
    }

    void setCallback(SerialCallback){
        this->_callback = _callback;
        useCallback = true;
    }

    int available(){
        return _module.available();
    }

    void readString(){
        if(_module.available()){

            _buffer[_bufferIndex++] = _module.read();
            if(_buffer[_bufferIndex -1] == '\n' && _buffer[_bufferIndex -2] == '\r'){
                if(useCallback){
                    _callback(_buffer, _bufferIndex);
                    clear();
                }else{
                    hasData = true;
                }
            }
            //delay(1);
        };
        if(_bufferIndex == 255){
            clear();
        }
    }

    bool hasAvailable(){
        return hasData;
    }

    char* getBuffer(){
        return _buffer;
    }

    int getLength(){
        return _bufferIndex;
    }

    void clear(){
         for (int i = 0; i < 256; i++)
         {
            _buffer[i] = 0;
         }
        _bufferIndex = 0;
        hasData = false;
    }

    void write(int val){
        _module.write(val);
    }

    void println(String val){
        _module.println(val);
    }
    
};

#endif