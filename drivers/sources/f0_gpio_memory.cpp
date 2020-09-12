#include "../includes/f0_gpio_memory.h"
#include "../includes/i_gpio.h"

Gpio_PinState F0GpioMemory::readPin(Gpio_Pin pin) {
  if ((IDR & static_cast<uint8_t>(pin)) != static_cast<uint8_t>(Gpio_PinState::RESET)) {
    return Gpio_PinState::SET;
  } else {
    return Gpio_PinState::RESET;
  }
}

void F0GpioMemory::write(Gpio_Pin pin, Gpio_PinState PinState) {
  if (PinState != Gpio_PinState::RESET)
    BSRR = static_cast<uint32_t>(pin);
  else
    BRR = static_cast<uint32_t>(pin);
}

void F0GpioMemory::toggle(Gpio_Pin pin) {
  ODR ^= static_cast<uint16_t>(pin);
}

void F0GpioMemory::init(Gpio_Pin pin, Gpio_Mode mode) {
  uint8_t position = get_pin_num(pin);

  if (mode == Gpio_Mode::DIGITAL_OUT) {
    set_mode(position, mode);
    set_output_type(position, Gpio_Output_Type::PUSH_PULL);
    set_output_speed(position, Gpio_Output_Speed::LOW_SPEED);
    set_pull(position, Gpio_Pupd::NOPULL);
  } else if (mode == Gpio_Mode::DIGITAL_IN) {
    set_mode(position, mode);
    set_pull(position, Gpio_Pupd::PULLDOWN);
  } else if (mode == Gpio_Mode::ALTERNATE_FUNCTION) {
    set_mode(position, mode);
  }
}

void F0GpioMemory::set_alternate_function(Gpio_Pin pin, Gpio_Alt_Func af, Gpio_Alt_Func_Mode mode) {
  uint8_t position = get_pin_num(pin);
  if (pin < Gpio_Pin::PIN_8) {
    AFR[0] &= ~(((uint32_t)0xFF) << (4 * position));
    AFR[0] |= (((uint32_t) 0x01) << (4 * position));
  } else {
    AFR[1] &= ~(((uint32_t)0xFF) << (4 * (position%8)));
    AFR[1] |= (((uint32_t) 0x01) << (4 * (position%8)));
  }

  if (mode == Gpio_Alt_Func_Mode::RX) {
    set_output_type(position, Gpio_Output_Type::OPEN_DRAIN);
    set_output_speed(position, Gpio_Output_Speed::LOW_SPEED);
    set_pull(position, Gpio_Pupd::PULLUP);
  } else if (mode == Gpio_Alt_Func_Mode::TX) {
    set_output_type(position, Gpio_Output_Type::PUSH_PULL);
    set_output_speed(position, Gpio_Output_Speed::LOW_SPEED);
    set_pull(position, Gpio_Pupd::PULLUP);
  }
}

void F0GpioMemory::set_mode(uint8_t position, Gpio_Mode mode) {
  uint32_t temp = MODER;
  temp &= ~(static_cast<uint32_t>(0x03) << (position * 2));
  temp |= (static_cast<uint8_t>(mode) << (position * 2));
  MODER = temp;
}

void F0GpioMemory::set_output_type(uint8_t position, Gpio_Output_Type type) {
  uint32_t temp = OTYPER;
  temp &= ~(static_cast<uint32_t>(0x01) << position);
  temp |= static_cast<uint8_t>(type) << position;
  OTYPER = temp;
}

void F0GpioMemory::set_output_speed(uint8_t position, Gpio_Output_Speed speed) {
  uint32_t temp = OSPEEDR;
  temp &= ~(static_cast<uint32_t>(0x03) << (position * 2));
  temp |= (static_cast<uint8_t>(speed) << (position * 2));
  OSPEEDR = temp;
}

void F0GpioMemory::set_pull(uint8_t position, Gpio_Pupd pupd) {
  uint32_t temp = PUPDR;
  temp &= ~(static_cast<uint32_t>(0x03) << (position * 2));
  temp |= (static_cast<uint8_t>(pupd) << (position * 2));
  PUPDR = temp;
}

uint8_t F0GpioMemory::get_pin_num(Gpio_Pin pin) {
  switch (pin) {
  case Gpio_Pin::PIN_0:return 0;
  case Gpio_Pin::PIN_1:return 1;
  case Gpio_Pin::PIN_2:return 2;
  case Gpio_Pin::PIN_3:return 3;
  case Gpio_Pin::PIN_4:return 4;
  case Gpio_Pin::PIN_5:return 5;
  case Gpio_Pin::PIN_6:return 6;
  case Gpio_Pin::PIN_7:return 7;
  case Gpio_Pin::PIN_8:return 8;
  case Gpio_Pin::PIN_9:return 9;
  case Gpio_Pin::PIN_10:return 10;
  case Gpio_Pin::PIN_11:return 11;
  case Gpio_Pin::PIN_12:return 12;
  case Gpio_Pin::PIN_13:return 13;
  case Gpio_Pin::PIN_14:return 14;
  case Gpio_Pin::PIN_15:return 15;
  case Gpio_Pin::PIN_All:break;
  }
}