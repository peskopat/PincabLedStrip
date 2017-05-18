#include <string.h>
#include "LedStrip.h"


uint16_t LedStrip::stripLen;


#define DATA_PIN     12 // GPIO12 / D6 on WeMos/NodeMCU ESP8266
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
//#define COLOR_ORDER RGB
#define COLOR_ORDER GRB
static CRGB *leds;


LedStrip::LedStrip(uint32_t numPerStrip,CRGB * ledsv)
{
								stripLen = numPerStrip;
								leds=ledsv;
}

void LedStrip::begin(void)
{
								FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, stripLen).setCorrection( TypicalLEDStrip );
								FastLED.setBrightness(  BRIGHTNESS );

}

void LedStrip::show(void)
{
								FastLED.show();
}

void LedStrip::setStripLength(uint16_t length)
{
								stripLen=length;
}


void LedStrip::setPixel(uint32_t num, int color)
{
								/*uint32_t strip, offset, mask;
								   uint8_t bit, *p;

								   strip = num / stripLen;
								   offset = num % stripLen;
								   bit = (1<<strip);
								   p = ((uint8_t *)drawBuffer) + offset * 24;
								   for (mask = (1<<23); mask; mask >>= 1) {
								        if (color & mask) {
								 * p++ |= bit;
								        } else {
								 * p++ &= ~bit;
								        }
								   }
								 */
								//leds[num]=color;
								leds[num].b=(color & 0xFF);  // Take just the lowest 8 bits.
								leds[num].g=((color >> 8)& 0xFF);  // Shift the integer right 8 bits.
								leds[num].r=((color >> 16)& 0xFF);  // Shift the integer right 8 bits.
}

int LedStrip::getPixel(uint32_t num)
{
								/*
								   uint32_t strip, offset, mask;
								   uint8_t bit, *p;
								   int color=0;

								   strip = num / stripLen;
								   offset = num % stripLen;
								   bit = (1<<strip);
								   p = ((uint8_t *)drawBuffer) + offset * 24;
								   for (mask = (1<<23); mask; mask >>= 1) {
								        if (*p++ & bit) color |= mask;
								   }
								   return color;
								 */
								return leds[num];
}
