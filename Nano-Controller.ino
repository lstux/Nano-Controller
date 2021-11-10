#include "Nano-Controller.h"
NanoController *nc;

void setup() {
  nc = new NanoController();
}

void loop() {
  nc->update(2);
}
