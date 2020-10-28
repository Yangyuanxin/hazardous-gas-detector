#include "para.h"
#include "iniparser.h"

dictionary  *Config_ini = NULL;
Conf_Para User_Memory_Para ;

/*Ĭ��ϵͳ������Ϣ*/
char *System_Config_Info =
{
    "[Setting]\n"
    "Vol_flag=1;\n"					/*����������*/
    "Sensivity=1;\n"				/*�����ȼ���  0:�� 1:�� 2:��*/
    "Debug_flag=1;\n"				/*���Ա�־*/
    "Detect_Log_Serial_Number=0;\n"	/*���������ˮ��*/
    "SENSIVITY_LOW    = 1000;\n"    /*��������*/
    "SENSIVITY_MEDIUM = 300;\n"     /*��������*/
    "SENSIVITY_HIGH   = 200;\n"     /*��������*/
};

/*����һ��Ĭ�ϵ������ļ�*/
static void Create_Default_InI_File(void)
{
    retUSER_SYS_CONFIG = f_open(&USER_SYS_CONFIG_File, SETTING_PARA, FA_OPEN_ALWAYS | FA_WRITE);

    if(FR_OK != retUSER_SYS_CONFIG)
    {
        fprintf(stderr, "iniparser: cannot open %s\n", SETTING_PARA);
        return ;
    }

    f_printf(&USER_SYS_CONFIG_File, System_Config_Info);
    f_close(&USER_SYS_CONFIG_File);
}

/*����ϵͳ����*/
static void Load_System_Para(void)
{
    /*����*/
    User_Memory_Para.volume = iniparser_getint(Config_ini, "Setting:Vol_flag", -1);

    if(-1 == User_Memory_Para.volume)
        User_Memory_Para.volume = 1 ;

    /*������*/
    User_Memory_Para.sensivity = iniparser_getint(Config_ini, "Setting:Sensivity", -1);

    if(-1 == User_Memory_Para.sensivity)
        User_Memory_Para.sensivity = 1 ;

    /*���Ա�־*/
    User_Memory_Para.debug_flag = iniparser_getint(Config_ini, "Setting:Debug_flag", -1);

    if(-1 == User_Memory_Para.debug_flag)
        User_Memory_Para.debug_flag = 1 ;

    DEBUG("����:%d\n", User_Memory_Para.volume);
    DEBUG("������:%d\n", User_Memory_Para.sensivity);
    DEBUG("���Ա�־:%d\n", User_Memory_Para.debug_flag);

    /*����¼��ˮ��*/
    User_Memory_Para.detetct_log_serial_number = iniparser_getint(Config_ini, "Setting:Detect_Log_Serial_Number", -1);

    if(-1 == User_Memory_Para.detetct_log_serial_number)
        User_Memory_Para.detetct_log_serial_number = 0 ;

    DEBUG("�����ˮ��:%d\n", User_Memory_Para.detetct_log_serial_number);
    User_Memory_Para.alarm_threshold[0] = \
                                          iniparser_getint(Config_ini, "Setting:SENSIVITY_LOW", -1);
    User_Memory_Para.alarm_threshold[1] = \
                                          iniparser_getint(Config_ini, "Setting:SENSIVITY_MEDIUM", -1);
    User_Memory_Para.alarm_threshold[2] = \
                                          iniparser_getint(Config_ini, "Setting:SENSIVITY_HIGH", -1);

    for(int i = 0 ; i < 3 ; i++)
    {
        if(-1 == User_Memory_Para.alarm_threshold[i])
        {
            User_Memory_Para.alarm_threshold[0] = 1000 ;
            User_Memory_Para.alarm_threshold[1] = 300 ;
            User_Memory_Para.alarm_threshold[2] = 200 ;
            break ;
        }
    }

    for(int i = 0 ; i < 3 ; i++)
        DEBUG("������:%d  ��ֵ:%d\n", i, User_Memory_Para.alarm_threshold[i]);
}

