#include "main_ui.h"
#include "bsp_bmp.h"

/*长按左键待机*/
#define ITEM_STANDBY_X		 			20
#define ITEM_STANDBY_Y		 			208

#define LOGO_X	55
#define LOGO_Y 	55

#define DETECT_LOGO 	"0:/UI/main_page/detect_logo.bmp"
#define LOG_LOGO 		"0:/UI/main_page/log_logo.bmp"
#define CONF_LOGO 		"0:/UI/main_page/conf_logo.bmp"

/*主页面事件处理*/
static void Handler_Main_Page_Left_Key(void);
static void Handler_Main_Page_Left_Long_Key(void);
static void Handler_Main_Page_Right_Key(void);
static void Handler_Main_Page_Right_Long_Key(void);

Event_Frame Main_Page_Event[] =
{
    {Handler_Main_Page_Left_Key},
    {Handler_Main_Page_Left_Long_Key},
    {Handler_Main_Page_Right_Key},
    {Handler_Main_Page_Right_Long_Key},
};

Main_Page_Ui main_page_ui ;
LCD_Fill_Para LOGO_Fill_Para = {LOGO_X, LOGO_X + 128, LOGO_Y, LOGO_Y + 128, BLACK} ;
LCD_Ascii_Show_Para datatime_display_para = {0, 5, 240, DateTime_Handler_Info.DisPlay_DateBuf, BLACK, WHITE, 24} ;

/*主页面初始化*/
void main_page_init(void)
{
    main_page_ui.select_item = 0;
    Flow_Cursor.flow_cursor = MAIN_PAGE ;
    lcd_model.lcd_driver->lcd_display_onoff(0);
    Get_Date_Time();
    sprintf(DateTime_Handler_Info.DisPlay_DateBuf, "%04d-%02d-%02d %02d:%02d:%02d", \
            DateTime_Handler_Info.year, DateTime_Handler_Info.month, DateTime_Handler_Info.day, \
            DateTime_Handler_Info.hour, DateTime_Handler_Info.minute, DateTime_Handler_Info.sec
           );
    lcd_model.lcd_driver->lcd_show_ascii_str(datatime_display_para);
    Select_Main_Menu_Item(main_page_ui.select_item);
    lcd_model.lcd_driver->lcd_display_onoff(1);
}


//选择菜单项
void Select_Main_Menu_Item(uint8_t item)
{
    lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);

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

/*左键处理*/
static void Handler_Main_Page_Left_Key(void)
{
    (main_page_ui.select_item < 2) ? \
    (main_page_ui.select_item++) : 	 \
    (main_page_ui.select_item = 0);
    Select_Main_Menu_Item(main_page_ui.select_item);
}

/*左键长按处理*/
static void Handler_Main_Page_Left_Long_Key(void)
{
    sleep_page_init();
}

/*右键处理*/
static void Handler_Main_Page_Right_Key(void)
{
    switch(main_page_ui.select_item)
    {
        case 0:
            lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
            test_page_init();
            break ;

        case 1:
            lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
            log_page_init();
            break ;

        case 2:
            lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
            conf_page_ui_init(0);
            break ;

        default:
            break ;
    }
}

/*右键长按处理*/
void Handler_Main_Page_Right_Long_Key(void)
{
	return ;
}


/*主页面事件处理*/
void main_page_process(uint8_t Event_Code)
{
    Main_Page_Event[Event_Code - 1].handler_func();
}

