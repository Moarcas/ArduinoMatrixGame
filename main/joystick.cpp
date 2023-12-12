#include "Arduino.h"

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1; 

const int maxThreshold = 600;
const int minThreshold = 400;

unsigned long lastTimeRead;
int readDelay = 300;

const int buttonDebounceDelay = 50;

unsigned long lastButtonPressTime = 0; 
int buttonState = 0;
int buttonLastValueRead = 0; 
bool joyMoved;

int xValue, yValue;
static char direction;

void setupJoystick() {
    pinMode(pinSW, INPUT_PULLUP);
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
}

bool buttonIsPressed() {
    bool pressed = false;
    int buttonValueRead = !digitalRead(pinSW);
    if (buttonValueRead != buttonLastValueRead) {
        lastButtonPressTime = millis();
    }
    if (millis() - lastButtonPressTime > buttonDebounceDelay) {
        if (buttonState != buttonValueRead) {
            buttonState = buttonValueRead;
            if (buttonState == HIGH) {
                pressed = true;
            }
        }
    }
    buttonLastValueRead = buttonValueRead;
    return pressed;
}

char getJoystickAction() {
    if (buttonIsPressed())
        return 'p';
    
    xValue = analogRead(pinX);
    yValue = analogRead(pinY);
    direction = 'n';

    if (xValue < minThreshold) {
        direction = 'l';
    }
    if (xValue > maxThreshold) {
        direction = 'r';
    }
    if (yValue < minThreshold ) {
        direction = 'u';
    }
    if (yValue > maxThreshold) {
        direction = 'd';
    }

    if (direction != 'n' && millis() - lastTimeRead > readDelay) {
        joyMoved = false;
        lastTimeRead = millis();
    }

    if (direction == 'n') {
        joyMoved = false;
        return direction;
    }

    if (joyMoved) 
        direction = 'n';

    joyMoved = true;

    return direction;
}

