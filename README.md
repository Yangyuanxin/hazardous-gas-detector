# 腾讯物联网操作系统的危险气体探测仪

#### 介绍
前面我们分享了几篇文章：

[基于事件型表驱动法菜单框架之小熊派简易气体探测器实战项目开发(上)](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA==&mid=2649001834&idx=1&sn=e8f4ee520328398c7791ff487a5ded12&chksm=870fc7adb0784ebbb61817309e503cd1cf170858ce7c291c63bb46808c48a6c144547f626462&scene=21#wechat_redirect)

[基于事件型表驱动法菜单框架之小熊派简易气体探测器实战项目开发(中)](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA==&mid=2649001954&idx=1&sn=b88e4057909af0303dfb021bca328266&chksm=870fc725b0784e33a52a61ee379688281cc2773a207622b15cf4dfafad5c96535dd2e4f4b226&scene=21#wechat_redirect)

[表驱动+状态机法AD传感器驱动检测框架](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA==&mid=2649002041&idx=1&sn=b33eac1c10a584523c5f7c5ad695c9cf&chksm=870fd8feb07851e8a66d4b9f146b87cb653625942217f5a8ff417c220fc2d212545baa470e6d&scene=21#wechat_redirect)

[有关版本等信息的重要性(以STM32产品开发为例)](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA==&mid=2649002172&idx=1&sn=55b5b31a1218c7e75867f66cce2dd557&chksm=870fd87bb078516d2bca305d1d7c4c420497d6f29b9599d3f9fc57671bab915dbc3710642208&scene=21#wechat_redirect)

这几篇文章都跟最终要达到的效果关联很大，但是功能并没有完善，今天分享的这个总算是有点像产品的样子了，但无奈硬件资源有限，无法完成太多功能，但我还是希望有朝一日，我能利用我身边的资源把它做成一个公模开源的手持式危险气体探测仪，并继续完善优化软件逻辑以及产品功能，甚至会加入一些标准化的东西(国标、行标、企标)，让它看起来真正的像一个产品，并且希望有机会能够量产，帮助更多的工程师入门。

## 1、软件组成

### 1.1、软件架构图

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVRU2liRERlRExoNWxxbzZVenJjUmc4dnFKbVc1MkhQZkR3dDhGNFpDQ2VrME4wdkRkdjNMb21nLzY0MA?x-oss-process=image/format,png)

### 1.2、软件框架图

#### 1.2.1 整体框架图

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVwUGVXT3MxZUxpY3NrTVpLV1NpYXFWMHBNaWFhcFRGZnNFOUFkQTZWekJubHNFZHVXTWRabHY3UlEvNjQw?x-oss-process=image/format,png)

#### 1.2.2 核心软件框架

## LCD驱动框架数据结构

![image-20201106085512333](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085512333.png)

![image-20201106085528972](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085528972.png)

这里提供了将驱动框架与驱动进行对接的能力，`&lcd_driver`拿到的是定义在驱动文件里的一个已经赋值了的结构体`lcd_driver`，这样，当我在别的地方定义一个`LCD_Driver_Model`的变量，就可以将这个变量与驱动结构体进行对接，这样就可以通过这个变量来操作驱动结构体里的接口了。

## LCD驱动数据结构

![image-20201106085552807](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085552807.png)

LCD驱动这个数据结构要做的事情就是提供操作LCD驱动能力的接口，这个接口的设计与硬件无关。

![image-20201106085613399](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085613399.png)

驱动框架依赖于驱动接口，这样的话我们需要实现驱动接口里的方法，在对应的方法里，我们要去调用LCD设备相关的接口，进而去操作LCD设备，以下是接口对应的实现：

![image-20201106085822107](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085822107.png)

## LCD设备数据结构

![image-20201106085635671](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20201106085635671.png)

LCD设备所需要做的事情就是将这个数据结构里的功能函数与真实的LCD驱动接口进行对接。比如我们看`LCD_Init`这个接口的实现，这个就是真实调用LCD的真实硬件操作了：

## 菜单框架与传感器检测框架

菜单部分以及传感器部分都是基于表驱动+状态机的方式实现：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVHUDF4Z2ljT3M5dHFiMkJ3aWJ4TEUzSW9pYVM1Zm9HdVRNNU1RMHgzNjMwa3U1SVlJTU0wVFROY1EvNjQw?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVUdjhpYW5yaWFQU3JRTWNZYW5VNWw3NnBibTJPSzY1Y1ZEOEJTZnZDaEkyZG1ITWJlYjVaU1lKZy82NDA?x-oss-process=image/format,png)

#### 1.3.1 优化UI界面

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVaR3Z1Y0w0b0JWUlFzbnBrdDVsTWcwN0ZjU0REQWVSTVhGdmU4Nm1EeUlCcGVrMFVIN0hYZEEvNjQw?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVWT0FCdjBkSENKRWRnbno1a09ra3d4RmFvQTl2VkJvdWZzcU5pY25mNlRJOFl3ZWtCYUlYVUJBLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVzMTBpYjM0N1JPZjROZWt5OTVvbEpmMlBDM1g2ZXVYNDVLaWJTaWFkUVVoZE1IZXlVSmlhd3ZZVDlBLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVPR3ZJazI3RnVLTU5jbndBejlkNTNHeFBQUHoyN0w2cUc4cmhuTExuaWM5OWlhaWNwYzJKczJjaWFBLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVUS2p2ZVdSa0NiQVQwUmlhaWIzWkFuVlh1RU1oTGpaMG9GNzh3Q2ZNNEJ6MDRWS1hDaDZFRTJOZy82NDA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVEZUVvN2Y0UnRMN0J3WFhiWEJzT2MyN3A5UWhUc2o1NERkZGliMTlRMlJycWxab3I0bEQwZEV3LzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0ZmRtRDgyNWJIVnhiNFo4VTZhaWNNM2NoNzZqZG9uVHZrZmg2TGZVYmR1eWljemd3Qk1NRFR6Zy82NDA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVmZ3dMQk9BekVHaWFLRWJyck1pY3VxU01uaWE2cXZ0STRRQUFIRjNHU0M1UHl4aWJyVmp4blc1c2tRLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVneWhJZ1ZWaHQ5WHo2RWFOcktDSTQ1Y1RyYWR1R1paTU1tVW9XR1RJcVJpYnZSV0RXQ0U5U2JBLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmUweHRibnhnQlRpY2ljcm1zWkxINldVR0hRc0JCUGc0TUd6Nko2NVRqMExRYTBWWkRTTXFYNFphUS82NDA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVpYUVnOFpKdTMzc2ZJTkRJWnhVS1BpYjY4SGVJcmlhUlhkMmE4SmJtcmYzOUNiMjJwRTZZekU5YVEvNjQw?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0eUZhZ0xWbUsxTUVMcjloZVBoamljR3lIYTBnY2NNbzNWVlE3VUtpYnZrZ05maHpEbjFTSGJDdy82NDA?x-oss-process=image/format,png)    ![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmUxa0tyTlJBRGMxMnNyaWFnaWM2RXNGbFZQUDd4STJscGVMUFNzTjV2QVM4eVNMakZaUGtvQndSQS82NDA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0WU92ZFBWWWcwaWNiNnNnWDB1cHc3ZnpHU2NpYjVDUERqbkRxbGlibGliQkVRRFRpYUxiNzhZVUZpYkEvNjQw?x-oss-process=image/format,png)

