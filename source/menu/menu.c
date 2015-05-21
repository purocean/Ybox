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
#include "../mine/mine.h"

enum FID Func_id = MENU;
unsigned char menu_id = MENU_COUNT - 1;

void menu_init(void){
    Func_id = MENU;
    LCD_clear();
    menu_switch();
}

void menu_switch(void){
    unsigned char x;
    unsigned char len = strlen(menu_text[menu_id]);

    x = len <= 14 ? (LCD_WIDTH - len * 6) / 2 : 0; // 屏幕一行最多显示 14 个字符, 居中显示

    LCD_draw_pic(26, 1, 32, 32, menu_icon[menu_id]);
    LCD_draw_string_ascil_6x8(0, 5, "              "); // 绘制 14 个空格，防止上次文字的残留
    LCD_draw_string_ascil_6x8(x, 5, menu_text[menu_id]);
}

void menu(void){
    static bit key_flag = 1;

    if(KEY_LEFT){
        if(key_flag){
            key_flag = 0;

            menu_id = (menu_id <= 0) ? MENU_COUNT - 1 : menu_id - 1;
            menu_switch();
        }
    }else if(KEY_RIGHT){
        if(key_flag){
            key_flag = 0;

            menu_id = (menu_id >= MENU_COUNT - 1) ?  0: menu_id + 1;
            menu_switch();
        }
    }else if(KEY_START){
        if(key_flag){
            key_flag = 0;
            switch(menu_id){
                case 1:
                    mine_init();
                    return;
                    break;
                case 0:
                    about_init();
                    return;
                    break;
            }
        }
    }else if(KEY_EXIT){
        key_flag = 0;

        menu_id = MENU_COUNT - 1;
        menu_switch();
    }else{
        key_flag = 1;
    }
}
