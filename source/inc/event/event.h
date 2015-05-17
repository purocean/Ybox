/**
 * 事件相关
 * 洋子
 * purocean@gmail.com
 * 2015年5月11日22:05:00
 */

#ifndef __EVENT_H__
#define __EVENT_H__

// 按键定义
sbit P_B        = P2 ^ 0;
sbit P_A        = P2 ^ 1;
sbit P_RIGHT    = P2 ^ 2;
sbit P_DOWNWARD = P2 ^ 3;
sbit P_LEFT     = P2 ^ 4;
sbit P_UPWARD   = P2 ^ 5;
sbit P_START    = P2 ^ 6;
sbit P_EXIT     = P2 ^ 7;

// 按键被按下，已经消除抖动
extern bit KEY_UPWARD;
extern bit KEY_LEFT;
extern bit KEY_DOWNWARD;
extern bit KEY_RIGHT;
extern bit KEY_A;
extern bit KEY_B;
extern bit KEY_EXIT;
extern bit KEY_START;

extern unsigned int Menu_id;

// 扫描按键
void event_scan_key(void);

#endif
