#ifndef CAT_FEEDER_IGPIO_H
#define CAT_FEEDER_IGPIO_H

class IGpio
{
public:
  uint8_t           HAL_GPIO_ReadPin(uint16_t GPIO_Pin) = 0;
  void              HAL_GPIO_WritePin(uint16_t GPIO_Pin, GPIO_PinState PinState) = 0;
  void              HAL_GPIO_TogglePin(uint16_t GPIO_Pin) = 0;
  HAL_StatusTypeDef HAL_GPIO_LockPin(uint16_t GPIO_Pin) = 0;
};

#endif //CAT_FEEDER_IGPIO_H