#### 1.3.2 TencentOS tiny加持 

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV5bm9pYVFOVHgxaWFVaWI4eGFzbUtsdFJjVUU0SWNnb2FZOWhtT1FpY2xRWXg1ZW41UDZJajg1ZTZBLzY0MA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVmVnhXZUVZZmZaTExpY0VTNUR0U3ZaRGJFNmpDaWM1ODdpYjRjRjRDaWFlOGZaNEhOd1FDSzJaQzF3LzY0MA?x-oss-process=image/format,png)

由于有TecentOS tiny RTOS的加持，使得我们编程的行为习惯不能像裸机那么随便了，所以，在多个任务并行的过程中，在一些临界区资源的地方必须要加上调度锁，以防止线程切换的过程中产生一些乱象，比如LCD显示接口，但凡是需要显示的地方，都要做好保护，如果没有做好保护，那你可能会看到类似如下的现象：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV3dGhpYnNuT2VnaldlSTZrbFo3c0s4T25qTlVoTUxQakI5ODJNdnhucXQ5VVVxaWJ4NVNtTkJ5dy82NDA?x-oss-process=image/format,png)

明明我的软件代码编写的逻辑就没有在这个地方做显示，为啥突然有个莫名其妙的色块产生？？这就是因为任务发生切换导致显示的错乱现象；简单的可能是这样的现象，严重的话产品直接就死机了。那么如何加调度锁呢？

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVQNTlsNGJTWHNmcDY3UjBzY2cwU2ljOGs5a0M1bEdPVHp3b1BpY2c5WDg1WjZLUGpCY3gzUjdSQS82NDA?x-oss-process=image/format,png)

