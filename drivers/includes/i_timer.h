#ifndef I_TIMER_H
#define I_TIMER_H

#include <cstdint>

enum class Timer_Peripheral : uint32_t {
  TIMER6 = 0x40001000,
  TIMER7 = 0x40001400
};

enum class Timer_IRQn : uint8_t {
  TIM6_IRQn = 17,
  TIM7_IRQn = 18
};

class ITimer {
public:
  virtual void init(uint16_t period, uint16_t prescaler, uint32_t priority) = 0;
  virtual void register_callback(std::function<void()> &&f) = 0;
};

#endif //I_TIMER_H
