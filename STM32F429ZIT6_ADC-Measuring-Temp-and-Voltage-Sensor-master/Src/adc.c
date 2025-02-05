#include "adc.h"
#include "common.h"
#include <stdio.h>


void adcSetChannelSamplingSequence(AdcReg *adc, int channels[]) {
	int i = 0, temp = 0;
	IoRegister *adcReg = &((adc)->SQR3);

	while (channels[i] != -1) {

		if(i == 6) {
			adcReg--;
			temp = i - 6;
		}

		if(i == 12) {
			adcReg--;
			temp = i - 12;
		}

		if(i > 15) {
			adc->SQR1 |= (16 << 20);
			return;
		}

		if(channels[i] > 18)
			*(adcReg) |= (18 << temp * 5);
		else if(channels[i] < 0)
			*(adcReg) |= (0 << temp * 5);
		else if(channels[i] <= 18 && channels[i] >= 0)
				*(adcReg) |= (channels[i] << temp * 5);

		i++;
		temp++;
	}

	adc->SQR1 |= (i << 20);
}


void adcChannelSamplingTime(AdcReg *adc, int channel, int cycles) {
	IoRegister *adcReg = &((adc)->SMPR2);

	if(channel > 9) {
		adcReg--;
		channel -= 10;
	}

	if(channel > 9)
		return;

	if(channel >= 0)
		*(adcReg) |= cycles << channel * 3;
}


void adcConfigure(AdcReg *adc, long long mode) {
	adc->CR1 = (uint32_t)(mode & 0xffffffff);
	adc->CR2 = (uint32_t)((mode >> 32) & 0xffffffff);
}

uint16_t adcReadValue(AdcReg *adc) {
	return adc->DR;
}

int adcReadCommonValue() {
	return commonAdc->CDR;
}
