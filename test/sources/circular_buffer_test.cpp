#include "catch2/catch.hpp"

#include "circular_buffer.h"
#include <cstdint>

TEST_CASE("Circular buffer", "[circular_buffer]") {
  const size_t BUFFER_SIZE = 100;
  CircularBuffer<unsigned char, BUFFER_SIZE> cbuf;

  SECTION("Add one char") {
    REQUIRE(cbuf.push('a') == 0);
    REQUIRE(cbuf.size() == 1);
    REQUIRE(cbuf.available() == BUFFER_SIZE-1);
  }

  SECTION("Add one char in full buffer") {
    CircularBuffer<unsigned char, 1> new_cbuf;
    REQUIRE(new_cbuf.push('a') == 0);
    REQUIRE(new_cbuf.push('a') == -1);
    REQUIRE(new_cbuf.size() == 1);
    REQUIRE(new_cbuf.available() == 0);
  }

  SECTION("Get one char") {
    unsigned char expected = 'a';
    cbuf.push(expected);

    unsigned char popped = 0;
    REQUIRE(cbuf.pop(popped) == 0);
    REQUIRE(popped == expected);
  }

  SECTION("Get two char with one available") {
    unsigned char expected = 'a';
    cbuf.push(expected);

    unsigned char popped = 0;
    REQUIRE(cbuf.pop(popped) == 0);
    REQUIRE(popped == expected);
    REQUIRE(cbuf.pop(popped) == -1);
  }
}