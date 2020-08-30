#ifndef F0_GPIO_MEMORY_H
#define F0_GPIO_MEMORY_H

#include <cstdint>
#include "i_gpio.h"

typedef uint32_t volatile device_register;

class F0GpioMemory {
public:
  F0GpioMemory() = default;
  ~F0GpioMemory() = default;
  GPIO_PinState readPin(GPIO_Pin pin);
  void write(GPIO_Pin pin, GPIO_PinState PinState);
  void toggle(GPIO_Pin pin);
  void init(GPIO_Pin pin, GPIO_Mode mode);
  void set_alternate_function(GPIO_Pin pin, GPIO_Alt_Func af, GPIO_Alt_Func_Mode mode);

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
  static constexpr uint8_t NB_PINS = 16;
  void set_mode(uint8_t position, GPIO_Mode mode);
  void set_output_type(uint8_t position, GPIO_Output_Type type);
  void set_output_speed(uint8_t position, GPIO_Output_Speed speed);
  void set_pull(uint8_t position, GPIO_Pupd pupd);
  static uint8_t get_pin_num(GPIO_Pin pin);
};

#endif //F0_GPIO_MEMORY_H
