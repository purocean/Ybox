/* 扫雷游戏
 * 洋子
 * purocean@gmail.com
 * 2015年5月17日00:16:46
 */

#ifndef __MINE_H__
#define __MINE_H__

#define MINE_ROW 6 // 行数
#define MINE_COL 10 // 列数
#define MINE_BEST_ADDR 0x2000 // 最佳时间储存地址

void mine_init(void);

extern unsigned char     mine_map[MINE_COL][MINE_ROW];
extern unsigned char     mine_count, mine_notdig_count;
extern unsigned char     mine_x, mine_y;
extern unsigned      int mine_time;
extern unsigned long int mine_start_time;
extern bit mine_isover;
extern bit mine_success;

// 主方法
void mine(void);
void mine_draw_div(void);
void mine_draw(void);
bit mine_out_of_range(signed char x, signed char y);
bit mine_is_mine(signed char x, signed char y);
void mine_set_state(signed char x, signed char y, unsigned char state);
unsigned char mine_get_state(signed char x, signed char y);
void mine_dig(signed char x, signed char y) compact reentrant;

#endif
