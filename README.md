RGB_light_wheel.ino

A dimmable color spectrum generator for the PL9823 Programmable RGB LED

Jake Romero from Creative Engineering Solutions here: 

When I first tinkered with the Knight Rider instructables project 
for PL9823 Programmable RGB LEDs, I found that at full power 
many brands of LEDs were way too bright for the test bench 
and production environments. 

So I modified masteruan's code by adding a 6-bit attenuator 
to the color function call. 

I also hard-coded options for evenly-spaced color transitions 
and wrote a for loop to iterate through them.

Thanks to masteruan at instructables.com and to the folks at 
Adafruit for graciously contributing the Adafruit_NeoPixel library. 

credits:

https://www.instructables.com/id/Multicolor-Knight-Rider-with-RGB-PL9823-LED-Arduin/

https://github.com/adafruit/Adafruit_NeoPixel
