#ifndef __ADC_H__
#define __ADC_H__

#include <stdio.h>
#include "common.h"

typedef struct AdcReg AdcReg;
struct AdcReg {
	IoRegister SR;					//0x00	Status Register
	IoRegister CR1;					//0x04	Control Register 1
	IoRegister CR2;		    		//0x08	Control Register 2
	IoRegister SMPR1;				//0x0C	Sample Time Register 1
	IoRegister SMPR2;				//0x10	Sample Time Register 2
	IoRegister JOFR1;				//0x14	Injected Channel Data Offset Register 1
	IoRegister JOFR2;				//0x18	Injected Channel Data Offset Register 1
	IoRegister JOFR3;				//0x1C	Injected Channel Data Offset Register 3
	IoRegister JOFR4;				//0x20	Injected Channel Data Offset Register 4
	IoRegister HTR;					//0x24	Watchdog Higher Threshold Register
	IoRegister LTR;					//0x28	Watchdog Lower Threshold Register
	IoRegister SQR1;				//0x2C	Regular Sequence Register 1
	IoRegister SQR2;				//0x30	Regular Sequence Register 2
	IoRegister SQR3;				//0x34	Regular Sequence Register 3
	IoRegister JSQR;				//0x38	Injected Sequence Register
	IoRegister JDR1;				//0x3C	Injected Data Register 1
	IoRegister JDR2;				//0x40	Injected Data Register 2
	IoRegister JDR3;				//0x44	Injected Data Register 3
	IoRegister JDR4;				//0x48	Injected Data Register 4
	IoRegister DR;					//0x4C	Regular Data Register
};

typedef struct AdcCommonReg AdcCommonReg;
struct AdcCommonReg {
	IoRegister CSR;					//0x00	Common Status Register
	IoRegister CCR;					//0x04	Common Control Register
	IoRegister CDR;					//0x08	Common Data Register
};

#define adc1		((AdcReg *)0x40012000)
#define adc2		((AdcReg *)0x40012100)
#define adc3		((AdcReg *)0x40012200)
#define commonAdc 	((AdcCommonReg *)0x40012300)

//Status Register
#define ADC_OVR		(1 << 5)
#define ADC_STRT	(1 << 4)
#define ADC_JSTRT	(1 << 3)
#define ADC_JEOC	(1 << 2)
#define ADC_EOC		(1 << 1)
#define ADC_AWD		(1 << 0)

//Overrun Interrupt Enable
#define ADC_OVERRUN_INT_DISABLE 	(0ULL << 26)
#define ADC_OVERRUN_INT_ENABLE 		(1ULL << 26)

//Resolution
#define ADC_RESO_12_BIT				(0ULL << 24)
#define ADC_RESO_10_BIT				(1ULL << 24)
#define ADC_RESO_8_BIT				(2ULL << 24)
#define ADC_RESO_6_BIT				(3ULL << 24)

//Regular Channel Analog Watchdog Enable
#define ADC_REG_ANALOG_WD_DISABLE	(0ULL << 23)
#define ADC_REG_ANALOG_WD_ENABLE	(1ULL << 23)


//Injected Channel Analog Watchdog Enable
#define ADC_INJ_ANALOG_WD_DISABLE	(0ULL << 22)
#define ADC_INJ_ANALOG_WD_ENABLE	(1ULL << 22)

//Discont. Mode Channel Counter
#define ADC_DISC_1_CHANNEL			(0ULL << 13)
#define ADC_DISC_2_CHANNEL			(1ULL << 13)
#define ADC_DISC_3_CHANNEL			(2ULL << 13)
#define ADC_DISC_4_CHANNEL			(3ULL << 13)
#define ADC_DISC_5_CHANNEL			(4ULL << 13)
#define ADC_DISC_6_CHANNEL			(5ULL << 13)
#define ADC_DISC_7_CHANNEL			(6ULL << 13)
#define ADC_DISC_8_CHANNEL			(7ULL << 13)

//Discont. Mode on Injected Enable
#define ADC_INJ_DISC_DISABLE		(0ULL << 12)
#define ADC_INJ_DISC_ENABLE			(1ULL << 12)

//Discont. Mode on Regular Enable
#define ADC_REG_DISC_DISABLE		(0ULL << 11)
#define ADC_REG_DISC_ENABLE			(1ULL << 11)

//Automatic Injected Group Conversion
#define ADC_INJ_AUTO_DISABLE		(0ULL << 10)
#define ADC_INJ_AUTO_ENABLE			(1ULL << 10)

//Watchdog on a Single Channel in Scan Mode
#define ADC_WD_ALL_CHANNEL			(0ULL << 9)
#define ADC_WD_SINGLE_CHANNEL		(1ULL << 9)

//Scan Mode
#define ADC_SCAN_MODE_DISABLE		(0ULL << 8)
#define ADC_SCAN_MODE_ENABLE		(1ULL << 8)

