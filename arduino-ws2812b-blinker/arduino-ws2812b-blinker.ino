#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#define PIXEL_PIN 1
#define BTN_PIN 2
#define BTN_INTERRUPT 0
#define PIXEL_COUNT 12

Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

unsigned short int delayOptions[] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400};
unsigned short int blinkDelay = 0;
unsigned short int menuDelayThreshold = 1000;
byte r = 255;
byte g = 0;
byte b = 0;

void setLED(byte r, byte g, byte b) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    delay(20);
    pixels.show();
}

void blinkLEDS(byte r, byte g, byte b, int delayMs, int count) {
    for (int i = 0; i < count; i++) {
        setLED(r, g, b);
        delay(delayMs);
        setLED(0, 0, 0);
        delay(delayMs);
    }
}

void changeColor() {
    if (r == 255) {
        r = 0;
        g = 255;
        b = 0;
    } else if (g == 255) {
        r = 0;
        g = 0;
        b = 255;
    } else if (b == 255) {
        r = 255;
        g = 0;
        b = 0;
    } else {  // fallback for empty/wrong eeprom entry
        r = 255;
        g = 0;
        b = 0;
    }
    EEPROM.write(100, r);
    EEPROM.write(101, g);
    EEPROM.write(102, b);
}

void btnPressed() {
    unsigned long startTime = millis();
    unsigned long usedTime = 0;
    while (digitalRead(BTN_PIN) == LOW) {
        usedTime = millis() - startTime;
        if (usedTime >= menuDelayThreshold) {
            blinkLEDS(255, 255, 255, 100, 2);
            byte selectedOption = 0;
            while (digitalRead(BTN_PIN) == LOW && selectedOption < 12) {
                delay(400);
                pixels.setPixelColor(selectedOption, pixels.Color(255, 255, 255));
                pixels.show();
                selectedOption += 1;
            }
            EEPROM.write(103, highByte(delayOptions[selectedOption - 1]));
            EEPROM.write(104, lowByte(delayOptions[selectedOption - 1]));
            blinkDelay = delayOptions[selectedOption - 1];
            break;
        }
    }
    if (usedTime < menuDelayThreshold) {
        changeColor();
    }
}

void setup() {
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(PIXEL_PIN, OUTPUT);
    attachInterrupt(BTN_INTERRUPT, btnPressed, FALLING);  // interupt 0 = pin 2
    pixels.begin();
    r = EEPROM.read(100);
    g = EEPROM.read(101);
    b = EEPROM.read(102);
    blinkDelay = (EEPROM.read(103) << 8) + EEPROM.read(104);
}

void loop() {
    setLED(r, g, b);
    delay(blinkDelay);
    setLED(0, 0, 0);
    delay(blinkDelay);
}