例如，给显示一个ASCII码字符串的地方加上调度锁：

```c
/**
 * @brief  显示一个ASCII码字符串
 * @param   x,y  显示起始坐标
 * @param   str  需要显示的字符串
 * @param   size 字体大小(支持16/24/32号字体)
 * @return  none
 * @note  1. 需要font.h字库文件的支持
 *      2. 超过指定width不显示超过的字符
 */
void LCD_ShowCharStr(uint16_t x, uint16_t y, uint8_t max_width, char* str, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{
  //锁定系统调度
 tos_knl_sched_lock();
 max_width += x;
 
 while((*str <= '~') && (*str >= ' ')) //判断是否非法字符
 {
   if(x >= max_width)
   {
     //x方向越界，结束
     break;
   }
   
   LCD_ShowChar(x,y,*str,back_color, font_color,font_size);
   x += font_size / 2;
   str++;
 }
  //解锁系统调度
 tos_knl_sched_unlock();
}
```

加调度锁的方法，即是在函数入口处加上`tos_knl_sched_lock`，在函数出口的地方`tos_knl_sched_unlock`解除调度锁，这样就完成了一个显示过程的保护，当然，在对SD卡文件系统读写参数的过程中，我们也需要做好保护，比如：

```c
/*用户参数保存处理*/
void User_Para_Save_Process(void)
{
    //锁定系统调度
    tos_knl_sched_lock();
    /*write config.ini parse*/
    retUSER_SYS_CONFIG = f_open(&USER_SYS_CONFIG_File, SETTING_PARA, FA_OPEN_EXISTING | FA_WRITE);
 
    if(FR_OK != retUSER_SYS_CONFIG)
    {
        printf("iniparser: cannot open %s\n", SETTING_PARA);
        return ;
    }
 
    printf("参数设置保存成功\n");
    iniparser_dump_ini(Config_ini, &USER_SYS_CONFIG_File);
    f_close(&USER_SYS_CONFIG_File);
    iniparser_freedict(Config_ini);
    Load_Config_ini_File();
    //解锁系统调度
    tos_knl_sched_unlock();
}
/*用户参数保存处理*/
void User_Para_Save_Process(void)
{
    //锁定系统调度
    tos_knl_sched_lock();
    /*write config.ini parse*/
    retUSER_SYS_CONFIG = f_open(&USER_SYS_CONFIG_File, SETTING_PARA, FA_OPEN_EXISTING | FA_WRITE);
 
    if(FR_OK != retUSER_SYS_CONFIG)
    {
        printf("iniparser: cannot open %s\n", SETTING_PARA);
        return ;
    }
 
    printf("参数设置保存成功\n");
    iniparser_dump_ini(Config_ini, &USER_SYS_CONFIG_File);
    f_close(&USER_SYS_CONFIG_File);
    iniparser_freedict(Config_ini);
    Load_Config_ini_File();
    //解锁系统调度
    tos_knl_sched_unlock();
}
```

如果没有做好保护，当你在写入参数到文件系统的时候，此时任务发送了切换，那么很容易就会导致写入错乱进而跳转到：

```c
/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */
 
    /* USER CODE END HardFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}
```

系统有时候就莫名其妙的卡死了；以上这些都是我个人对于RTOS的学习和使用经验，如有说得不合理的地方，欢迎大佬指点迷津。

#### 1.3.3 记录及记录逻辑

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVWT0FCdjBkSENKRWRnbno1a09ra3d4RmFvQTl2VkJvdWZzcU5pY25mNlRJOFl3ZWtCYUlYVUJBLzY0MA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0eUZhZ0xWbUsxTUVMcjloZVBoamljR3lIYTBnY2NNbzNWVlE3VUtpYnZrZ05maHpEbjFTSGJDdy82NDA?x-oss-process=image/format,png)![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0WU92ZFBWWWcwaWNiNnNnWDB1cHc3ZnpHU2NpYjVDUERqbkRxbGlibGliQkVRRFRpYUxiNzhZVUZpYkEvNjQw?x-oss-process=image/format,png)

