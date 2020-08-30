#include <memory>
#include "catch2/catch.hpp"
#include "f0Gpio.h"
#include "f0_gpio_memory.h"

TEST_CASE("Gpio", "[gpio]") {
  static constexpr unsigned int GPIOREGISTERSSIZE = 44;

  SECTION("Test instance size") {
    F0GpioMemory instance;
    REQUIRE(sizeof(instance) == GPIOREGISTERSSIZE);
  }
}

