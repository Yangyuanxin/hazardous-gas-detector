#include "test_ui.h"
#include "bsp_bmp.h"


//ˢ�¶���
void icon_reflash(uint8_t status)
{
    if(Sensor_Flow_Cursor.Detect_Step == BASE_LINE)
    {
        switch(status)
        {
            case 0:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, B0_LOGO);
                break ;

            case 1:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, B1_LOGO);
                break ;

            case 2:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, B2_LOGO);
                break ;

            default:
                break ;
        }
    }
    else if(Sensor_Flow_Cursor.Detect_Step == DETECTING)
    {
        switch(status)
        {
            case 0:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, D0_LOGO);
                break ;

            case 1:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, D1_LOGO);
                break ;

            case 2:
                Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, D2_LOGO);
                break ;

            default:
                break ;
        }
    }
}

/*��ʾ��׼1����0*/
void display_base(uint8_t enable)
{
    if(enable == 1)
    {
        Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, B2_LOGO);
        LCD_ShowChinese(94, 130, (uint8_t *)"��׼", WHITE, BLACK, 24, 1);
    }
    else if(enable == 0)
    {
        LCD_Fill(DETECT_LOGO_X, DETECT_LOGO_Y, DETECT_LOGO_X + 84, DETECT_LOGO_Y + 84, BLACK);
        LCD_Fill(94, 130, 94 + 48, 130 + 24, BLACK);
    }
}

/*��ʾ���1����0*/
void display_detect(uint8_t enable)
{
    if(enable == 1)
    {
        Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, D2_LOGO);
        LCD_ShowChinese(94, 130, (uint8_t *)"���", WHITE, BLACK, 24, 1);
    }
    else if(enable == 0)
    {
        LCD_Fill(DETECT_LOGO_X, DETECT_LOGO_Y, DETECT_LOGO_X + 84, DETECT_LOGO_Y + 84, BLACK);
        LCD_Fill(94, 130, 94 + 48, 130 + 24, BLACK);
    }
}

/*��ʾ��ȫ1����0*/
void display_safety(uint8_t enable)
{
    if(enable == 1)
    {
        Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, R0_LOGO);
        LCD_ShowChinese(94, 130, (uint8_t *)"��ȫ", GREEN, BLACK, 24, 1);
    }
    else if(enable == 0)
    {
        LCD_Fill(DETECT_LOGO_X, DETECT_LOGO_Y, DETECT_LOGO_X + 84, DETECT_LOGO_Y + 84, BLACK);
        LCD_Fill(94, 130, 94 + 48, 130 + 24, BLACK);
    }
}

/*��ʾΣ��1����0*/
void display_danger(uint8_t enable)
{
    if(enable == 1)
    {
        Lcd_show_bmp(DETECT_LOGO_X, DETECT_LOGO_Y, R1_LOGO);
        LCD_ShowChinese(94, 130, (uint8_t *)"Σ��", RED, BLACK, 24, 1);
    }
    else if(enable == 0)
    {
        LCD_Fill(DETECT_LOGO_X, DETECT_LOGO_Y, DETECT_LOGO_X + 84, DETECT_LOGO_Y + 84, BLACK);
        LCD_Fill(94, 130, 94 + 48, 130 + 24, BLACK);
    }
}

/*��ʾ��������*/
void Display_Process_Bar_Frame(int enable)
{
    if(enable == 1)
    {
        LCD_Draw_ColorRect(10, 180, 230, 190, BLUE);
        LCD_Fill(12, 182, 228, 188, BLACK);
    }
    else if(enable == 0)
    {
        LCD_Draw_ColorRect(10, 180, 230, 190, BLACK);
        LCD_Fill(12, 182, 228, 188, BLACK);
    }
}

/*��ʾ1����0������*/
void Display_Process_Bar(int Process, int enable)
{
    uint8_t buf[] = {20, 40, 80, 100, 120, 140, 160, 180, 200, 228};

    if(enable == 1)
    {
        LCD_Fill(12, 182, buf[Process / 10], 188, GREEN);
    }
    else if(enable == 0)
    {
        Display_Process_Bar_Frame(enable);
        LCD_Fill(12, 182, buf[9], 188, BLACK);
    }
}

/*��ʾ�̸�ֵ*/
void display_smoke_value(int smoke_value, uint16_t color, uint8_t enable)
{
    char display_buf[20] = {0};
    memset(display_buf, 0, 20);
    sprintf(display_buf, "%04dppm", smoke_value);
	/*�����˵��Ա�־�Ż���ʾ�̸�ֵ*/
	if(User_Memory_Para.debug_flag == 1)
	{
		if(enable == 1)
			LCD_ShowCharStr(SMOKE_X, SMOKE_Y, 100, display_buf, BLACK, color, 24);
		else if(enable == 0)
			LCD_ShowCharStr(SMOKE_X, SMOKE_Y, 100, display_buf, BLACK, BLACK, 24);
	}
}


/*����ҳ���ʼ��*/
void test_page_init(void)
{
    Flow_Cursor.flow_cursor = TEST_PAGE ;
    /*������������̳�ʼ��*/
    Sensor_Detect_Init();
    /*��ʾ��׼*/
    display_base(1);
    display_smoke_value(0, GREEN, 1);
}

/*����ҳ���¼�����*/
void test_page_process(uint8_t Event_Code)
{
    switch(Event_Code)
    {
        /*���¿�ʼ����*/
        case LEFT:
            /*������������̳�ʼ��*/
            Sensor_Detect_Init();
            mq2_sensor_interface.led_control(&mq2_sensor_interface, 0);
            mq2_sensor_interface.buzzer_control(&mq2_sensor_interface, 0);
            Display_Process_Bar(0, 0);
            display_smoke_value(0, BLACK, 0);
            LCD_Fill(94, 130, 94 + 48, 130 + 24, BLACK);
            /*��ʾ��׼*/
            display_base(1);
            break ;

        /*�˳�*/
        case RIGHT:
            tos_knl_sched_lock();
            Sensor_Flow_Cursor.Start_Detect = 0 ;
            Sensor_Flow_Cursor.Count_Alarm = 0 ;
            Sensor_Flow_Cursor.Test_Process = 0 ;
            Sensor_Flow_Cursor.Detect_Step = NULL_STATUS ;
            mq2_sensor_interface.led_control(&mq2_sensor_interface, 0);
            mq2_sensor_interface.buzzer_control(&mq2_sensor_interface, 0);
            LCD_Clear(BLACK);
            Flow_Cursor.flow_cursor = MAIN_PAGE ;
            main_page_init();
            tos_knl_sched_unlock();
            break ;

        default:
            break ;
    }
}

