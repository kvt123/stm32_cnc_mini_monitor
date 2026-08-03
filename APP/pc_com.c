#include "pc_com.h"

// --- KHỞI TẠO UART2 (PA2 = TX, PA3 = RX) ---
void PC_COM_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 1. Cấp xung nhịp cho USART2 (Nằm trên APB1) và GPIOA (Nằm trên APB2)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. Cấu hình chân PA2 (TX) - Alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. Cấu hình chân PA3 (RX) - Input floating
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 4. Cấu hình thông số USART2
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);


}

// --- HÀM ĐỌC UART KHÔNG CHẶN (NON-BLOCKING) ---
char PC_COM_ReceiveByte_NonBlocking(void)
{
    // Kiểm tra cờ RXNE (Receive Data Register Not Empty) của USART2
    if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
    {
        return (char)USART_ReceiveData(USART2);
    }
    return 0; // Trả về 0 nếu không có ký tự nào được gửi tới
}