#include "button.h"

static void Button_Delay(void) {
    for (volatile uint32_t i = 0; i < 20000; i++);
}

void Button_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Cấu hình 8 chân nút bấm là Input Pull-Up
    GPIO_InitStructure.GPIO_Pin = BTN_PAUSE_PIN | BTN_Y_PLUS_PIN | BTN_Y_MINUS_PIN | BTN_X_MINUS_PIN |
                                  BTN_X_PLUS_PIN | BTN_Z_PLUS_PIN | BTN_Z_MINUS_PIN | BTN_ENTER_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    GPIO_Init(BTN_PORT, &GPIO_InitStructure);
}

// 1. Quét phím Bấm - Nhả
char Button_Scan_Single(void) {
    static uint8_t prev_w=1, prev_s=1, prev_a=1, prev_d=1, prev_i=1, prev_k=1, prev_e=1;
    uint8_t curr;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_Y_PLUS_PIN);
    if(curr == 0 && prev_w == 1) { Button_Delay(); prev_w = 0; return 'w'; }
    else if (curr == 1) prev_w = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_Y_MINUS_PIN);
    if(curr == 0 && prev_s == 1) { Button_Delay(); prev_s = 0; return 's'; }
    else if (curr == 1) prev_s = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_X_MINUS_PIN);
    if(curr == 0 && prev_a == 1) { Button_Delay(); prev_a = 0; return 'a'; }
    else if (curr == 1) prev_a = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_X_PLUS_PIN);
    if(curr == 0 && prev_d == 1) { Button_Delay(); prev_d = 0; return 'd'; }
    else if (curr == 1) prev_d = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_Z_PLUS_PIN);
    if(curr == 0 && prev_i == 1) { Button_Delay(); prev_i = 0; return 'i'; }
    else if (curr == 1) prev_i = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_Z_MINUS_PIN);
    if(curr == 0 && prev_k == 1) { Button_Delay(); prev_k = 0; return 'k'; }
    else if (curr == 1) prev_k = 1;

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_ENTER_PIN);
    if(curr == 0 && prev_e == 1) { Button_Delay(); prev_e = 0; return 'e'; }
    else if (curr == 1) prev_e = 1;

    return 0; 
}

// 2. Quét phím Nhấn Giữ 
char Button_Scan_Continuous(void) {
    static uint8_t prev_e = 1;
    uint8_t curr;

    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_Y_PLUS_PIN) == 0)  return 'w';
    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_Y_MINUS_PIN) == 0) return 's';
    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_X_MINUS_PIN) == 0) return 'a';
    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_X_PLUS_PIN) == 0)  return 'd';
    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_Z_PLUS_PIN) == 0)  return 'i';
    if(GPIO_ReadInputDataBit(BTN_PORT, BTN_Z_MINUS_PIN) == 0) return 'k';

    curr = GPIO_ReadInputDataBit(BTN_PORT, BTN_ENTER_PIN);
    if(curr == 0 && prev_e == 1) { Button_Delay(); prev_e = 0; return 'e'; }
    else if (curr == 1) prev_e = 1;

    return 0;
}