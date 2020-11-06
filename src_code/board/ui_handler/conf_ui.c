#include "conf_ui.h"

Conf_Page conf_page_ui ;

/*配置页面菜单项显示*/
Item Conf_Item_Display[] =
{
    /*显示*/
    {70, 73,  "系统参数", WHITE, BLACK, 24, 1},		//0		/*检测阈值===>低、中、高*/
    {70, 102, "时间设置", WHITE, BLACK, 24, 1},		//1		/*声音、LED、数值显示*/
    {70, 131, "密码设置", WHITE, BLACK, 24, 1},		//2		/*开、关*/
    {70, 160, "仪器信息", WHITE, BLACK, 24, 1},		//3		/*显示版本号、ROM、RAM等信息*/
    /*隐藏*/
    {70, 73,  "系统参数", BLACK, BLACK, 24, 1},		//4		/*检测阈值===>低、中、高*/
    {70, 102, "时间设置", BLACK, BLACK, 24, 1},		//5		/*声音、LED、数值显示*/
    {70, 131, "密码设置", BLACK, BLACK, 24, 1},		//6		/*开、关*/
    {70, 160, "仪器信息", BLACK, BLACK, 24, 1},		//7		/*显示版本号、ROM、RAM等信息*/
};

/*选择菜单项目*/

void select_conf_item(uint8_t item, uint16_t color)
{
    LCD_Ascii_Show_Para disselect_ascii[] =
    {
        {46, 73, 24,  "*", BLACK, BLACK, 24},
        {46, 102, 24, "*", BLACK, BLACK, 24},
        {46, 131, 24, "*", BLACK, BLACK, 24},
        {46, 160, 24, "*", BLACK, BLACK, 24},

        {46, 73, 24,  "*", BLACK, color, 24},
        {46, 102, 24, "*", BLACK, color, 24},
        {46, 131, 24, "*", BLACK, color, 24},
        {46, 160, 24, "*", BLACK, color, 24},
    };

    for(int i = 0 ; i < 4 ; i++)
        lcd_model.lcd_driver->lcd_show_ascii_str(disselect_ascii[i]);

    if(item == 0)
        lcd_model.lcd_driver->lcd_show_ascii_str(disselect_ascii[4]);
    else if(item == 1)
        lcd_model.lcd_driver->lcd_show_ascii_str(disselect_ascii[5]);
    else if(item == 2)
        lcd_model.lcd_driver->lcd_show_ascii_str(disselect_ascii[6]);
    else if(item == 3)
        lcd_model.lcd_driver->lcd_show_ascii_str(disselect_ascii[7]);
}

//配置页面初始化
void conf_page_ui_init(uint8_t item)
{
    Flow_Cursor.flow_cursor = CONF_PAGE ;
    conf_page_ui.select_item = item ;

    for(int i = 0 ; i < 4 ; i++)
        display_menu_item(Conf_Item_Display, i);

    select_conf_item(conf_page_ui.select_item, RED);
}

//进入某一配置项
void enter_conf_item(uint8_t item)
{
    switch(item)
    {
        //系统参数
        case 0:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*系统参数页面初始化*/
            para_setting_page_init();
            break ;

        //时间设置
        case 1:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*时间页面初始化*/
            break ;

        //密码设置
        case 2:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*密码页面初始化*/
            password_page_init();
            break ;

        //仪器信息
        case 3:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            Version_Info_Page_Init();
            break ;

        default:
            break ;
    }
}


//配置页面按键处理
void conf_page_process(uint8_t Event_Code)
{
    switch(Event_Code)
    {
        //切换到下一项
        case LEFT:
            (conf_page_ui.select_item < 3) ? (conf_page_ui.select_item++) : (conf_page_ui.select_item = 0);
            select_conf_item(conf_page_ui.select_item, RED);
            break ;

        //进入某一项
        case RIGHT:
            lcd_model.lcd_driver->lcd_display_onoff(0);
            enter_conf_item(conf_page_ui.select_item);
            lcd_model.lcd_driver->lcd_display_onoff(1);
            break ;

        //退出菜单回到主菜单
        case RIGHT_LONG:
            lcd_model.lcd_driver->lcd_display_onoff(0);
            select_conf_item(conf_page_ui.select_item, BLACK);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            Flow_Cursor.flow_cursor = MAIN_PAGE ;
            Select_Main_Menu_Item(main_page_ui.select_item);
            lcd_model.lcd_driver->lcd_display_onoff(1);
            break ;

        default:
            break ;
    }
}






