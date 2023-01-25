/*
  main.cpp 
  Marie Makes Star Wars Cylinder Code.
  (C) 2023 Kevin Clement <kevin.clement@gmail.com>
*/

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 3
#define DATA_PIN 17
#define UV_PIN 15

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  Serial.println("Marie Makes Star Wars Cylinder...");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

  pinMode(UV_PIN, OUTPUT);
}

void loop() {
  // digitalWrite(UV_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  // digitalWrite(UV_PIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);   

  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  FastLED.show();
  delay(500);

  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
  delay(500);
}