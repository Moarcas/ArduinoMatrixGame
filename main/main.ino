#include "map.h"
#include "player.h"
#include "joystick.h"
#include "menu.h"
#include "lcd.h"

char joystickAction;

void setup() {
    Serial.begin(9600);

    setupMatrix();
    setupJoystick();
    setupLcd();

    delay(1000);
}

void loop() {
    joystickAction = getJoystickAction();

    processMenuState(joystickAction);
}

