#include <memory>
#include "catch2/catch.hpp"
#include "../../drivers/includes/f0_gpio.h"
#include "../../drivers/includes/f0_gpio_memory.h"

TEST_CASE("Gpio", "[gpio]") {
  static constexpr unsigned int GPIOREGISTERSSIZE = 44;

  SECTION("Test instance size") {
    F0GpioMemory instance;
    REQUIRE(sizeof(instance) == GPIOREGISTERSSIZE);
  }
}

