/* 扫雷游戏
 * 洋子
 * purocean@gmail.com
 * 2015年5月17日00:16:46
 */

#include <reg51.h>
#include <stdlib.h>
#include "../inc/event/event.h"
#include "../inc/lcd/nokia_5110.h"
#include "../inc/timer/timer.h"
#include "mine.h"
#include "mine_data.h"
#include "../menu/menu.h"

unsigned char     mine_map[MINE_COL][MINE_ROW];
unsigned char     mine_count, mine_notdig_count;
unsigned char     mine_x, mine_y;
unsigned      int mine_time;
unsigned long int mine_start_time;
bit mine_isover;
bit mine_success;

void mine_init(void){
    unsigned char x, y;
    Func_id = MINE;

    mine_notdig_count = MINE_ROW * MINE_COL;
    mine_count = 0;
    mine_start_time = Timer_stamp_ms;
    mine_time = 0;
    mine_x = 0;
    mine_y = 0;
    mine_isover = 0;
    mine_success = 0;

    srand(Timer_stamp_ms);
    for(x = 0; x < MINE_COL; ++x){
        for(y = 0; y < MINE_ROW; ++y){
            if((rand() % 8 == 1)){ // 大于 100 表示是一个雷, 1 / 8 概率
                mine_map[x][y] = 110;
                ++mine_count;
            }else{
                mine_map[x][y] = 10;
            }
        }
    }

    LCD_clear();
    mine_draw();
}

bit mine_out_of_range(signed char x, signed char y){
    if(x < 0 || MINE_COL - 1 < x || y < 0 || MINE_ROW - 1 < y){
        return 1;
    }

    return 0;
}

bit mine_is_mine(signed char x, signed char y){
    if(mine_map[x][y] >= 100){
        return 1;
    }

    return 0;
}

void mine_set_state(signed char x, signed char y, unsigned char state){
    mine_map[x][y] = (mine_map[x][y] / 100) * 100 + state;
}

unsigned char mine_get_state(signed char x, signed char y){
    return mine_map[x][y] % 100;
}

void mine_dig(signed char x, signed char y) compact reentrant{
    signed char i, j;
    unsigned char count = 0;

    if(mine_isover || mine_out_of_range(x, y) || mine_get_state(x, y) != 10){
        return;
    }

    for(i = x - 1; i <= x + 1; ++i){
        for(j = y - 1; j <= y + 1; ++j){
            if(mine_out_of_range(i, j) || (i == x && j == y)){
                continue;
            }

            if(mine_is_mine(i, j)){
                ++count;
            }
        }
    }

    mine_set_state(x, y, count);

    --mine_notdig_count;
    if(mine_notdig_count == mine_count){ // 扫雷完成
        mine_isover = 1;
        mine_success = 1;
        mine_time = (Timer_stamp_ms  - mine_start_time) / 1000;
        mine_draw_div();
        return;
    }

    if(count > 0){
        return;
    }

    for(i = x - 1; i <= x + 1; ++i){
        for(j = y - 1; j <= y + 1; ++j){
            mine_dig(i, j);
        }
    }
}

void mine_draw_div(void){
    unsigned char x, y;
    unsigned char state = 0;

    for(x = 0; x < MINE_COL; ++x){
        for(y = 0; y < MINE_ROW; ++y){
            state = mine_map[x][y] % 100;

            if(x == mine_x && y == mine_y){
                state += 11;
            }

            LCD_draw_pic(x * 8, y, 8, 8, mine_img_div[state]);

            if(mine_isover && mine_is_mine(x, y)){
                LCD_draw_pic(x * 8, y, 8, 8, mine_img_div[22]);
            }
        }
    }
}

void mine_draw(void){
    if(mine_isover){
        if(mine_success){
            LCD_draw_string_ascil_6x8(0, 2, "Time:");
            LCD_draw_int_6x8(31, 2, mine_time);
            // LCD_draw_string_ascil_6x8(0, 3, "Best:10:10:10");
            // LCD_draw_string_ascil_6x8(0, 3, "  Press START  ");
        }else{
            LCD_draw_string_ascil_6x8(0, 2, ":( Press START ");
        }
        return;
    }

    mine_draw_div();
}

void mine(void){
    static bit key_flag = 1;

    if(KEY_B){
        if(key_flag){
            key_flag = 0;

            if(mine_get_state(mine_x, mine_y) == 10){
                mine_set_state(mine_x, mine_y, 9);;
            }else if(mine_get_state(mine_x, mine_y) == 9){
                mine_set_state(mine_x, mine_y, 10);
            }
        }
    }else if(KEY_A){
        if(key_flag){
            key_flag = 0;

            if(mine_is_mine(mine_x, mine_y)){
                mine_isover = 1;
                mine_draw_div();
            }else{
                mine_dig(mine_x, mine_y);
            }
        }
    }else if(KEY_EXIT){
        if(key_flag){
            key_flag = 0;
            menu_init();
            return;
        }
    }else if(KEY_START){
        if(key_flag){
            key_flag = 0;
            mine_init();
            return;
        }
    }else if(KEY_LEFT){
        if(key_flag){
            key_flag = 0;
            mine_x = (0 < mine_x) ? mine_x - 1 : MINE_COL - 1;
        }
    }else if(KEY_RIGHT){
        if(key_flag){
            key_flag = 0;
            mine_x = (mine_x < MINE_COL - 1) ? mine_x + 1 : 0;
        }
    }else if(KEY_UPWARD){
        if(key_flag){
            key_flag = 0;
            mine_y = (0 < mine_y) ? mine_y - 1 : MINE_ROW - 1;
        }
    }else if(KEY_DOWNWARD){
        if(key_flag){
            key_flag = 0;
            mine_y = (mine_y < MINE_ROW - 1) ? mine_y + 1 : 0;
        }
    }else{
        key_flag = 1;
    }

    mine_draw();
}
