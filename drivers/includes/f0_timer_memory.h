#ifndef F0_TIMER_MEMORY_H
#define F0_TIMER_MEMORY_H

#include <cstdint>

enum class CR1: uint16_t {
  CEN     = 0x01U,
  UDIS    = 0x02U,
  URS     = 0x04U,
  OPM     = 0x08U,
  ARPE    = 0x80U
};

enum class EGR: uint16_t {
  UG      = 0x01U
};

enum class DIER: uint16_t {
  UIE     = 0x001U,
  UDE     = 0x100U
};

enum class SR: uint16_t {
  UIF     = 0x01U
};

class F0TimerMemory {
public:
  F0TimerMemory() = default;
  ~F0TimerMemory() = default;
  void init(uint16_t period, uint16_t prescaler);
  void enable_interrupts();

  void clear_interrupt_flag();

protected:
  device_register CR1;          //0x00
  device_register CR2;          //0x04
  device_register SMCR;         //0x08
  device_register DIER;         //0x0C
  device_register SR;           //0x10
  device_register EGR;          //0x14
  device_register CCMR1;        //0x18
  device_register CCMR2;        //0x1C
  device_register CCER;         //0x20
  device_register CNT;          //0x24
  device_register PSC;          //0x28
  device_register ARR;          //0x2C
  device_register RCR;          //0x30
  device_register CCR1;         //0x34
  device_register CCR2;         //0x38
  device_register CCR3;         //0x3C
  device_register CCR4;         //0x40
  device_register BDTR;         //0x44
  device_register DCR;          //0x48
  device_register DMAR;         //0x4C
  device_register OR;           //0x50
};

#endif // F0_TIMER_MEMORY_H
