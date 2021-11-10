// IR related functions
#include "Nano-Controller.h"

void NanoController::send_ir_code() {
  if (this->state.joystick1.x > 800) { this->ir->send(SONY, NC_IR_UP, 20); return; }
  if (this->state.joystick1.x < 200) { this->ir->send(SONY, NC_IR_DOWN, 20); return; }
  if (this->state.joystick1.y > 800) { this->ir->send(SONY, NC_IR_RIGHT, 20); return; }
  if (this->state.joystick1.y < 200) { this->ir->send(SONY, NC_IR_LEFT, 20); return; }
  if (this->state.joystick2.x > 800) { this->ir->send(SONY, NC_IR_UP2, 20); return; }
  if (this->state.joystick2.x < 200) { this->ir->send(SONY, NC_IR_DOWN2, 20); return; }
  if (this->state.joystick2.y > 800) { this->ir->send(SONY, NC_IR_RIGHT2, 20); return; }
  if (this->state.joystick2.y < 200) { this->ir->send(SONY, NC_IR_LEFT2, 20); return; }
  if (this->button_state(JOYSTICK1_BTN)) { this->ir->send(SONY, NC_IR_JOY1, 20); return; }
  if (this->button_state(JOYSTICK2_BTN)) { this->ir->send(SONY, NC_IR_JOY2, 20); return; }
  if (this->button_state(START_BTN))     { this->ir->send(SONY, NC_IR_START, 20); return; }
  if (this->button_state(SELECT_BTN))    { this->ir->send(SONY, NC_IR_SELECT, 20); return; }
  if (this->button_state(A_BTN)) { this->ir->send(SONY, NC_IR_A, 20); return; }
  if (this->button_state(B_BTN)) { this->ir->send(SONY, NC_IR_B, 20); return; }
  if (this->button_state(C_BTN)) { this->ir->send(SONY, NC_IR_C, 20); return; }
  if (this->button_state(D_BTN)) { this->ir->send(SONY, NC_IR_D, 20); return; }
}
