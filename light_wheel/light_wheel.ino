
// https://arduino.stackexchange.com/questions/35734/better-cycling-through-the-rgb-colors
#include <Adafruit_NeoPixel.h>

// SETUP YOUR OUTPUT PIN AND NUMBER OF PIXELS
#define PIN 6
#define NUM_PIXELS  6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ400);

void setup() {
  strip.begin();
  clearStrip(); // Initialize all pixels to 'off'
  delay(1000);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

//  rainbow(20);
//  delay(50000);
//  colorWipe(strip.Color(0, 0, 0), 50); // blank
  rainbowCycle(20);
//  delay(5000);
//    colorWipe(strip.Color(0, 0, 0), 50); // blank
//   delay(5000);
//  theaterChaseRainbow(50);
//  delay(5000);
//    colorWipe(strip.Color(0, 0, 0), 50); // blank
//   delay(5000);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void clearStrip() {
  for( int i = 0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255,6));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255,6));     
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255,6));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, int att) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color((255 - WheelPos * 3)>>att, 0, (WheelPos * 3)>>att);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, (WheelPos * 3)>>att, (255 - WheelPos * 3)>>att);
  }
  WheelPos -= 170;
  return strip.Color((WheelPos * 3)>>att, (255 - WheelPos * 3)>>att, 0);
}
