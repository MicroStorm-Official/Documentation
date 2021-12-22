
#include <Adafruit_NeoPixel.h>
#include "SoftwareMQTT.h"
#include "MotorDriver.h"

#include "Wire.h"
#include <MPU6050_light.h>
#define PIN 8 //On Trinket or Gemma, suggest changing this to 1

SoftwareMQTT mqtt(9, 10);
MotorDriver driver(5, A0, A1, 6, A2, A3);
Adafruit_NeoPixel pixels(1, PIN, NEO_GRB + NEO_KHZ800);
int rgb[] = {0, 0, 0};
const String id = "0";
//
MPU6050 mpu(Wire);
unsigned long timer = 0;
int heading = 0;
bool newHeading = false;

void setup()
{
  Serial.begin(9600);
  mqtt.begin(19200);
  driver.setup();
  Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0)
  {
  } // stop everything if could not connect to MPU6050
  Serial.println("setup");
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  mqtt.subscribe(id + "/pixel/r", [](const String data)
  {
    rgb[0] = data.toInt();
    pixels.setPixelColor(0, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();
  });

  mqtt.subscribe(id + "/pixel/g", [](const String data)
  {
    rgb[1] = data.toInt();
    Serial.println("G:" + data);
    pixels.setPixelColor(0, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();
  });

  mqtt.subscribe(id + "/pixel/b", [](const String data)
  {
    rgb[2] = data.toInt();
    Serial.println("B:" + data);
    pixels.setPixelColor(0, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();
  });

  mqtt.subscribe(id + "/motors/speed", [](const String data)
  {
    int splitIndex = data.indexOf(",");
    if (splitIndex == -1) {
      return;
    }
    String L = data.substring(0, splitIndex);
    String R = data.substring(splitIndex + 1);
    driver.set(0, L.toInt());
    driver.set(1, R.toInt());
  });
  
  mqtt.subscribe(id + "/location/heading/set", [](const String data)
  {
    heading = data.toInt();
    newHeading = true;
  });

  mqtt.publish(id + "/register", id);
}

void loop()
{
  driver.loop();

  mpu.update();

  if ((millis() - timer) > 10)
  { // print data every 10ms
    timer = millis();
    if (newHeading)
    {
      mqtt.publish(id + "/location/heading/done", "0");
      if (((int)mpu.getAngleZ()) == heading || ((int)mpu.getAngleZ()) - 2 == heading || ((int)mpu.getAngleZ()) + 2 == heading)
      {
        newHeading = false;
        heading = 0;
        driver.set(1, 0);
        driver.set(0, 0);
        mqtt.publish(id + "/location/heading", String((int)mpu.getAngleZ()));
        mqtt.publish(id + "/location/heading/done", "1");

      }
      else if (mpu.getAngleZ() > heading)
      {
        driver.set(1, 70);
        driver.set(0, -70);
      }
      else if (mpu.getAngleZ() < heading)
      {
        driver.set(1, -70);
        driver.set(0, 70);
      }
    }
    else
    {
      mqtt.loop();
      mqtt.publish(id + "/location/heading", String((int)mpu.getAngleZ()));
    }


  }
}
