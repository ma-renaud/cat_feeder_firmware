#include <cstdint>
#include <algorithm>

extern std::uintptr_t _rodata_begin;
extern std::uintptr_t _data_begin;
extern std::uintptr_t _data_end;

extern std::uintptr_t _bss_begin;
extern std::uintptr_t _bss_end;

extern void (*_ctors_begin[])(void);
extern void (*_ctors_end[])(void);

void init_data();
void init_bss();
void init_static_ctor();

void Reset_Handler()
{
  init_data();
  init_bss();
  init_static_ctor();

  //asm volatile ("bl __libc_init_array");
  asm volatile ("bl  main");
}

void init_data() {
  const std::size_t cnt = (&_data_end - &_data_begin);
  std::copy(&_rodata_begin, &_rodata_begin + cnt, &_data_begin);
}

void init_bss() {
  std::fill(&_bss_begin, &_bss_end, 0U);
}

void init_static_ctor() {
  const std::size_t cnt = _ctors_end - _ctors_begin;
  for (std::size_t i = 0; i < cnt; i++) {
    _ctors_begin[i]();
  }
}