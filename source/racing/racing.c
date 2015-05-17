/* 赛车游戏
 * 洋子
 * purocean@gmail.com
 * 2015年5月16日23:08:58
 */

#include <reg51.h>
#include "../inc/event/event.h"
#include "../inc/lcd/nokia_5110.h"
#include "../menu/menu.h"
#include "racing.h"
#include "racing_data.h"

void racing_init(void){
    Menu_id = 200;
    LCD_clear();
}

void racing(void){
    static bit key_flag = 1;

    if(KEY_LEFT){
        if(key_flag){
            key_flag = 0;
        }
    }else if(KEY_RIGHT){
        if(key_flag){
            key_flag = 0;
        }
    }else if(KEY_START){
        if(key_flag){
            key_flag = 0;
        }
    }else if(KEY_EXIT){
        if(key_flag){
            racing_exit();
            key_flag = 0;
            return;
        }
    }else{
        key_flag = 1;
    }

    racing_test();
}

void racing_test(void){
    static unsigned char i;

    ++i;

    LCD_draw_int_6x8(50,3,i);
}

void racing_exit(void){
    menu_init();
}
