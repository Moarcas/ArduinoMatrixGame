#include "lcd.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "bullet.h"

enum MenuState {
    INTRO,
    START_GAME,
        GAME,
        END_GAME,
    SETTINGS,
        LCD_BRIGHTNESS,
            SET_LCD_BRIGHTNESS,
        MATRIX_BRIGHTNESS,
            SET_MATRIX_BRIGHTNESS,
        NAME,
            SET_NAME,
    ABOUT,
        SHOW_ABOUT,
};

MenuState currentMenuState = INTRO;

void showMenu() {
    switch (currentMenuState) {
        case START_GAME:
            lcdPrintMessage("Start game");
            break;
        case GAME:
            lcdShowGameInfo();
            break;
        case END_GAME:
            lcdShowEndGame();
            break;
        case SETTINGS:
            lcdPrintMessage("Settings");
            break;
        case LCD_BRIGHTNESS:
            lcdPrintMessage("LCD brightness");
            break;
        case MATRIX_BRIGHTNESS:
            lcdPrintMessage("Matrix brightness");
            break;
        case ABOUT:
            lcdPrintMessage("About");
            break;
        case SET_LCD_BRIGHTNESS:
            lcdPrintBrightnessLevel(lcdGetBrightnessLevel());
            break;
        case SET_MATRIX_BRIGHTNESS:
            lcdPrintBrightnessLevel(matrixGetBrightnessLevel());
            break;
        case SHOW_ABOUT:
            lcdPrintAbout();
            break;
        case NAME:
            lcdPrintMessage("Change name");
    }
}

void processIntro(char action) {
    if (action == 'p')
        currentMenuState = START_GAME;
}

void processStartGame(char action) {
    switch (action) {
        case 'u':
            currentMenuState = ABOUT;
            break;
        case 'd':
            currentMenuState = SETTINGS;
            showSettingsMatrix();
            break;
        case 'p':
            currentMenuState = GAME;
            generateMap();
            incresePlayerLife(100);
            break;
    }
}

void processGame(char action) {
    showMap();
    processPlayerInfo();
    if (getPlayerLife() == 0) {
        currentMenuState = END_GAME;
        showEndGameMatrix();
        showMenu();
    }
    if (action == 'l' || action == 'r' || action == 'u' || action == 'd') {
        movePlayer(action);
        changeMiniMapPosition(getPlayerPosition(), action);
        return;
    }
    if (action == 'p') {
        shoot(getPlayerPosition(), getPlayerOrientation());
    }
}

void processEndGame(char action) {
    if (action == 'p')
        currentMenuState = START_GAME;

}

void processSettings(char action) {
    switch (action) {
        case 'u':
            currentMenuState = START_GAME;
            break;
        case 'd':
            currentMenuState = ABOUT;
            break;
        case 'p':
            currentMenuState = LCD_BRIGHTNESS;
            break;
    }
}

void processAbout(char action) {
    switch (action) {
        case 'u':
            currentMenuState = SETTINGS;
            break;
        case 'd':
            currentMenuState = START_GAME;
            break;
        case 'p':
            currentMenuState = SHOW_ABOUT;
            break;
    }
}

void processLcdBrightness(char action) {
    switch (action) {
        case 'u':
        case 'd':
            currentMenuState = MATRIX_BRIGHTNESS;
            break;
        case 'l':
            currentMenuState = SETTINGS;
            break;
        case 'p':
            currentMenuState = SET_LCD_BRIGHTNESS;
            break;
    }
}

void processSetLcdBrightness(char action) {
    switch (action) {
        case 'l':
            lcdChangeBrightnessLevel(-1);
            break;
        case 'r':
            lcdChangeBrightnessLevel(1);
            break;
        case 'p':
            currentMenuState = LCD_BRIGHTNESS;
            break;
    }
}

void processMatrixBrightness(char action) {
    switch (action) {
        case 'u':
        case 'd':
            currentMenuState = LCD_BRIGHTNESS;
            break;
        case 'l':
            currentMenuState = SETTINGS;
            break;
        case 'p':
            currentMenuState = SET_MATRIX_BRIGHTNESS;
            break;
    }
}

void processSetMatrixBrightness(char action) {
    switch (action) {
        case 'l':
            matrixChangeBrightnessLevel(-1);
            break;
        case 'r':
            matrixChangeBrightnessLevel(1);
            break;
        case 'p':
            currentMenuState = MATRIX_BRIGHTNESS;
            break;
    }
}

void processShowAbout(char action) {
    if (action == 'p')
        currentMenuState = ABOUT;
}

void processMenuState(char action) {
    switch (currentMenuState) {
        case INTRO:
            processIntro(action);
            break;
        case START_GAME:
            processStartGame(action);
            showGameMatrix();
            break;
        case GAME:
            processGame(action);
            break;
        case END_GAME:
            processEndGame(action);
            break;
        case SETTINGS:
            processSettings(action);
            showSettingsMatrix();
            break;
        case ABOUT:
            processAbout(action);
            showAboutMatrix();
            break;
        case LCD_BRIGHTNESS:
            processLcdBrightness(action);
            break;
        case MATRIX_BRIGHTNESS:
            processMatrixBrightness(action);
            break;
        case SET_LCD_BRIGHTNESS:
            processSetLcdBrightness(action);
            break;
        case SET_MATRIX_BRIGHTNESS:
            processSetMatrixBrightness(action);
            break;
        case SHOW_ABOUT:
            processShowAbout(action);
            break;
    }
    if (action != 'n' || currentMenuState == GAME)
        showMenu();
}
