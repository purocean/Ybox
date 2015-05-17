/* 主菜单选项
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日22:00:19
 */

#ifndef __MENU_H__
#define __MENU_H__

extern unsigned int Menu_id;

// 初始化菜单
void menu_init(void);

// 切换当前 Menu_id 对应的菜单
void menu_switch(void);

// 切换主菜单;
void menu_switch_loop(unsigned char is_left);

// 主方法
void menu(void);

#endif
