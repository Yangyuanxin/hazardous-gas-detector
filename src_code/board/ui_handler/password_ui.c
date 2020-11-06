#include "password_ui.h"

Password_Page password_page_ui ;

Item Password_Item[] =
{
    {INPUT_PASSWD_TEXT_START_X, INPUT_PASSWD_TEXT_START_Y, "����������", BLACK, BLACK, INPUT_PASSWD_TEXT_FONT, 1},		//0  ����
    {INPUT_PASSWD_TEXT_START_X, INPUT_PASSWD_TEXT_START_Y, "����������", WHITE, BLACK, INPUT_PASSWD_TEXT_FONT, 1},		//1  ��ʾ
};

/*��ʾ1/����0�������������*/
void password_input_item_display(int enable)
{
    if(enable == 1)
        display_menu_color_item(Password_Item, 1, Password_Item[1].front_color);
    else if(enable == 0)
        display_menu_color_item(Password_Item, 0, Password_Item[0].front_color);
}

/*��ʾ������ֵ*/
void password_number_display(int enable)
{
	 LCD_Ascii_Show_Para password_ascii[] =
    {
        {NUM_ONE_TEXT_X, NUM_ONE_TEXT_Y, 125, password_page_ui.display_buf, BLACK, RED, NUM_ONE_TEXT_FONT},
		{NUM_TWO_TEXT_X, NUM_TWO_TEXT_Y, 125, password_page_ui.display_buf, BLACK, WHITE, NUM_TWO_TEXT_FONT},
		{NUM_THREE_TEXT_X, NUM_THREE_TEXT_Y, 20, password_page_ui.display_buf, BLACK, WHITE, NUM_THREE_TEXT_FONT},
		
		{NUM_ONE_TEXT_X, NUM_ONE_TEXT_Y, 125, password_page_ui.display_buf, BLACK, BLACK, NUM_ONE_TEXT_FONT},
		{NUM_TWO_TEXT_X, NUM_TWO_TEXT_Y, 125, password_page_ui.display_buf, BLACK, BLACK, NUM_TWO_TEXT_FONT},
		{NUM_THREE_TEXT_X, NUM_THREE_TEXT_Y, 20, password_page_ui.display_buf, BLACK, BLACK, NUM_THREE_TEXT_FONT},
    };
	
    if(enable == 1)
    {
        memset(password_page_ui.Password, 0, 3);

        memset(password_page_ui.display_buf, 0, 10);
        sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[0]);
		lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[0]);

        memset(password_page_ui.display_buf, 0, 10);
        sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[1]);
        lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[1]);

        memset(password_page_ui.display_buf, 0, 10);
        sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[2]);
        lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[2]);
    }
    else if(enable == 0)
    {
		for(int i = 3 ; i < 6 ; i++)
			lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[i]);
    }
}


/*���������ʼ��*/
void password_page_para_init(void)
{
    password_page_ui.select_item = 0 ;
    memset(password_page_ui.display_buf, 0, 10);
    memset(password_page_ui.Password, 0, 3);
}

/*�������ó�ʼ��*/
void password_page_init(void)
{
    Flow_Cursor.flow_cursor = PASSWD_PAGE ;
    password_page_para_init();
    password_input_item_display(1);
    password_number_display(1);
}

/*ѡ�о�������λ��������*/
void select_password_item(int item)
{
	 LCD_Ascii_Show_Para password_ascii[] =
    {
        {NUM_ONE_TEXT_X, NUM_ONE_TEXT_Y, 125, password_page_ui.display_buf, BLACK, WHITE, NUM_ONE_TEXT_FONT},
		{NUM_TWO_TEXT_X, NUM_TWO_TEXT_Y, 125, password_page_ui.display_buf, BLACK, WHITE, NUM_TWO_TEXT_FONT},
		{NUM_THREE_TEXT_X, NUM_THREE_TEXT_Y, 20, password_page_ui.display_buf, BLACK, WHITE, NUM_THREE_TEXT_FONT},
		
		{NUM_ONE_TEXT_X, NUM_ONE_TEXT_Y, 125, password_page_ui.display_buf, BLACK, RED, NUM_ONE_TEXT_FONT},
		{NUM_TWO_TEXT_X, NUM_TWO_TEXT_Y, 125, password_page_ui.display_buf, BLACK, RED, NUM_TWO_TEXT_FONT},
		{NUM_THREE_TEXT_X, NUM_THREE_TEXT_Y, 20, password_page_ui.display_buf, BLACK, RED, NUM_THREE_TEXT_FONT},
    };
	
	
    memset(password_page_ui.display_buf, 0, 10);
    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[0]);
	lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[0]);

    memset(password_page_ui.display_buf, 0, 10);
    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[1]);
    lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[1]);

    memset(password_page_ui.display_buf, 0, 10);
    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[2]);
    lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[2]);

    switch(password_page_ui.select_item)
    {
        case 0:
            memset(password_page_ui.display_buf, 0, 10);
            sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[0]);
            lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[3]);
            break ;

        case 1:
            memset(password_page_ui.display_buf, 0, 10);
            sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[1]);
            lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[4]);
            break ;

        case 2:
            memset(password_page_ui.display_buf, 0, 10);
            sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[2]);
            lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[5]);
            break ;

        default:
            break ;
    }
}

