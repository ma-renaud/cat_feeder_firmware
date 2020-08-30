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
    gpio->write(selectedPin, GPIO_PinState::SET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test write to zero") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->write(selectedPin, GPIO_PinState::SET);
    gpio->updateRegisters();
    gpio->write(selectedPin, GPIO_PinState::RESET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == 0);
  }

  SECTION("Test read") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->setPin(selectedPin);

    REQUIRE(gpio->idr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test init digital out") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_5;
    gpio->init(selectedPin, GPIO_Mode::DIGITAL_OUT);

    REQUIRE(gpioRegisters[1] == 0);
    REQUIRE(gpioRegisters[2] == 0);
    REQUIRE(gpioRegisters[3] == 0);
  }

  SECTION("Test init alternate functions") {
    GPIO_Pin selectedPin = GPIO_Pin::PIN_2;
    gpio->init(selectedPin, GPIO_Mode::ALTERNATE_FUNCTION);

    REQUIRE(gpioRegisters[1] == 0);
    REQUIRE(gpioRegisters[2] == 0);
    REQUIRE(gpioRegisters[3] == 0);
  }
}
