#ifndef PLAYER.H
#define PLAYER.H
#include "map.h"

void generatePlayerPosition();

void showPlayer();

void movePlayer(char direction);

void processPlayerInfo();

Position getPlayerPosition();

char getPlayerOrientation();

void resetPlayerInfo();

void savePlayerScore();

int getPlayerLife();

int getPlayerPower();

int getPlayerScore();

void increasePlayerLife(int);

void increasePlayerPower(int);

void increasePlayerScore(int);

#endif
