/* stm32 for cnc mini control */

A0 - X_STEP
A1 - Y_STEP
A2 - Z_STEP

A3 - X_DIR
A4 - y_DIR
A5 - z_DIR

B10 - X_LIMIT
B11 - Y_LIMIT
B12 - Z_LIMIT

A9 (stm32_1) - A10 (stm32_2)
A10 (stm32_1) - A9 (stm32_2)


/* stm32 for display lcd and read sd card */

// LCD st7789

B12 - CS
A8 - DC
A11 - RTS
B15 - SDA
B13 - SCL
VCC - 3.3v

// SD CARD

VCC - 5v
A6 - MISO
A7 - MOSI
A5 - SCK
A4 - CS

// button


BTN_PORT            GPIOB
BTN_PAUSE_PIN       GPIO_Pin_1   // <-- Nút Tạm Dừng / 
BTN_Y_PLUS_PIN      GPIO_Pin_5   // Nút Lên / Y+ ('w')
BTN_Y_MINUS_PIN     GPIO_Pin_6   // Nút Xuống / Y- 
BTN_X_MINUS_PIN     GPIO_Pin_7   // Nút Trái / X- ('a')
BTN_X_PLUS_PIN      GPIO_Pin_8   // Nút Phải / X+ ('d')
BTN_Z_PLUS_PIN      GPIO_Pin_9   // Nút Z Lên ('i')
BTN_Z_MINUS_PIN     GPIO_Pin_10  // Nút Z Xuống ('k')
BTN_ENTER_PIN       GPIO_Pin_11 