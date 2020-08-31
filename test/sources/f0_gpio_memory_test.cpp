#include "catch2/catch.hpp"
#include "f0_gpio_memory.h"

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

  void setPin(Gpio_Pin pin) {
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
    Gpio_Pin selectedPin = Gpio_Pin::PIN_5;
    gpio->toggle(selectedPin);

    REQUIRE(gpio->odr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test write to one") {
    Gpio_Pin selectedPin = Gpio_Pin::PIN_5;
    gpio->write(selectedPin, Gpio_PinState::SET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test write to zero") {
    Gpio_Pin selectedPin = Gpio_Pin::PIN_5;
    gpio->write(selectedPin, Gpio_PinState::SET);
    gpio->updateRegisters();
    gpio->write(selectedPin, Gpio_PinState::RESET);
    gpio->updateRegisters();

    REQUIRE(gpio->odr() == 0);
  }

  SECTION("Test read") {
    Gpio_Pin selectedPin = Gpio_Pin::PIN_5;
    gpio->setPin(selectedPin);

    REQUIRE(gpio->idr() == static_cast<uint32_t>(selectedPin));
  }

  SECTION("Test init digital out") {
    Gpio_Pin selectedPin = Gpio_Pin::PIN_5;
    gpio->init(selectedPin, Gpio_Mode::DIGITAL_OUT);

    REQUIRE(gpioRegisters[1] == 0);
    REQUIRE(gpioRegisters[2] == 0);
    REQUIRE(gpioRegisters[3] == 0);
  }

  SECTION("Test init alternate functions") {
    Gpio_Pin selectedPin = Gpio_Pin::PIN_2;
    gpio->init(selectedPin, Gpio_Mode::ALTERNATE_FUNCTION);

    REQUIRE(gpioRegisters[1] == 0);
    REQUIRE(gpioRegisters[2] == 0);
    REQUIRE(gpioRegisters[3] == 0);
  }
}
