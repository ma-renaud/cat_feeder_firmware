#ifndef F0_GPIO_MEMORY_H
#define F0_GPIO_MEMORY_H

#include <cstdint>
#include "f0_memory.h"
#include "i_gpio.h"

class F0GpioMemory {
public:
  F0GpioMemory() = default;
  ~F0GpioMemory() = default;
  Gpio_PinState readPin(Gpio_Pin pin);
  void write(Gpio_Pin pin, Gpio_PinState PinState);
  void toggle(Gpio_Pin pin);
  void init(Gpio_Pin pin, Gpio_Mode mode);
  void set_alternate_function(Gpio_Pin pin, Gpio_Alt_Func af, Gpio_Alt_Func_Mode mode);

protected:
  device_register MODER;
  device_register OTYPER;
  device_register OSPEEDR;
  device_register PUPDR;
  device_register IDR;
  device_register ODR;
  device_register BSRR;
  device_register LCKR;
  device_register AFR[2];
  device_register BRR;

private:
  void set_mode(uint8_t position, Gpio_Mode mode);
  void set_output_type(uint8_t position, Gpio_Output_Type type);
  void set_output_speed(uint8_t position, Gpio_Output_Speed speed);
  void set_pull(uint8_t position, Gpio_Pupd pupd);
  static uint8_t get_pin_num(Gpio_Pin pin);
};

#endif //F0_GPIO_MEMORY_H
