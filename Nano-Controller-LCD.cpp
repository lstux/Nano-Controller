// LCD related functions
#include "Nano-Controller.h"

void NanoController::lcdBootup() {
  #ifdef DEBUG
  Serial.println("Initializing LCD display");
  #endif
  this->lcd->firstPage();
  do {
    this->lcd->setFont(u8g2_font_ncenB12_tr);
    this->lcd->drawStr(10, 16, "NanoController");
    this->lcd->setFont(u8g2_font_ncenB08_tr);
    this->lcd->drawStr(10, 26, "Booting...");
  } while (this->lcd->nextPage());
  return;
}

void NanoController::lcdDrawState() {
  uint8_t j1x = round((float)((float)this->state.joystick1.x/1023)*30);
  uint8_t j1y = round((float)((float)this->state.joystick1.y/1023)*30);
  uint8_t j2x = round((float)((float)this->state.joystick2.x/1023)*30);
  uint8_t j2y = round((float)((float)this->state.joystick2.y/1023)*30);
  uint8_t frame_size = 30;
  uint8_t frame1_x = 0;
  uint8_t frame1_y = 26;
  uint8_t frame2_x = 40;
  uint8_t frame2_y = 16;

  this->lcd->firstPage();
  do {
    this->lcd->drawFrame(frame1_x,frame1_y,frame_size,frame_size);
    if (this->button_state(JOYSTICK1_BTN)!=0) this->lcd->drawCircle(frame1_x + j1x, frame1_y + frame_size - j1y, 2);
    else this->lcd->drawCircle(frame1_x + j1x, frame1_y + frame_size - j1y, 1);
    this->lcd->drawFrame(frame2_x,frame2_y,frame_size,frame_size);
    if (this->button_state(JOYSTICK2_BTN)!=0) this->lcd->drawCircle(frame2_x + j2x, frame2_y + frame_size - j2y, 2);
    else this->lcd->drawCircle(frame2_x + j2x, frame2_y + frame_size - j2y, 1);

    //this->lcd->setFont(u8g2_font_ncenR08_tr);
    //if (this->button_state(START_BTN)!=0) this->lcd->drawStr(frame1_x, 10, "Start");
    //if (this->button_state(SELECT_BTN)!=0) this->lcd->drawStr(frame2_x, 10, "Select");

    if (this->button_state(A_BTN)!=0) this->lcd->setFont(u8g2_font_ncenB08_tr);
    else this->lcd->setFont(u8g2_font_ncenR08_tr);
    this->lcd->drawStr(110, 54, "A ");
    if (this->button_state(B_BTN)!=0) this->lcd->setFont(u8g2_font_ncenB08_tr);
    else this->lcd->setFont(u8g2_font_ncenR08_tr);
    this->lcd->drawStr(120, 42, "B ");
    if (this->button_state(C_BTN)!=0) this->lcd->setFont(u8g2_font_ncenB08_tr);
    else this->lcd->setFont(u8g2_font_ncenR08_tr);
    this->lcd->drawStr(100, 42, "C ");
    if (this->button_state(D_BTN)!=0) this->lcd->setFont(u8g2_font_ncenB08_tr);
    else this->lcd->setFont(u8g2_font_ncenR08_tr);
    this->lcd->drawStr(110, 30, "D");

  } while (this->lcd->nextPage());
}
