#include "file_browser.h"
#include "sdcard.h" 
#include <stdio.h>  

char file_list[MAX_FILES_TO_LOAD][13];
uint16_t total_files = 0;              
uint16_t cursor_pos = 0;
static uint16_t prev_cursor_pos = 0;   

// Hai biến này giao tiếp với file main.c
char selected_gcode_file[13] = "";
uint8_t flag_file_selected = 0; 

void Browser_ScanFiles(void)
{
    DIR dir;
    FILINFO fno;
    total_files = 0;
    cursor_pos = 0;
    prev_cursor_pos = 0;

    _mountSdcard(); // ÉP MOUNT THẺ (Sửa lỗi Open Dir Failed trước đây)

    if (f_opendir(&dir, "") == FR_OK) 
    {
        while (f_readdir(&dir, &fno) == FR_OK && fno.fname[0] != 0) 
        {
            if (!(fno.fattrib & AM_DIR) && !(fno.fattrib & AM_HID)) 
            {
                strncpy(file_list[total_files], fno.fname, 13);
                total_files++;
                if (total_files >= MAX_FILES_TO_LOAD) break; 
            }
        }
        f_closedir(&dir);
    }
}

static void Draw_ListItem(uint16_t index, uint8_t is_selected)
{
    if (index >= total_files) return;
    uint16_t page_start_index = (cursor_pos / MAX_LINES_PER_PAGE) * MAX_LINES_PER_PAGE;
    uint16_t screen_line = index - page_start_index;
    uint16_t y_pos = 25 + (screen_line * 20); 

    if (is_selected) 
    {
        ST7789_DrawFilledRectangle(0, y_pos, ST7789_WIDTH, 20, GRAY); 
        ST7789_WriteString(2, y_pos, ">", Font_11x18, YELLOW, GRAY);
        ST7789_WriteString(18, y_pos, file_list[index], Font_11x18, YELLOW, GRAY);
    } 
    else 
    {
        ST7789_DrawFilledRectangle(0, y_pos, ST7789_WIDTH, 20, BLACK);
        ST7789_WriteString(18, y_pos, file_list[index], Font_11x18, WHITE, BLACK);
    }
}

void Browser_DrawUI(UI_Refresh_Mode_t mode)
{
    if (mode == UI_REFRESH_CURSOR) 
    {
        Draw_ListItem(prev_cursor_pos, 0); 
        Draw_ListItem(cursor_pos, 1);      
        return;
    }

    ST7789_Fill_Color(BLACK); 
    ST7789_DrawFilledRectangle(0, 0, ST7789_WIDTH, 20, BLUE);
    ST7789_WriteString(5, 2, "CHON FILE GCODE", Font_11x18, WHITE, BLUE);
    ST7789_DrawLine(0, 21, ST7789_WIDTH, 21, YELLOW);

    if (total_files == 0) {
        ST7789_WriteString(10, 40, "No files found!", Font_11x18, RED, BLACK);
        return;
    }

    uint16_t start_index = (cursor_pos / MAX_LINES_PER_PAGE) * MAX_LINES_PER_PAGE;
    for (uint16_t i = 0; i < MAX_LINES_PER_PAGE; i++) 
    {
        uint16_t list_index = start_index + i;
        if (list_index >= total_files) break; 
        Draw_ListItem(list_index, (list_index == cursor_pos));
    }
}

void Browser_ProcessInput(char key)
{
    if (key == KEY_DOWN) {
        if (total_files > 0 && cursor_pos < total_files - 1) {
            prev_cursor_pos = cursor_pos;
            cursor_pos++;
            if ((cursor_pos / MAX_LINES_PER_PAGE) != (prev_cursor_pos / MAX_LINES_PER_PAGE)) {
                Browser_DrawUI(UI_REFRESH_FULL); 
            } else {
                Browser_DrawUI(UI_REFRESH_CURSOR); 
            }
        }
    }
    else if (key == KEY_UP) {
        if (total_files > 0 && cursor_pos > 0) {
            prev_cursor_pos = cursor_pos;
            cursor_pos--;
            if ((cursor_pos / MAX_LINES_PER_PAGE) != (prev_cursor_pos / MAX_LINES_PER_PAGE)) {
                Browser_DrawUI(UI_REFRESH_FULL); 
            } else {
                Browser_DrawUI(UI_REFRESH_CURSOR);
            }
        }
    }
    else if (key == KEY_ENTER) {
        if (total_files > 0) {
            // Khi nhấn Enter, copy tên file vào biến toàn cục và bật cờ báo hiệu cho main.c
            strncpy(selected_gcode_file, file_list[cursor_pos], 13);
            flag_file_selected = 1;
        }
    }
}

void Browser_Init(void)
{
    flag_file_selected = 0;
    Browser_ScanFiles();
    Browser_DrawUI(UI_REFRESH_FULL); 
}