#include <LiquidCrystal.h>
#include "Arduino.h"
#include <EEPROM.h>
#include "lcd.h"
#include "player.h"

const int rs = 9;
const int en = 8;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;
const int brightnessPin = 3;
const int brightnessMemoryAddress = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int maxLevelBrightness = 14;

const byte fullCharacter[8] = {
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};

const byte emptyCharacter[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

byte heartCharacter[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

byte swordCharacter[] = {
    B00100,
    B01110,
    B01110,
    B01110,
    B01110,
    B11111,
    B00100,
    B01110
};

byte arrowUpCharacter[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B00000
};

byte arrowDownCharacter[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void lcdPrintIntroMessage() {
    lcd.print("Welcome back!");
    lcd.setCursor(0, 1);
    lcd.print("Press joystick to start");
}

void setupLcd() {
    lcdChangeBrightnessLevel(0);
    lcd.createChar(0, fullCharacter);
    lcd.createChar(1, emptyCharacter);
    lcd.createChar(2, heartCharacter);
    lcd.createChar(3, swordCharacter);
    lcd.createChar(4, arrowUpCharacter);
    lcd.createChar(5, arrowDownCharacter);
    lcd.begin(16, 2);
    lcdPrintIntroMessage();
}

void lcdPrintMessage(char* text) {
    lcd.clear();
    lcd.print(text);
}

void lcdPrintBrightnessLevel(int brightnessLevel) {
    lcd.setCursor(0, 1);
    lcd.print('[');
    lcd.setCursor(15, 1);
    lcd.print(']');
    for (int i = 1; i <= brightnessLevel; i++) {
        lcd.setCursor(i, 1);
        lcd.write(byte(0));
    }
    for (int i = brightnessLevel + 1; i < 15; i++) {
        lcd.setCursor(i, 1);
        lcd.write(byte(1));
    }
}

int brightnessValueFromLevel(int level) {
    return 160 - 4 * level;
}

void lcdChangeBrightnessLevel(int difference) {
    int brightnessLevel, newBrightnessLevel;
    EEPROM.get(brightnessMemoryAddress, brightnessLevel);
    newBrightnessLevel = brightnessLevel + difference;
    if (newBrightnessLevel >= 1 && newBrightnessLevel <= maxLevelBrightness) {
        EEPROM.put(brightnessMemoryAddress, newBrightnessLevel);
        analogWrite(brightnessPin, brightnessValueFromLevel(newBrightnessLevel));
    }
}

int lcdGetBrightnessLevel() {
    int brightnessLevel;
    EEPROM.get(brightnessMemoryAddress, brightnessLevel);
    return brightnessLevel;
}

void lcdShowEndGame() {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("YOU LOST");
}

void lcdShowGameInfo() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("$");
    lcd.print(getPlayerPoints());
    lcd.setCursor(5, 0);
    lcd.write((byte)3);
    lcd.print(getPlayerPower());
    lcd.setCursor(12, 0);
    lcd.write((byte)2);
    lcd.print(getPlayerLife());
}

void lcdPrintAbout() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("git: moarcas");
    lcd.setCursor(0, 1);
    lcd.print("Name: Cosmin");
}

void lcdPrintMenu(char* text) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text);
    lcd.setCursor(15, 1);
    lcd.write(byte(4));
    lcd.setCursor(0, 1);
    lcd.write(byte(5));
}
