#include "datetime_ui.h"
#include "rtc.h"

Item_Font Clock_Item[] =
{
    {CLOCK_TEXT_START_X, CLOCK_TEXT_START_Y, "时钟设置", BLACK, BLACK, CLOCK_TEXT_FONT, 1},		//0  隐藏  0
    {CLOCK_TEXT_START_X, CLOCK_TEXT_START_Y, "时钟设置", WHITE, BLACK, CLOCK_TEXT_FONT, 1},		//1  显示  1

    {YEAR_TEXT_START_X, YEAR_TEXT_START_Y, "年", BLACK, BLACK, YEAR_TEXT_FONT, 1},						//1  隐藏  2
    {MONTH_TEXT_START_X, MONTH_TEXT_START_Y, "月", BLACK, BLACK, MONTH_TEXT_FONT, 1},					//1  隐藏	 3
    {DAY_TEXT_START_X, DAY_TEXT_START_Y, "日", BLACK, BLACK, DAY_TEXT_FONT, 1},								//1  隐藏	 4
    {HOUR_TEXT_START_X, HOUR_TEXT_START_Y, "时", BLACK, BLACK, HOUR_TEXT_FONT, 1},						//1  隐藏	 5
    {MIN_TEXT_START_X, MIN_TEXT_START_Y, "分", BLACK, BLACK, MIN_TEXT_FONT, 1},								//1  隐藏	 6
    {SEC_TEXT_START_X, SEC_TEXT_START_Y, "秒", BLACK, BLACK, SEC_TEXT_FONT, 1},								//1  隐藏  7

    {YEAR_TEXT_START_X, YEAR_TEXT_START_Y, "年", WHITE, BLACK, YEAR_TEXT_FONT, 1},						//1  显示  8
    {MONTH_TEXT_START_X, MONTH_TEXT_START_Y, "月", WHITE, BLACK, MONTH_TEXT_FONT, 1},					//1  显示  9
    {DAY_TEXT_START_X, DAY_TEXT_START_Y, "日", WHITE, BLACK, DAY_TEXT_FONT, 1},								//1  显示	 10
    {HOUR_TEXT_START_X, HOUR_TEXT_START_Y, "时", WHITE, BLACK, HOUR_TEXT_FONT, 1},						//1  显示	 11
    {MIN_TEXT_START_X, MIN_TEXT_START_Y, "分", WHITE, BLACK, MIN_TEXT_FONT, 1},								//1  显示	 12
    {SEC_TEXT_START_X, SEC_TEXT_START_Y, "秒", WHITE, BLACK, SEC_TEXT_FONT, 1},								//1  显示	 13
};

Clock_Setting Clock_Para ;
//计算天数算法
static void cal_day(void);

//显示日期和时间
void display_datetime(DateTime_HandleTypeDef item, uint8_t hide)
{
    Clock_Para.year   = item.year;
    Clock_Para.month  = item.month;
    Clock_Para.day    = item.day;
    Clock_Para.hour   = item.hour;
    Clock_Para.minute = item.minute;
    Clock_Para.sec    = item.sec;

    if(hide == 0)
    {
        memset(Clock_Para.display_buf, 0, 10);
        // sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
        sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
        //LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
        LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
        LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
        LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, WHITE, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
        LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
        LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
        LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, WHITE, 24);
    }
    else
    {
        memset(Clock_Para.display_buf, 0, 10);
        //sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
        sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
        //LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, BLACK, 24);
        LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, BLACK, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
        LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, BLACK, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
        LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, BLACK, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
        LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, BLACK, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
        LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, BLACK, 24);

        memset(Clock_Para.display_buf, 0, 10);
        sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
        LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, BLACK, 24);
    }
}

/*选中具体调整项*/
void select_datatime_item(int item)
{
    memset(Clock_Para.display_buf, 0, 10);
    // sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
    sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
    // LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);
    LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

    memset(Clock_Para.display_buf, 0, 10);
    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
    LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

    memset(Clock_Para.display_buf, 0, 10);
    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
    LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, WHITE, 24);

    memset(Clock_Para.display_buf, 0, 10);
    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
    LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

    memset(Clock_Para.display_buf, 0, 10);
    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
    LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, WHITE, 24);

    memset(Clock_Para.display_buf, 0, 10);
    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
    LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, WHITE, 24);

    switch(Clock_Para.select_item)
    {
        case 0:
            memset(Clock_Para.display_buf, 0, 10);
            //sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
            //LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);

            sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
            LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        case 1:
            memset(Clock_Para.display_buf, 0, 10);
            sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
            LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        case 2:
            memset(Clock_Para.display_buf, 0, 10);
            sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
            LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        case 3:
            memset(Clock_Para.display_buf, 0, 10);
            sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
            LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        case 4:
            memset(Clock_Para.display_buf, 0, 10);
            sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
            LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        case 5:
            memset(Clock_Para.display_buf, 0, 10);
            sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
            LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
            break ;

        default:
            break ;
    }
}

