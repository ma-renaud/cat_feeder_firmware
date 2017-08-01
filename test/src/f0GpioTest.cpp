#include <memory>
#include "gmock/gmock.h"
#include "f0GpioMemory.h"

using namespace testing;

class F0Gpio
{
   public:
      F0Gpio() = default;
      ~F0Gpio() = default;

   private:
      std::unique_ptr<F0GpioMemory> gpio_memory = std::make_unique<F0GpioMemory>();
};

class GpioGroup : public Test
{
   public:
      std::unique_ptr<F0Gpio> gpio;

      void SetUp() override
      {
         gpio = std::make_unique<F0Gpio>();
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

