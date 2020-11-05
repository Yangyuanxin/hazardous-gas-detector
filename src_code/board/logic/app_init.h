#ifndef __APP_INIT_H
#define __APP_INIT_H
#include "main.h"
#include "lcd_driver_frame.h"

#define NR_ARRAY(x) sizeof(x)/sizeof(x[0])

extern LCD_Driver_Model lcd_model ; 

/*启动操作系统*/
void start_tencent_os(void);







#endif //__APP_INIT_H


