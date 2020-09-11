
#include <array>
#include "isr_vectors.h"

#define STM32_HANDLERS_OFFSET 16

/**
 * While not a function, it is convenient to declare it as such, because now it can be put into the
 * reset vectors (array of functions).
*/
extern "C" void _estack(void);
void Reset_Handler();

/**
 * Handler that won't exit. If an exception occurs, and you didn't define an handler for it, yer dead.
 */
extern "C"
{
__attribute__((noreturn)) void Unassigned_Handler(void) {
  for (;;) {
    // If you get here, An interrupt is generated and the ISR vector is not set.
    // To get which ISR number is trigged, in gdb console type this: p getVectNumber()
    // This will tell the number of the ISR called. If the ISR number is 15, mostly the systick_handler is not defined.
    // To use the systick, replace WEAK_FUNC(SysTick_Handler) by void SysTick_Handler();
    // Add the STMicro::STMicroNow library and recompile the code.
    // If the ISR number is not 15, look at array void (*isr_vector[])(void) to get the ISR name. Use the number to find the index
    asm("BKPT #0");
  }
}
}

int getVectNumber() {
  return SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
}

//#define ISR_LOW_MEMORY 1
#ifdef ISR_LOW_MEMORY
#warning "Modify this line to adapt it to the design. Adjust the number of element in the array"
//The number of element in the array must match. The -1 is important here. This tell that the IRQn is available
std::array<std::pair<int, std::function<void()>>,1> isrHandlers = {
    std::make_pair(-1, Unassigned_Handler)
};
void ISR()
{
    for(decltype(isrHandlers.size()) i = 0 ; i < isrHandlers.size(); ++i)
    {
        if(isrHandlers[i].first == getVectNumber())
        {
            isrHandlers[i].second();
            return;
        }
    }
}
void registerHandler(IRQn_Type irqn, std::function<void()> &&f)
{
    auto it = std::find_if(std::begin(isrHandlers), std::end(isrHandlers),
        [&irqn](auto p)
        {
            return p.first == irqn;
        }
    );

    if(it == std::end(isrHandlers))
    {
        for(decltype(isrHandlers.size()) i = 0; i < isrHandlers.size(); i++)
        {
            if(isrHandlers[i].first == -1)
            {
                isrHandlers[i] = std::make_pair(irqn, f);
            }
        }
    }
}
#else
std::array<std::function<void()>, 32> isrHandlers = {
    Unassigned_Handler, /*WWDG_IRQHandler*/
    Unassigned_Handler, /*PVD_IRQHandler*/
    Unassigned_Handler, /*RTC_IRQHandler*/
    Unassigned_Handler, /*FLASH_IRQHandler*/
    Unassigned_Handler, /*RCC_CRS_IRQHandler*/
    Unassigned_Handler, /*EXTI0_1_IRQHandler*/
    Unassigned_Handler, /*EXTI2_3_IRQHandler*/
    Unassigned_Handler, /*EXTI4_15_IRQHandler*/
    Unassigned_Handler, /*0*/
    Unassigned_Handler, /*DMA1_Channel1_IRQHandler*/
    Unassigned_Handler, /*DMA1_Channel2_3_IRQHandler*/
    Unassigned_Handler, /*DMA1_Channel4_5_IRQHandler*/
    Unassigned_Handler, /*ADC_COMP_IRQHandler*/
    Unassigned_Handler, /*TIM1_BRK_UP_TRG_COM_IRQHandler*/
    Unassigned_Handler, /*TIM1_CC_IRQHandler*/
    Unassigned_Handler, /*0*/
    Unassigned_Handler, /*TIM3_IRQHandler*/
    Unassigned_Handler, /*TIM6_IRQHandler*/
    Unassigned_Handler, /*0*/
    Unassigned_Handler, /*TIM14_IRQHandler*/
    Unassigned_Handler, /*TIM15_IRQHandler*/
    Unassigned_Handler, /*TIM16_IRQHandler*/
    Unassigned_Handler, /*TIM17_IRQHandler*/
    Unassigned_Handler, /*I2C1_IRQHandler*/
    Unassigned_Handler, /*I2C2_IRQHandler*/
    Unassigned_Handler, /*SPI1_IRQHandler*/
    Unassigned_Handler, /*SPI2_IRQHandler*/
    Unassigned_Handler, /*USART1_IRQHandler*/
    Unassigned_Handler, /*USART2_IRQHandler*/
    Unassigned_Handler, /*0*/
    Unassigned_Handler, /*0*/
    Unassigned_Handler, /*0*/

};

