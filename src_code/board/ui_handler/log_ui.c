#include "log_ui.h"

/*��¼��ѯ*/
#define LOG_TITLE_X  		67
#define LOG_TITLE_Y	 		40

/*���*/
#define SERIAL_NUM_X		0
#define SERIAL_NUM_Y		90

/*���ʱ��*/
#define DETECT_DATETIME_X	0
#define DETECT_DATETIME_Y	135

/*�����*/
#define DETECT_RESULT_X		0
#define DETECT_RESULT_Y		180

/*�޼�¼*/
#define NO_LOG_TITLE_X 		74
#define NO_LOG_TITLE_Y 		105

/*��¼��ѯҳ��˵�����ʾ*/
Item Log_Item[] =
{
    {LOG_TITLE_X, LOG_TITLE_Y, 				"��¼��ѯ", WHITE, BLACK, 24, 1},		//0
    {SERIAL_NUM_X, SERIAL_NUM_Y, 			"���", 	WHITE, BLACK, 24, 1},		//1
    {DETECT_DATETIME_X, DETECT_DATETIME_Y,  "���ʱ��", 	WHITE, BLACK, 24, 1},	//2
    {DETECT_RESULT_X, DETECT_RESULT_Y, 		"�����", 	WHITE, BLACK, 24, 1},	//3

    {LOG_TITLE_X, LOG_TITLE_Y, 				"��¼��ѯ", BLACK, BLACK, 24, 1},		//4
    {SERIAL_NUM_X, SERIAL_NUM_Y, 			"���", 	BLACK, BLACK, 24, 1},		//5
    {DETECT_DATETIME_X, DETECT_DATETIME_Y,  "���ʱ��", 	BLACK, BLACK, 24, 1},	//6
    {DETECT_RESULT_X, DETECT_RESULT_Y, 		"�����", 	BLACK, BLACK, 24, 1},	//7
};

/*��¼��ѯҳ��״̬��ʾ*/
Item Log_Status_Item[] =
{
    {NO_LOG_TITLE_X, NO_LOG_TITLE_Y, 		"�޼�¼", WHITE, BLACK, 32, 1},		//0
    {NO_LOG_TITLE_X, NO_LOG_TITLE_Y, 		"�޼�¼", BLACK, BLACK, 32, 1},		//1
};

/*��ʾ��¼ҳ������*/
static void Display_log_setting_page_item_font(int item, uint16_t color)
{
    LCD_ShowChinese(Log_Item[item].x, Log_Item[item].y,
                    Log_Item[item].Str, color,
                    Log_Item[item].back_color, Log_Item[item].font_num, Log_Item[item].mode);
}

/*��¼ҳ����ʾ1����0*/
void log_item_display(uint8_t enable)
{
    if(enable == 1)
    {
        for(int i = 0 ; i < 4 ; i++)
            Display_log_setting_page_item_font(i, WHITE);

        /*��ʾ���ð��*/
        LCD_ShowCharStr(SERIAL_NUM_X + 48, SERIAL_NUM_Y, 125, ":", BLACK, WHITE, 24);
        /*��ʾ���ʱ��ð��*/
        LCD_ShowCharStr(DETECT_DATETIME_X + 96, DETECT_DATETIME_Y, 125, ":", BLACK, WHITE, 24);
        /*��ʾ�����ð��*/
        LCD_ShowCharStr(DETECT_RESULT_X + 96, DETECT_RESULT_Y, 125, ":", BLACK, WHITE, 24);
    }
    else if(enable == 0)
    {
        for(int i = 4 ; i < 8 ; i++)
            Display_log_setting_page_item_font(i, BLACK);

        /*��ʾ���ð��*/
        LCD_ShowCharStr(SERIAL_NUM_X + 48, SERIAL_NUM_Y, 125, ":", BLACK, BLACK, 24);
        /*��ʾ���ʱ��ð��*/
        LCD_ShowCharStr(DETECT_DATETIME_X + 96, DETECT_DATETIME_Y, 125, ":", BLACK, BLACK, 24);
        /*��ʾ�����ð��*/
        LCD_ShowCharStr(DETECT_RESULT_X + 96, DETECT_RESULT_Y, 125, ":", BLACK, BLACK, 24);
    }
}

/*��ʾ�޼�¼*/
void display_no_log(uint8_t enable)
{
    if(enable == 1)
    {
        LCD_ShowChinese(Log_Status_Item[0].x, Log_Status_Item[0].y,
                        Log_Status_Item[0].Str, Log_Status_Item[0].front_color,
                        Log_Status_Item[0].back_color, Log_Status_Item[0].font_num, Log_Status_Item[0].mode);
    }
    else if(enable == 0)
    {
        LCD_ShowChinese(Log_Status_Item[1].x, Log_Status_Item[1].y,
                        Log_Status_Item[1].Str, Log_Status_Item[1].front_color,
                        Log_Status_Item[1].back_color, Log_Status_Item[1].font_num, Log_Status_Item[1].mode);
    }
}

