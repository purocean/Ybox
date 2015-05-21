/* 主菜单选项
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日22:00:19
 */

#ifndef __MENU_H__
#define __MENU_H__

/**
 * 功能 ID
 * 0 主菜单
 * 1 关于
 * 2 扫雷
**/
enum FID{
      MENU = 0, ABOUT, MINE
};

extern enum FID Func_id;
extern unsigned char menu_id;

// 初始化菜单
void menu_init(void);

// 切换当前 Menu_id 对应的菜单
void menu_switch();

// 主方法
void menu(void);

#endif