记录存储相关数据结构如下：

```c
/*文件名大小限制*/
#define FILE_NAME_LEN 20
/*检测数据大小限制*/
#define DETECT_DATA_LEN 50
/*一个文件存储检测记录的条数*/
#define DETECT_DATA_INDEX 100
 
typedef struct 
{
    int serial_number ;      //序号
    int year ;               //2019-
    uint8_t month ;          //0-12
    uint8_t day ;            //0-31
    uint8_t hour ;           //0-24
    uint8_t minute ;         //0-59
    uint8_t detect_result ;  //检测结果
    /*当前位于文件的哪一行*/
    int Current_Line;
    /*当前文件编号查询索引*/
    int file_number_index ;
    /*当前流水号，每次记录初始化的时候会赋值一次*/
    int Current_Serial_Number ;
} Record_Data;
extern Record_Data csv_file_record ;
```

记录逻辑采用分文件csv存储，将csv文件序号存放在ini文件中，然后通过文件序号快速定位到具体是哪个csv文件的哪一行，该策略支持10000条数据实时查询并能保证流程不卡顿，已在相关产品中量产应用。

#### 1.3.4 完成阈值设置逻辑

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVUS2p2ZVdSa0NiQVQwUmlhaWIzWkFuVlh1RU1oTGpaMG9GNzh3Q2ZNNEJ6MDRWS1hDaDZFRTJOZy82NDA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVGdkhqUGxqMVV2dXQxYTNwSGpMQU9zN0c0YWEwZTNCT3NPcjRRU0NpYjhpYTBweHhUZEtDaWF0SmcvNjQw?x-oss-process=image/format,png)

该设置逻辑分为三档，分别是低、中、高灵敏度，分别对应1000、300、200三档阈值设定，该灵敏度对应的阈值与检测逻辑相关联，对应逻辑关系如下：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVnUGljS2JFV2J6V1NyNmpkbnBnN3paSzRaTG9va0dQbkU1bzF4dG1pY2ljQW9oTnRXVk13V3FBaWF3LzY0MA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVwN0N1YWFMVDVQcHkzTnhSVW9VekQ0bWNGRm9WbkE0NjlQQTFCbDRjenlzZFQ3TkQ1aG1sUEEvNjQw?x-oss-process=image/format,png)

阈值设置是系统配置参数的其中一项，数据结构如下：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmUxQTZsUmtHZzZiTzlzZVJYc1R0NHZjOUpHaDR2dE9yM1cwdTdrWkdUYjNpYVBOU2dKd05sVUtRLzY0MA?x-oss-process=image/format,png)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVpYXh0NkJORVJCd3A0WjJORGRpYWFpYTNmN1JyWWNkYXRkTlZUeGNmVTlleGFwMTZqZm0xMW1mdUEvNjQw?x-oss-process=image/format,png)

#### 1.3.5 完成报警设置逻辑

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVEZUVvN2Y0UnRMN0J3WFhiWEJzT2MyN3A5UWhUc2o1NERkZGliMTlRMlJycWxab3I0bEQwZEV3LzY0MA?x-oss-process=image/format,png)

它是系统配置参数的其中一项，数据结构如下：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV4MmhPN0Zkc01QRTZYRzduVm5YZWxUSzBjWVlRQnlFbWRpYURiNmVRZDlGOHBMaHNpYXJKZmdzdy82NDA?x-oss-process=image/format,png)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV6d2J6MUZ0YTFIZXJMbU44aWF3MTVuYlRrRE1LQTdUYXgwc3B5a2dVV2RQcUVEaWJpY0FyckxGT2cvNjQw?x-oss-process=image/format,png)

该设置逻辑分为开关，当打开报警，则检测逻辑跳转到危险时，蜂鸣器会发出响声，否则不会发出响声，它的过程是通过一个标志volume进行控制的。

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVkQ2lheEZ6ZnlyUWp5QXpoV2trbFJvNEpGM0dlYkgzeVU2TlJyaWFMN1VPU3oxcnozQThPOGlicEEvNjQw?x-oss-process=image/format,png)

