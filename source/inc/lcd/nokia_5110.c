/**
 * 诺基亚 LCD 5110 驱动
 * 洋子
 * purocean@gmail.com
 * 2015年5月10日17:26:22
 */

#include <reg51.h>
#include "font_ascil.h"
#include "nokia_5110.h"


// 延时一段时间
void _LCD_delay_awhile(void){
    unsigned int i;
    for(i = 5000; i > 0; --i);
}

// 初始化 LCD
void LCD_init(void){
    LCD_RST = 0; // 产生一个让LCD复位的低电平脉冲
    _LCD_delay_awhile();
    LCD_RST = 1;

    LCD_CE = 0; // 关闭 LCD
    _LCD_delay_awhile();
    LCD_CE = 1; // 开启 LCD
    _LCD_delay_awhile();

    LCD_write_byte(0x21, 0); // 使用扩展命令设置 LCD 模式
    LCD_write_byte(0x9c, 0); // 设置偏置电压
    LCD_write_byte(0x07, 0); // 温度校正
    LCD_write_byte(0x17, 0); // 1:48
    LCD_write_byte(0x20, 0); // 使用基本命令

    LCD_clear(); // 清屏
    LCD_write_byte(0x0c, 0); // 设定显示模式，正常显示
    LCD_CE = 0; // 关闭LCD
}

// 清屏
void LCD_clear(void){
    unsigned int i;

    LCD_set_pos(0, 0);

    for(i = LCD_WIDTH * LCD_HEIGHT; i > 0; --i){
        LCD_write_byte(0x00, 1);
    }
}

/**
 * 设置坐标
 * @param X 0-83
 * @param Y 0-5
 */
void LCD_set_pos(unsigned char x, unsigned char y){
    if(x >= LCD_WIDTH){
        // x = 0;
        return;
    }

    if(y >= LCD_ROW){
        // y = 0;
        return;
    }

    LCD_write_byte(0x80 | x, 0);
    LCD_write_byte(0x40 | y, 0);
}


/**
 * 画字符
 * @param c 字符
 */
void LCD_draw_char_6x8(unsigned char c){
    unsigned char line;

    c -= 32;
    for(line = 0; line < LCD_ROW; line++){
        LCD_write_byte(font_ascii_6x8[c][line], 1);
    }
}

/**
 * 画 ASCIL 字符串
 * @param x
 * @param y
 * @param s
 */
void LCD_draw_string_ascil_6x8(unsigned char x, unsigned char y, char *s){
    LCD_set_pos(x, y);

    while(*s){
        LCD_draw_char_6x8(*s);
        ++s;
    }
}

/**
 * 画整数
 * @param x
 * @param y
 * @param num
 */
void LCD_draw_int_6x8(unsigned char x, unsigned char y, long num){
    unsigned char temp[11];
    char i = 0;

    LCD_set_pos(x, y);

    if(num < 0){
        num = -num;
        LCD_draw_char_6x8('-');
    }else{
        LCD_draw_char_6x8(' ');
    }

    if(num == 0){
        LCD_draw_char_6x8('0');
        return;
    }

    while(num){
        temp[i] = '0' + (num % 10);
        num /= 10;
        ++i;
    }

    for(--i; i >= 0; --i){
        LCD_draw_char_6x8(temp[i]);
    }
}

/**
 * 绘制图片
 * @param x
 * @param y
 * @param w   图片宽
 * @param h   图片高
 * @param map 图片数组
 */
void LCD_draw_pic(unsigned char x, unsigned char y, unsigned char w,
        unsigned char h, unsigned char *map){
    unsigned int i, n;
    unsigned char row;

    if(h % 8 == 0){
        row = h / 8; // 计算位图所占行数
    }else{
        row = h / 8 + 1;
    }

    for(n = 0; n < row; ++n){

        LCD_set_pos(x, y);
        for(i = 0; i < w; ++i){
            LCD_write_byte(map[i + n * w], 1);
        }

        ++y;
    }
}

/**
 * 写数据到 LCD
 * @param dat    数据
 * @param command 命令 0 或者 1
 */
void LCD_write_byte(unsigned char dat, unsigned char command){
    unsigned char i;
    LCD_CE = 0;

    if(command == 0){
        LCD_DC = 0; // 传送命令到 LCD
    }else{
        LCD_DC = 1; // 传送绘制数据到 LCD
    }

    for(i = 8; i > 0; --i){
        if(dat & 0x80){
            SDIN = 1;
        }else{
            SDIN = 0;
        }

        SCLK = 0;
        dat <<=  1;
        SCLK = 1;
    }

    LCD_CE = 1;
}
