#ifndef __PASSWORD_UI_H
#define __PASSWORD_UI_H
#include "main.h"

//�������������
#define INPUT_PASSWD_TEXT_START_X 60
#define INPUT_PASSWD_TEXT_START_Y 50
#define INPUT_PASSWD_TEXT_FONT    24

//�����һλ
#define NUM_ONE_TEXT_X					80
#define NUM_ONE_TEXT_Y          117
#define NUM_ONE_TEXT_FONT				24

//����ڶ�λ
#define NUM_TWO_TEXT_X				  116
#define NUM_TWO_TEXT_Y					117
#define NUM_TWO_TEXT_FONT       24

//�������λ
#define NUM_THREE_TEXT_X				150
#define NUM_THREE_TEXT_Y				117
#define NUM_THREE_TEXT_FONT     24

typedef struct
{
    uint8_t select_item ;
    uint8_t Password[3];
    char 	display_buf[10];
} Password_Page ;


/*�������ó�ʼ��*/
void password_page_init(void);
/*��������ҳ�水������*/
void password_page_process(uint8_t KeyValue);


#endif //__PASSWORD_UI_H

