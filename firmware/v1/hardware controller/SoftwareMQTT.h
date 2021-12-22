#ifndef SOFTWAREMQTT_h
#define SOFTWAREMQTT_h

#include <Arduino.h>
#include "Module.h"

#define SubCallback void (*_subCallback)(const String)

class SoftwareMQTT : public Module
{

    struct Subscription
    {
        String topic;
        SubCallback;
    };

    struct Publish
    {
        String topic;
        String data;
    };

private:
    Subscription substriptions[10];
    Publish publishes[5];
    int subIndex = 0;
    int pubIndex = 0;

private:
    void handle(char *payload, unsigned int length)
    {
        String dataString = "";
        for (int i = 0; i < length - 2; i++) // don't include  \r\n so last 2 chars
        {
            dataString += payload[i];
        }
        // Serial.println(dataString);
        if (dataString.startsWith("UPD:"))
        {
            dataString.remove(0, 4);
            int endTopic = dataString.indexOf(";");
            if(endTopic == -1){
                return;
            }
            String topic = dataString.substring(0, endTopic);
            String data = dataString.substring(endTopic + 1);
            for (int i = 0; i < subIndex; i++)
            {
                if (substriptions[i].topic == topic)
                {
                    substriptions[i]._subCallback(data);
                    break;
                }
            }
        }
    }

public:
    SoftwareMQTT(int rx, int tx) : Module(rx, tx) {}

    void subscribe(String topic, SubCallback)
    {
        Subscription newSub = {topic.c_str(), _subCallback};
        substriptions[subIndex++] = newSub;
        println("SUB:" + topic);
        delay(100);
        Serial.println("SUB:" + topic);
    }

    void publish(String topic, String data)
    {
        bool publishFound = false;
        bool publish = true;
        for (int i = 0; i < pubIndex; i++)
        {
            if (publishes[i].topic == topic)
            {
                publishFound = true;
                if (publishes[i].data == data)
                {
                    publish = false;
                }
                else
                {
                    publishes[i].data = data;
                }
                break;

            }
        }
        if (!publishFound)
        {
            Publish newPub = {topic, data};
            publishes[pubIndex++] = newPub;
        }
        if (publish)
        {
            println("PUB:" + topic + ";" + data);
        }

        //        Serial.println("PUB:" + topic + ";" + data);
    }

    void loop()
    {
        readString();
        if (Module::hasAvailable())
        {
            handle(Module::getBuffer(), Module::getLength());
            Module::clear();
        }
    }
};

#endif
