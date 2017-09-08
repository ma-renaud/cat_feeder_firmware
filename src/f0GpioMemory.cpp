#include "f0GpioMemory.h"

void F0GpioMemory::toggle(GPIO_Pin pin) {
  ODR ^= static_cast<uint16_t>(pin);
}

void F0GpioMemory::write(GPIO_Pin pin, uint8_t PinState) {
  ODR = static_cast<uint16_t>(pin);
}