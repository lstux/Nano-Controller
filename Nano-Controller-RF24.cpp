#include "Nano-Controller.h"

#ifdef DEBUG
#include <printf.h>
#endif

void NanoController::rf24Init() {
#ifdef DEBUG
  Serial.println("Initializing RF24 module");
#endif
  this->rf24 = new RF24(RF24_CE_PIN, RF24_CS_PIN);
  this->rf24->begin();
  this->rf24->setPALevel(RF24_PA_LOW);
  this->rf24->setDataRate(RF24_250KBPS);
  this->rf24->setChannel(this->rf24_channel);
  this->rf24->openWritingPipe(this->rf24_emitter);
  this->rf24->openReadingPipe(1, this->rf24_receiver);
  this->rf24->startListening();
#ifdef DEBUG
  /*Serial.println("RF24 details :");
  Serial.print("  PA level      : ");
  switch(this->rf24->getPALevel) {
    case(RF24_PA_MIN):  Serial.print("PA_MIN"); break;
    case(RF24_PA_LOW):  Serial.print("PA_LOW"); break;
    case(RF24_PA_HIGH): Serial.print("PA_HIGH"); break;
    case(RF24_PA_MAX):  Serial.print("PA_MAX"); break;
  }
  Serial.println(" (PA_LOW)");

  Serial.print("  Data rate     : ");
  switch(this->rf24->getDataRate()) {
    case(RF24_250KBPS): Serial.print("250Kb/s"); break;
    case(RF24_1MBPS):   Serial.print(" 1Mb/s"); break;
    case(RF24_2MBPS):   Serial.print(" 2Mb/s"); break;
  }
  Serial.println(" (250KBPS)");

  Serial.print("  Channel       : ");
  uint16_t mhz = 2400 + (this->rf24_channel * 10);
  Serial.print("("); Serial.print(mhz); Serial.println("Mhz)");

  Serial.print("  Controller ID : "); Serial.println(this->rf24_emitter);

  Serial.print("  Model ID      : "); Serial.println(this->rf24_receiver);
  */

  printf_begin();
  this->rf24->printDetails();
#endif
}

void NanoController::rf24SendState() {
  while(this->rf24->testCarrier()) {};
#ifdef DEBUG
  Serial.print("Sending controller state with RF24, payload=");
  Serial.println(sizeof(controller_state));
#endif
  this->rf24->stopListening();
  this->rf24->write(&this->state, sizeof(controller_state));
  this->rf24->startListening();
}