//Interrupt for Injected Channel Enable
#define ADC_INJ_INT_DISABLE			(0ULL << 7)
#define ADC_INJ_INT_ENABLE			(1ULL << 7)

//Analog Watchdog Interrupt Enable
#define ADC_WD_INT_DISABLE			(0ULL << 6)
#define ADC_WD_INT_ENABLE			(1ULL << 6)

//End of Conversion Interrupt Enable
#define ADC_EOC_INT_DISABLE			(0ULL << 5)
#define ADC_EOC_INT_ENABLE			(1ULL << 5)

//Analog Watchdog Channel Select
#define ADC_ANALOG_INPUT_CHANNEL0	0
#define ADC_ANALOG_INPUT_CHANNEL1	1
#define ADC_ANALOG_INPUT_CHANNEL2	2
#define ADC_ANALOG_INPUT_CHANNEL3	3
#define ADC_ANALOG_INPUT_CHANNEL4	4
#define ADC_ANALOG_INPUT_CHANNEL5	5
#define ADC_ANALOG_INPUT_CHANNEL6	6
#define ADC_ANALOG_INPUT_CHANNEL7	7
#define ADC_ANALOG_INPUT_CHANNEL8	8
#define ADC_ANALOG_INPUT_CHANNEL9	9
#define ADC_ANALOG_INPUT_CHANNEL10	10
#define ADC_ANALOG_INPUT_CHANNEL11	11
#define ADC_ANALOG_INPUT_CHANNEL12	12
#define ADC_ANALOG_INPUT_CHANNEL13	13
#define ADC_ANALOG_INPUT_CHANNEL14	14
#define ADC_ANALOG_INPUT_CHANNEL15	15
#define ADC_ANALOG_INPUT_CHANNEL16	16
#define ADC_ANALOG_INPUT_CHANNEL17	17
#define ADC_ANALOG_INPUT_CHANNEL18	18

//Start Conversion of Regular Channels
#define ADC_REGULAR_START_CONV		(1ULL << 62)

//External Trigger Enable for Reg Chnl
#define ADC_REG_TRIG_DISABLE			(0ULL << 60)
#define ADC_REG_TRIG_RISE_EDGE			(1ULL << 60)
#define ADC_REG_TRIG_FALL_EDGE			(2ULL << 60)
#define ADC_REG_TRIG_BOTH_EDGES			(3ULL << 60)

//External Event Select for Reg Chnl
#define ADC_REG_TIM1_CC1_EVENT				(0ULL << 56)
#define ADC_REG_TIM1_CC2_EVENT				(1ULL << 56)
#define ADC_REG_TIM1_CC3_EVENT				(2ULL << 56)
#define ADC_REG_TIM2_CC2_EVENT				(3ULL << 56)
#define ADC_REG_TIM2_CC3_EVENT				(4ULL << 56)
#define ADC_REG_TIM2_CC4_EVENT				(5ULL << 56)
#define ADC_REG_TIM2_TRGO_EVENT				(6ULL << 56)
#define ADC_REG_TIM3_CC1_EVENT				(7ULL << 56)
#define ADC_REG_TIM3_TRGO_EVENT				(8ULL << 56)
#define ADC_REG_TIM4_CC4_EVENT				(9ULL << 56)
#define ADC_REG_TIM5_CC1_EVENT				(10ULL << 56)
#define ADC_REG_TIM5_CC2_EVENT				(11ULL << 56)
#define ADC_REG_TIM5_CC3_EVENT				(12ULL << 56)
#define ADC_REG_TIM8_CC1_EVENT				(13ULL << 56)
#define ADC_REG_TIM8_TRGO_EVENT				(14ULL << 56)
#define ADC_REG_EXTI_LINE11_EVENT			(15ULL << 56)

//Start Conversion of Injected Channels
#define ADC_INJECTED_START_CONV			(1ULL << 54)

//External Trigger Enable for Inj Chnl
#define ADC_INJ_TRIG_DISABLE			(0ULL << 52)
#define ADC_INJ_TRIG_RISE_EDGE			(1ULL << 52)
#define ADC_INJ_TRIG_FALL_EDGE			(2ULL << 52)
#define ADC_INJ_TRIG_BOTH_EDGES			(3ULL << 52)

