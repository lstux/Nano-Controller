//Nano Controller base functions
#include "Nano-Controller.h"

uint8_t NanoController::joystick_change(joystick_state current, joystick_state last, uint16_t threshold=10) {
  if (abs(current.x - last.x) > threshold) return 1;
  if (abs(current.y - last.y) > threshold) return 1;
  return 0;
}

void NanoController::serialState() {
  Serial.print("Controller State : ");
  Serial.print("J1("); Serial.print(this->state.joystick1.x); Serial.print(","); Serial.print(this->state.joystick1.y);
  Serial.print(","); Serial.print(this->button_state(JOYSTICK1_BTN)); Serial.print("), ");
  Serial.print("J2("); Serial.print(this->state.joystick2.x); Serial.print(","); Serial.print(this->state.joystick2.y);
  Serial.print(","); Serial.print(this->button_state(JOYSTICK2_BTN)); Serial.print("), ");
  Serial.print("START="); Serial.print(this->button_state(START_BTN)); Serial.print(", ");
  Serial.print("SELECT="); Serial.print(this->button_state(SELECT_BTN)); Serial.print(", ");
  Serial.print("A="); Serial.print(this->button_state(A_BTN)); Serial.print(", ");
  Serial.print("B="); Serial.print(this->button_state(B_BTN)); Serial.print(", ");
  Serial.print("C="); Serial.print(this->button_state(C_BTN)); Serial.print(", ");
  Serial.print("D="); Serial.print(this->button_state(D_BTN)); Serial.print(", ");
  Serial.print("COMBINED_BUTTONS="); Serial.println(this->state.buttons);
}

uint8_t NanoController::update(uint8_t send_mode=0) {
  uint8_t r=0, b=0;
  joystick_state js = { analogRead(JOYSTICK1_X_PIN), analogRead(JOYSTICK1_Y_PIN) };
  if (this->joystick_change(this->state.joystick1, js)) { r++; this->state.joystick1 = js; }
  js = { analogRead(JOYSTICK2_X_PIN), analogRead(JOYSTICK2_Y_PIN) };
  if (this->joystick_change(this->state.joystick2, js)) { r++; this->state.joystick2 = js; }
  if (!digitalRead(JOYSTICK1_BTN_PIN))  b += 1;
  if (!digitalRead(JOYSTICK2_BTN_PIN))  b += 2;
  if (!digitalRead(START_BTN_PIN))     b += 4;
  if (!digitalRead(SELECT_BTN_PIN))    b += 8;
  if (!digitalRead(A_BTN_PIN))         b += 16;
  if (!digitalRead(B_BTN_PIN))         b += 32;
  if (!digitalRead(C_BTN_PIN))         b += 64;
  if (!digitalRead(D_BTN_PIN))         b += 128;
  if (this->state.buttons != b) r++;
  this->state.buttons = b;
  if (r>0) {
    this->lcdDrawState();
    switch(send_mode) {
      case(1) : this->send_ir_code(); break;
      case(2) : this->rf24SendState(); break;
    }
#ifdef DEBUG
    this->serialState();
#endif
  }
  return r;
}

NanoController::NanoController() {
#ifdef DEBUG
  Serial.begin(SERIALSPEED);
  Serial.println("NanoController Initializing...");
#endif
  this->lcd = new U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0);
  this->lcd->begin();
  this->lcdBootup();
#ifdef DEBUG
  Serial.println("Setting pinModes");
#endif
  pinMode(JOYSTICK1_X_PIN, INPUT);
  pinMode(JOYSTICK1_Y_PIN, INPUT);
  pinMode(JOYSTICK2_X_PIN, INPUT);
  pinMode(JOYSTICK2_Y_PIN, INPUT);
  pinMode(JOYSTICK1_BTN_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK2_BTN_PIN, INPUT_PULLUP);
  pinMode(START_BTN_PIN, INPUT_PULLUP);
  pinMode(SELECT_BTN_PIN, INPUT_PULLUP);
  pinMode(A_BTN_PIN, INPUT_PULLUP);
  pinMode(B_BTN_PIN, INPUT_PULLUP);
  pinMode(C_BTN_PIN, INPUT_PULLUP);
  pinMode(D_BTN_PIN, INPUT_PULLUP);
  this->state.joystick1 = { 511, 511 };
  this->state.joystick2 = { 511, 511 };
  this->state.buttons = 0;
#ifdef DEBUG
  Serial.println("Initializing IR emitter");
#endif
  this->ir_enabled = 1;
  this->ir = new IRsend();
  this->rf24Init();
#ifdef DEBUG
  Serial.println("Reading initial state");
#endif
  this->update(0);
#ifdef DEBUG
  Serial.println("NanoController Initialized!");
  delay(2000);
#endif
}

uint8_t NanoController::button_state(uint8_t buttonId) {
  //uint8_t mask = 1 << buttonId;
  //uint8_t masked_state = this->state.buttons & mask;
  //return masked_state >> buttonId;
  return (this->state.buttons & (1 << buttonId)) >> buttonId;
}
