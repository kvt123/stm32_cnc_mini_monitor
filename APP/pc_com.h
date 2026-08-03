#ifndef __PC_COM_H
#define __PC_COM_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

// --- NGUYÊN MẪU HÀM ---
void PC_COM_Init(uint32_t baudrate);
char PC_COM_ReceiveByte_NonBlocking(void);

#endif