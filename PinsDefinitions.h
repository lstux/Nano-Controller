#ifndef _PINSDEFINITIONS_H_
#define _PINSDEFINITIONS_H_

/*
0.96" LCD PINS (I2C) :
  LCD_SDA A4
  LCD_SCL A5
*/

/*
NRF24L01 PINS (SPI) :
  RF24_MOSI_PIN  11
  RF24_MISO_PIN  12
  RF24_CLOCK_PIN 13
*/
#define RF24_CE_PIN 10
#define RF24_CS_PIN 9

/*
  IR EMITTER PIN
*/
#define IR_EMIT_PIN 3


/*
  INPUTS PINS
*/
#define JOYSTICK1_X_PIN A6
#define JOYSTICK1_Y_PIN A7
#define JOYSTICK2_X_PIN A3
#define JOYSTICK2_Y_PIN A2

#define JOYSTICK1_BTN_PIN A1
#define JOYSTICK2_BTN_PIN A0
#define START_BTN_PIN     2
#define SELECT_BTN_PIN    4
#define A_BTN_PIN         5
#define B_BTN_PIN         6
#define C_BTN_PIN         7
#define D_BTN_PIN         8

#define JOYSTICK1_BTN 0
#define JOYSTICK2_BTN 1
#define START_BTN     2
#define SELECT_BTN    3
#define A_BTN         4
#define B_BTN         5
#define C_BTN         7
#define D_BTN         6

#endif