void clock_item_display(int enable)
{
    if(enable == 1)
    {
        //LCD_ShowChinese(Clock_Item[1].x, Clock_Item[1].y,
        //                Clock_Item[1].Str, Clock_Item[1].front_color,
        //                Clock_Item[1].back_color, Clock_Item[1].font_num, Clock_Item[1].mode);
        display_menu_color_item(Clock_Item, 1, Clock_Item[1].front_color, Clock_Item[1].back_color);

        for(int i = 8 ; i < 14 ; i++)
        {
            LCD_ShowChinese(Clock_Item[i].x, Clock_Item[i].y,
                            Clock_Item[i].Str, Clock_Item[i].front_color,
                            Clock_Item[i].back_color, Clock_Item[i].font_num, Clock_Item[i].mode);
        }

        display_datetime(DateTime_Handler_Info, 0);
    }
    else if(enable == 0)
    {
        //LCD_ShowChinese(Clock_Item[0].x, Clock_Item[0].y,
        //                Clock_Item[0].Str, Clock_Item[0].front_color,
        //                Clock_Item[0].back_color, Clock_Item[0].font_num, Clock_Item[0].mode);
        display_menu_color_item(Clock_Item, 0, Clock_Item[0].front_color, Clock_Item[0].back_color);

        for(int i = 2 ; i < 8 ; i++)
        {
            //  LCD_ShowChinese(Clock_Item[i].x, Clock_Item[i].y,
            //                  Clock_Item[i].Str, Clock_Item[i].front_color,
            //                 Clock_Item[i].back_color, Clock_Item[i].font_num, Clock_Item[i].mode);
            display_menu_color_item(Clock_Item, i, Clock_Item[i].front_color, Clock_Item[i].back_color);
        }

        display_datetime(DateTime_Handler_Info, 1);
    }
}


/*日期时间初始化*/
void datetime_page_init(void)
{
    Flow_Cursor.flow_cursor = DATETIME_PAGE ;
    Clock_Para.select_item = 0 ;
    clock_item_display(1);
}

//跳转到下一设置项
void jump_next_item(void)
{
    switch(Clock_Para.select_item)
    {
        case 0:
            Clock_Para.select_item = 1 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        case 1:
            Clock_Para.select_item = 2 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        case 2:
            Clock_Para.select_item = 3 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        case 3:
            Clock_Para.select_item = 4 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        case 4:
            Clock_Para.select_item = 5 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        case 5:
            Clock_Para.select_item = 0 ;
            select_datatime_item(Clock_Para.select_item);
            break ;

        default:
            break ;
    }
}

