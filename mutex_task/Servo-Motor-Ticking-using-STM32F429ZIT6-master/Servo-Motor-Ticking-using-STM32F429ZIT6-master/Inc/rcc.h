#ifndef __RCC_H__
#define __RCC_H__
#include <stdio.h>
#include "Common.h"

typedef struct RccRegs RccRegs;
struct RccRegs {
	IoRegister CR;						//0x00 Control Reg
	IoRegister PLLCFGR;					//0x04 PLL Config Reg
	IoRegister CFGR;				    //0x08 Clock Config Reg
	IoRegister CIR;						//0x0C Clock Interrupt Reg
	IoRegister AHB1RSTR;				//0x10 AHB1 Peripheral Reset Reg
	IoRegister AHB2RSTR;				//0x14 AHB2 Peripheral Reset Reg
	IoRegister AHB3RSTR;				//0x18 AHB3 Peripheral Reset Reg
	IoRegister Reserved0;				//0x1C Reserved
	IoRegister APB1RSTR;				//0x20 APB1 Peripheral Reset Reg
	IoRegister APB2RSTR;				//0x24 APB2 Peripheral Reset Reg
	IoRegister Reserved1[2];			//0x28 Reserved
	IoRegister AHB1ENR;					//0x30 AHB1 Peripheral Clock Reg
	IoRegister AHB2ENR;					//0x34 AHB2 Peripheral Clock Reg
	IoRegister AHB3ENR;					//0x38 AHB3 Peripheral Clock Reg
	IoRegister Reserved2;				//0x3C Reserved
	IoRegister APB1ENR;					//0x40 APB1 Peripheral Clock Reg
	IoRegister APB2ENR;					//0x44 APB2 Peripheral Clock Reg
	IoRegister Reserved3[2];			//0x48 Reserved
	IoRegister AHB1ELPENR;				//0x50 AHB1 Peripheral Low Power Clock Reg
	IoRegister AHB2ELPENR;				//0x54 AHB2 Peripheral Low Power Clock Reg
	IoRegister AHB3ELPENR;				//0x58 AHB3 Peripheral Low Power Clock Reg
	IoRegister Reserved4;				//0x5C Reserved
	IoRegister APB1ELPENR;				//0x60 APB1 Peripheral Low Power Clock Reg
	IoRegister APB2ELPENR;				//0x64 APB2 Peripheral Low Power Clock Reg
	IoRegister Reserved5[2];			//0x68 Reserved
	IoRegister BDCR;					//0x70 Backup Domain Con Reg
	IoRegister CSR;						//0x74 Clock Con & Status Reg
	IoRegister Reserved6[2];			//0x78 Reserved
	IoRegister SSCGR;					//0x80 Spread Spectrum Clock Gen Reg
	IoRegister PLL12SCFGR;				//0x84 PLLI2S Config Reg
};

#define rcc										((RccRegs *)0x40023800)

//MACROS
//DMA
#define ENABLE_DMA1_CLK_GATING()				rcc->AHB1ENR |= (1 << 21)

#define RESET_DMA1()							rcc->AHB1RSTR |= (1 << 21)

#define UNRESET_DMA1()							rcc->AHB1RSTR &= ~(1 << 21)

//TIMER
#define ENABLE_TIMER_3_CLK_GATING()				rcc->APB1ENR |= (1 << 1)

#define RESET_TIMER_3()							rcc->APB1RSTR |= (1 << 1)

#define UNRESET_TIMER_3()						rcc->APB1RSTR &= ~(1 << 1)

//GPIO
#define ENABLE_GPIOB_CLK_GATING()				rcc->AHB1ENR |= (1 << 1)

#define RESET_GPIOB()							rcc->AHB1RSTR |= (1 << 1)

#define UNRESET_GPIOB()							rcc->AHB1RSTR &= ~(1 << 1)

#endif //__RCC_H__
