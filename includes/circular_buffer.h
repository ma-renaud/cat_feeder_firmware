#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <array>
#include <atomic>
#include <cstdint>

// Lockfree circular buffer
// Can only support one producer and one consumer
// One space is lost for the lookahead -> SIZE+1

template<class T, std::size_t SIZE>
class CircularBuffer {
public:
  CircularBuffer() = default;
  ~CircularBuffer() = default;

  int8_t push(T data){
    std::size_t next;

    next = (head + 1) % (SIZE+1);
    if (next == tail) // Full
      return -1;  //fail

    buffer[head] = data;
    head = next;
    buf_size++;
    return 0;  //success
  }

  int8_t pop(T &data) {
    std::size_t next;

    if (head == tail)  // no data
      return -1;  //fail

    next = (tail + 1) % (SIZE+1);

    data = buffer[tail];
    tail = next;
    buf_size--;
    return 0;  //success
  }

  std::size_t size() {
    return buf_size;
  }

  std::size_t available() {
    return SIZE - buf_size;
  }

private:
  std::atomic_size_t head {0};
  std::atomic_size_t tail {0};
  std::atomic_size_t buf_size {0};
  std::array<std::uint8_t, SIZE+1> buffer;
};

#endif //CIRCULARBUFFER_H