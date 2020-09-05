#ifndef F0_MEMORY_H
#define F0_MEMORY_H

#include <cstdint>
#include <type_traits>

typedef uint32_t volatile device_register;

/***************************************************************************************
*    Title: Effective Modern C++ - Item 10
*    Author: Scott Meyers
*    Date: November 2014
*
***************************************************************************************/
template <typename E>
constexpr auto to_underlying(E e) noexcept
{
  return static_cast<std::underlying_type_t<E>>(e);
}

#endif //F0_MEMORY_H