//设置日期时间
void setting_datetime(uint8_t KeyValue)
{
    switch(KeyValue)
    {
        case RIGHT:
            switch(Clock_Para.select_item)
            {
                case 0:
                    (Clock_Para.year < 2099) ? (Clock_Para.year++) : (Clock_Para.year = 2099);
                    memset(Clock_Para.display_buf, 0, 10);
                    // sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
                    // LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
                    LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 1:
                    (Clock_Para.month < 12) ? (Clock_Para.month++) : (Clock_Para.month = 12);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
                    LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 2:
                    cal_day();
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
                    LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 3:
                    (Clock_Para.hour < 23) ? (Clock_Para.hour++) : (Clock_Para.hour = 23);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
                    LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 4:
                    (Clock_Para.minute < 59) ? (Clock_Para.minute++) : (Clock_Para.minute = 59);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
                    LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 5:
                    (Clock_Para.sec < 59) ? (Clock_Para.sec++) : (Clock_Para.sec = 59);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
                    LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;
            }

            break ;

        case LEFT:
            switch(Clock_Para.select_item)
            {
                case 0:
                    (Clock_Para.year > 2000) ? (Clock_Para.year--) : (Clock_Para.year = 2000);
                    memset(Clock_Para.display_buf, 0, 10);
                    //sprintf(Clock_Para.display_buf, "%02d", Clock_Para.year - 2000);
                    //LCD_ShowCharStr(YEAR_TEXT_START_X - 24, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    sprintf(Clock_Para.display_buf, "%04d", Clock_Para.year);
                    LCD_ShowCharStr(0, YEAR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 1:
                    (Clock_Para.month > 1) ? (Clock_Para.month--) : (Clock_Para.month = 1);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.month);
                    LCD_ShowCharStr(MONTH_TEXT_START_X - 24, MONTH_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 2:
                    (Clock_Para.day > 1) ? (Clock_Para.day--) : (Clock_Para.day = 1);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.day);
                    LCD_ShowCharStr(DAY_TEXT_START_X - 24, DAY_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 3:
                    (Clock_Para.hour > 0) ? (Clock_Para.hour--) : (Clock_Para.hour = 0);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.hour);
                    LCD_ShowCharStr(HOUR_TEXT_START_X - 24, HOUR_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 4:
                    (Clock_Para.minute > 0) ? (Clock_Para.minute--) : (Clock_Para.minute = 0);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.minute);
                    LCD_ShowCharStr(MIN_TEXT_START_X - 24, MIN_TEXT_START_Y, 125, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;

                case 5:
                    (Clock_Para.sec > 0) ? (Clock_Para.sec--) : (Clock_Para.sec = 0);
                    memset(Clock_Para.display_buf, 0, 10);
                    sprintf(Clock_Para.display_buf, "%02d", Clock_Para.sec);
                    LCD_ShowCharStr(SEC_TEXT_START_X - 24, SEC_TEXT_START_Y, 20, Clock_Para.display_buf, BLACK, RED, 24);
                    break ;
            }

            break ;
    }
}
/*日期时间设置页面按键处理*/
void datetime_page_process(uint8_t KeyValue)
{
    switch(KeyValue)
    {
        case LEFT:
            setting_datetime(LEFT);
            break ;

        case RIGHT:
            setting_datetime(RIGHT);
            break ;

        case ENTER_SHORT:
            jump_next_item();
            break ;

        /*返回配置菜单*/
        case ENTER_LONG:
            if(HAL_OK == RTC_Set_Date(Clock_Para.year - 2000, Clock_Para.month, Clock_Para.day, RTC_WEEKDAY_MONDAY))
            {
                if(HAL_OK == RTC_Set_Time(Clock_Para.hour, Clock_Para.minute, Clock_Para.sec, 0))
                {
                    DEBUG("设置日期时间成功\n");
                }
            }

            clock_item_display(0);
            Flow_Cursor.flow_cursor = CONF_PAGE ;
            conf_page_ui.select_item = 1 ;
            conf_page_menu_list_display(1);
            conf_page_menu_list_select(conf_page_ui.select_item);
            break ;

        default:
            break ;
    }
}

//计算天数算法
static void cal_day(void)
{
    if(IS_LEAP_YEAR(Clock_Para.year))
    {
        switch(Clock_Para.month)
        {
            case Jan:
            case Mar:
            case May:
            case Jul:
            case Aug:
            case Oct:
            case Dec:
                if(Clock_Para.day < MAX_MON_DAY)
                    Clock_Para.day++ ;

                break ;

            case Apr:
            case Jun:
            case Sep:
            case Nov:
                if(Clock_Para.day < MIN_MON_DAY)
                    Clock_Para.day++ ;

                break ;

            default:
                if(Clock_Para.day < FEB_MON_MAX_DAY)
                    Clock_Para.day++ ;

                ;
                break ;

        }
    }
    else
    {
        switch(Clock_Para.month)
        {
            case Jan:
            case Mar:
            case May:
            case Jul:
            case Aug:
            case Oct:
            case Dec:
                if(Clock_Para.day < MAX_MON_DAY)
                    Clock_Para.day++ ;

                break ;

            case Apr:
            case Jun:
            case Sep:
            case Nov:
                if(Clock_Para.day < MIN_MON_DAY)
                    Clock_Para.day++ ;

                ;
                break ;

            default:
                if(Clock_Para.day < FEB_MON_MIN_DAY)
                    Clock_Para.day++ ;

                ;
                break ;
        }
    }
}

