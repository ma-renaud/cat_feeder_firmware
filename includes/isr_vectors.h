
#pragma once
#include <functional>
#include <stm32f0xx.h>
void registerHandler(IRQn_Type irqn, std::function<void()> &&f);
    