/*���������ļ�*/
void Load_Config_ini_File(void)
{
    Config_ini = iniparser_load(SETTING_PARA);

    /*�����ʧ���ˣ��򴴽�һ��ȫ�µ�ini�����ļ���Ȼ�������ļ����к����Ľ�������*/
    if(NULL == Config_ini)
    {
        DEBUG("cannot parse %s file\n", SETTING_PARA);
        Create_Default_InI_File();
        Config_ini = iniparser_load(SETTING_PARA);

        if(NULL == Config_ini)
        {
            DEBUG("����Ĭ��INI�ļ���������س���\n");
            return  ;
        }
    }

    DEBUG("����INI�ļ��ɹ�\n");
    /*����ϵͳ����*/
    Load_System_Para();
}

/*���õ���*/
void setting_debug(uint8_t status)
{
    char buf[5] = {0};
    memset(buf, 0, 5);
    sprintf(buf, "%d", status);
    User_Memory_Para.debug_flag = status ;
    iniparser_set(Config_ini, "Setting:Debug_flag", buf);
    DEBUG("���õ���:%d\r\n", iniparser_getint(Config_ini, "Setting:Debug_flag", -1));
    User_Para_Save_Process();
}

/*��������*/
void setting_volume(uint8_t status)
{
    char buf[5] = {0};
    memset(buf, 0, 5);
    sprintf(buf, "%d", status);
    User_Memory_Para.volume = status ;
    iniparser_set(Config_ini, "Setting:Vol_flag", buf);
    DEBUG("��������:%d\r\n", iniparser_getint(Config_ini, "Setting:Vol_flag", -1));
    User_Para_Save_Process();
}

/*����������*/
void setting_sensivity(uint8_t status)
{
    char buf[5] = {0};
    memset(buf, 0, 5);
    sprintf(buf, "%d", status);
    User_Memory_Para.sensivity = status ;
    iniparser_set(Config_ini, "Setting:Sensivity", buf);
    DEBUG("����������:%d\r\n", iniparser_getint(Config_ini, "Setting:Sensivity", -1));
    User_Para_Save_Process();
}


/*������ֵ*/
void Alarm_Threhold_Setting(void)
{
    char buf1[5] = {0};
    char buf2[5] = {0};
    char buf3[5] = {0};
    sprintf(buf1, "%d", User_Memory_Para.alarm_threshold[0]);
    sprintf(buf2, "%d", User_Memory_Para.alarm_threshold[1]);
    sprintf(buf3, "%d", User_Memory_Para.alarm_threshold[2]);

    iniparser_set(Config_ini, "Setting:SENSIVITY_LOW", buf1);		/*��������*/
    iniparser_set(Config_ini, "Setting:SENSIVITY_MEDIUM", buf2);	/*��������*/
    iniparser_set(Config_ini, "Setting:SENSIVITY_HIGH", buf3);		/*��������*/
    User_Para_Save_Process();
}

/*��¼��ˮ�ű��洦��*/
void User_Detect_Log_Save_Process(void)
{
    char buf[5] = {0};
    memset(buf, 0, 5);
    sprintf(buf, "%d", User_Memory_Para.detetct_log_serial_number);
    iniparser_set(Config_ini, "Setting:Detect_Log_Serial_Number", buf);
    DEBUG("���ü����ˮ��:%d\r\n", iniparser_getint(Config_ini, "Setting:Detect_Log_Serial_Number", -1));
    User_Para_Save_Process();
}

/*�û��������洦��*/
void User_Para_Save_Process(void)
{
    //����ϵͳ����
    tos_knl_sched_lock();
    /*write config.ini parse*/
    retUSER_SYS_CONFIG = f_open(&USER_SYS_CONFIG_File, SETTING_PARA, FA_OPEN_EXISTING | FA_WRITE);

    if(FR_OK != retUSER_SYS_CONFIG)
    {
        printf("iniparser: cannot open %s\n", SETTING_PARA);
        return ;
    }

    printf("�������ñ���ɹ�\n");
    iniparser_dump_ini(Config_ini, &USER_SYS_CONFIG_File);
    f_close(&USER_SYS_CONFIG_File);
    iniparser_freedict(Config_ini);
    Load_Config_ini_File();
    //����ϵͳ����
    tos_knl_sched_unlock();
}

