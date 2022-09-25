# Arduino NeoPixel Blinker
[![CircleCI](https://circleci.com/gh/MerzSebastian/arduino-ws2812b-blinker.svg?style=svg)](https://circleci.com/gh/MerzSebastian/arduino-ws2812b-blinker)

A small arduino project that makes neopixel addressable leds flash. You can change the pauses between the flashes as well as the color. Both values are stored in the eeprom and loaded on restart.
The pipeline was set up with CircleCi and the arduino-cli.

## Setup your board
There are a few settings that must be made if you want to use this project.
```
#define  PIXEL_PIN  1
#define  BTN_PIN  2
#define  BTN_INTERRUPT  0
#define  PIXEL_COUNT  12
```
|definition|description|
|---|---|
|PIXEL_PIN|data pin for ws2812b leds|
|BTN_PIN|pin for button, this has to be a interrupt pin / BTN_PIN <=> button <=> vcc|
|BTN_INTERRUPT|interrupt pin, must correlate with BTN_PIN|
|PIXEL_COUNT|how many leds are connected to the data pin?|

## Change color
Short press the button. It will cycle trough 3 colors (red, green, blue)
## Change blink delay
Hold the button for 1 second. As you do so, the leds will flash twice briefly, indicating that it will now begin cycling through the options. 
Now you only have to release the button at the right time to select another delay.
First flash is 200ms, second flash is 400ms, third flash is 600ms, ..., twelfth flash is 2400ms
