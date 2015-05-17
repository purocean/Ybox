/**
 * 诺基亚 LCD 5100 驱动
 * 洋子
 * purocean@gmail.com
 * 2015年5月8日18:21:48
 */

#ifndef __LCD_NOKIA_5100_H__
#define __LCD_NOKIA_5100_H__
/**
 * 需要使用的各个引脚
 */

#define LCD_WIDTH 84 // LCD 宽，像素
#define LCD_HEIGHT 48 // LCD 高，像素
#define LCD_ROW 6 // LCD 能显示行数

sbit SCLK    = P1^4;
sbit SDIN    = P1^3;
sbit LCD_DC  = P1^2;
sbit LCD_CE  = P1^1;
sbit LCD_RST = P1^0;

// LCD 初始化
void LCD_init(void);

// 清屏
void LCD_clear(void);

// 设置坐标
void LCD_set_pos(unsigned char x, unsigned char y);

// 画字符
void LCD_draw_char_6x8(unsigned char c);

// 画字符串，不支持中文
void LCD_draw_string_ascil_6x8(unsigned char x, unsigned char y, char *s);

// 画整数
void LCD_draw_int_6x8(unsigned char x, unsigned char y, long num);

// 绘制图片到屏幕
void LCD_draw_pic(unsigned char x, unsigned char y, unsigned char w,
        unsigned char h, unsigned char *map);

// 向 LCD 传输数据
void LCD_write_byte(unsigned char dat, unsigned char dc);

#endif
