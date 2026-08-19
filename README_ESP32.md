///////////////////////////////////////////////////////////////
/* stm32 for cnc mini control */
///////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////
/* stm32 for display lcd and read sd card */
///////////////////////////////////////////////////////////////

// LCD st7789

B12 - CS
A8 - DC
A11 - RTS
B15 - SDA
B13 - SCL
VCC - 3.3v
GND chung

// SD CARD

VCC - 5v
GND chung

// 74HC157 (16 chaan)

VCC(3.3v) - pin 16
GND (chung) - pin 8

// 74HC125 (14 chaan)

VCC(3.3v) - pin 14
GND (chung) - pin 7
PIN2(miso sd input) - PIN5 (miso sd input)

// 74HC157 <-> stm32f103

PIN2 (CS) - A4
PIN5 (SCK) - A5
PIN11 (MOSI) - A7

// 74HC157 <-> 74HC125 <-> ESP32 C3

PIN1 (S- select) - PIN1 (1OE) - PIN2 (GPIO2)

// 74HC157 <-> ESP32 C3

PIN3 (1I1) - PIN7(CS)
PIN6 (2I1) - PIN4 (SCK)
PIN10 (3I1) - PIN6 (MOSI)

// 74HC157 <-> sd card

PIN4 (1Y) - CS
PIN7 (2Y) - SCK
PIN9 (3Y) - MOSI

// 74HC125 <-> ESP32 C3

PIN4 (2OE) - PIN3 (GPIO3)

// 74HC125 <-> stm32f103

PIN3 (OUTPUT) - A6 (MISO)

// 74HC125 <-> SD card
PIN1 - MISO



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

