#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "lcd.h"
#include "player.h"
#include "scoreRecorder.h"
#include "bullet.h"

const int rs = 9;
const int en = 8;
const int d4 = 7;
const int d5 = A5;
const int d6 = 3;
const int d7 = 4;

const int brightnessPin = 5;
const int brightnessMemoryAddress = 4;

const int contrastPin = 6;
const int contrastMemoryAddress = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int maxLevelBrightness = 14;
const int maxLevelContrast = 14;

unsigned long lastShift;
const int delayShift = 500;

const byte fullCharacter[8] = {
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000
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

byte arrowLeftCharacter[] = {
    B00000,
    B00000,
    B00010,
    B00110,
    B01110,
    B00110,
    B00010,
    B00000
};

byte bulletCharacter[] = {
    B00100,
    B01110,
    B01110,
    B01110,
    B01110,
    B01110,
    B00000,
    B01110
};

void lcdPrintIntroMessage() {
    lcd.setCursor(2, 0);
    lcd.print("Welcome back!");
}

void setupLcd() {
    pinMode(rs, OUTPUT);
    pinMode(en, OUTPUT);
    pinMode(d4, OUTPUT);
    pinMode(d5, OUTPUT);
    pinMode(d6, OUTPUT);
    pinMode(d7, OUTPUT);
    pinMode(brightnessPin, OUTPUT);
    pinMode(contrastPin, OUTPUT);

    lcdChangeBrightnessLevel(0);
    lcdChangeContrastLevel(0);
    lcd.createChar(0, fullCharacter);
    lcd.createChar(1, emptyCharacter);
    lcd.createChar(2, heartCharacter);
    lcd.createChar(3, swordCharacter);
    lcd.createChar(4, arrowUpCharacter);
    lcd.createChar(5, arrowDownCharacter);
    lcd.createChar(6, arrowLeftCharacter);
    lcd.createChar(7, bulletCharacter);
    lcd.begin(16, 2);
    lcdPrintIntroMessage();
}

void lcdPrintBrightnessLevel(int brightnessLevel) {
    lcd.setCursor(0, 1);
    lcd.print('[');
    lcd.setCursor(15, 1);
    lcd.print(']');
    for (int i = 1; i <= brightnessLevel; i++) {
        lcd.setCursor(i, 1);
        lcd.write((byte)0);
    }
    for (int i = brightnessLevel + 1; i < 15; i++) {
        lcd.setCursor(i, 1);
        lcd.write((byte)1);
    }
}

int brightnessValueFromLevel(int level) {
    return 50 + 10 * level;
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

void lcdResetBrightness() {
    EEPROM.put(brightnessMemoryAddress, int(maxLevelBrightness / 2));
    analogWrite(brightnessPin, brightnessValueFromLevel(int(maxLevelBrightness /2)));

}

int lcdGetBrightnessLevel() {
    int brightnessLevel;
    EEPROM.get(brightnessMemoryAddress, brightnessLevel);
    return brightnessLevel;
}

int contrastValueFromLevel(int level) {
    return 170 - 4 * level;
}

void lcdChangeContrastLevel(int difference) {
    int contrastLevel, newContrastLevel;
    EEPROM.get(contrastMemoryAddress, contrastLevel);
    newContrastLevel = contrastLevel + difference;
    if (newContrastLevel >= 1 && newContrastLevel <= maxLevelContrast) {
        EEPROM.put(contrastMemoryAddress, newContrastLevel);
        analogWrite(contrastPin, contrastValueFromLevel(newContrastLevel));
    }
}

void lcdResetContrast() {
    EEPROM.put(contrastMemoryAddress, int(maxLevelContrast / 2));
    analogWrite(contrastPin, contrastValueFromLevel(int(maxLevelContrast / 2)));
}

int lcdGetContrastLevel() {
    int contrastLevel;
    EEPROM.get(contrastMemoryAddress, contrastLevel);
    return contrastLevel;
}

void lcdShowEndGameScreen1() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Congratulations!"));
    lcd.setCursor(0, 1);
    lcd.print(F("Your score: "));
    lcd.print(getPlayerScore());
}

void lcdShowEndGameScreen2() {
    int playerScore = getPlayerScore();
    int place = getScorePosition(playerScore) + 1;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("Your score: "));
    lcd.print(playerScore);
    lcd.setCursor(0, 0);
    lcd.print(F("You place: "));
    if (place > 5)
        lcd.print("> 5");
    else
        lcd.print(place);
}

void lcdShowEndGameWriteName() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Enter your name:"));
    lcd.setCursor(0, 1);
    lcd.print(getPlayerName());
    lcd.write((byte)6);
}

void lcdShowGameInfo() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("$");
    lcd.print(getPlayerScore());

    lcd.setCursor(5, 0);
    lcd.write((byte)2);
    lcd.print(getPlayerLife());

    lcd.setCursor(11, 0);
    lcd.print(F("LVL:"));
    lcd.print(getLevel());

    lcd.setCursor(0, 1);
    lcd.write((byte)3);
    lcd.print('[');
    for (int i = 0; i < getPlayerPower(); i++)
        lcd.write((byte)0);
    lcd.setCursor(7, 1);
    lcd.print(']');

    lcd.setCursor(11, 1);
    lcd.print('[');
    for (int i = 0; i < getNumberShotgunShoots(); i++)
        lcd.write((byte)7);
    lcd.setCursor(15, 1);
    lcd.print(']');
}

void lcdPrintAbout() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print(F("Game name: Odiseea Pixelata"));
    lcd.setCursor(3, 1);
    lcd.print(F("Author name:Cosmin  github:moarcas"));
}

void lcdPrintMenu(char* text) {
    lcd.clear();
    lcd.setCursor(8 - strlen(text) / 2, 0);
    lcd.print(text);
    lcd.setCursor(15, 1);
    lcd.write((byte)4);
    lcd.setCursor(0, 1);
    lcd.write((byte)5);
}

void lcdPrintSubmenu(char *text) {
    lcd.clear();
    lcd.setCursor(8 - strlen(text) / 2, 0);
    lcd.print(text);
    lcd.setCursor(0, 1);
    lcd.write((byte)6);
    lcd.setCursor(7, 1);
    lcd.write((byte)5);
    lcd.setCursor(15, 1);
    lcd.write((byte)4);
}

void lcdScrollLeft() {
    if (millis() - lastShift > delayShift) {
        lcd.scrollDisplayLeft();
        lastShift = millis();
    }
}

void lcdPrintHowToPlay() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Destroy walls before you run out of life"));
    lcd.setCursor(0, 1);
    lcd.print(F("Destroy 5 walls to get 3 super shoots"));
}

void lcdPrintHighscore(int place, int score, String name) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Name: "));
    lcd.print(name);
    lcd.setCursor(0, 1);
    lcd.print(F("Place "));
    lcd.print(place);
    lcd.setCursor(8, 1);
    lcd.print(F("Score"));
    lcd.print(score);
}
