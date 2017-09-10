#include "gmock/gmock.h"
#include "f0GpioMemory.h"

using namespace testing;

class GPIOExposed : public F0GpioMemory{
   public:
      uint32_t odr() const {return ODR;}
      uint32_t idr() const {return IDR;}

      void updateRegisters(){
        ODR = ODR & ~(BRR);
        ODR = ODR & ~(BSRR >> 16) | (BSRR & 0xFFFF);
        BRR = 0;
        BSRR = 0;
      }

      void setPin(GPIO_Pin pin) {
        IDR = IDR | (static_cast<uint32_t>(pin) & 0xFFFF);
      }
};

class GpioMemoryGroup : public Test
{
   public:
      static constexpr unsigned int GPIOREGISTERSSIZE = 44;
      std::array<uint32_t, GPIOREGISTERSSIZE> gpioRegisters;
      GPIOExposed* gpio = reinterpret_cast<GPIOExposed*>(gpioRegisters.data());

      void SetUp() override
      {
         gpioRegisters.fill(0);
      }

      void TearDown() override {}
};

TEST_F(GpioMemoryGroup, TestInstanceSize)
{
   F0GpioMemory instance;
   ASSERT_THAT(sizeof(instance), Eq(GPIOREGISTERSSIZE));
}

TEST_F(GpioMemoryGroup, TestToggle)
{
  GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
   gpio->toggle(selectedPin);

   ASSERT_THAT(gpio->odr(), Eq(static_cast<uint32_t>(selectedPin)));
}

TEST_F(GpioMemoryGroup, TestWriteToOne)
{
  GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
  gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_SET);
  gpio->updateRegisters();

  ASSERT_THAT(gpio->odr(), Eq(static_cast<uint32_t>(selectedPin)));
}

TEST_F(GpioMemoryGroup, TestWriteToZero)
{
  GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
  gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_SET);
  gpio->updateRegisters();
  gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_RESET);
  gpio->updateRegisters();

  ASSERT_THAT(gpio->odr(), Eq(0));
}

TEST_F(GpioMemoryGroup, TestRead)
{
  GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
  gpio->setPin(selectedPin);

  ASSERT_THAT(gpio->idr(), Eq(static_cast<uint32_t>(selectedPin)));
}
