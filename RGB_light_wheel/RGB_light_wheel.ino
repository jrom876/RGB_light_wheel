/* 
  * RGB_light_wheel.ino
  * 
  * A dimmable color spectrum generator for 
  * the PL9823 Programmable RGB LED
  * CESLLC, August 2020
  * 
  * Jake Romero from Creative Engineering Solutions here: 
  *  
  * When I first tinkered with the Knight Rider instructables 
  * project for PL9823 Programmable RGB LEDs, I found that 
  * at full power many brands of LEDs were way too bright for 
  * the test bench and production environments. 
  * 
  * So I modified masteruan's code by adding a simple 6-bit attenuator 
  * to the color function call. 
  * 
  * I also hard-coded options for evenly-spaced color transitions 
  * and wrote a for loop to iterate through them.
  * 
  * @credits
  * Thanks to masteruan at instructables.com and to the folks at 
  * Adafruit for graciously contributing the Adafruit_NeoPixel library. 
  * 
  * https://www.instructables.com/id/Multicolor-Knight-Rider-with-RGB-PL9823-LED-Arduin/
  * https://github.com/adafruit/Adafruit_NeoPixel
*/
#include <Adafruit_NeoPixel.h>

// SETUP YOUR OUTPUT PIN AND NUMBER OF PIXELS
#define PIN 6
#define BUZZER 7
#define NUM_PIXELS  6
#define vel 1 // Velocity in milliseconds
#define uvel 5 // delay in microseconds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ400);

void setup() {
  pinMode(BUZZER, OUTPUT); // 7
  strip.begin();
  clearStrip(); // Initialize all pixels to 'off'
  delay(1000);
}

//// Iterate through a whole rainbow of colors
void loop() {
  for(int i=0; i<36; i++) {
    knightRider(64, uvel, 1, longrainbow(i,6));
//    clearStrip();
//    delay(200);
  }
}

// Cycles - one cycle is scanning through all pixels left then right (or right then left)
// Speed - how fast one cycle is (32 with 16 pixels is default knightRider speed)
// Width - how wide the trail effect is on the fading out LEDs.  The original display used
//         light bulbs, so they have a persistance when turning off.  This creates a trail.
//         Effective range is 2 - 8, 4 is default for 16 pixels.  Play with this.
// Color - 32-bit packed RGB color value.  All pixels will be this color.
// knightRider(cycles, speed, width, color);
void knightRider(uint16_t cycles, uint16_t speed, uint8_t width, uint32_t color) {
  uint32_t old_val[NUM_PIXELS]; // up to 256 lights!
  for(int i = 0; i < cycles; i++){
    for (int count = 1; count<NUM_PIXELS; count++) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x>0; x--) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x-1, old_val[x-1]); 
      }
      strip.show();
//      delay(speed);
      delayMicroseconds(speed);
    }
    for (int count = NUM_PIXELS-1; count>=0; count--) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x<=NUM_PIXELS ;x++) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x+1, old_val[x+1]);
      }
      strip.show();
//      delay(speed);
      delayMicroseconds(speed);
    }
  }
}

