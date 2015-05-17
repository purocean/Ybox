/**
 * 定时器相关
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日21:31:31
 */

#include <reg51.h>
#include "timer.h"

bit Timer_T0_flag = 0;

void timer_init(void){
    TMOD = 0x01; // 设置定时器 0 为非门控制方式 1
    TH0  = (65536 - TIMER_MS_COUNT_NUM) / 256; // 装载计数器初值
    TL0  = (65536 - TIMER_MS_COUNT_NUM) % 256;
    EA   = 1; // CPU 中断开放
    ET0  = 1; // 开放 T/CO
    TR0  = 1; // 启动 T/C0
}

unsigned char timer_delay_ms(unsigned long ms){
    while(ms > 0){
        if(Timer_T0_flag){
            timer_init();
            --ms;
            Timer_T0_flag =0;
        }
    }

    return 1;
}

void timer_ms_interrupt(void) interrupt 1 using 1{
    Timer_T0_flag = 1;
    timer_init();
}
