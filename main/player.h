#ifndef PLAYER.H
#define PLAYER.H
#include "map.h"
#include "Arduino.h"

void generatePlayerPosition();

void showPlayer();

void movePlayer(char direction);

void processPlayerInfo();

Position getPlayerPosition();

char getPlayerOrientation();

void resetPlayerInfo();

int getPlayerLife();

int getPlayerPower();

int getPlayerScore();

String getPlayerName();

void increasePlayerLife(int);

void increasePlayerPower(int);

void increasePlayerScore(int);

void playerNameDeleteLastChar();

void playerNameNextChar();

void playerNamePrevChar();

void playerNameAddChar();

#endif
