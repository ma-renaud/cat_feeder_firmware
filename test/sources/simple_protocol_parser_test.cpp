#include "catch2/catch.hpp"
#include "serialParser.h"

TEST_CASE("SimpleProtocolParser", "[simple_protocol_parser]") {
  using Catch::Matchers::Equals;
  SerialParser parser;

  SECTION("Test receive three data") {
    std::vector<std::string> expected {"aaaaa", "aa", "a"};

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

    CHECK_THAT(parser.getDecoded(), Equals(expected));
  }
}
