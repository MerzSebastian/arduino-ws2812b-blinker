#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define PIXEL_PIN 1
#define BTN_PIN 2
#define BTN_INTERRUPT 0
#define PIXEL_COUNT 12

Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
unsigned short int delayOptions[] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400};
uint8_t delayOptionsIndex = 0;
uint8_t colorOptions[][] = {{255, 0, 0},{0, 255, 0},{0, 0, 255}};
uint8_t colorOptionsIndex = 0;
unsigned short int menuDelayThreshold = 1000;

void setLED(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    delay(20);
    pixels.show();
}

void blinkLEDS(uint8_t r, uint8_t g, uint8_t b, unsigned short int delayMs, unsigned short int count) {
    for (unsigned short int i = 0; i < count; i++) {
        setLED(r, g, b);
        delay(delayMs);
        setLED(0, 0, 0);
        delay(delayMs);
    }
}

void btnPressed() {
    unsigned long startTime = millis();
    unsigned long usedTime = 0;
    while (digitalRead(BTN_PIN) == LOW) {
        usedTime = millis() - startTime;
        if (usedTime >= menuDelayThreshold) {
            blinkLEDS(255, 255, 255, 100, 2);
            uint8_t selectedOption = 0;
            while (digitalRead(BTN_PIN) == LOW && selectedOption < (sizeof(delayOptions)/sizeof(delayOptions[0])) {
                blinkLEDS(255, 255, 255, 300, selectedOption);
                selectedOption += 1;
                delay(1000);
            }
            EEPROM.write(101, selectedOption - 1);
            delayOptionsIndex = selectedOption - 1;
            break;
        }
    }
    if (usedTime < menuDelayThreshold) {
        colorOptionsIndex += 1;
        EEPROM.write(100, colorOptionsIndex);
    }
}

void loadSettings() {
    colorOptionsIndex = EEPROM.read(100);
    delayOptionsIndex = EEPROM.read(101);
    if ((colorOptionsIndex > (sizeof(colorOptions)/sizeof(colorOptions[0]) || colorOptionsIndex >= 0) && (delayOptionsIndex > (sizeof(delayOptions)/sizeof(delayOptions[0]) || delayOptionsIndex >= 0)) {
        EEPROM.write(100, 0);
        EEPROM.write(101, 0);
        colorOptionsIndex = 0;
        delayOptionsIndex = 0;
    }
}

void setup() {
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(PIXEL_PIN, OUTPUT);
    attachInterrupt(BTN_INTERRUPT, btnPressed, FALLING);
    pixels.begin();
    loadSettings();
}

void loop() {
    setLED(colorOptions[delayOptionsIndex][0], colorOptions[delayOptionsIndex][1], colorOptions[delayOptionsIndex][2]);
    delay(delayOptionsIndex);
    setLED(0, 0, 0);
    delay(delayOptionsIndex);
}