/*��ʾ���*/
static void display_log_serial_number(int serial_number, uint8_t enable)
{
    char buf[10] = {0};
    memset(buf, 0, 10);
    sprintf(buf, "%05d", serial_number);

    if(enable == 1)
        LCD_ShowCharStr(SERIAL_NUM_X + 60, SERIAL_NUM_Y, 100, buf, BLACK, WHITE, 24);
    else if(enable == 0)
        LCD_ShowCharStr(SERIAL_NUM_X + 60, SERIAL_NUM_Y, 100, buf, BLACK, BLACK, 24);
}

/*��ʾ������ں�ʱ��*/
static void display_log_detect_datetime(int year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t enable)
{
    char buf[20] = {0};
    memset(buf, 0, 10);
    sprintf(buf, "%02d%02d%02d%02d%02d", year - 2000, month, day, hour, minute);

    if(enable == 1)
        LCD_ShowCharStr(DETECT_DATETIME_X + 108, DETECT_DATETIME_Y, 120, buf, BLACK, WHITE, 24);
    else if(enable == 0)
        LCD_ShowCharStr(DETECT_DATETIME_X + 108, DETECT_DATETIME_Y, 120, buf, BLACK, BLACK, 24);
}

/*��ʾ�����*/
static void display_log_detect_result(uint8_t result, uint8_t enable)
{
    char buf[10] = {0};
    memset(buf, 0, 10);
		LCD_Fill(DETECT_RESULT_X+108, DETECT_RESULT_Y, DETECT_RESULT_X+108+ 48, DETECT_RESULT_Y+24, BLACK);
    if(enable == 1)
    {
        if(result == 0)
            LCD_ShowChinese(DETECT_RESULT_X + 108, DETECT_RESULT_Y,	\
                            (uint8_t *)"��ȫ", WHITE, BLACK, 24, 1);
        else if(result == 1)
            LCD_ShowChinese(DETECT_RESULT_X + 108, DETECT_RESULT_Y,	\
                            (uint8_t *)"Σ��", WHITE, BLACK, 24, 1);
    }
    else if(enable == 0)
    {
        LCD_ShowChinese(DETECT_RESULT_X + 108, DETECT_RESULT_Y,	\
                        (uint8_t *)"��ȫ", BLACK, BLACK, 24, 0);
        LCD_ShowChinese(DETECT_RESULT_X + 108, DETECT_RESULT_Y,	\
                        (uint8_t *)"Σ��", BLACK, BLACK, 24, 0);
    }
}

/*��¼��ѯ���ݳ�ʼ��*/
void log_page_data_init(void)
{
    /*��ȡ��ǰ������ˮ��*/
    csv_file_record.Current_Serial_Number = \
                                            User_Memory_Para.detetct_log_serial_number ;

    if(0 == csv_file_record.Current_Serial_Number % DETECT_DATA_INDEX)
    {
        csv_file_record.file_number_index = \
                                            csv_file_record.Current_Serial_Number / DETECT_DATA_INDEX - 1 ;
    }
    else
    {
        csv_file_record.file_number_index = \
                                            csv_file_record.Current_Serial_Number / DETECT_DATA_INDEX;
    }

    /*���㵱ǰ������λ�ڸ��ļ��ĵڼ���*/
    if((csv_file_record.Current_Serial_Number % DETECT_DATA_INDEX == 0) \
            && (csv_file_record.Current_Serial_Number >= DETECT_DATA_INDEX))
    {
        csv_file_record.Current_Line = \
                                       csv_file_record.Current_Serial_Number % \
                                       DETECT_DATA_INDEX + DETECT_DATA_INDEX;
    }
    else
    {
        csv_file_record.Current_Line = \
                                       csv_file_record.Current_Serial_Number % \
                                       DETECT_DATA_INDEX ;
    }

    /*��ǰû���κ�����*/
    if(0 == csv_file_record.Current_Serial_Number)
    {
        DEBUG("��ǰ�޼�¼����...\n");
        display_no_log(1);
    }
    /*��ǰ������*/
    else
    {
        log_item_display(1);
        /*��ʾ���¼��õ���һ�����ݣ���Ҫ����õ���ǰλ���ĸ��ļ��������Լ���ǰλ����һ��*/
        ReadlLineData(csv_file_record.file_number_index, csv_file_record.Current_Line);
        /*��ʾ��¼�洢��*/
        display_log_serial_number(csv_file_record.Current_Serial_Number, 1);
        display_log_detect_datetime(csv_file_record.year, csv_file_record.month,
                                    csv_file_record.day, csv_file_record.hour, csv_file_record.minute, 1);
        display_log_detect_result(csv_file_record.detect_result, 1);
        /*��ʾ��¼�洢��*/
    }
}

/*��¼��ѯҳ���ʼ��*/
void log_page_init(void)
{
    Flow_Cursor.flow_cursor = LOG_PAGE ;
    log_page_data_init();
}


