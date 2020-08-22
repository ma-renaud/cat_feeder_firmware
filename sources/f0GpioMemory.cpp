#include "f0GpioMemory.h"

GPIO_PinState F0GpioMemory::readPin(GPIO_Pin pin){
  if ((IDR & static_cast<uint8_t>(pin)) != static_cast<uint8_t>(GPIO_PinState::GPIO_PIN_RESET))
  {
    return GPIO_PinState::GPIO_PIN_SET;
  }
  else
  {
    return GPIO_PinState::GPIO_PIN_RESET;
  }
}

void F0GpioMemory::write(GPIO_Pin pin, GPIO_PinState PinState) {
  if(PinState != GPIO_PinState::GPIO_PIN_RESET)
    BSRR = static_cast<uint32_t>(pin);
  else
    BRR = static_cast<uint32_t>(pin);
}

void F0GpioMemory::toggle(GPIO_Pin pin) {
  ODR ^= static_cast<uint16_t>(pin);
}