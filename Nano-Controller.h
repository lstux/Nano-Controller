#ifndef _NANO_CONTROLLER_H_
#define _NANO_CONTROLLER_H_

#define DEBUG

#include <Arduino.h>
#include <stdint.h>
#include <IRLibAll.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <RF24.h>

#ifndef SERIALSPEED
#define SERIALSPEED 115200
#endif

#include "PinsDefinitions.h"
#include "IRCodes.h"

struct joystick_state {
  uint16_t x;
  uint16_t y;
};

struct controller_state {
  joystick_state joystick1;
  joystick_state joystick2;
  uint8_t buttons;
};

class NanoController {
  private:
    U8G2_SSD1306_128X64_NONAME_1_HW_I2C* lcd;
    void lcdBootup();
    void lcdDrawState();
    void serialState();
    IRsend *ir;
    uint8_t ir_enabled = 0;
    void send_ir_code();
    RF24 *rf24;
    uint64_t rf24_emitter  = 0x01000000000000; //TODO assign pseudo random address
    uint64_t rf24_receiver = 0x02000000000000; //TODO restore from EEPROM, bind procedure
    uint8_t rf24_channel = 0x10; //2.4GHz + rf24_channel*1MHz
    void rf24Init();
    void rf24SendState();
    controller_state state;
    uint8_t button_state(uint8_t buttonId);
    uint8_t joystick_change(joystick_state current, joystick_state last, uint16_t threshold);
  public:
    NanoController();
    uint8_t update(uint8_t send_mode); //Returns 0 if no changes, 1 else #send_mode : 0=none, 1=ir, 2=rf24
};

#endif
