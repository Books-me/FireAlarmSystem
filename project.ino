#include <FastLED.h>

#define NUM_LEDS 14
#define LED_PIN D4

CRGB leds[NUM_LEDS];

int smokeSensor = A0;
int buzzer = D7;
int relay = D5;
int BLINK_INTERVAL = 500;
int previousMillis = 0;
bool ledState = false;

void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(smokeSensor, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

}

void loop() {
  
  int analogSensor = analogRead(smokeSensor);
  int currentMillis = millis();

  Serial.println(analogSensor);
  if (analogSensor > 300)
  {
      if (currentMillis - previousMillis >= BLINK_INTERVAL) 
       {
            if(!ledState)
              {
                   fill_solid(leds, NUM_LEDS, CRGB::Red);
                   FastLED.show();
                   ledState = true;
                   previousMillis = currentMillis;
              }
            else 
              {
                   fill_solid(leds, NUM_LEDS, CRGB::Black);
                   FastLED.show();
                   ledState = false;
                   previousMillis = currentMillis;
              }
       }
    Serial.println("smoke detected");
  }
  else
  {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
  }

}
