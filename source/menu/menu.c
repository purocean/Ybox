/* 主菜单选项
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日22:00:19
 */

#include <reg51.h>
#include <string.h>
#include "../inc/event/event.h"
#include "../inc/lcd/nokia_5110.h"
#include "menu.h"
#include "menu_data.h"
#include "../about/about.h"
#include "../racing/racing.h"

void menu_init(void){
    Menu_id = 100;
    LCD_clear();
    menu_switch();
}

void menu_switch(void){
    unsigned char x = 0;
    unsigned char y = 5;
    unsigned int index = Menu_id / 10  - 10;
    unsigned char len = strlen(menu_text[index]);

    if(len <= 14){ // 屏幕一行最多显示 14 个字符
        x = (LCD_WIDTH - len * 6) / 2; // 居中显示
    }

    LCD_draw_pic(26, 1, 32, 32, menu_icon[index]);
    LCD_draw_string_ascil_6x8(0, y, "              "); // 绘制 14 个空格，防止上次文字的残留
    LCD_draw_string_ascil_6x8(x, y, menu_text[index]);
}

void menu_switch_loop(unsigned char is_left){
    unsigned char max_index = 100 + MENU_COUNT * 10 - 10;

    if(is_left){
        Menu_id = (Menu_id <= 100) ? max_index : Menu_id - 10;
    }else{
        Menu_id = (Menu_id >= max_index) ? 100 : Menu_id + 10;
    }

    menu_switch();
}

void menu(void){
    static bit key_flag = 1;

    if(KEY_LEFT){
        if(key_flag){
            key_flag = 0;
            menu_switch_loop(1);
        }
    }else if(KEY_RIGHT){
        if(key_flag){
            key_flag = 0;
            menu_switch_loop(0);
        }
    }else if(KEY_START){
        if(key_flag){
            key_flag = 0;
            switch(Menu_id){
                case 100:
                    racing_init();
                    return;
                    break;
                case 110:
                    about_init();
                    return;
                    break;
            }
        }
    }else if(KEY_EXIT){
        if(key_flag){
            menu_init();
            key_flag = 0;
            return;
        }
    }else{
        key_flag = 1;
    }
}
