#include "catch2/catch.hpp"
#include "../../drivers/includes/f0_rcc_memory.h"

class RCCExposed : public F0RccMemory{
public:
  uint32_t cr() const {return CR;}

  void or_cr(uint32_t val) {
    CR = CR | val;
  }
};

TEST_CASE("RccMemory", "[rcc_memory]") {
  static constexpr unsigned int RCCREGISTERSSIZE = 56; //14*4
  std::array<uint32_t, RCCREGISTERSSIZE> rccRegisters;
  RCCExposed* rcc = reinterpret_cast<RCCExposed*>(rccRegisters.data());
  rccRegisters.fill(0);

  SECTION("Test instance size") {
    F0RccMemory instance;
    REQUIRE(sizeof(instance) == RCCREGISTERSSIZE);
  }

  SECTION("Test init with pll") {
    rcc->or_cr(0x02000000 | 0x00000002);
    rcc->init(Rcc_PLL_Source::HSI, Rcc_PLL_Mul::MUL12);

    REQUIRE(rccRegisters[0] == 0x3000003);
    REQUIRE(rccRegisters[1] == 0x280002);
  }
}