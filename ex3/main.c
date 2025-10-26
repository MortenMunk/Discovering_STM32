#include "stm32f1xx.h"

volatile int i = 0;

void inc() { i++; }

int main() {
  while (1) {
    inc();
  }
}
