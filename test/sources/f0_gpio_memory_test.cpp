#include "catch2/catch.hpp"
#include "f0GpioMemory.h"

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

TEST_CASE("GpioMemory", "[gpio_memory]") {

  static constexpr unsigned int GPIOREGISTERSSIZE = 44;
  std::array<uint32_t, GPIOREGISTERSSIZE> gpioRegisters;
  GPIOExposed* gpio = reinterpret_cast<GPIOExposed*>(gpioRegisters.data());
  gpioRegisters.fill(0);

  SECTION("Test instance size") {
    F0GpioMemory instance;
    REQUIRE(sizeof(instance) == GPIOREGISTERSSIZE);
  }

  SECTION("Test toogle") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->toggle(selectedPin);

    REQUIRE(gpio->odr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test write to one") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_SET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test write to zero") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_SET);
    gpio->updateRegisters();
    gpio->write(selectedPin, GPIO_PinState::GPIO_PIN_RESET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == 0);
  }

  SECTION("Test read") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->setPin(selectedPin);

    REQUIRE(gpio->idr() == static_cast<uint32_t>(selectedPin));
  }
}
