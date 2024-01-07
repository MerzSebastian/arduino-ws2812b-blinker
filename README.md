# Arduino NeoPixel Blinker
[![CircleCI](https://circleci.com/gh/MerzSebastian/arduino-ws2812b-blinker.svg?style=svg)](https://circleci.com/gh/MerzSebastian/arduino-ws2812b-blinker)

A small arduino project that makes neopixel addressable leds flash. You can change the pauses between the flashes as well as the color. Both values are stored in the eeprom and loaded on restart.
The pipeline was set up with CircleCi and the arduino-cli.

## Setup your board
There are a few settings that might has to be changed if you want to use this project for a different board. I used the digispark rev v3 dev board. 
![diagram](https://github.com/MerzSebastian/arduino-ws2812b-blinker/blob/main/documentation/diagram.png)

```
#define  PIXEL_PIN  1
#define  BTN_PIN  2
#define  BTN_INTERRUPT  0
#define  PIXEL_COUNT  12
```
|definition|description|
|---|---|
|PIXEL_PIN|data pin for ws2812b leds|
|BTN_PIN|pin for button, this has to be a interrupt pin / BTN_PIN <=> button <=> GND|
|BTN_INTERRUPT|interrupt pin, must correlate with BTN_PIN|
|PIXEL_COUNT|how many leds are connected to the data pin?|

Info: You only need to bridge the diode if you want to add a lot of leds. Do at your own risk :)

## Change color
Short press the button. It will cycle trough 3 colors (red, green, blue)
## Change blink delay
To adjust the delay of the flashing you have to press and hold the button. After 1 second, the leds flash twice quickly, which indicates that you have entered the options menu. Keep holding and let go if you chosen your option.
Possible options:
|option|blink delay in ms|
|---|---|
|1|200|
|2|400|
|3|600|
|4|800|
|5|1000|
|6|1200|
|7|1400|
|8|1600|
|9|1800|
|10|2000|
|11|2200|
|12|2400|
