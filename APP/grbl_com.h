#ifndef __GRBL_COM_H
#define __GRBL_COM_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "button.h"
#include "st7789.h"

// --- NGUYÊN MẪU HÀM GIAO TIẾP GRBL ---
void GRBL_Init(uint32_t baudrate);
void GRBL_SendChar(char c);
void GRBL_SendString(const char* str);
uint8_t GRBL_WaitForOK(void);

// Biến toàn cục nhận cờ báo từ ngắt
extern volatile uint8_t grbl_ok_received;
extern volatile uint8_t grbl_error_received; // <-- Thêm biến cờ lỗi

#endif
