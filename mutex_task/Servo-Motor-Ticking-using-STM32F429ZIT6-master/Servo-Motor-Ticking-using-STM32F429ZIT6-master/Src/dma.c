#include "dma.h"

void dmaConfigureStream(DmaRegs *dma, int stream, int configuration) {
	dma->S[stream].CR &= ~(configuration);
	dma->S[stream].CR = configuration;
}

void dmaStreamConfigureTransfer(DmaRegs *dma, int stream, uint32_t source_addr, uint32_t dest_addr , uint16_t num_of_transfer) {
	dma->S[stream].NDTR &= 0;
	dma->S[stream].NDTR |= num_of_transfer;
	dma->S[stream].PAR &= 0;
	dma->S[stream].PAR |= dest_addr;
	dma->S[stream].M0AR &= 0;
	dma->S[stream].M0AR |= source_addr;
}
