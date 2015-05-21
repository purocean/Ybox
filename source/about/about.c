/* 关于
 * 洋子
 * purocean@gmail.com
 * 2015年5月17日00:16:46
 */

#include <reg51.h>
#include "../inc/event/event.h"
#include "../inc/lcd/nokia_5110.h"
#include "about.h"
#include "about_data.h"
#include "../menu/menu.h"

void about_init(void){
    Func_id = ABOUT;
    LCD_clear();
}

void about(void){
    static bit key_flag = 1;

    if(KEY_EXIT){
        if(key_flag){
            key_flag = 0;

            menu_init();
            return;
        }
    }else{
        key_flag = 1;
    }

    LCD_draw_pic(18, 0, 48, 48, about_img);
}
