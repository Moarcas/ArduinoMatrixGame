#ifndef SCORERECORDER.H
#define SCORERECORDER.H


bool isOnPodium(int score);

void saveScore(int score, String name);

int getScorePosition(int score);

void resetHighscore();

void showHighscore();

void goToNextHighscore();

void goToPrevHighscore();

#endif
