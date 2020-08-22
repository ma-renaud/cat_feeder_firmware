#include <memory>
#include "catch2/catch.hpp"
#include "f0GpioMemory.h"

class F0Gpio : public IGpio {
public:
  F0Gpio() = default;
  ~F0Gpio() = default;

  GPIO_PinState readPin(GPIO_Pin pin) override { return gpio_memory->readPin(pin); }
  void writePin(GPIO_Pin pin, GPIO_PinState PinState) override {}
  void togglePin(GPIO_Pin pin) override { gpio_memory->toggle(pin); }

private:
  std::unique_ptr<F0GpioMemory> gpio_memory = std::make_unique<F0GpioMemory>();
};

TEST_CASE("Gpio", "[gpio]") {
  std::unique_ptr<F0Gpio> gpio;
  gpio = std::make_unique<F0Gpio>();

  SECTION("Test instance size") {
    F0GpioMemory instance;
    REQUIRE(1 == 1);
  }

  gpio.reset();
}

