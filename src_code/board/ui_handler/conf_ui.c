#include "conf_ui.h"

Conf_Page conf_page_ui ;

/*����ҳ��˵�����ʾ*/
Item Conf_Item_Display[] =
{
    /*��ʾ*/
    {70, 73,  "ϵͳ����", WHITE, BLACK, 24, 1},		//0		/*�����ֵ===>�͡��С���*/
    {70, 102, "ʱ������", WHITE, BLACK, 24, 1},		//1		/*������LED����ֵ��ʾ*/
    {70, 131, "��������", WHITE, BLACK, 24, 1},		//2		/*������*/
    {70, 160, "������Ϣ", WHITE, BLACK, 24, 1},		//3		/*��ʾ�汾�š�ROM��RAM����Ϣ*/
    /*����*/
    {70, 73,  "ϵͳ����", BLACK, BLACK, 24, 1},		//4		/*�����ֵ===>�͡��С���*/
    {70, 102, "ʱ������", BLACK, BLACK, 24, 1},		//5		/*������LED����ֵ��ʾ*/
    {70, 131, "��������", BLACK, BLACK, 24, 1},		//6		/*������*/
    {70, 160, "������Ϣ", BLACK, BLACK, 24, 1},		//7		/*��ʾ�汾�š�ROM��RAM����Ϣ*/
};

/*ѡ��˵���Ŀ*/

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

//����ҳ���ʼ��
void conf_page_ui_init(uint8_t item)
{
    Flow_Cursor.flow_cursor = CONF_PAGE ;
    conf_page_ui.select_item = item ;

    for(int i = 0 ; i < 4 ; i++)
        display_menu_item(Conf_Item_Display, i);

    select_conf_item(conf_page_ui.select_item, RED);
}

//����ĳһ������
void enter_conf_item(uint8_t item)
{
    switch(item)
    {
        //ϵͳ����
        case 0:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*ϵͳ����ҳ���ʼ��*/
            para_setting_page_init();
            break ;

        //ʱ������
        case 1:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*ʱ��ҳ���ʼ��*/
            break ;

        //��������
        case 2:

            for(int i = 4 ; i < 8 ; i++)
                display_menu_item(Conf_Item_Display, i);

            select_conf_item(conf_page_ui.select_item, BLACK);
            /*����ҳ���ʼ��*/
            password_page_init();
            break ;

        //������Ϣ
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
            lcd_model.lcd_driver->lcd_display_onoff(0);
            enter_conf_item(conf_page_ui.select_item);
            lcd_model.lcd_driver->lcd_display_onoff(1);
            break ;

        //�˳��˵��ص����˵�
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






