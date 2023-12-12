#ifndef LCD.H
#define LCD.H

void setupLcd();

void lcdPrintMessage(char* text);

void lcdPrintBrightnessLevel(int brightnessLevel);

void lcdChangeBrightnessLevel(int);

int lcdGetBrightnessLevel();

void lcdShowGameInfo();

void lcdShowEndGame();

void lcdPrintAbout();

#endif
