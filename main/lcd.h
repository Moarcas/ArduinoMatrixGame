#ifndef LCD.H
#define LCD.H

#include "Arduino.h"

void setupLcd();

void lcdPrintMenu(char* text);

void lcdPrintSubmenu(char* text);

void lcdPrintBrightnessLevel(int brightnessLevel);

void lcdChangeBrightnessLevel(int);

void lcdResetBrightness();

int lcdGetBrightnessLevel();

void lcdChangeContrastLevel(int);

void lcdResetContrast();

int lcdGetContrastLevel();

void lcdShowGameInfo();

void lcdShowEndGameScreen1();

void lcdShowEndGameScreen2();

void lcdShowEndGameWriteName();

void lcdPrintAbout();

void lcdScrollLeft();

void lcdPrintHowToPlay();

void lcdPrintHighscore(int place, int score, String name);

#endif
