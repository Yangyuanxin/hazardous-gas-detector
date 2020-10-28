#include "main_ui.h"
#include "bsp_bmp.h"

/*�����������*/
#define ITEM_STANDBY_X		 			20
#define ITEM_STANDBY_Y		 			208

#define LOGO_X	55
#define LOGO_Y 	55

#define DETECT_LOGO "0:/UI/main_page/detect_logo.bmp"
#define LOG_LOGO 		"0:/UI/main_page/log_logo.bmp"
#define CONF_LOGO 		"0:/UI/main_page/conf_logo.bmp"

uint8_t main_item = 0 ;


/*��ҳ���ʼ��*/
void main_page_init(void)
{
    Flow_Cursor.flow_cursor = MAIN_PAGE ;
    //��LCD��ʾ
    LCD_DisplayOff();
    //��ʾʱ��
    Get_Date_Time();
    sprintf(DateTime_Handler_Info.DisPlay_DateBuf, "%04d-%02d-%02d %02d:%02d:%02d", \
            DateTime_Handler_Info.year, DateTime_Handler_Info.month, DateTime_Handler_Info.day, \
            DateTime_Handler_Info.hour, DateTime_Handler_Info.minute, DateTime_Handler_Info.sec
           );
    LCD_ShowCharStr(0, 5, 240, DateTime_Handler_Info.DisPlay_DateBuf, BLACK, WHITE, 24);
    Select_Main_Menu_Item(main_item);
    //��LCD��ʾ
    LCD_DisplayOn();
}


//ѡ��˵���
void Select_Main_Menu_Item(uint8_t item)
{
    LCD_Fill(LOGO_X, LOGO_Y, LOGO_X + 128, LOGO_Y + 128, BLACK);

    switch(item)
    {
        case 0:
            Lcd_show_bmp(LOGO_X, LOGO_Y, DETECT_LOGO);
            break ;

        case 1:
            display_smoke_value(0, BLACK, 0);
            Lcd_show_bmp(LOGO_X, LOGO_Y, LOG_LOGO);
            break ;

        case 2:
            display_smoke_value(0, BLACK, 0);
            Lcd_show_bmp(LOGO_X, LOGO_Y, CONF_LOGO);
            break ;

        default :
            break ;
    }
}

//���л���ҳ��˵�,�ҽ���˵���
void Select_Main_Menu(uint8_t Event_Code)
{
    switch(Event_Code)
    {
        case LEFT:
            (main_item < 2) ? (main_item++) : (main_item = 0);
            Select_Main_Menu_Item(main_item);
            break ;

        case RIGHT:
            switch(main_item)
            {
                case 0:
                    LCD_Fill(LOGO_X, LOGO_Y, LOGO_X + 128, LOGO_Y + 128, BLACK);
                    test_page_init();
                    break ;

                case 1:
										LCD_Fill(LOGO_X, LOGO_Y, LOGO_X + 128, LOGO_Y + 128, BLACK);
										log_page_init();
                    break ;

                case 2:
                    LCD_Fill(LOGO_X, LOGO_Y, LOGO_X + 128, LOGO_Y + 128, BLACK);
                    conf_page_ui_init(0);
                    break ;

                default:
                    break ;
            }

            break ;

        default:
            break ;
    }
}



/*��ҳ���¼�����*/
void main_page_process(uint8_t Event_Code)
{
    switch(Event_Code)
    {
        case LEFT:
            Select_Main_Menu(Event_Code);
            break ;

        case RIGHT:
            Select_Main_Menu(Event_Code);
            break ;

        case LEFT_LONG:
            sleep_page_init();
            break ;

        default:
            break ;
    }
}

