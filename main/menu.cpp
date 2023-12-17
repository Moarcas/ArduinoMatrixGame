#include "lcd.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "bullet.h"
#include "scoreRecorder.h"
#include "sound.h"

enum MenuState {
    INTRO,
    START_GAME,
        GAME,
        END_GAME_SCREEN1,
        END_GAME_SCREEN2,
        END_GAME_WRITE_NAME,
    HIGHSCORE,
        SHOW_HIGHSCORE,
    SETTINGS,
        LCD_BRIGHTNESS,
            SET_LCD_BRIGHTNESS,
        MATRIX_BRIGHTNESS,
            SET_MATRIX_BRIGHTNESS,
        SET_SOUND,
            SOUND_ON,
            SOUND_OFF,
        RESET_DATA,
            RESET_LCD_BRIGHTNESS,
            RESET_MATRIX_BIRGHTNESS,
            RESET_HIGHSCORE,
    ABOUT,
        SHOW_ABOUT,
    HOW_TO_PLAY,
        SHOW_HOW_TO_PLAY,
};

MenuState currentMenuState = INTRO;

void showMenu() {
    switch (currentMenuState) {
        case START_GAME:
            lcdPrintMenu("Start game");
            break;
        case GAME:
            lcdShowGameInfo();
            break;
        case END_GAME_SCREEN1:
            lcdShowEndGameScreen1();
            break;
        case END_GAME_SCREEN2:
            lcdShowEndGameScreen2();
            break;
        case END_GAME_WRITE_NAME:
            lcdShowEndGameWriteName();
            break;
        case HIGHSCORE:
            lcdPrintMenu("Highscore");
            break;
        case SHOW_HIGHSCORE:
            showHighscore();
            break;
        case SETTINGS:
            lcdPrintMenu("Settings");
            break;
        case LCD_BRIGHTNESS:
            lcdPrintSubmenu("LCD brightness");
            break;
        case MATRIX_BRIGHTNESS:
            lcdPrintSubmenu("Map brightness");
            break;
        case SET_SOUND:
            lcdPrintSubmenu("Sound ON/OFF");
            break;
        case SOUND_ON:
            lcdPrintSubmenu("Turn sound ON");
            break;
        case SOUND_OFF:
            lcdPrintSubmenu("Turn sound OFF");
            break;
        case RESET_DATA:
            lcdPrintSubmenu("Reset data");
            break;
        case RESET_LCD_BRIGHTNESS:
            lcdPrintSubmenu("Reset lcd b.");
            break;
        case RESET_MATRIX_BIRGHTNESS:
            lcdPrintSubmenu("Reset matrix b.");
            break;
        case RESET_HIGHSCORE:
            lcdPrintSubmenu("Reset highscore");
            break;
        case ABOUT:
            lcdPrintMenu("About");
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
        case HOW_TO_PLAY:
            lcdPrintMenu("How to play");
            break;
        case SHOW_HOW_TO_PLAY:
            lcdPrintHowToPlay();
            break;
    }
}

void processIntro(char action) {
    showIntroMatrix();
    if (action == 'p')
        currentMenuState = START_GAME;
}

void processStartGame(char action) {
    switch (action) {
        case 'u':
            currentMenuState = HOW_TO_PLAY;
            menuSound();
            break;
        case 'd':
            currentMenuState = HIGHSCORE;
            menuSound();
            break;
        case 'p':
            currentMenuState = GAME;
            selectionSound();
            generateMap();
            resetPlayerInfo();
            break;
    }
}

