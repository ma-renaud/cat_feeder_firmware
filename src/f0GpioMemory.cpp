#include "f0GpioMemory.h"

void F0GpioMemory::toggle(Pins pin)
{
   ODR ^= static_cast<uint16_t>(pin);
}