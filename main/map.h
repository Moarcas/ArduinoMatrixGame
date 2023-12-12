#ifndef MAP.H
#define MAP.H

struct Position {
    int line;
    int column;
};

const int matrixSize = 8;
const int mapSize = 16;

extern bool gameMap[mapSize][mapSize];

void setupMatrix();

void matrixChangeBrightnessLevel(int);

int matrixGetBrightnessLevel();

void generateMap();

void showMap();

bool isOnMap(Position);

bool isWall(Position);

void changeMiniMapPosition(Position playerPosition, char direction);

void showEndGameMatrix();

void showSettingsMatrix();

void showGameMatrix();

void showAboutMatrix();

#endif