#### 1.3.6 完成调试模式逻辑

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV0ZmRtRDgyNWJIVnhiNFo4VTZhaWNNM2NoNzZqZG9uVHZrZmg2TGZVYmR1eWljemd3Qk1NRFR6Zy82NDA?x-oss-process=image/format,png)

它是系统配置参数的其中一项，数据结构如下：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVzMjBmeVhXWm9pY25EN2ljb045NUFpYWQ3dFJZTmsxTjBkZ3NmcUw1Zm1wNFJGQlJ1WWN0cDlBRncvNjQw?x-oss-process=image/format,png)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVyTjVPQ3J4N01GRGEwQkxyMjQ5eGFmbzlUblNOWjdxRWFQaWNRd0h3ajJOOHhDbnZxNVRoTkZnLzY0MA?x-oss-process=image/format,png)

该设置逻辑分为开关，当打开调试，则检测逻辑中显示烟感值，否则不会显示烟感值，它的过程是通过一个标志debug_flag进行控制的。

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVQelZRcU83R3NPWW9ER3ozRkRKSmhZTmE4Y2VGY3V3VlVSRmliQmRJUWpxTm9aeVU2WTBlYWJnLzY0MA?x-oss-process=image/format,png)

#### 1.3.7 完成仪器信息查看

**![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVmZ3dMQk9BekVHaWFLRWJyck1pY3VxU01uaWE2cXZ0STRRQUFIRjNHU0M1UHl4aWJyVmp4blc1c2tRLzY0MA?x-oss-process=image/format,png)**

这个功能在上一篇文章其实已经提及了，这里就不再重复说了，详细请看上一篇推文：

[有关版本等信息的重要性(以STM32产品开发为例)](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA%3D%3D&chksm=870fd87bb078516d2bca305d1d7c4c420497d6f29b9599d3f9fc57671bab915dbc3710642208&idx=1&mid=2649002172&scene=21&sn=55b5b31a1218c7e75867f66cce2dd557#wechat_redirect)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVFSkRXblVuRGN1NFYzeXR1anZmemM2aExqQTd2bkh5T1dzek05MVltQ2dHSkozTnBwdnJ1SHcvNjQw?x-oss-process=image/format,png)

## 2、其它

另外要注意的地方，SD卡内存放的UI为显示界面一些图标存放的地方，其它的文件由软件自动生成：

- Para.ini(配置文件)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV4STVPdWIzSkFPcEVxRmFucGZUTWZtVnB1RXB5bDBjaWNZZ3F5RGJEM05OYUNpYUV3RXB3b0R3Zy82NDA?x-oss-process=image/format,png)

- BearPi_Log0.csv(检测记录存储文件)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmV6d0NrQ2p2MVJLaWFEYWJQVXhVOGtLUjM1eHNCRXAxbDlScUc1cFlPVkpwcW50VzhRRmEzeUdBLzY0MA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSThMRHhEZFZKWDBPWnN6NElvMFg2NmVqYlFCNkZwcUZuMWRMTnFtblFFRHREb1RzaHlFZ05YbHRZT2czVGlhb2s5TE5DQXNZRUZXeG1BLzY0MA?x-oss-process=image/format,png)

本节代码已同步到码云的代码仓库中,获取方法如下：

#### 1、新建一个文件夹

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTlCSmlibTh1aWNGbFNpYmljRjUxV0dQbGJsVjN1MHdBM2FFTzEzenZuU1JzRUxtUXhRMlVFaENGN0tGWWpBcXEyRncwc21ueFFudDBpYnBoQS82NDA?x-oss-process=image/format,png)

#### 2、使用git clone远程获取文初的代码仓库

项目开源仓库：

```go
https://gitee.com/morixinguan/tencent-os-tiny-hazardous-gas-detector.git
```

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTlCSmlibTh1aWNGbFNpYmljRjUxV0dQbGJsMEZpYmlhaDlTSXFWYmhETkRVcXRxTVcybmtTR3hpYWFuWjlFOFRQV3k5YlFhVU41c3BFU3VpYkZhZy82NDA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTlCSmlibTh1aWNGbFNpYmljRjUxV0dQbGJsNVlDakVCRkpSMWhraWFEbk9HZ205YkdBb1dCS1k2TnFXSGVEMHljc09sQWExMDBUT2RqQ2toZy82NDA?x-oss-process=image/format,png)