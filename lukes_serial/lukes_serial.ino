// Glediator example with OctoWS2811, by mortonkopf
//
// https://forum.pjrc.com/threads/33012-Gladiator-with-OctoWS2811-working-example

// You can also use Jinx to record Glediator format data to a SD card.
// To play the data from your SD card, use this modified program:
// https://forum.pjrc.com/threads/46229&viewfull=1#post153927

#include <OctoWS2811.h>

const int ledsPerStrip = 600;
const int NUM_LEDS = 4800;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int j = 0;
byte r,g,b;
int i;

void setup() {
  Serial.begin(500000);
  leds.begin();
  leds.show();
}

int serialGlediator() {
  while (!Serial.available()) {}
  return Serial.read();
}

void idlePattern(int g, int r) {
	return;
	leds.setPixel(j, Color(g,r,0));
	j++;
	leds.show();
}


void loop() {

  //while (serialGlediator() != 1) {idlePattern(5, 30);}

  // 255 is the 'end of frame' command
  // 254 is the 'skip pixel' command

  for (i=0; i < NUM_LEDS; i++) {
    b = serialGlediator();
    if(b == 255) break;
    r = serialGlediator();
    if(r == 255) break;
    g = serialGlediator();
    if(g == 255) break;
    if(r == 254 && g == 254 && b == 254) continue;
    leds.setPixel(i, Color(r,g,b));
  }
  j++;
  leds.show();
}

/* Helper functions */
// Create a 24 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  return (((unsigned int)b << 16) | ((unsigned int)r << 8) | (unsigned int)g);
}
