#include "grbl_com.h"

volatile uint8_t grbl_ok_received = 0;
volatile uint8_t grbl_error_received = 0; // <-- Cờ báo lỗi/Alarm

// --- KHỞI TẠO UART1 CÓ SỬ DỤNG NGẮT ---
void GRBL_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

// --- TRÌNH PHỤC VỤ NGẮT UART1 (BẮT TỪ KHÓA LỖI) ---
void USART1_IRQHandler(void)
{
    static char prev_char = 0;
    
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char curr_char = (char)USART_ReceiveData(USART1);
        
        // 1. Nhặt chữ "ok"
        if (prev_char == 'o' && curr_char == 'k')
        {
            grbl_ok_received = 1; 
        }
        // 2. Nhặt chữ "er" (Trong từ error:xx của GRBL)
        else if (prev_char == 'e' && curr_char == 'r')
        {
            grbl_error_received = 1;
        }
        // 3. Nhặt chữ "AL" (Trong từ ALARM:xx của GRBL)
        else if (prev_char == 'A' && curr_char == 'L')
        {
            grbl_error_received = 1;
        }

        prev_char = curr_char;
    }
    
    if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
    {
        USART_ReceiveData(USART1);
    }
}


void GRBL_SendChar(char c)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void GRBL_SendString(const char* str)
{
    while (*str)
    {
        GRBL_SendChar(*str++);
    }
}

// --- HÀM CHỜ PHẢN HỒI ---
// Trả về: 1 (OK), 2 (LỖI HOẶC ALARM)
uint8_t GRBL_WaitForOK(void)
{
    uint8_t is_paused = 0;
    uint8_t pending_ok = 0;
    uint8_t pause_btn_state = 1; 
    uint32_t debounce_counter = 0;

    grbl_ok_received = 0; 
    grbl_error_received = 0; 

    while (1)
    {
        // <-- THÊM MỚI: Bắt tín hiệu LỖI / ALARM từ ngắt
        if (grbl_error_received == 1)
        {
            grbl_error_received = 0;
            return 2; // Trả về 2 báo hiệu có lỗi chết người
        }

        // KIỂM TRA CỜ "OK" TỪ NGẮT
        if (grbl_ok_received == 1)
        {
            grbl_ok_received = 0; 
            
            if (is_paused == 1) {
                pending_ok = 1; 
            } else {
                return 1; // Thành công
            }
        }

        // QUÉT NÚT PAUSE 
        if (debounce_counter > 0) {
            debounce_counter--; 
        }
        else 
        {
            uint8_t curr_btn = GPIO_ReadInputDataBit(BTN_PORT, BTN_PAUSE_PIN);
            
            if (curr_btn == 0 && pause_btn_state == 1)
            {
                pause_btn_state = 0;
                debounce_counter = 100000; 
                
                if (is_paused == 0)
                {
                    GRBL_SendChar('!'); 
                    is_paused = 1;
                    // <-- Đã căn chỉnh chữ PAUSED xuống góc dưới màn hình (Y=240) 
                    // để không đè lên Progress Bar ở Y=140
                    ST7789_DrawFilledRectangle(0, 240, ST7789_WIDTH, 30, BLUE);
                    ST7789_WriteString(40, 242, "* PAUSED *", Font_16x26, YELLOW, BLUE);
                }
                else
                {
                    GRBL_SendChar('~'); 
                    is_paused = 0;
                    // Xóa hoàn toàn dòng chữ PAUSED bằng màu nền
                    ST7789_DrawFilledRectangle(0, 240, ST7789_WIDTH, 30, BLUE);
                    
                    if (pending_ok) return 1; 
                }
            }
            else if (curr_btn == 1) 
            {
                pause_btn_state = 1;
            }
        }
    }
}