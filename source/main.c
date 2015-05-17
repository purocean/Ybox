/**
 * 用单片机制作游戏机
 * 洋子
 * purocean@gmail.com
 * 2015年5月8日17:53:05
 */

#include <reg51.h>
#include "inc/event/event.h"
#include "inc/timer/timer.h"
#include "inc/lcd/nokia_5110.h"
#include "menu/menu.h"
#include "about/about.h"
#include "racing/racing.h"

/**
 * 菜单 ID
 * 100-199 分配给主菜单，一级子项为 1x0， 二级 1xy
 * 200-299 分配给赛车游戏
**/
unsigned int Menu_id;

// 初始化工作
void init(void);

void main(void){
    init();

    for(;;){
        // 扫描按键
        event_scan_key();


        if(200 <= Menu_id && Menu_id < 300){
            racing();
        }else if(100 <= Menu_id && Menu_id < 200){
            menu();
        }else if(900 <= Menu_id && Menu_id < 1000){
            about();
        }

        LCD_draw_int_6x8(42, 0,P2);
        LCD_draw_int_6x8(0, 0, Menu_id);
    }
}

void init(void){
    timer_init();
    LCD_init();
    LCD_clear();
    menu_init();
}
