#include "nvic_config.h"

#include "at32f435_437.h"

/**
 * @brief nvic configuration function
 * 
 */
void nvic_config(void)
{
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

    NVIC_SetPriority(MemoryManagement_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(BusFault_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(UsageFault_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(SVCall_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(DebugMonitor_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(PendSV_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
    NVIC_SetPriority(SysTick_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
}
