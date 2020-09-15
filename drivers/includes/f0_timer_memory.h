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

#endif // F0_TIMER_MEMORY_H
