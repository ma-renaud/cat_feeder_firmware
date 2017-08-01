#include <c++/bits/unique_ptr.h>
#include "gmock/gmock.h"
#include "IGpioMemory.h"

using namespace testing;

class GpioMemoryDouble: public IGpioMemory
{
   public:
      GpioMemoryDouble() = default;
      ~GpioMemoryDouble() = default;

      void toggle(Pins pin) override{};
};

class F0Gpio
{
   public:
      explicit F0Gpio(std::unique_ptr<IGpioMemory> _gpio_memory): gpio_memory(std::move(_gpio_memory))
      {

      }
      ~F0Gpio() = default;

   private:
      std::unique_ptr<IGpioMemory> gpio_memory;
};

class GpioGroup : public Test
{
   public:
      std::unique_ptr<IGpioMemory> gpio_memory = std::unique_ptr<IGpioMemory>(new GpioMemoryDouble());
      std::unique_ptr<F0Gpio> gpio;

      void SetUp() override
      {
         gpio = std::make_unique<F0Gpio>(std::move(gpio_memory));
      }

      void TearDown() override
      {
         gpio.reset();
      }
};

TEST_F(GpioGroup, TestTest)
{
   FAIL();
}

