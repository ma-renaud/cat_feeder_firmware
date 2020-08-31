#ifndef F0_GPIO_H
#define F0_GPIO_H

#include "i_rcc.h"
#include "i_gpio.h"
#include "f0_gpio_memory.h"

class F0Gpio : public IGpio {
public:
  explicit F0Gpio(Gpio_Port port, Gpio_Pin pin, IRcc *rcc) {
    GPIO_TypeDef *port_addr;
    Rcc_Gpio rcc_port;
    switch (port) {
    case Gpio_Port::PORTA:
      port_addr = GPIOA;
      rcc_port = Rcc_Gpio::PORTA;
      break;
    case Gpio_Port::PORTB:
      port_addr = GPIOB;
      rcc_port = Rcc_Gpio::PORTB;
      break;
    case Gpio_Port::PORTC:
      port_addr = GPIOC;
      rcc_port = Rcc_Gpio::PORTC;
      break;
    case Gpio_Port::PORTD:
      port_addr = GPIOD;
      rcc_port = Rcc_Gpio::PORTD;
      break;
    case Gpio_Port::PORTF:
      port_addr = GPIOF;
      rcc_port = Rcc_Gpio::PORTF;
      break;
    }

    rcc->enable_gpio_port(rcc_port);
    gpio_memory = reinterpret_cast<F0GpioMemory *>(port_addr);
    this->pin = pin;
  }
  ~F0Gpio() = default;

  Gpio_PinState read() override { return gpio_memory->readPin(pin); }
  void write(Gpio_PinState PinState) override { gpio_memory->write(pin, PinState); }
  void toggle() override { gpio_memory->toggle(pin); }
  void init(Gpio_Mode mode) override { gpio_memory->init(this->pin, mode); }
  void init(Gpio_Mode mode, Gpio_Alt_Func af, Gpio_Alt_Func_Mode af_mode) override {
    gpio_memory->init(this->pin, mode);
    gpio_memory->set_alternate_function(pin, af, af_mode);
  }

private:
  F0GpioMemory *gpio_memory;
  Gpio_Pin pin;
};

#endif //F0_GPIO_H
