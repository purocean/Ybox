/* 定时器相关
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日21:31:31
 */

#ifndef __TIMMER_H__
#define __TIMMER_H__

#define TIMER_FOSC 236570 // 单片机晶振频率
#define TIMER_MS_COUNT_NUM (100000/(12000000/TIMER_FOSC)-12) // 一毫秒计数次数
// #define TIMER_MS_COUNT_NUM 2000 // 一毫秒计数次数

extern bit Timer_T0_flag; // T0 中断标志
extern unsigned long int Timer_stamp_ms; // 系统启动时间，毫秒

// 定时器初始化
void timer_init(void);

// 延时毫秒
unsigned char timer_delay_ms(unsigned long ms);

#endif
