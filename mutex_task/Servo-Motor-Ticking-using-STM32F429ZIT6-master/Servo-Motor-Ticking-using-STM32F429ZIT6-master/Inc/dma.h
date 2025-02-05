#ifndef __DMA_H__
#define __DMA_H__

#include "Common.h"

typedef struct DmaStreamRegs DmaStreamRegs;
struct DmaStreamRegs {
	IoRegister CR;
	IoRegister NDTR;
	IoRegister PAR;
	IoRegister M0AR;
	IoRegister M1AR;
	IoRegister FCR;
};

typedef struct DmaRegs DmaRegs;
struct DmaRegs {
	IoRegister LISR;
	IoRegister HISR;
	IoRegister LIFCR;
	IoRegister HIFCR;
	DmaStreamRegs S[8];
};

#define dma1 		((DmaRegs *) 0x40026000)

//Flags
#define DMA_TCIF			(1 << 5)	//Transfer Complete Flag
#define DMA_HTIF			(1 << 4)	//Half Transfer Flag
#define DMA_TEIF			(1 << 3)	//Transfer Error Flag
#define DMA_DMEIF			(1 << 2)	//Direct Mode Error Flag
#define DMA_FEIF			(1 << 0)	//FIFO error Flag

//Stream Selection
#define DMA_STRM0			0
#define DMA_STRM1			1
#define DMA_STRM2			2
#define DMA_STRM3			3
#define DMA_STRM4			4
#define DMA_STRM5			5
#define DMA_STRM6			6
#define DMA_STRM7			7

//Channel Selection
#define DMA_CHN_MASK		(7 << 25)	//Channels Mask
#define DMA_CHN0			(0 << 25)	//Channel 0 Selection (DEFAULT)
#define DMA_CHN1			(1 << 25)	//Channel 1 Selection
#define DMA_CHN2			(2 << 25)	//Channel 2 Selection
#define DMA_CHN3			(3 << 25)	//Channel 3 Selection
#define DMA_CHN4			(4 << 25)	//Channel 4 Selection
#define DMA_CHN5			(5 << 25)	//Channel 5 Selection
#define DMA_CHN6			(6 << 25)	//Channel 6 Selection
#define DMA_CHN7			(7 << 25)	//Channel 7 Selection

//Memory Transfer Burst Size
#define DMA_MBURST_MASK			(3 << 23)	//Memory Burst Mask
#define DMA_MBURST_NO_INC		(0 << 23)	//Single Memory Burst
#define DMA_MBURST_INC_BY_4		(1 << 23)	//Memory Burst of 4
#define DMA_MBURST_INC_BY_8		(2 << 23)	//Memory Burst of 8
#define DMA_MBURST_INC_BY_16	(3 << 23)	//Memory Burst of 16

//Peripheral Transfer Burst Size
#define DMA_PBURST_MASK			(3 << 21)	//Peripheral Burst Mask
#define DMA_PBURST_NO_INC		(0 << 21)	//Single Peripheral Burst
#define DMA_PBURST_INC_BY_4		(1 << 21)	//Peripheral Burst of 4
#define DMA_PBURST_INC_BY_8		(2 << 21)	//Peripheral Burst of 8
#define DMA_PBURST_INC_BY_16	(3 << 21)	//Peripheral Burst of 16

//Memory Buffer Current Target
#define DMA_CURRENT_TARGET_MASK (1 << 19) 	//Current Target Mask
#define DMA_CURRENT_TARGET_MEM0	(0 << 19)	//Current Target is Memory 0
#define DMA_CURRENT_TARGET_MEM1 (1 << 19)	//Current Target is Memory 1

//Double Buffer
#define DMA_DBM_MASK		(1 << 18) 	//Double Buffer Mode Mask
#define DMA_DBM_DIS			(0 << 18)	//Disable Double Buffer Mode
#define DMA_DBM_EN			(1 << 18)	//Enable Double Buffer Mode

