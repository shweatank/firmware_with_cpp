#include "timer.h"
#include <stdio.h>

void timerInitOutputCompare(TimerRegs *timer, uint32_t channel,  uint32_t mode, uint32_t outPolarity, uint32_t compareValue) {
	//IoRegister *ccmrReg = &(timer->CCMR1);
	//int mask = 0xff;

	//if(channel >=)
	timerOcSetMode(timer, channel, mode);
	TIM_SET_OC_VALUE(timer, channel, compareValue);
	TIM_SET_OC_POLARITY(timer, channel, outPolarity);
}

void timerOcSetMode(TimerRegs *timer, uint32_t channel, uint32_t mode) {
	uint32_t numOfShifts = 0;
	IoRegister *ccmr = &timer->CCMR1;

	if(((channel - 1) & 1) == 1)
		numOfShifts = 8;

	if(channel > 2)
		ccmr++;

	*ccmr = mode << (numOfShifts + 4);
}
