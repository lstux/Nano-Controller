#include "NanoController.h"

void NanoController() {
  //Initialize buttons pins as INPUT_PULLUP
  pinMode(JOY1_BTN, INPUT_PULLUP);
  pinMode(JOY2_BTN, INPUT_PULLUP);
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_X, INPUT_PULLUP);
  pinMode(BTN_Y, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_START, INPUT_PULLUP);
}

void NanoController::getInputs() {
  this->joy1_x = analogRead(JOY1_X);
  this->joy1_y = analogRead(JOY1_Y);
  this->joy2_x = analogRead(JOY2_X);
  this->joy2_y = analogRead(JOY2_Y);
  uint8_t buttons = 0;
  if (digitalRead(BTN_A)==0)      buttons += 1;
  if (digitalRead(BTN_B)==0)      buttons += 2;
  if (digitalRead(BTN_X)==0)      buttons += 4;
  if (digitalRead(BTN_Y)==0)      buttons += 8;
  if (digitalRead(BTN_SELECT)==0) buttons += 16;
  if (digitalRead(BTN_START)==0)  buttons += 32;
  if (digitalRead(JOY1_BTN)==0)   buttons += 64;
  if (digitalRead(JOY2_BTN)==0)   buttons += 128;
  this->buttons = buttons;
}

char* serialDump() {
  char *dump = (char*)calloc(64);
  return dump;
}