void clearStrip() {
  for( int i = 0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}

uint32_t setWhite(byte tone) {
  return strip.Color(tone, tone, tone);
}

uint32_t attWhite(uint8_t att) {
  uint8_t attval = ((att>=0)&&(att<7))?att:6;
  return strip.Color(0xFF>>attval, 0xFF>>attval, 0xFF>>attval);
}

// Using a counter and for() loop, input a value 0 to 255 to get a color value.
// The colors transition like: red - org - ylw - grn - cyn - blue - vio - mag - back to red.
// Entering 255 will give you white, if you need it.
uint32_t shortrainbow(int pos, int att) {
  switch(pos) {
    case 0: return strip.Color(255>>att, 0, 0); break;
    case 1: return strip.Color(255>>att, 85>>att, 0); break;
    case 2: return strip.Color(255>>att, 169>>att, 0); break;
    case 3: return strip.Color(255>>att, 255>>att, 0); break;
    case 4: return strip.Color(169>>att, 255>>att, 0); break;
    case 5: return strip.Color(85>>att, 255>>att, 0); break;
    case 6: return strip.Color(0, 255>>att, 0); break;
    case 7: return strip.Color(0, 255>>att, 85>>att); break;
    case 8: return strip.Color(0, 255>>att, 169>>att); break;
    case 9: return strip.Color(0, 255>>att, 255>>att); break;
    case 10: return strip.Color(0, 169>>att, 255>>att); break;
    case 11: return strip.Color(0, 85>>att, 255>>att); break;
    case 12: return strip.Color(0, 0, 255>>att); break;
    case 13: return strip.Color(85>>att, 0, 255>>att); break;
    case 14: return strip.Color(169>>att, 0, 255>>att); break;
    case 15: return strip.Color(255>>att, 0, 255>>att); break;
    case 16: return strip.Color(255>>att, 0, 169>>att); break;
    case 17: return strip.Color(255>>att, 0, 85>>att); break;
    default: return strip.Color(0, 0, 0); break;
  }
 }

uint32_t longrainbow(int pos, int att) {
  switch(pos) {
    case 0: return strip.Color(255>>att, 0, 0); break;
    case 1: return strip.Color(255>>att, 42>>att, 0); break;
    case 2: return strip.Color(255>>att, 85>>att, 0); break;
    case 3: return strip.Color(255>>att, 127>>att, 0); break;
    case 4: return strip.Color(255>>att, 169>>att, 0); break;
    case 5: return strip.Color(255>>att, 212>>att, 0); break;
    case 6: return strip.Color(255>>att, 255>>att, 0); break;
    case 7: return strip.Color(212>>att, 255>>att, 0); break;
    case 8: return strip.Color(169>>att, 255>>att, 0); break;
    case 9: return strip.Color(127>>att, 255>>att, 0); break;
    case 10: return strip.Color(85>>att, 255>>att, 0); break;
    case 11: return strip.Color(42>>att, 255>>att, 0); break;
    case 12: return strip.Color(0, 255>>att, 0); break;
    case 13: return strip.Color(0, 255>>att, 42>>att); break;
    case 14: return strip.Color(0, 255>>att, 85>>att); break;
    case 15: return strip.Color(0, 255>>att, 127>>att); break;
    case 16: return strip.Color(0, 255>>att, 169>>att); break;
    case 17: return strip.Color(0, 255>>att, 212>>att); break;
    case 18: return strip.Color(0, 255>>att, 255>>att); break;
    case 19: return strip.Color(0, 212>>att, 255>>att); break;
    case 20: return strip.Color(0, 169>>att, 255>>att); break;
    case 21: return strip.Color(0, 127>>att, 255>>att); break;
    case 22: return strip.Color(0, 85>>att, 255>>att); break;
    case 23: return strip.Color(0, 42>>att, 255>>att); break;
    case 24: return strip.Color(0, 0, 255>>att); break;
    case 25: return strip.Color(42>>att, 0, 255>>att); break;    
    case 26: return strip.Color(85>>att, 0, 255>>att); break;
    case 27: return strip.Color(127>>att, 0, 255>>att); break;
    case 28: return strip.Color(169>>att, 0, 255>>att); break;
    case 29: return strip.Color(212>>att, 0, 255>>att); break;
    case 30: return strip.Color(255>>att, 0, 255>>att); break;    
    case 31: return strip.Color(255>>att, 0, 212>>att); break;
    case 32: return strip.Color(255>>att, 0, 169>>att); break;
    case 33: return strip.Color(255>>att, 0, 127>>att); break;
    case 34: return strip.Color(255>>att, 0, 85>>att); break;
    case 35: return strip.Color(255>>att, 0, 42>>att); break;
    default: return strip.Color(0, 0, 0); break;
  }
 }
