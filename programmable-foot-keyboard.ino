#include <TrinketKeyboard.h>
#define KEYBOARD_NONE 0

// CONFIGURATION ///////////////////////////////////////////////

// Banks

const uint8_t banks[][2][2] = {
  // Scroll
  {{KEYBOARD_NONE, KEYCODE_ARROW_UP}, {KEYBOARD_NONE, KEYCODE_ARROW_DOWN}},
  // Record
  {{KEYBOARD_NONE, KEYBOARD_NONE}, {KEYBOARD_NONE, KEYCODE_R}},
  // Switch tabs
  {{KEYCODE_MOD_LEFT_CONTROL | KEYCODE_MOD_LEFT_SHIFT, KEYCODE_TAB}, {KEYCODE_MOD_LEFT_CONTROL, KEYCODE_TAB}},
  // Switch windows
  {{KEYCODE_MOD_LEFT_GUI | KEYCODE_MOD_LEFT_SHIFT, KEYCODE_TAB}, {KEYCODE_MOD_LEFT_GUI, KEYCODE_TAB}},
};

// Buttons

#define BUTTON_0 0
#define BUTTON_1 2

// Delays

#define DELAY_UNTIL_PRESSED 10
#define DELAY_UNTIL_RESET 500

// PRESSING STATES /////////////////////////////////////////////

#define PRESSING_STATE_INITIAL 0
#define PRESSING_STATE_DEBOUNCING 1
#define PRESSING_STATE_PRESSED 2
#define PRESSING_STATE_RESET 3

// GLOBAL STATE ///////////////////////////////////////////////

byte currentBank = 0;
byte currentPressingState = PRESSING_STATE_INITIAL;
unsigned long currentPressingStartTime = millis();

// AUXILIARY /////////////////////////////////////////////////

bool pressedFor(unsigned long duration) {
  return millis() - currentPressingStartTime > duration;
}

bool isPressed(uint8_t button) {
  return digitalRead(button) == LOW;
}

// MAIN //////////////////////////////////////////////////////

void setup() {
  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);

  digitalWrite(BUTTON_0, HIGH);
  digitalWrite(BUTTON_1, HIGH);

  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll();

  if (! isPressed(BUTTON_0) && ! isPressed(BUTTON_1)) {
    if (currentPressingState != PRESSING_STATE_INITIAL) {
      currentPressingState = PRESSING_STATE_INITIAL;
      TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYBOARD_NONE);
    }
    return;
  }

  switch(currentPressingState) {
    case PRESSING_STATE_INITIAL:
      currentPressingState = PRESSING_STATE_DEBOUNCING;
      currentPressingStartTime = millis();
      break;
    case PRESSING_STATE_DEBOUNCING:
      if (pressedFor(DELAY_UNTIL_PRESSED)) {
        currentPressingState = PRESSING_STATE_PRESSED;
        if (isPressed(BUTTON_0) && isPressed(BUTTON_1)) {
          currentBank = (currentBank + 1) % (sizeof(banks) / sizeof(banks[2][2]));
        } else if (isPressed(BUTTON_0)) {
          TrinketKeyboard.pressKey(banks[currentBank][0][0], banks[currentBank][0][1]);
        } else if (isPressed(BUTTON_1)) {
          TrinketKeyboard.pressKey(banks[currentBank][1][0], banks[currentBank][1][1]);
        }
      }
      break;
    case PRESSING_STATE_PRESSED:
      if (pressedFor(DELAY_UNTIL_RESET)) {
        currentPressingState = PRESSING_STATE_RESET;
        if (isPressed(BUTTON_0) && isPressed(BUTTON_1)) {
          currentBank = 0;
        }
      }
      break;
  }
}
