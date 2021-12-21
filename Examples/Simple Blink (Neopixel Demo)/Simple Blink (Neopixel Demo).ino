#include <Adafruit_NeoPixel.h> // Download and install Adafruit_NeoPixel Library

#define PIN 12 // Pin to use the Neopixels

#define NUMPIXELS 2 // Two onboard Neopixels

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
  pixels.clear();

  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 108, 3));
    pixels.show();
    delay(500);   
  }
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    delay(500);
  }
}