/*��¼ҳ��������ǰ������*/
void log_page_data_prev_next_handler(uint8_t KeyValue)
{
    int ret = -1 ;

    switch(KeyValue)
    {
        case LEFT:
            (csv_file_record.Current_Serial_Number > 1) ?	\
            (csv_file_record.Current_Serial_Number--) :	\
            (csv_file_record.Current_Serial_Number = 1);

            /*���㵱ǰ������λ�ڸ��ļ�������===>������1*/
            if(0 == csv_file_record.Current_Serial_Number % 100)
                csv_file_record.file_number_index = csv_file_record.Current_Serial_Number / 100 - 1 ;
            else
                csv_file_record.file_number_index = csv_file_record.Current_Serial_Number / 100 ;

            /*���㵱ǰ������λ�ڸ��ļ��ĵڼ���*/
            if((csv_file_record.Current_Serial_Number % 100 == 0) && (csv_file_record.Current_Serial_Number >= 100))
                csv_file_record.Current_Line = csv_file_record.Current_Serial_Number % 100 + 100;
            else
                csv_file_record.Current_Line = csv_file_record.Current_Serial_Number % 100 ;

            ret = ReadlLineData(csv_file_record.file_number_index, csv_file_record.Current_Line);

            if(ret > 0)
            {
                DEBUG("�ļ�����:%d ��ǰ��ˮ��:%d  λ���ļ��ĵ�%d��\n", csv_file_record.file_number_index,
                      csv_file_record.Current_Serial_Number, csv_file_record.Current_Line);
                display_log_serial_number(csv_file_record.Current_Serial_Number, 1);
                display_log_detect_datetime(csv_file_record.year, csv_file_record.month,
                                            csv_file_record.day, csv_file_record.hour, csv_file_record.minute, 1);
                display_log_detect_result(csv_file_record.detect_result, 1);
            }

            break ;

        case RIGHT:
            (csv_file_record.Current_Serial_Number < User_Memory_Para.detetct_log_serial_number) ?	\
            (csv_file_record.Current_Serial_Number++) :	\
            (csv_file_record.Current_Serial_Number = User_Memory_Para.detetct_log_serial_number);

            /*���㵱ǰ������λ�ڸ��ļ�������*/
            if(0 == csv_file_record.Current_Serial_Number % 100)
                csv_file_record.file_number_index = csv_file_record.Current_Serial_Number / 100 - 1 ;
            else
                csv_file_record.file_number_index = csv_file_record.Current_Serial_Number / 100 ;

            /*���㵱ǰ������λ�ڸ��ļ��ĵڼ���*/
            if((csv_file_record.Current_Serial_Number % 100 == 0) && (csv_file_record.Current_Serial_Number >= 100))
                csv_file_record.Current_Line = csv_file_record.Current_Serial_Number % 100 + 100;
            else
                csv_file_record.Current_Line = csv_file_record.Current_Serial_Number % 100 ;

            ret = ReadlLineData(csv_file_record.file_number_index, csv_file_record.Current_Line);

            if(ret > 0)
            {
                DEBUG("�ļ�����:%d ��ǰ��ˮ��:%d  λ���ļ��ĵ�%d��\n", csv_file_record.file_number_index,
                      csv_file_record.Current_Serial_Number, csv_file_record.Current_Line);
                display_log_serial_number(csv_file_record.Current_Serial_Number, 1);
                display_log_detect_datetime(csv_file_record.year, csv_file_record.month,
                                            csv_file_record.day, csv_file_record.hour, csv_file_record.minute, 1);
                display_log_detect_result(csv_file_record.detect_result, 1);
            }

            break ;
    }
}


/*��¼ҳ�水������*/
void log_page_process(uint8_t KeyValue)
{
    switch(KeyValue)
    {
        /*��ǰ����¼����*/
        case LEFT:
            if(csv_file_record.Current_Serial_Number != 0)
                log_page_data_prev_next_handler(KeyValue);

            break ;

        /*��󷭼�¼����*/
        case RIGHT:
            if(csv_file_record.Current_Serial_Number != 0)
                log_page_data_prev_next_handler(KeyValue);

            break ;

        /*�����˻���ҳ���¼ѡ��*/
        case RIGHT_LONG:
            log_item_display(0);

            /*��������޼�¼��ʾ��ҳ�棬�˳�ʱҪ����ѡ��*/
            if(csv_file_record.Current_Serial_Number == 0)
                display_no_log(0);
            /*���ؼ�¼����ѡ��*/
            else
            {
                display_log_serial_number(csv_file_record.Current_Serial_Number, 0);
                display_log_detect_datetime(csv_file_record.year, csv_file_record.month,
                                            csv_file_record.day, csv_file_record.hour, csv_file_record.minute, 0);
                display_log_detect_result(csv_file_record.detect_result, 0);
            }

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
            break ;

        default:
            break ;
    }
}


