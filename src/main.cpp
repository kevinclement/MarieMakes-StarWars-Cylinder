/*
  main.cpp 
  Marie Makes Star Wars Cylinder Code.
  (C) 2023 Kevin Clement <kevin.clement@gmail.com>
*/

#include <Arduino.h>
#include <FastLED.h>
#include <Bounce2.h>

#define UV_PRESS_TIME_MS 1500
#define NUM_LEDS 3
#define DATA_PIN 17
#define UV_PIN 15
#define BTN_PIN 8

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define array of color changes
#define NUM_LED_COLORS 4
CRGB LED_SEQ[] = {CRGB::White, CRGB::Red, CRGB::Green, CRGB::Blue};
unsigned int cur_color = 0;

unsigned long pressed_time = 0;
Bounce bounce = Bounce();
bool uv_on = false;
int brightness = 0;
int fadeAmount = 5; 
bool fading = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Marie Makes Star Wars Cylinder...");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(UV_PIN, OUTPUT);
  bounce.attach(BTN_PIN, INPUT);
  bounce.interval(5); // interval in ms
}

void loop() {
  bounce.update();

  if (bounce.changed()) {
    int deboucedInput = bounce.read();

    // unpressed
    if (deboucedInput == LOW) {
      Serial.print("CLICKED.");

      if (cur_color == 0 && !fading) {
        fading = true;
      } else {
        fading = false;
        cur_color = (cur_color + 1) % NUM_LED_COLORS;
      }

      pressed_time = 0;

    // pressed
    } else {
      pressed_time = millis();
    }
  }

  // check for button held
  if (pressed_time > 0 && millis() - pressed_time > UV_PRESS_TIME_MS) {
    pressed_time = 0;
    if (!uv_on) {
      Serial.println("Button held.  Turning UV on...");
      uv_on = true;
    } else {
      Serial.println("Button held.  Turning UV off...");
      uv_on = false;
    }
  }

  if (uv_on) {
    leds[0] = leds[1] = leds[2] = CRGB::Black;
  } else {
    leds[0] = leds[1] = leds[2] = LED_SEQ[cur_color];
  }

  digitalWrite(UV_PIN, uv_on ? HIGH : LOW);

  if (fading) {
    leds[0].fadeLightBy(brightness);
    leds[1].fadeLightBy(brightness);
    leds[2].fadeLightBy(brightness);
  }

  FastLED.show();

  if (fading) {
    brightness = brightness + fadeAmount;
    if(brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ; 
    }    
    delay(100);
  }
}