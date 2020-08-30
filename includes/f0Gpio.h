#ifndef F0GPIO_H
#define F0GPIO_H

#include "i_gpio.h"
#include "f0_gpio_memory.h"

class F0Gpio : public IGpio {
public:
  explicit F0Gpio(GPIO_Port port, GPIO_Pin pin) {
    GPIO_TypeDef *port_addr;
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
  void configure_alternate_function(GPIO_Alt_Func af, GPIO_Alt_Func_Mode mode) override { gpio_memory->set_alternate_function(pin, af, mode); }

private:
  F0GpioMemory *gpio_memory;
  GPIO_Pin pin;
};

#endif //F0GPIO_H
