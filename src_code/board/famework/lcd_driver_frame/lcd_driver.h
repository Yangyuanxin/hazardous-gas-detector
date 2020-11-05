#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H
#include <stdint.h>


/*��һ������ɫ�ӿڲ���*/
typedef struct
{
    uint16_t x_start; 
	uint16_t x_end	;
	uint16_t y_start; 
	uint16_t y_end	;
	uint16_t color	;
} LCD_Fill_Para ;

/*������ʾ�ӿڲ���*/
typedef struct
{
    uint16_t x_start; 
	uint16_t x_end	;
	uint16_t y_start; 
	uint16_t y_end	;
	uint16_t color	;
} LCD_Line_Show_Para ;

/*��������ʾ�ӿڲ���*/
typedef struct
{
    uint16_t x_start; 
	uint16_t x_end	;
	uint16_t y_start; 
	uint16_t y_end	;
	uint16_t color	;
} LCD_Rect_Show_Para ;

/*ASCII�ַ�����ʾ�ӿڲ���*/
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint8_t max_width;
    char* str;
    uint16_t bc;
    uint16_t fc;
    uint8_t sizey;
} LCD_Ascii_Show_Para ;

/*ͼ����ʾ�ӿڲ���*/
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    const uint8_t *p;
} LCD_Image_Show_Para ;

/*������ʾ�ӿڲ���*/
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint8_t *s;
    uint16_t fc;
    uint16_t bc;
    uint8_t sizey;
    uint8_t mode ;
} LCD_Chinese_Show_Para ;


/*lcd�����ӿ�*/
typedef struct
{
    /*LCD��ʼ��*/
    void (*lcd_init)(void);
    /*LCD����*/
    void (*lcd_clear)(uint16_t);
    /*������Ļ��������*/
    void (*lcd_display_onoff)(uint8_t);
    /*��һ��ָ������ɫ*/
    void (*lcd_fill)(LCD_Fill_Para para);

    /*LCD����*/
    void (*lcd_draw_line)(LCD_Line_Show_Para para);
    /*LCD������*/
    void (*lcd_draw_rect)(LCD_Rect_Show_Para para);

    /*LCD��ʾͼ��*/
    void (*lcd_show_image)(LCD_Image_Show_Para para);
    /*LCD��ʾ�����ַ���*/
    void (*lcd_show_chinese_str)(LCD_Chinese_Show_Para para);
    /*LCD��ʾASCII�ַ���*/
    void (*lcd_show_ascii_str)(LCD_Ascii_Show_Para para);
} LCD_Driver ;
extern LCD_Driver lcd_driver;








#endif //LCD_DRIVER_H

