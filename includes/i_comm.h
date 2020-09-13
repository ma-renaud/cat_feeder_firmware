#ifndef I_COMM_H
#define I_COMM_H

#include <cstdint>

class IComm {
public:
  virtual void send(std::uint8_t) const = 0;
  virtual bool receive(std::uint8_t&) = 0;
};

#endif //I_COMM_H
