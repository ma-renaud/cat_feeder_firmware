#include "gmock/gmock.h"

typedef uint32_t volatile device_register;

using namespace testing;

enum class Pins : uint16_t
{
   PIN_0   = 0x0001,
   PIN_1   = 0x0002,
   PIN_2   = 0x0004,
   PIN_3   = 0x0008,
   PIN_4   = 0x0010,
   PIN_5   = 0x0020,
   PIN_6   = 0x0040,
   PIN_7   = 0x0080,
   PIN_8   = 0x0100,
   PIN_9   = 0x0200,
   PIN_10  = 0x0400,
   PIN_11  = 0x0800,
   PIN_12  = 0x1000,
   PIN_13  = 0x2000,
   PIN_14  = 0x4000,
   PIN_15  = 0x8000,
   PIN_All = 0xFFFF
};

class GPIO
{
   public:
      void toggle(Pins pin)
      {
         ODR ^= static_cast<uint16_t>(pin);
      }
   private:
      device_register MODER;
      device_register OTYPER;
      device_register ODR;
};

class GpioGroup : public Test
{

};

TEST_F(GpioGroup, FirstGpioTest)
{
   int expected = 12;
   GPIO instance;
   instance.toggle(Pins::PIN_2);
   ASSERT_THAT(sizeof(instance), Eq(expected));
}