//External Event Select for Inj Chnl
#define ADC_INJ_TIM1_CC4_EVENT				(0ULL << 48)
#define ADC_INJ_TIM1_TRGO_EVENT				(1ULL << 48)
#define ADC_INJ_TIM2_CC1_EVENT				(2ULL << 48)
#define ADC_INJ_TIM2_TRGO_EVENT				(3ULL << 48)
#define ADC_INJ_TIM3_CC2_EVENT				(4ULL << 48)
#define ADC_INJ_TIM3_CC4_EVENT				(5ULL << 48)
#define ADC_INJ_TIM4_CC1_EVENT				(6ULL << 48)
#define ADC_INJ_TIM4_CC2_EVENT				(7ULL << 48)
#define ADC_INJ_TIM4_CC3_EVENT				(8ULL << 48)
#define ADC_INJ_TIM4_TRGO_EVENT				(9ULL << 48)
#define ADC_INJ_TIM5_CC4_EVENT				(10ULL << 48)
#define ADC_INJ_TIM5_TRGO_EVENT				(11ULL << 48)
#define ADC_INJ_TIM8_CC2_EVENT				(12ULL << 48)
#define ADC_INJ_TIM8_CC3_EVENT				(13ULL << 48)
#define ADC_INJ_TIM8_CC4_EVENT				(14ULL << 48)
#define ADC_INJ_EXTI_LINE15_EVENT			(15ULL << 48)

//Data Alignment
#define ADC_RIGHT_ALIGNMENT				(0ULL << 43)
#define ADC_LEFT_ALIGNMENT				(1ULL << 43)

//End of Conversion Selection
#define ADC_EACH_SEQ_EOC				(0ULL << 42)
#define ADC_EACH_CONV_EOC				(1ULL << 42)

//DMA Disable Selection
#define ADC_DMA_NO_NEW_REQUEST			(0ULL << 41)
#define ADC_DMA_NEW_REQUEST				(1ULL << 41)

//DMA Mode Enable
#define ADC_DMA_MODE_DISABLE			(0ULL << 40)
#define ADC_DMA_MODE_ENABLE				(1ULL << 40)

//Continuous Conversion Selection
#define ADC_SINGLE_CONVERSION			(0ULL << 33)
#define ADC_CONTINUOUS_CONVERSION       (1ULL << 33)

//ADC On/Off
#define ADC_OFF							(0ULL << 32)
#define ADC_ON							(1ULL << 32)

//Sample Time (Cycles)
#define ADC_3_CYCLES					0
#define ADC_15_CYCLES					1
#define ADC_28_CYCLES					2
#define ADC_56_CYCLES					3
#define ADC_84_CYCLES					4
#define ADC_112_CYCLES					5
#define ADC_144_CYCLES					6
#define ADC_480_CYCLES					7

//Temperature Sensor Enable
#define ADC_TEMP_SENSOR			(1 << 23)

//Battery Sensor Enable
#define ADC_BATT_SENSOR		(1 << 22)

//ADC Prescaler
#define ADC_PRESCALER_BY_2		0
#define ADC_PRESCALER_BY_4		1
#define ADC_PRESCALER_BY_6		2
#define ADC_PRESCALER_BY_8		3

//MACROS
#define ADC_ENABLE(adc)					(adc)->CR2 |= ADC_ON
#define ADC_DISABLE(adc)				(adc)->CR2 &= ~(ADC_ON)

#define ADC_START_CONVERSION(adc)										\
					do {												\
						ADC_CLEAR_STATUS(adc, ADC_STRT);				\
						(adc)->CR2 |= (1 << 30);						\
					}while(0)

#define ADC_GET_STATUS(adc, flag)			(adc)->SR & (flag)
#define ADC_CLEAR_STATUS(adc, flag)			(adc)->SR &= ~(flag)
#define ADC_CLEAR_ALL_FLAGS(adc)			ADC_CLEAR_STATUS(adc,ADC_OVR  | \
																ADC_STRT  | \
																ADC_JSTRT | \
																ADC_JEOC  | \
																ADC_EOC   | \
																ADC_AWD)

#define ADC_HAS_CONVERSION_ENDED(adc)		ADC_GET_STATUS(adc, ADC_EOC)
#define ADC_IS_ADC_OVERRUN(adc)				ADC_GET_STATUS(adc, ADC_OVR)


#define ADC_TEMP_SENSOR_DISABLE()		(commonAdc)->CCR &= ~(ADC_TEMP_SENSOR)
#define ADC_TEMP_SENSOR_ENABLE()		(commonAdc)->CCR |= ADC_TEMP_SENSOR
#define ADC_BATT_SENSOR_DISABLE()		(commonAdc)->CCR &= ~(ADC_BATT_SENSOR)
#define ADC_BATT_SENSOR_ENABLE()		(commonAdc)->CCR |= ADC_BATT_SENSOR
#define ADC_SET_PRESCALER(num)												\
	do {																	\
		(commonAdc)->CCR &= ~(0xff << 16);									\
		(commonAdc)->CCR |= (num << 16);									\
	}while(0)

void adcSetChannelSamplingSequence(AdcReg *adc, int channels[]);
void adcChannelSamplingTime(AdcReg *adc, int channel, int cycles);
void adcConfigure(AdcReg *adc, long long mode);
uint16_t adcReadValue(AdcReg *adc);
int adcReadCommonValue();
#endif //__ADC_H__
