#include "catch2/catch.hpp"
#include "simple_protocol_parser.h"

class SimpleProtocolParserStub : public SimpleProtocolParser
{
   public:
      SimpleProtocolParserStub() { trace = ""; }
      std::string getTrace() { return trace; }

   private:
      std::string trace;

      void receptionStart() override { trace += "S"; }
      void receiveData([[maybe_unused]] char received) override { trace += "D"; }
      void appendReceivedData() override { trace += "A"; }
      void receptionCompleted() override { trace += "E"; }
};

TEST_CASE("SimpleProtocolParserLogic", "[simple_protocol_parser_logic]") {
  using Catch::Matchers::Equals;
  SimpleProtocolParserStub parser;

  SECTION("Test start char state change") {
    parser.receiveChar('<');

    CHECK_THAT(parser.getTrace().c_str(), Equals("S"));
  }

  SECTION("Test receive four char then end") {
    parser.receiveChar('<');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('>');

    CHECK_THAT(parser.getTrace().c_str(), Equals("SDDDDAE"));
  }

  SECTION("Test receive three data") {
    parser.receiveChar('<');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar(':');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar(':');
    parser.receiveChar('a');
    parser.receiveChar('>');

    CHECK_THAT(parser.getTrace().c_str(), Equals("SDDDDDADDADAE"));
  }
}