/*��ת����һ����������*/
void jump_next_device_cail_password_item(void)
{
    switch(password_page_ui.select_item)
    {
        case 0:
            password_page_ui.select_item = 1 ;
            select_password_item(password_page_ui.select_item);
            break ;

        case 1:
            password_page_ui.select_item = 2 ;
            select_password_item(password_page_ui.select_item);
            break ;

        case 2:
            password_page_ui.select_item = 0 ;
            select_password_item(password_page_ui.select_item);
            break ;

        default:
            break ;
    }
}


/*��������ҳ�水������*/
void password_page_process(uint8_t KeyValue)
{
	LCD_Ascii_Show_Para password_ascii[] =
    {
        {NUM_ONE_TEXT_X, NUM_ONE_TEXT_Y, 125, password_page_ui.display_buf, BLACK, RED, NUM_ONE_TEXT_FONT},
		{NUM_TWO_TEXT_X, NUM_TWO_TEXT_Y, 125, password_page_ui.display_buf, BLACK, RED, NUM_TWO_TEXT_FONT},
		{NUM_THREE_TEXT_X, NUM_THREE_TEXT_Y, 20, password_page_ui.display_buf, BLACK, RED, NUM_THREE_TEXT_FONT},
    };
    switch(KeyValue)
    {
		case LEFT:
			 jump_next_device_cail_password_item();
		     break ;
        case RIGHT:
            switch(password_page_ui.select_item)
            {
                case 0:
                    (password_page_ui.Password[0] > 0) ? \
                    (password_page_ui.Password[0]--) :		\
                    (password_page_ui.Password[0] = 9);
                    memset(password_page_ui.display_buf, 0, 10);
                    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[0]);
                    lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[0]);
                    break ;

                case 1:
                    (password_page_ui.Password[1] > 0) ? \
                    (password_page_ui.Password[1]--) :		\
                    (password_page_ui.Password[1] = 9);
                    memset(password_page_ui.display_buf, 0, 10);
                    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[1]);
                    lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[1]);
                    break ;

                case 2:
                    (password_page_ui.Password[2] > 0) ? \
                    (password_page_ui.Password[2]--) :		\
                    (password_page_ui.Password[2] = 9);
                    memset(password_page_ui.display_buf, 0, 10);
                    sprintf(password_page_ui.display_buf, "%d", password_page_ui.Password[2]);
                    lcd_model.lcd_driver->lcd_show_ascii_str(password_ascii[2]);
                    break ;

                default:
                    break;
            }
            break ;

        /*�������˵���������*/
        case LEFT_LONG:
		case RIGHT_LONG:
            /*�������������õ��û�������*/
            User_Memory_Para.password[0] = password_page_ui.Password[0];
            User_Memory_Para.password[1] = password_page_ui.Password[1];
            User_Memory_Para.password[2] = password_page_ui.Password[2];
            /*�����豸����*/
            //setting_device_password(User_Memory_Para.password[0], User_Memory_Para.password[1], User_Memory_Para.password[2]);
            password_input_item_display(0);
            password_number_display(0);
            DEBUG("�������õ�����:%d%d%d\n", User_Memory_Para.password[0], User_Memory_Para.password[1], User_Memory_Para.password[2]);
            /*��������ҳ��*/
            conf_page_ui.select_item = 2 ;
			Flow_Cursor.flow_cursor = CONF_PAGE ;
			conf_page_ui_init(conf_page_ui.select_item);
            break ;

        default:
            break ;
    }
}