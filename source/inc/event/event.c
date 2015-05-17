/**
 * 事件相关
 * 洋子
 * purocean@gmail.com
 * 2015年5月11日22:05:00
 */

#include <reg51.h>
#include "event.h"
#include "../timer/timer.h"
#include "../lcd/nokia_5110.h"
#include "../../menu/menu.h"

bit KEY_UPWARD   = 0;
bit KEY_LEFT     = 0;
bit KEY_DOWNWARD = 0;
bit KEY_RIGHT    = 0;
bit KEY_A        = 0;
bit KEY_B        = 0;
bit KEY_EXIT     = 0;
bit KEY_START    = 0;

void event_scan_key(void){
    if(!P_EXIT && timer_delay_ms(9) && !P_EXIT){
        KEY_EXIT = 1;
    }else{
        KEY_EXIT = 0;
    }

    if(!P_START && timer_delay_ms(9) && !P_START){
        KEY_START = 1;
    }else{
        KEY_START = 0;
    }

    if(!P_UPWARD && timer_delay_ms(9) && !P_UPWARD){
        KEY_UPWARD = 1;
    }else{
        KEY_UPWARD = 0;
    }

    if(!P_LEFT && timer_delay_ms(9) && !P_LEFT){
        KEY_LEFT = 1;
    }else{
        KEY_LEFT = 0;
    }

    if(!P_DOWNWARD && timer_delay_ms(9) && !P_DOWNWARD){
        KEY_DOWNWARD = 1;
    }else{
        KEY_DOWNWARD = 0;
    }

    if(!P_RIGHT && timer_delay_ms(9) && !P_RIGHT){
        KEY_RIGHT = 1;
    }else{
        KEY_RIGHT = 0;
    }

    if(!P_A && timer_delay_ms(9) && !P_A){
        KEY_A = 1;
    }else{
        KEY_A = 0;
    }

    if(!P_B && timer_delay_ms(9) && !P_B){
        KEY_B = 1;
    }else{
        KEY_B = 0;
    }
}
