#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

// --- MACRO DEFINE CHÂN NÚT BẤM (Đã chuyển sang PB5-PB11) ---
#define BTN_PORT            GPIOB
#define BTN_PAUSE_PIN       GPIO_Pin_1   // <-- Nút Tạm Dừng / Tiếp Tục
#define BTN_Y_PLUS_PIN      GPIO_Pin_5   // Nút Lên / Y+ ('w')
#define BTN_Y_MINUS_PIN     GPIO_Pin_6   // Nút Xuống / Y- ('s')
#define BTN_X_MINUS_PIN     GPIO_Pin_7   // Nút Trái / X- ('a')
#define BTN_X_PLUS_PIN      GPIO_Pin_8   // Nút Phải / X+ ('d')
#define BTN_Z_PLUS_PIN      GPIO_Pin_9   // Nút Z Lên ('i')
#define BTN_Z_MINUS_PIN     GPIO_Pin_10  // Nút Z Xuống ('k')
#define BTN_ENTER_PIN       GPIO_Pin_11  // Nút Chọn / Chốt Gốc ('e')

// --- NGUYÊN MẪU HÀM ---
void Button_Init(void);
char Button_Scan_Single(void);     // Dùng cho UI (Bấm nhả)
char Button_Scan_Continuous(void); // Dùng cho Jogging (Nhấn giữ)

#endif
