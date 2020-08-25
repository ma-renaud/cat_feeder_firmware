/***************************************************************************************
*    Title: The design and implementation of a lock-free ring-buffer with contiguous reservations
*    Author: James Munns & Andrea Lattuada
*    Date: 2019/06/03
*    Availability: https://ferrous-systems.com/blog/lock-free-ring-buffer/
***************************************************************************************/

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <array>
#include <cstdint>

template<class T, std::size_t SIZE>
class CircularBuffer {
public:
  CircularBuffer() = default;
  ~CircularBuffer() = default;

  uint8_t push(T data){
    std::size_t next;

    next = (head + 1) % SIZE;
    if (next == tail) // Full
      return -1;

    buffer[head] = data;
    head = next;
    return 0;
  }

  uint8_t pop(T &data) {
    std::size_t next;

    if (head == tail)  // no data
      return -1;

    next = (tail + 1) % SIZE;;

    *data = buffer[tail];  // Read data and then move
    tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
  }
private:
  std::size_t head {0};
  std::size_t tail {0};
  std::array<std::uint8_t, SIZE> buffer;
};

#endif //CIRCULARBUFFER_H