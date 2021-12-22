#include "Module.h"
#include <EspMQTTClient.h>
  


EspMQTTClient client("SSID_______", "PASSWORD______", "BROKER_IP_____", "robot-0", 1883);
const String topicPrefix = "microstorm/robots/";


Module HardwareController;

void setup() {
  HardwareController.begin(19200);
  HardwareController.setCallback([](String dataString) {
    if (dataString.startsWith("PUB:")) {
      dataString.remove(0, 4);
      int endTopic = dataString.indexOf(";");
      String topic = topicPrefix + dataString.substring(0, endTopic);
      String data = dataString.substring(endTopic + 1);
      client.publish(topic, data);
    } else if (dataString.startsWith("SUB:")) {
      dataString.remove(0, 4);
      dataString.remove(dataString.length()-1, 2);
      dataString = topicPrefix + dataString;
      client.subscribe(dataString, [](const String &topic,const String & payload) {
        String ref = topic;
        ref.remove(0, topicPrefix.length());
        Serial.println("UPD:"+ref+";"+payload);
      });
    }
  });
}

void onConnectionEstablished()
{}



void loop() {
  HardwareController.listen();
  client.loop();
}
