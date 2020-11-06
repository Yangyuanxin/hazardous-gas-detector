#include "app_init.h"
#include "adc.h"
#include "fatfs.h"
#include "rtc.h"
#include "sdmmc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_bmp.h"


FATFS fs;						  /* FatFs�ļ�ϵͳ���� */
FRESULT f_res;                    /* �ļ�������� */
#define START_LOGO	"0:/UI/start_logo/start_logo.bmp"
LCD_Driver_Model lcd_model ;

/*Ĭ������*/
#define DEFULT_TASK_SIZE				256
void default_task(void *pdata);
osThreadDef(default_task, osPriorityLow, 1, DEFULT_TASK_SIZE);

/*��������*/
#define KEY_TASK_SIZE					2000
void StartKeyTask(void  *argument);
osThreadDef(StartKeyTask, osPriorityRealtime, 1, KEY_TASK_SIZE);

/*״̬��������*/
#define STATUS_BAR_TASK_SIZE			400
void StartStatus_Bar_Task(void  *argument);
osThreadDef(StartStatus_Bar_Task, osPriorityLow, 1, STATUS_BAR_TASK_SIZE);
LCD_Bmp_Show_Para boot_logo_para ={0,0,START_LOGO};

int $Sub$$main(void)
{
	
    extern int main(void);
    extern int $Super$$main(void);
    int ret = -1 ;
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI2_Init();
    MX_USART1_UART_Init();
    MX_RTC_Init();
    MX_ADC1_Init();
    MX_TIM16_Init();
    MX_SDMMC1_SD_Init();
    MX_FATFS_Init();
	Register_Driver_Model(&lcd_model);
    PowerOn();
	lcd_model.lcd_driver->lcd_init();
    ret = Mount_SD();
    if(ret != 0)
    {
        printf("SD Card mount ERROR\r\n");
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        return -1 ;
    }
    /*��ȡ������Ϣ*/
    Load_Config_ini_File();
	lcd_model.lcd_driver->Lcd_show_bmp(boot_logo_para);
	lcd_model.lcd_driver->lcd_display_onoff(1);
    HAL_Delay(1500);
    Sensor_Register(&mq2_sensor_interface);
	lcd_model.lcd_driver->lcd_clear(BLACK);
    Menu_Init();
    //��ָʾ��
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    //�ص�������main������
    $Super$$main();
	return 0 ;
}

/*��������ϵͳ*/
void start_tencent_os(void)
{
	 /*��ʼ����ѶOS tiny�ں�*/
    osKernelInitialize();
    /*����������һ��Ĭ������*/
    osThreadCreate(osThread(default_task), NULL);
    /*����TencentOS tiny�ں�*/
    osKernelStart();
}


/*Ĭ��������*/
void default_task(void *pdata)
{
    tos_knl_sched_lock();
    /*������������*/
    osThreadCreate(osThread(StartKeyTask), NULL);
    /*����״̬������*/
    osThreadCreate(osThread(StartStatus_Bar_Task), NULL);
    tos_knl_sched_unlock();
}

/*����������*/
void StartKeyTask(void *argument)
{
    int Count_Timer = 0 ;
    __IO uint8_t KeyCode = 255;

    while(1)
    {
        /*��ȡ��ֵ*/
        GetKey(&KeyCode);

        if(255 != KeyCode)
        {
            Menu_Select_Item(Flow_Cursor.flow_cursor, KeyCode);
            KeyCode = 255 ;
        }

        /*�����ǰ�ڲ���ҳ�� && ��ʼ����־Ϊ1������봫�������ݴ���*/
        if(Flow_Cursor.flow_cursor == TEST_PAGE && Sensor_Flow_Cursor.Start_Detect == 1)
        {
            ++Count_Timer ;

            if(Count_Timer == 20)
            {
                Count_Timer = 0 ;
                mq2_sensor_interface.get_smoke_value(&mq2_sensor_interface);
                Sensor_Handler(Sensor_Flow_Cursor.Detect_Step, mq2_sensor_interface.Smoke_Value);
            }
        }

        tos_sleep_ms(5);
    }
}

/*״̬��������ʾ����*/
extern LCD_Ascii_Show_Para datatime_display_para ;
void StartStatus_Bar_Task(void *argument)
{
    while(1)
    {
        Get_Date_Time();
        sprintf(DateTime_Handler_Info.DisPlay_DateBuf, "%02d:%02d:%02d", \
                DateTime_Handler_Info.hour, DateTime_Handler_Info.minute, DateTime_Handler_Info.sec);
		lcd_model.lcd_driver->lcd_show_ascii_str(datatime_display_para);
        tos_sleep_ms(1000);
    }
}
