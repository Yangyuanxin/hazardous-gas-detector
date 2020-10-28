#include "conf_ui.h"

#define MENU_X					70+24
#define MENU_Y					43

#define PARA_SETTING_X					70
#define PARA_SETTING_Y					73

#define ALARM_SETTING_X					70
#define ALARM_SETTING_Y					102

#define DEBUG_SETTING_X					70
#define DEBUG_SETTING_Y					131

#define DEVICE_INFO_SETTING_X		70
#define DEVICE_INFO_SETTING_Y		160

//#���ַ�
#define ICON_X									70-24
#define ICON_Y									73

Conf_Page conf_page_ui ;

/*����ҳ��˵�����ʾ*/
Item Conf_Item_Title_Display[] =
{
    /*��ʾ*/
    {MENU_X, MENU_Y,  						"�˵�", GREEN, BLACK, 24, 1},
    /*����*/
    {MENU_X, MENU_Y,  						"�˵�", BLACK, BLACK, 24, 1},
};

/*����ҳ��˵�����ʾ*/
Item Conf_Item_Display[] =
{
    /*��ʾ*/
    {PARA_SETTING_X, PARA_SETTING_Y,  						"��ֵ����", WHITE, BLACK, 24, 1},		//0		/*�����ֵ===>�͡��С���*/
    {ALARM_SETTING_X, ALARM_SETTING_Y,  					"��������", WHITE, BLACK, 24, 1},		//1		/*������LED����ֵ��ʾ*/
    {DEBUG_SETTING_X, DEBUG_SETTING_Y,  					"����ģʽ", WHITE, BLACK, 24, 1},		//2		/*������*/
    {DEVICE_INFO_SETTING_X, DEVICE_INFO_SETTING_Y, "������Ϣ", WHITE, BLACK, 24, 1},		//3		/*��ʾ�汾�š�ROM��RAM����Ϣ*/
    /*����*/
    {PARA_SETTING_X, PARA_SETTING_Y,  						"��ֵ����", BLACK, BLACK, 24, 1},		//4		/*�����ֵ===>�͡��С���*/
    {ALARM_SETTING_X, ALARM_SETTING_Y,  					"��������", BLACK, BLACK, 24, 1},		//5		/*������LED����ֵ��ʾ*/
    {DEBUG_SETTING_X, DEBUG_SETTING_Y,  					"����ģʽ", BLACK, BLACK, 24, 1},		//6		/*������*/
    {DEVICE_INFO_SETTING_X, DEVICE_INFO_SETTING_Y, "������Ϣ", BLACK, BLACK, 24, 1},		//7		/*��ʾ�汾�š�ROM��RAM����Ϣ*/
};

/*ѡ��˵���Ŀ*/
void select_conf_item(uint8_t item, uint16_t color)
{
    LCD_ShowCharStr(ICON_X, PARA_SETTING_Y, 24, "*", BLACK, BLACK, 24);
    LCD_ShowCharStr(ICON_X, ALARM_SETTING_Y, 24, "*", BLACK, BLACK, 24);
    LCD_ShowCharStr(ICON_X, DEBUG_SETTING_Y, 24, "*", BLACK, BLACK, 24);
    LCD_ShowCharStr(ICON_X, DEVICE_INFO_SETTING_Y, 24, "*", BLACK, BLACK, 24);

    switch(item)
    {
        case 0:
            LCD_ShowCharStr(ICON_X, PARA_SETTING_Y, 24, "*", BLACK, color, 24);
            break ;

        case 1:
            LCD_ShowCharStr(ICON_X, ALARM_SETTING_Y, 24, "*", BLACK, color, 24);
            break ;

        case 2:
            LCD_ShowCharStr(ICON_X, DEBUG_SETTING_Y, 24, "*", BLACK, color, 24);
            break ;

        case 3:
            LCD_ShowCharStr(ICON_X, DEVICE_INFO_SETTING_Y, 24, "*", BLACK, color, 24);
            break ;

        default:
            break ;
    }
}

//����ҳ���ʼ��
void conf_page_ui_init(uint8_t item)
{
    Flow_Cursor.flow_cursor = CONF_PAGE ;

    /*Ĭ��ѡ���0��*/
    conf_page_ui.select_item = item ;
    display_menu_item(Conf_Item_Title_Display, 0);

    for(int i = 0 ; i < 4 ; i++)
        display_menu_item(Conf_Item_Display, i);

    select_conf_item(conf_page_ui.select_item, RED);

    LCD_ShowChinese(20, 208, (uint8_t *)"�����Ҽ��˳�", BLACK, BLACK, 32, 1);
}

//����ĳһ������
void enter_conf_item(uint8_t item)
{
    switch(item)
    {
        //��ֵ����
        case 0:
            display_menu_item(Conf_Item_Title_Display, 1);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            threshold_page_ui_init(0);
            break ;

        //��������
        case 1:
            display_menu_item(Conf_Item_Title_Display, 1);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            alarm_setting_page_ui_init(0);
            break ;

        //����ģʽ
        case 2:
            display_menu_item(Conf_Item_Title_Display, 1);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            debug_page_ui_init(0);
            break ;

        //������Ϣ
        case 3:
            display_menu_item(Conf_Item_Title_Display, 1);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            Version_Info_Page_Init();
            break ;

        default:
            break ;
    }
}


//����ҳ�水������
void conf_page_process(uint8_t Event_Code)
{
    switch(Event_Code)
    {
        //�л�����һ��
        case LEFT:
            (conf_page_ui.select_item < 3) ? (conf_page_ui.select_item++) : (conf_page_ui.select_item = 0);
            select_conf_item(conf_page_ui.select_item, RED);
            break ;

        //����ĳһ��
        case RIGHT:
            LCD_DisplayOff();
            enter_conf_item(conf_page_ui.select_item);
            LCD_DisplayOn();
            break ;

        //�˳��˵��ص����˵�
        case RIGHT_LONG:
            LCD_DisplayOff();
            select_conf_item(conf_page_ui.select_item, BLACK);
            LCD_ShowChinese(20, 208, (uint8_t *)"�����Ҽ��˳�", BLACK, BLACK, 32, 1);
            display_menu_item(Conf_Item_Title_Display, 1);

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            Flow_Cursor.flow_cursor = MAIN_PAGE ;
            Select_Main_Menu_Item(main_item);
            LCD_DisplayOn();
            break ;

        default:
            break ;
    }
}






