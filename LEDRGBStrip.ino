#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 4
#define LED_COUNT 40

// Library for WS2812 by Adafruit
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

    leds.begin();
    leds.setBrightness(255);
    clearLEDs();
    leds.show();
}

/*
    0: Ping pong        A-->B-->A..
    1: Rainbow
    2: Ping no-Pong     A-->B
*/
void loop() {
        /*
        // Ping pong
        for (int i=0; i<3; i++) {
            cylon(RED, 75); 
        }
        */
        // Rainbow
        
        //for (int i=0; i < LED_COUNT * 2; i++) {
        //    rainbow(i);
        //    delay(150);
        //}
        
        /*
        // Cascade
        cascade(DEEPSKYBLUE, TOP_DOWN, 100);
        cascade(GREEN, TOP_DOWN, 100);
        cascade(ORANGERED, TOP_DOWN, 100);
        cascade(RED, TOP_DOWN, 100);
        
        setAllColor(255,100,0);
        
        delay(20000);
        */

        
        //setAllColor(255,100,0);
        
        //delay(2000);
        //police();

        rainbowFull(15);
        
}

void rainbowFull(int delay_ms) {
  for (int transition = 0; transition < 6; transition++) {
    for (int color = 0; color < 255; color++) {
      for (int j=0; j < 255; j++) {
          // 192 total colors in rainbowOrder function.
          leds.setPixelColor(j, rainbowOrderFull(color, transition));
      }
      leds.show();
      delay(delay_ms);
    }
  }
}

uint32_t rainbowOrderFull(byte position, int transition) {
  if (transition == 0)  
    // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
    return leds.Color(0xFF, position, 0);
  else if (transition == 1) {
    // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
    return leds.Color(0xff - position, 0xFF, 0);
  }
  else if (transition == 2) {
    // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
    return leds.Color(0, 0xFF, position);
  }
  else if (transition == 3) {
    // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
    return leds.Color(0, 0xff - position, 0xFF);
  }
  else if (transition == 4) {
    // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
    return leds.Color(position, 0, 0xFF);
  }
  else {
    //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
    return leds.Color(0xFF, 0x00, 0xff - position);
  }
  
}

void police() {

    for(int i = 0; i < 30; i++){
        for(i = 0; i < LED_COUNT/2; i++) {
            leds.setPixelColor(i, 0,0,255);
        }
        for(i = LED_COUNT/2; i < LED_COUNT; i++) {
            leds.setPixelColor(i, 0,0,0);
        }
        leds.show();
        delay(250);
        for(i = 0; i < LED_COUNT/2; i++) {
            leds.setPixelColor(i, 0,0,0);
        }
        for(i = LED_COUNT/2; i < LED_COUNT; i++) {
            leds.setPixelColor(i, 0,0,255);
        }
        leds.show();
        delay(250);
    }
    
}

void setAllColor(byte r, byte g, byte b) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds.setPixelColor(i, r,g,b);
    }
    leds.show();
}

void cylon(unsigned long color, byte wait) {
    
    // weight determines how much lighter the outer "eye" colors are
    const byte weight = 4;  
    
    byte red    = (color & 0xFF0000) >> 16;
    byte green  = (color & 0x00FF00) >> 8;
    byte blue   = (color & 0x0000FF);

    // A--->B
    for (int i=0; i<=LED_COUNT-1; i++) {
        clearLEDs();
        leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
        // Two eyes on each side get progressively dimmer
        for (int j=1; j<3; j++) {
            if (i-j >= 0)
                leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
            if (i-j <= LED_COUNT)
                leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
        }
        leds.show();
        delay(wait);
    }
    // B--->A
    for (int i=LED_COUNT-2; i>=1; i--) {
        clearLEDs();
        leds.setPixelColor(i, red, green, blue);
        for (int j=1; j<3; j++) {
            if (i-j >= 0)
                leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
            if (i-j <= LED_COUNT)
                leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
        }
        leds.show();
        delay(wait);
    }
}

void cascade(unsigned long color, byte direction, byte wait) {
    if (direction == TOP_DOWN) {
        for (int i=0; i<LED_COUNT; i++) {
            clearLEDs();  // Turn off all LEDs
            leds.setPixelColor(i, color);  // Set just this one
            leds.show();
            delay(wait);
        }
    }
    else {
        for (int i=LED_COUNT-1; i>=0; i--) {
            clearLEDs();
            leds.setPixelColor(i, color);
            leds.show();
            delay(wait);
        }
    }
}

void clearLEDs() {
    for (int i=0; i<LED_COUNT; i++) {
        leds.setPixelColor(i, 0);
    }
}

void rainbow(byte startPosition) {
    // Scale our rainbow
    int rainbowScale = 192 / LED_COUNT;
  
    for (int i=0; i<LED_COUNT; i++) {
        // 192 total colors in rainbowOrder function.
        leds.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
    }
    leds.show();
}

uint32_t rainbowOrder(byte position) {
  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
  if (position < 31)  
    return leds.Color(0xFF, position * 8, 0);
  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
  else if (position < 63) {
    position -= 31;
    return leds.Color(0xFF - position * 8, 0xFF, 0);
  }
  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
  else if (position < 95) {
    position -= 63;
    return leds.Color(0, 0xFF, position * 8);
  }
  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
  else if (position < 127) {
    position -= 95;
    return leds.Color(0, 0xFF - position * 8, 0xFF);
  }
  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
  else if (position < 159) {
    position -= 127;
    return leds.Color(position * 8, 0, 0xFF);
  }
  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
  else {
    position -= 159;
    return leds.Color(0xFF, 0x00, 0xFF - position * 8);
  }
  
}
