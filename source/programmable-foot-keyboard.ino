// References:
//   https://learn.adafruit.com/trinket-usb-keyboard/code
//   https://learn.adafruit.com/trinket-usb-keyboard/prank-example
//   https://github.com/adafruit/Adafruit-Trinket-USB/
//   https://github.com/adafruit/Adafruit-Trinket-USB/blob/51f208bc569dd79d7357f16d548ed0c43f4927e8/TrinketKeyboard/TrinketKeyboard.h

#include <TrinketKeyboard.h>

// KEYBOARD //////////////////////////////////////////////////

#define KEYBOARD_NONE 0

void releaseKeys() {
  TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYBOARD_NONE);
}

// BUTTONS /////////////////////////////////////////////////////

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 2

bool isPressed(uint8_t button) {
  return digitalRead(button) == LOW;
}

// BANKS //////////////////////////////////////////////////////

// Press both buttons to go to next bank.

#define BANK_ARROWS 0

// LEFT  -> UP
// RIGHT -> DOWN

#define BANK_RECORD 1

// LEFT  ->
// RIGHT -> R

#define BANK_TABS 2

// LEFT  -> SHIFT + CONTROL + TAB
// RIGHT -> CONTROL + TAB

#define BANK_WINDOWS 3

// LEFT  -> SHIFT + COMMAND + TAB
// RIGHT -> COMMAND + TAB

#define BANK_DEFAULT 0
#define BANK_COUNT 4

// Number of banks.

byte bank = BANK_DEFAULT;

void pressKey() {
  if (isPressed(BUTTON_LEFT) && isPressed(BUTTON_RIGHT)) {
    bank = (bank + 1) % BANK_COUNT;
    return;
  }

  switch (bank) {
    case BANK_ARROWS:
      if (isPressed(BUTTON_LEFT)) {
        TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYCODE_ARROW_UP);
      } else if (isPressed(BUTTON_RIGHT)) {
        TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYCODE_ARROW_DOWN);
      }
      break;
    case BANK_RECORD:
      if (isPressed(BUTTON_LEFT)) {
        TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYBOARD_NONE);
      } else if (isPressed(BUTTON_RIGHT)) {
        TrinketKeyboard.pressKey(KEYBOARD_NONE, KEYCODE_R);
      }
      break;
    case BANK_TABS:
      if (isPressed(BUTTON_LEFT)) {
        TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL | KEYCODE_MOD_LEFT_SHIFT, KEYCODE_TAB);
      } else if (isPressed(BUTTON_RIGHT)) {
        TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_TAB);
      }
      break;
    case BANK_WINDOWS:
      if (isPressed(BUTTON_LEFT)) {
        TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI | KEYCODE_MOD_LEFT_SHIFT, KEYCODE_TAB);
      } else if (isPressed(BUTTON_RIGHT)) {
        TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_TAB);
      }
      break;
  }
}

void holdKey() {
  if (isPressed(BUTTON_LEFT) && isPressed(BUTTON_RIGHT)) {
    bank = BANK_DEFAULT;
    return;
  }
}

// STATES /////////////////////////////////////////////////////

// START -> DEBOUNCING -> PRESSED -> HOLD
// ^ ^ ^         |           |        |
// | | -----------           |        |
// | -------------------------        |
// ------------------------------------

#define STATE_START 0
#define STATE_DEBOUNCING 1
#define STATE_PRESSED 2
#define STATE_HOLD 3

#define DELAY_DEBOUNCING 10
#define DELAY_HOLD 500

byte state = STATE_START;
unsigned long lastStateTransition = millis();

bool inStateFor(unsigned long duration) {
  return millis() - lastStateTransition > duration;
}

// STATES TRANSITIONS ///////////////////////////////////////

void stateTransition(byte toState) {
  switch (state) {
    case STATE_START:
      switch (toState) {
        case STATE_START:
          // ERROR
          break;
        case STATE_DEBOUNCING:
          // NO-OP
          break;
        case STATE_PRESSED:
          // ERROR
          break;
        case STATE_HOLD:
          // ERROR
          break;
      }
      break;
    case STATE_DEBOUNCING:
      switch (toState) {
        case STATE_START:
          // NO-OP
          break;
        case STATE_DEBOUNCING:
          // ERROR
          break;
        case STATE_PRESSED:
          pressKey();
          break;
        case STATE_HOLD:
          // ERROR
          break;
      }
      break;
    case STATE_PRESSED:
      switch (toState) {
        case STATE_START:
          releaseKeys();
          break;
        case STATE_DEBOUNCING:
          // ERROR
          break;
        case STATE_PRESSED:
          // ERROR
          break;
        case STATE_HOLD:
          holdKey();
          break;
      }
    case STATE_HOLD:
      switch (toState) {
        case STATE_START:
          releaseKeys();
          break;
        case STATE_DEBOUNCING:
          // ERROR
          break;
        case STATE_PRESSED:
          // ERROR
          break;
        case STATE_HOLD:
          // ERROR
          break;
      }
      break;
  }

  lastStateTransition = millis();
  state = toState;
}

// BUTTONS TRANSITIONS /////////////////////////////////////////

void buttonTransition() {
  if (state != STATE_START && ! isPressed(BUTTON_LEFT) && ! isPressed(BUTTON_RIGHT)) {
    stateTransition(STATE_START);
    return;
  }

  switch (state) {
    case STATE_START:
      if (isPressed(BUTTON_LEFT) || isPressed(BUTTON_RIGHT)) {
        stateTransition(STATE_DEBOUNCING);
      }
      break;
    case STATE_DEBOUNCING:
      if (inStateFor(DELAY_DEBOUNCING)) {
        stateTransition(STATE_PRESSED);
      }
      break;
    case STATE_PRESSED:
      if (inStateFor(DELAY_HOLD)) {
        stateTransition(STATE_HOLD);
      }
      break;
    case STATE_HOLD:
      // NO-OP
      break;
  }
}

// SETUP /////////////////////////////////////////////////////

void setup() {
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);

  digitalWrite(BUTTON_LEFT, HIGH);
  digitalWrite(BUTTON_RIGHT, HIGH);

  TrinketKeyboard.begin();
}

// LOOP //////////////////////////////////////////////////////

void loop() {
  TrinketKeyboard.poll();

  buttonTransition();
}
