/**********************************************************************
  ESPNow remote for WLED
  Copyright (c) 2024  Damian Schneider (@DedeHai)
  Licensed under the EUPL v. 1.2 or later
  https://github.com/DedeHai/WLED-ESPNow-Remote
***********************************************************************/


#define DISABLE_DEEPSLEEP // uncomment to disable going to deepsleep: any GPIO can be used for a button at the expense of ~8x shorter battery life

// hardware configuration  note: using both ROTARY_ENCODER and BUTTON_MATRIX may work but is untested
// Both works: in this case is RotaryButton Part of ButtonMatrix -> must be Pos 1,1
#define ROTARY_ENCODER // uncomment to use rotary encoder (can have additional buttons)
#define BUTTON_MATRIX  // uncomment to use a button matrix as input

#if defined(ROTARY_ENCODER)

  // if use Button in Button Matrix uncomment or set to 0
  // #define NUM_BUTTONS_ROT 1

  #define NUM_ROTARYLEVELS 3
  #define ACTIVE_TIME 20000
  #define KEEPROTARYLEVEL_TIME 40

  #define CLK_PIN 21
  #define DT_PIN 20
  #define BTN_PIN 10

  #ifdef NUM_BUTTONS_ROT
    #define NUM_BUTTON_PINS NUM_BUTTONS_ROT
    #if NUM_BUTTONS_ROT > 0
      RTC_DATA_ATTR uint8_t buttonPins[NUM_BUTTON_PINS] = { BTN_PIN };
    #endif
  #endif

#endif

#if defined(BUTTON_MATRIX)

  // Pin Settings in config.cpp

  #define MATRIX_COLS 4
  #define MATRIX_ROWS 5
  #define NUM_BUTTONS_MAT (MATRIX_COLS * MATRIX_ROWS)

  RTC_DATA_ATTR uint8_t columnPins[MATRIX_COLS] = { 0, 1, 2, 3 };
  RTC_DATA_ATTR uint8_t rowPins[MATRIX_ROWS] = { 10, 4, 5, 6, 7 };

# endif

#if !defined(BUTTON_MATRIX) && !defined(ROTARY_ENCODER)

  #define NUM_BUTTONS_DEF 6
  #define ACTIVE_TIME 6000

  #define NUM_BUTTON_PINS NUM_BUTTONS_DEF
  RTC_DATA_ATTR uint8_t buttonPins[NUM_BUTTON_PINS] = { 0, 1, 2, 3, 4, 5 };

#endif

/* Set Correct Defines dont change */
#ifndef NUM_BUTTONS_ROT
  #define NUM_BUTTONS_ROT 0
#endif
#ifndef NUM_BUTTONS_MAT
  #define NUM_BUTTONS_MAT 0
#endif
#ifndef NUM_BUTTONS_DEF
  #define NUM_BUTTONS_DEF 0
#endif
#ifndef NUM_BUTTON_PINS
  #define NUM_BUTTON_PINS 0
#endif
#define NUM_BUTTONS (NUM_BUTTONS_ROT + NUM_BUTTONS_MAT + NUM_BUTTONS_DEF)
/* Set Correct Defines dont change */
