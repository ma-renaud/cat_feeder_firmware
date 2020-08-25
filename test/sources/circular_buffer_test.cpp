#include "catch2/catch.hpp"

#include "circular_buffer.h"
#include <cstdint>

TEST_CASE("Circular buffer", "[circular_buffer]") {
  const size_t BUFFER_SIZE = 100;
  cbuf_handle_t cbuf = circular_buffer_init(BUFFER_SIZE);

  SECTION("Add one char") {
    REQUIRE(circular_buffer_put(cbuf, 'a') == 0);
    REQUIRE(circular_buf_size(cbuf) == 1);
    REQUIRE(circular_buf_available(cbuf) == BUFFER_SIZE-1);
  }

  SECTION("Add one char with invalid buffer") {
    circular_buffer_free(&cbuf);
    REQUIRE(circular_buffer_put(cbuf, 'a') == -1);
  }

  SECTION("Get one char") {
    unsigned char expected = 'a';
    circular_buffer_put(cbuf, expected);

    unsigned char test = 0;
    REQUIRE(circular_buffer_get(cbuf, &test) == 0);
    REQUIRE(test == expected);
  }

  SECTION("Get one char with invalid buffer") {
    circular_buffer_free(&cbuf);
    unsigned char test = 0;
    REQUIRE(circular_buffer_get(cbuf, &test) == -1);
  }

  SECTION("Get two char with one available") {
    unsigned char expected = 'a';
    circular_buffer_put(cbuf, expected);
    circular_buf_size(cbuf);

    unsigned char test = 0;
    REQUIRE(circular_buffer_get(cbuf, &test) == 0);
    REQUIRE(test == expected);
    REQUIRE(circular_buffer_get(cbuf, &test) == -1);
  }

  SECTION("Add four char in a two space buffer with overwrite") {
    const size_t NEW_BUFFER_SIZE = 2;
    circular_buffer_free(&cbuf);
    cbuf = circular_buffer_init(NEW_BUFFER_SIZE);

    REQUIRE(circular_buffer_put_over(cbuf, 'a') == 0);
    REQUIRE(circular_buffer_put_over(cbuf, 'b') == 0);
    REQUIRE(circular_buffer_put_over(cbuf, 'c') == 0);
    REQUIRE(circular_buffer_put_over(cbuf, 'd') == 0);
    REQUIRE(circular_buf_size(cbuf) == 2);
    REQUIRE(circular_buf_full(cbuf) == 1);

    unsigned char test = 0;
    REQUIRE(circular_buffer_get(cbuf, &test) == 0);
    REQUIRE(test == 'c');
    REQUIRE(circular_buffer_get(cbuf, &test) == 0);
    REQUIRE(test == 'd');
    REQUIRE(circular_buffer_get(cbuf, &test) == -1);
  }

  SECTION("Resize buffer from existing one") {
    const size_t INIT_BUFFER_SIZE = 5;
    const size_t NEW_BUFFER_SIZE = 10;
    circular_buffer_free(&cbuf);
    cbuf = circular_buffer_init(5);
    for(int i=97; i < 97+INIT_BUFFER_SIZE; i++)
      circular_buffer_put(cbuf, i);

    REQUIRE(circular_buffer_put(cbuf, 'a') == -1);

    cbuf_handle_t new_cbuf = circular_buffer_resize(cbuf, NEW_BUFFER_SIZE);
    circular_buffer_free(&cbuf);
    cbuf = new_cbuf;

    for(int i=97+INIT_BUFFER_SIZE; i < 97+INIT_BUFFER_SIZE+3; i++)
      circular_buffer_put(cbuf, i);

    unsigned char test = 0;
    for(int i=0; i < INIT_BUFFER_SIZE+3; i++) {
      circular_buffer_get(cbuf, &test);
      REQUIRE(test == 97 + i);
    }
  }

  circular_buffer_free(&cbuf);
}