//Priority Level
#define DMA_PRIOR_MASK		(3 << 16) 	//Channel Priority Mask
#define DMA_LOW_PRIOR		(0 << 16)	//Low Channel Priority
#define DMA_MED_PRIOR		(1 << 16)	//Medium Channel Priority
#define DMA_HIGH_PRIOR		(2 << 16)	//High Channel Priority
#define DMA_VHIGH_PRIOR		(3 << 16)	//Very High Channel Priority

//Peripheral Increment Offset Size
#define DMA_PINC_OFFSET_MASK			(1 << 15) 	//Peripheral Increment Offset Size Mask
#define DMA_PINC_PSIZE_OFFSET			(0 << 15)	//Peripheral Offset Increased By Peripheral Size
#define DMA_PINC_FIXED_OFFSET			(1 << 15)	//Peripheral Offset Increased By Fixed 4 Bytes

//Memory Data Size
#define DMA_MEM_DATA_SIZE_MASK	(3 << 13) 	//Memory Data Size Mask
#define DMA_MEM_DATA_SIZE_BYTE	(0 << 13)	//Memory 1 Byte Data Size
#define DMA_MEM_DATA_SIZE_HALF	(1 << 13)	//Memory Half Word Data Size
#define DMA_MEM_DATA_SIZE_WORD	(2 << 13)	//Memory Word Data Size

//Peripheral Data Size
#define DMA_PERI_DATA_SIZE_MASK	(3 << 11) 	//Peripheral Data Size Mask
#define DMA_PERI_DATA_SIZE_BYTE	(0 << 11)	//Peripheral 1 Byte Data Size
#define DMA_PERI_DATA_SIZE_HALF	(1 << 11)	//Peripheral Half Word Data Size
#define DMA_PERI_DATA_SIZE_WORD	(2 << 11)	//Peripheral Word Data Size

//Memory Increment Mode
#define DMA_MINC_MASK		(1 << 10) 		//Memory Increment Mode Mask
#define DMA_MINC_DIS		(0 << 10)		//Disable Memory Increment Mode
#define DMA_MINC_EN			(1 << 10)		//Enable Memory Increment Mode

//Peripheral Increment Mode
#define DMA_PINC_MASK		(1 << 9) 		//Peripheral Increment Mode Mask
#define DMA_PINC_DIS		(0 << 9)		//Disable Peripheral Increment Mode
#define DMA_PINC_EN			(1 << 9)		//Enable Peripheral Increment Mode

//Circular Mode
#define DMA_CIRC_MASK		(1 << 8) 		//Circular Mode Mask
#define DMA_CIRC_DIS   		(0 << 8)		//Disable Circular Mode
#define DMA_CIRC_EN     	(1 << 8)		//Enable Circular Mode

//Data Transfer Direction
#define DMA_DIR_MASK		(1 << 6) 		//Data Transfer Direction Mask
#define DMA_DIR_PERIMEM		(0 << 6)		//Peripheral to Memory
#define DMA_DIR_MEMPERI		(1 << 6)		//Memory to Peripheral
#define DMA_DIR_MEMMEM		(2 << 6)		//Memory to Memory

//Peripheral Flow Controller
#define DMA_FLOW_CON_MASK	(1 << 5) 		//Peripheral Flow Controller Mask
#define DMA_FLOW_CON		(0 << 5)		//DMA Flow Controller
#define DMA_PERI_FLOW_CON   (1 << 5)		//Peripheral Flow Controller

//Interrupts
#define DMA_TCIE			(1 << 4)
#define DMA_HTIE			(1 << 3)
#define DMA_TEIE			(1 << 2)
#define DMA_DMEIE			(1 << 1)

//Stream Enable
#define DMA_STREAM_DIS	0
#define DMA_STREAM_EN	1

#define DMA_ENABLE_STREAM(dma, stream)								\
					(dma)->S[stream].CR |= DMA_STREAM_EN;			\

#define DMA_DISABLE_STREAM(dma, stream)								\
					(dma)->S[stream].CR &= ~(DMA_STREAM_EN);		\

void dmaConfigureStream(DmaRegs *dma, int stream, int configuration);
void dmaStreamConfigureTransfer(DmaRegs *dma, int stream, uint32_t source_addr, uint32_t dest_addr , uint16_t num_of_transfer);

#endif //__DMA_H__