void ISR() {
  isrHandlers[getVectNumber() - STM32_HANDLERS_OFFSET]();
}

void registerHandler(IRQn_Type irqn, std::function<void()> &&f) {
  isrHandlers[irqn] = f;
}
#endif

#define WEAK_FUNC(name) extern void name (void) __attribute__ ((weak, noreturn, nothrow, alias ("Unassigned_Handler")));
WEAK_FUNC(NMI_Handler)
WEAK_FUNC(HardFault_Handler)
WEAK_FUNC(MemManage_Handler)
WEAK_FUNC(BusFault_Handler)
WEAK_FUNC(UsageFault_Handler)
WEAK_FUNC(SVC_Handler)
WEAK_FUNC(DebugMon_Handler)
WEAK_FUNC(PendSV_Handler)
WEAK_FUNC(SysTick_Handler)

/*
 * ISR vectors.
 */
void (*isr_vector[])(void) __attribute__ ((used, section (".isr_vector"))) = {

    _estack, /* not a funtion */
    Reset_Handler,                                  // 0x0004
    NMI_Handler,                                    // 0x0008
    HardFault_Handler,                              // 0x000C
    0,  /* all reserved */                          // 0x0010
    0,                                              // 0x0014
    0,                                              // 0x0018
    0,                                              // 0x001C
    0,                                              // 0x0020
    0,                                              // 0x0024
    0,                                              // 0x0028
    SVC_Handler,                                    // 0x002C
    0,  /* reserved */                              // 0x0030
    0,                                              // 0x0034
    PendSV_Handler,                                 // 0x0038
    SysTick_Handler,                                // 0x003C
    /* STM32 handlers */
    ISR, /*WWDG_IRQHandler*/                        // 0x0040
    ISR, /*0*/                                      // 0x0044
    ISR, /*RTC_IRQHandler*/                         // 0x0048
    ISR, /*FLASH_IRQHandler*/                       // 0x004C
    ISR, /*RCC_CRS_IRQHandler*/                     // 0x0050
    ISR, /*EXTI0_1_IRQHandler*/                     // 0x0054
    ISR, /*EXTI2_3_IRQHandler*/                     // 0x0058
    ISR, /*EXTI4_15_IRQHandler*/                    // 0x005C
    ISR, /*0*/                                      // 0x0060
    ISR, /*DMA1_Channel1_IRQHandler*/               // 0x0064
    ISR, /*DMA1_Channel2_3_IRQHandler*/             // 0x0068
    ISR, /*DMA1_Channel4_5_IRQHandler*/             // 0x006C
    ISR, /*ADC_COMP_IRQHandler*/                    // 0x0070
    ISR, /*TIM1_BRK_UP_TRG_COM_IRQHandler*/         // 0x0074
    ISR, /*TIM1_CC_IRQHandler*/                     // 0x0078
    ISR, /*0*/                                      // 0x007C
    ISR, /*TIM3_IRQHandler*/                        // 0x0080
    ISR, /*TIM6_IRQHandler*/                        // 0x0084
    ISR, /*0*/                                      // 0x0088
    ISR, /*TIM14_IRQHandler*/                       // 0x008C
    ISR, /*TIM15_IRQHandler*/                       // 0x0090
    ISR, /*TIM16_IRQHandler*/                       // 0x0094
    ISR, /*TIM17_IRQHandler*/                       // 0x0098
    ISR, /*I2C1_IRQHandler*/                        // 0x009C
    ISR, /*I2C2_IRQHandler*/                        // 0x00A0
    ISR, /*SPI1_IRQHandler*/                        // 0x00A4
    ISR, /*SPI2_IRQHandler*/                        // 0x00A8
    ISR, /*USART1_IRQHandler*/                      // 0x00AC
    ISR, /*USART2_IRQHandler*/                      // 0x00B0
    ISR, /*0*/                                      // 0x00B4
    ISR, /*0*/                                      // 0x00B8
    ISR, /*0*/                                      // 0x00BC
};
