# What is this?
It's the Arduino code used to control some of my WS2812 LED's.

# Usage
- Download the Adafruit Neopixel library from the Arduino IDE, or fetch it from the Adafruit Neopixel [repository](https://github.com/adafruit/Adafruit_NeoPixel).
- Set LED_COUNT to number of LED's, and PIN to desired digital pin.
- Connect Arduino GND, 5V and defined PIN, to the WS2812 GND, 5V, and DATA lines.
- Compile and upload to Arduino.

The WS2812 uses roughly 20mA per color channel, with a total of 60mA for each LED. (See [Sparkfun guide](https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide/all).)  
Actual current draw varies, so do some research/measurement if you want to be sure.  
Lower current can be supplied, reuslting in lower brightness.

# Example
<p align="center">
  <img src="example.png" width="50%"/>
</p>
