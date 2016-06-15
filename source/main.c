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
#include "mine/mine.h"

// 初始化工作
void init(void);

void main(void){
    init();

    //载入启动画面
    about();
    timer_delay_ms(1500);
    menu_init();

    for(;;){
        // 扫描按键
        event_scan_key();

        switch(Func_id){
            case 2:
                mine();
                break;
            case 1:
                about();
                break;
            default:
                menu();
        }

        // if(300 <= Menu_id && Menu_id < 400){
        //     mine();
        // }else if(200 <= Menu_id && Menu_id < 300){
        //     about();
        // }else if(100 <= Menu_id && Menu_id < 200){
        //     menu();
        // }

        // LCD_draw_int_6x8(42, 0,P2);
        // LCD_draw_int_6x8(0, 0, Menu_id);
    }
}

void init(void){
    timer_init();
    LCD_init();
    LCD_clear();
}
