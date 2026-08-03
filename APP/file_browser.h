#ifndef __FILE_BROWSER_H
#define __FILE_BROWSER_H

#include "stm32f10x.h"
#include "fatfs.h"
#include "st7789.h"
#include <string.h>

#define MAX_FILES_TO_LOAD   50    
// <-- Đã sửa: Tăng từ 10 lên 14 dòng vì màn hình 320px cao hơn
#define MAX_LINES_PER_PAGE  14    

#define KEY_UP      'w'
#define KEY_DOWN    's'
#define KEY_ENTER   'e'
#define KEY_BACK    'q'

typedef enum {
    UI_REFRESH_FULL,     
    UI_REFRESH_CURSOR    
} UI_Refresh_Mode_t;

// Biến toàn cục để main.c lấy được tên file
extern char selected_gcode_file[13];
extern uint8_t flag_file_selected;

void Browser_Init(void);
void Browser_ScanFiles(void);
void Browser_DrawUI(UI_Refresh_Mode_t mode);
void Browser_ProcessInput(char key);

#endif