#ifndef CAT_FEEDER_IGPIO_H
#define CAT_FEEDER_IGPIO_H

enum class Gpio_Port : uint8_t
{
  PORTA = 0,
  PORTB,
  PORTC,
  PORTD,
  PORTF
};

enum class Gpio_Pin : uint16_t
{
  PIN_0   = 0x0001,
  PIN_1   = 0x0002,
  PIN_2   = 0x0004,
  PIN_3   = 0x0008,
  PIN_4   = 0x0010,
  PIN_5   = 0x0020,
  PIN_6   = 0x0040,
  PIN_7   = 0x0080,
  PIN_8   = 0x0100,
  PIN_9   = 0x0200,
  PIN_10  = 0x0400,
  PIN_11  = 0x0800,
  PIN_12  = 0x1000,
  PIN_13  = 0x2000,
  PIN_14  = 0x4000,
  PIN_15  = 0x8000,
  PIN_All = 0xFFFF
};

enum class Gpio_PinState : uint8_t
{
  RESET = 0,
  SET
};

enum class Gpio_Mode : uint8_t {
  DIGITAL_IN = 0,
  DIGITAL_OUT,
  ALTERNATE_FUNCTION,
  ANALOG
};

enum class Gpio_Direction_Mode : uint8_t {
  INPUT = 0,
  OUTPUT
};

enum class Gpio_Output_Type : uint8_t {
  PUSH_PULL = 0,
  OPEN_DRAIN
};

enum class Gpio_Output_Speed : uint8_t {
  LOW_SPEED = 0,
  MEDIUM_SPEED,
  FAST_SPEED,
  HIGH_SPEED
};

enum class Gpio_Pupd : uint8_t {
  NOPULL = 0,
  PULLUP,
  PULLDOWN,
  RESERVED
};

enum class Gpio_Alt_Func: uint32_t {
  AF0 = 0,
  AF1,
  AF2,
  AF3,
  AF4,
  AF5,
  AF6,
  AF7
};

enum class Gpio_Alt_Func_Mode: uint8_t {
  RX = 0,
  TX
};

class IGpio
{
public:
  virtual Gpio_PinState   read() = 0;
  virtual void            write(Gpio_PinState PinState) = 0;
  virtual void            toggle() = 0;
  virtual void            init(Gpio_Mode mode) = 0;
  virtual void            init(Gpio_Mode mode, Gpio_Alt_Func af, Gpio_Alt_Func_Mode af_mode) = 0;
};

#endif //CAT_FEEDER_IGPIO_H
