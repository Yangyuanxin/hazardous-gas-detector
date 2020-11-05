#include "main_ui.h"
#include "bsp_bmp.h"

Main_Page_Ui main_page_ui ;
LCD_Fill_Para LOGO_Fill_Para = {55, 183, 55, 183, BLACK} ;
LCD_Ascii_Show_Para datatime_display_para = {0, 5, 240, DateTime_Handler_Info.DisPlay_DateBuf, BLACK, WHITE, 24} ;
LCD_Bmp_Show_Para main_logo_para[] =
{
    {55, 55, "0:/UI/main_page/detect_logo.bmp"},
    {55, 55, "0:/UI/main_page/log_logo.bmp"},
    {55, 55, "0:/UI/main_page/conf_logo.bmp"},
};

//选择菜单项
void Select_Main_Menu_Item(uint8_t item)
{
    lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);

    switch(item)
    {
        case 0:
            lcd_model.lcd_driver->Lcd_show_bmp(main_logo_para[0]);
            break ;

        case 1:
            display_smoke_value(0, BLACK, 0);
            lcd_model.lcd_driver->Lcd_show_bmp(main_logo_para[1]);
            break ;

        case 2:
            display_smoke_value(0, BLACK, 0);
            lcd_model.lcd_driver->Lcd_show_bmp(main_logo_para[2]);
            break ;

        default :
            break ;
    }
}

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


/********************************************按键处理****************************************************/
/*主页面事件处理*/
static void Handler_Main_Page_Left_Key(void);
static void Handler_Main_Page_Left_Long_Key(void);
static void Handler_Main_Page_Right_Key(void);

Event_Frame Main_Page_Event[] =
{
    {Handler_Main_Page_Left_Key},
    {Handler_Main_Page_Left_Long_Key},
    {Handler_Main_Page_Right_Key},
    {NULL},
};

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
    if(0 == main_page_ui.select_item)
    {
        lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
        test_page_init();
    }
    else if(1 == main_page_ui.select_item)
    {
        lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
        log_page_init();
    }
    else if(2 == main_page_ui.select_item)
    {
        lcd_model.lcd_driver->lcd_fill(LOGO_Fill_Para);
        conf_page_ui_init(0);
    }
}

/*主页面事件处理*/
void main_page_process(uint8_t Event_Code)
{
    if(Main_Page_Event[Event_Code - 1].handler_func != NULL)
        Main_Page_Event[Event_Code - 1].handler_func();
}
/********************************************按键处理****************************************************/
