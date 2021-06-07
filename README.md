light_wheel.ino 

RGB_light_wheel.ino 

Jake Romero, Creative Engineering Solutions

CES_LLC, August 2020


light_wheel.ino: multiple color spectrum generator algorithms for the PL9823 Programmable RGB LED

This file contains various color spectrum generators with attenuators and other options.


RGB_light_wheel.ino: A dimmable color spectrum generator for the PL9823 Programmable RGB LED

When I first tinkered with the Knight Rider instructables project 
for the PL9823 Programmable RGB LEDs (see below), I found that 
at full power many brands of RGB LEDs were way too bright for 
the test bench and production environments. 

So I added a 6-bit, 2^-N, user-defined attenuator to masteruan's code. 
The user can now select from no attenuation (0) to 1/64th power (6).

I also hard-coded 18 and 36 evenly-spaced color definitions to provide a
smooth transition through the color spectrum, and I wrote for loops 
to iterate through them.

I also added 2 functions to generate varying intensities of white light: 

setWhite() 

attWhite() 

which both provide user-defined intensities from off to full power (0 - 255).

This code snippet was written to help programmers utilize these LEDs.

@credits

Thanks to masteruan at instructables.com and to the folks at 
Adafruit for contributing the Adafruit_NeoPixel library. 

https://www.instructables.com/id/Multicolor-Knight-Rider-with-RGB-PL9823-LED-Arduin/

https://github.com/adafruit/Adafruit_NeoPixel
