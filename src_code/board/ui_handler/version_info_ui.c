#include "version_info_ui.h"

static void Handle_Version_Info_Page_Left_Key(void);
static void Handle_Version_Info_Page_Left_Long_Key(void);
static void Handle_Version_Info_Page_Right_Key(void);
static void Handle_Version_Info_Page_Right_Long_Key(void);
Event_Frame Version_Info_Page_Event[] = 
{
	{Handle_Version_Info_Page_Left_Key},
	{Handle_Version_Info_Page_Left_Long_Key},
	{Handle_Version_Info_Page_Right_Key},
	{Handle_Version_Info_Page_Right_Long_Key},
};

Type Package_Type[] =
{
    {0x00000, "LQFP64"},
    {0x00001, "WLCSP64"},
    {0x00010, "LQFP100"},
    {0x00101, "WLCSP36"},
    {0x01000, "UFQFPN32"},
    {0x01001, "LQFP32"},
    {0x01010, "UFQFPN48"},
    {0x01011, "LQFP48"},
    {0x01100, "WLCSP49"},
    {0x01101, "UFBGA64"},
    {0x01110, "UFBGA100"},
    {0x01111, "WLCSP36 with external SMPS"},
    {0x10110, "LQFP64 with external SMPS"},
};

version_para version_para_info ;

/*版本信息显示参数*/
LCD_Ascii_Show_Para ascii_show_para[] =
{
	/*显示*/
    {VERSION1_TEXT_START_X, VERSION1_TEXT_START_Y, 240, version_para_info.id, BLACK, RED, VERSION1_TEXT_FONT},
    {VERSION2_TEXT_START_X, VERSION2_TEXT_START_Y, 240, version_para_info.flash_size, BLACK, RED, VERSION2_TEXT_FONT},
    {VERSION3_TEXT_START_X, VERSION3_TEXT_START_Y, 240, version_para_info.Mcu_Package, BLACK, RED, VERSION3_TEXT_FONT},
	/*隐藏*/
    {VERSION1_TEXT_START_X, VERSION1_TEXT_START_Y, 240, version_para_info.id, BLACK, BLACK, VERSION1_TEXT_FONT},
    {VERSION2_TEXT_START_X, VERSION2_TEXT_START_Y, 240, version_para_info.flash_size, BLACK, BLACK, VERSION2_TEXT_FONT},
    {VERSION3_TEXT_START_X, VERSION3_TEXT_START_Y, 240, version_para_info.Mcu_Package, BLACK, BLACK, VERSION3_TEXT_FONT}
};

/*显示1隐藏0版本信息*/
void display_version_info(int enable)
{
    uint32_t Type_Value = 0 ;
    memset(version_para_info.id, 0, 50);
    memset(version_para_info.flash_size, 0, 20);
    memset(version_para_info.Mcu_Package, 0, 20);
    sprintf(version_para_info.id, "id:0x%x %x %x", \
            * (__IO uint32_t *)0x1FFF7590, \
            * (__IO uint32_t *)0x1FFF7590 + 0x04, \
            * (__IO uint32_t *)0x1FFF7590 + 0x08);
    sprintf(version_para_info.flash_size, "flash_size:%dKB", *(__IO uint16_t *)0x1FFF75E0);
    Type_Value = *(__IO uint32_t *)0x1FFF7500 & 0x1f ;

    for(int i = 0 ; i < sizeof(Package_Type) / sizeof(Package_Type[0]); i++)
    {
        if(Type_Value == Package_Type[i].value)
        {
            sprintf(version_para_info.Mcu_Package, "Mcu_Package:%s", Package_Type[i].Name);
            break ;
        }
    }

    if(enable == 1)
    {
		for(int i = 0 ; i < 3 ; i++)
			lcd_model.lcd_driver->lcd_show_ascii_str(ascii_show_para[i]);
    }
    else if(enable == 0)
    {
        for(int i = 3 ; i < 6 ; i++)
			lcd_model.lcd_driver->lcd_show_ascii_str(ascii_show_para[i]);
    }
}

/*版本信息页面初始化*/
void Version_Info_Page_Init(void)
{
    Flow_Cursor.flow_cursor = VERSION_PAGE ;
    display_version_info(1);
}


/*按键逻辑处理*/
static void Handle_Version_Info_Page_Left_Key(void)
{
	 display_version_info(0);
     conf_page_ui_init(3);
}

static void Handle_Version_Info_Page_Left_Long_Key(void)
{
	 display_version_info(0);
     conf_page_ui_init(3);
}

static void Handle_Version_Info_Page_Right_Key(void)
{
	 display_version_info(0);
     conf_page_ui_init(3);
}

static void Handle_Version_Info_Page_Right_Long_Key(void)
{
	 display_version_info(0);
     conf_page_ui_init(3);
}

/*版本信息按键操作*/
void version_info_page_process(uint8_t KeyValue)
{
	Version_Info_Page_Event[KeyValue-1].handler_func();
}
