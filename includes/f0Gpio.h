#ifndef F4GPIO_H
#define F4GPIO_H

#include "IGpio.h"
#include "f0GpioMemory.h"

class F0Gpio : public IGpio {
public:
  explicit F0Gpio(GPIO_Port port, GPIO_Pin pin) {
    switch (port) {
    case GPIO_Port::PORTA:
      port_addr = GPIOA;
      break;
    case GPIO_Port::PORTB:
      port_addr = GPIOB;
      break;
    case GPIO_Port::PORTC:
      port_addr = GPIOC;
      break;
    case GPIO_Port::PORTD:
      port_addr = GPIOD;
      break;
    case GPIO_Port::PORTF:
      port_addr = GPIOF;
      break;
    }
    gpio_memory = reinterpret_cast<F0GpioMemory *>(port_addr);
    this->pin = pin;
  }
  ~F0Gpio() = default;

  GPIO_PinState read() override { return gpio_memory->readPin(pin); }
  void write(GPIO_PinState PinState) override { gpio_memory->write(pin, PinState); }
  void toggle() override { gpio_memory->toggle(pin); }
  void init(GPIO_Mode mode) override { gpio_memory->init(this->pin, mode); }

private:
  F0GpioMemory *gpio_memory;
  GPIO_TypeDef *port_addr;
  GPIO_Pin pin;
};

#endif //F4GPIO_H
