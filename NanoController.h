#ifndef _NanoController_h_
#define _NanoController_h_

// Pins affectation
#define JOY1_X     A2
#define JOY1_Y     A1
#define JOY1_BTN   A0
#define JOY2_X     A7
#define JOY2_Y     A6
#define JOY2_BTN   A3
#define BTN_A      D4
#define BTN_B      D5
#define BTN_X      D6
#define BTN_Y      D7
#define BTN_SELECT D2 //(INT0)
#define BTN_START  D3 //(INT1)

/* NRF24L01 pin (SPI)
/ ??    D9
/ SS    D10
/ MOSI  D11
/ MISO  D12
/ CLOCK D13
/*

/* LCD display pins (I2C)
/ DATA  A4
/ CLOCK A5
/*

Class NanoController {
  public:
    uint8_t joy1_x;
    uint8_t joy1_y;
    uint8_t joy2_x;
    uint8_t joy2_y;
    uint8_t buttons;
    void NanoController();
    void getInputs();
    char* serialDump();
};

#endif
