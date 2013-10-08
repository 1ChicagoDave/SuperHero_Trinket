//Superhero Power Plant
//fades all pixel subtley
//code by Tony Sherwood for Adafruit Industries
// ** Modified by David Ratliff - October 2013

#include <Adafruit_NeoPixel.h>

#define PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(17, PIN, NEO_GRB + NEO_KHZ800);

int alpha; // Current value of the pixels
int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
int flip; // Randomly flip the direction every once in a while
int minAlpha = 35; // Min value of brightness
int maxAlpha = 180; // Max value of brightness
int alphaDelta = 4; // Delta of brightness between times through the loop
int wait = 1;        // the delay() value in colorWipe function - slows 'flicker' effect

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  initAlpha();
}

void loop() 
{

  flip = random(32);
  if(flip > 20) {
    dir = 1 - dir;
  }
  // Some example procedures showing how to display to the pixels:
  if (dir == 1) {
    alpha += alphaDelta;
  }
  if (dir == 0) {
    alpha -= alphaDelta;
  }
  if (alpha < minAlpha) {
    alpha = minAlpha;
    dir = 1;
  }
  if (alpha > maxAlpha) {
    alpha = maxAlpha;
    dir = 0;
  }

  colorWipe(strip.Color((alpha/8)-3, (alpha/10)-3, alpha)); // Blue - ish
  //    I added the RED & GREEN values to brighten it up and give a more random color effect.
  //   It still remains primarily blue. But varies levels of white & purple.
  //    This will most likely be worn under a shirt. I think this will geive best visible effect in those conditions

  // Bright flash very occasionally....
  if(flip == 30)
  { 
    colorWipe(strip.Color(0,0,80));
    delay(20);
  }
 // if(flip==29) colorWipe(strip.Color(15,0,50));

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void initAlpha()
{
  colorWipe(strip.Color(50, 50, 200)); // Blue-ish & BRIGHT as it turns on
  delay(50);
  colorWipe(strip.Color(200, 200, 255)); // Blue-ish & BRIGHT as it turns on
  delay(50);
  colorWipe(strip.Color(100, 100, 200)); // Blue-ish & BRIGHT as it turns on
  delay(50);

  for (int i=160; i>= 10; i--)    // fade all off EXCEPT BLUE
  {
    colorWipe(strip.Color(i, i, 200));
    i -= 3;
  }
  /*
  for (int i=200; i>= maxAlpha; i--)    // Fade BLUE down to minimum set level
   {
   colorWipe(strip.Color(10, 10, i));
   }
   */
}