void processGame(char action) {
    addWallsOnMap();
    showMap();
    processPlayerInfo();
    if (getPlayerLife() == 0) {
        currentMenuState = END_GAME_SCREEN1;
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

void processEndGameScreen1(char action) {
    if (action == 'p') {
        currentMenuState = END_GAME_SCREEN2;
        selectionSound();
    }
}

void processEndGameScreen2(char action) {
    if (action == 'p') {
        if (isOnPodium(getPlayerScore())) {
            currentMenuState = END_GAME_WRITE_NAME;
        }
        else {
            currentMenuState = START_GAME;
        }
        selectionSound();
    }
}

void processEndGameWriteName(char action) {
    switch (action) {
        case 'l':
            playerNameDeleteLastChar();
            break;
        case 'r':
            playerNameAddChar();
            break;
        case 'u':
            playerNameNextChar();
            break;
        case 'd':
            playerNamePrevChar();
            break;
        case 'p':
            saveScore(getPlayerScore(), getPlayerName());
            currentMenuState = START_GAME;
            selectionSound();
            break;
    }
}

void processHighscore(char action) {
    switch (action) {
        case 'u':
            currentMenuState = START_GAME;
            menuSound();
            break;
        case 'd':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'p':
            currentMenuState = SHOW_HIGHSCORE;
            selectionSound();
            break;
    }
}

void processShowHighscore(char action) {
    switch (action) {
        case 'u':
            goToPrevHighscore();
            break;
        case 'd':
            goToNextHighscore();
            break;
        case 'p':
            currentMenuState = HIGHSCORE;
            resetIndexHighscore();
            break;
    }
}

void processSettings(char action) {
    switch (action) {
        case 'u':
            currentMenuState = HIGHSCORE;
            menuSound();
            break;
        case 'd':
            currentMenuState = ABOUT;
            menuSound();
            break;
        case 'p':
            currentMenuState = LCD_BRIGHTNESS;
            selectionSound();
            break;
    }
}

void processAbout(char action) {
    switch (action) {
        case 'u':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'd':
            currentMenuState = HOW_TO_PLAY;
            menuSound();
            break;
        case 'p':
            currentMenuState = SHOW_ABOUT;
            selectionSound();
            break;
    }
}

void processLcdBrightness(char action) {
    switch (action) {
        case 'u':
            currentMenuState = RESET_DATA;
            menuSound();
            break;
        case 'd':
            currentMenuState = MATRIX_BRIGHTNESS;
            menuSound();
            break;
        case 'l':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'p':
            currentMenuState = SET_LCD_BRIGHTNESS;
            selectionSound();
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
            selectionSound();
            break;
    }
}

void processMatrixBrightness(char action) {
    switch (action) {
        case 'u':
            currentMenuState = LCD_BRIGHTNESS;
            menuSound();
            break;
        case 'd':
            currentMenuState = SET_SOUND;
            menuSound();
            break;
        case 'l':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'p':
            currentMenuState = SET_MATRIX_BRIGHTNESS;
            selectionSound();
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
            selectionSound();
            break;
    }
}

void processSound(char action) {
    switch (action) {
        case 'u':
            currentMenuState = MATRIX_BRIGHTNESS;
            menuSound();
            break;
        case 'd':
            currentMenuState = RESET_DATA;
            menuSound();
            break;
        case 'l':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'p':
            currentMenuState = SOUND_ON;
            selectionSound();
            break;
    }
}

void processSoundOn(char action) {
    switch (action) {
        case 'u':
        case 'd':
            currentMenuState = SOUND_OFF;
            menuSound();
            break;
        case 'l':
            currentMenuState = SET_SOUND;
            menuSound();
            break;
        case 'p':
            selectionSound();
            currentMenuState = SET_SOUND;
            changeSilentMode(false);
            break;
    }
}

void processSoundOff(char action) {
    switch (action) {
        case 'u':
        case 'd':
            currentMenuState = SOUND_ON;
            menuSound();
            break;
        case 'l':
            currentMenuState = SET_SOUND;
            menuSound();
            break;
        case 'p':
            selectionSound();
            currentMenuState = SET_SOUND;
            changeSilentMode(true);
            break;

    }
}

void processResetData(char action) {
    switch (action) {
        case 'u':
            currentMenuState = SET_SOUND;
            menuSound();
            break;
        case 'd':
            currentMenuState = LCD_BRIGHTNESS;
            menuSound();
            break;
        case 'l':
            currentMenuState = SETTINGS;
            menuSound();
            break;
        case 'p':
            currentMenuState = RESET_LCD_BRIGHTNESS;
            selectionSound();
    }
}

void processResetLcdBrightness(char action) {
    switch (action) {
        case 'u':
            currentMenuState = RESET_HIGHSCORE;
            menuSound();
            break;
        case 'd':
            currentMenuState = RESET_MATRIX_BIRGHTNESS;
            menuSound();
            break;
        case 'l':
            currentMenuState = RESET_DATA;
            menuSound();
            break;
        case 'p':
            lcdResetBrightness();
            currentMenuState = RESET_DATA;
            selectionSound();
            break;
    }
}

void processResetMatrixBrightness(char action) {
    switch (action) {
        case 'u':
            currentMenuState = RESET_LCD_BRIGHTNESS;
            menuSound();
            break;
        case 'd':
            currentMenuState = RESET_HIGHSCORE;
            menuSound();
            break;
        case 'l':
            currentMenuState = RESET_DATA;
            menuSound();
            break;
        case 'p':
            matrixResetBrightness();
            currentMenuState = RESET_DATA;
            selectionSound();
            break;
    }
}

void processResetHighscore(char action) {
    switch (action) {
        case 'u':
            currentMenuState = RESET_MATRIX_BIRGHTNESS;
            menuSound();
            break;
        case 'd':
            currentMenuState = RESET_LCD_BRIGHTNESS;
            menuSound();
            break;
        case 'l':
            currentMenuState = RESET_DATA;
            menuSound();
            break;
        case 'p':
            resetHighscore();
            currentMenuState = RESET_DATA;
            selectionSound();
            break;
    }
}

void processShowAbout(char action) {
    lcdScrollLeft();
    if (action == 'p')
        currentMenuState = ABOUT;
}

void processHowToPlay(char action) {
    switch (action) {
        case 'u':
            currentMenuState = ABOUT;
            menuSound();
            break;
        case 'd':
            currentMenuState = START_GAME;
            menuSound();
            break;
        case 'p':
            currentMenuState = SHOW_HOW_TO_PLAY;
            selectionSound();
            break;
    }
}

void processShowHowToPlay(char action) {
    lcdScrollLeft();
    if (action == 'p')
        currentMenuState = HOW_TO_PLAY;
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
        case END_GAME_SCREEN1:
            processEndGameScreen1(action);
            showEndGameMatrix(isOnPodium(getPlayerScore()));
            break;
        case END_GAME_SCREEN2:
            processEndGameScreen2(action);
            break;
        case END_GAME_WRITE_NAME:
            processEndGameWriteName(action);
            break;
        case HIGHSCORE:
            processHighscore(action);
            showHighscoreMatrix();
            break;
        case SHOW_HIGHSCORE:
            processShowHighscore(action);
            showHighscoreMatrix();
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
            showSettingsMatrix();
            break;
        case MATRIX_BRIGHTNESS:
            processMatrixBrightness(action);
            showSettingsMatrix();
            break;
        case SET_LCD_BRIGHTNESS:
            processSetLcdBrightness(action);
            showSettingsMatrix();
            break;
        case SET_MATRIX_BRIGHTNESS:
            processSetMatrixBrightness(action);
            showSettingsMatrix();
            break;
        case SET_SOUND:
            processSound(action);
            showSettingsMatrix();
            break;
        case SOUND_ON:
            processSoundOn(action);
            showSettingsMatrix();
            break;
        case SOUND_OFF:
            processSoundOff(action);
            showSettingsMatrix();
            break;
        case RESET_DATA:
            processResetData(action);
            showSettingsMatrix();
            break;
        case RESET_LCD_BRIGHTNESS:
            processResetLcdBrightness(action);
            showSettingsMatrix();
            break;
        case RESET_MATRIX_BIRGHTNESS:
            processResetMatrixBrightness(action);
            showSettingsMatrix();
            break;
        case RESET_HIGHSCORE:
            processResetHighscore(action);
            showSettingsMatrix();
            break;
        case SHOW_ABOUT:
            processShowAbout(action);
            showAboutMatrix();
            break;
        case HOW_TO_PLAY:
            processHowToPlay(action);
            showAboutMatrix();
            break;
        case SHOW_HOW_TO_PLAY:
            processShowHowToPlay(action);
            showAboutMatrix();
            break;
    }
    if (action != 'n' || currentMenuState == GAME)
        showMenu();
}
