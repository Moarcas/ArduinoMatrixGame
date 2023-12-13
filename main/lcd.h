#ifndef LCD.H
#define LCD.H

void setupLcd();

void lcdPrintMessage(char* text);

void lcdPrintMenu(char* text);

void lcdPrintSubmenu(char* text);

void lcdPrintBrightnessLevel(int brightnessLevel);

void lcdChangeBrightnessLevel(int);

int lcdGetBrightnessLevel();

void lcdShowGameInfo();

void lcdShowEndGameScreen1();

void lcdShowEndGameScreen2();

void lcdPrintAbout();

void lcdScrollLeft();

void lcdPrintHowToPlay();

#endif
