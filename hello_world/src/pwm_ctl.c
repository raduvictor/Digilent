#include "pwm_ctl.h"

#define DIVIDER_REG_OFFSET 0x4
#define DUTY_REG_OFFSET 0x8

void Pwm_SetDivider(uint32_t BaseAddress, uint8_t divider)
{
	*(uint32_t*)(BaseAddress + DIVIDER_REG_OFFSET) = divider;

}

void Pwm_SetDuty(uint32_t BaseAddress, uint8_t duty)
{
	*(uint32_t*)(BaseAddress + DUTY_REG_OFFSET) = duty;

}
