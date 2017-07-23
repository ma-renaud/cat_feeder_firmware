#include "gmock/gmock.h"
#include "f0GpioMemory.h"

using namespace testing;

class GPIOExposed : public F0GpioMemory{
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
   F0GpioMemory instance;
   ASSERT_THAT(sizeof(instance), Eq(GPIOREGISTERSSIZE));
}

TEST_F(GpioGroup, TestToggle)
{
   Pins selectedPin = Pins::PIN_5;
   gpio->toggle(selectedPin);

   ASSERT_THAT(gpio->odr(), static_cast<uint32_t>(selectedPin));
}
