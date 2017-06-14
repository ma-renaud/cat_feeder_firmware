#include "gmock/gmock.h"
#include <array>

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
};

class GPIOExposed : public GPIO{
   public:
      uint32_t odr() const {return ODR;}
};

class GpioGroup : public Test
{
   public:
      static constexpr int GPIOREGISTERSSIZE = 44;
      std::array<uint32_t, GPIOREGISTERSSIZE> gpioRegisters;
      GPIOExposed* gpio = reinterpret_cast<GPIOExposed*>(gpioRegisters.data());

      void SetUp() override
      {
         gpioRegisters.fill(0);
      }

      void TearDown() override {}
};

TEST_F(GpioGroup, TestInstanceSize)
{
   GPIO instance;
   ASSERT_THAT(sizeof(instance), Eq(GPIOREGISTERSSIZE));
}

TEST_F(GpioGroup, TestToggle)
{
   Pins selectedPin = Pins::PIN_5;
   gpio->toggle(selectedPin);

   ASSERT_THAT(gpio->odr(), static_cast<uint32_t>(selectedPin));
}
