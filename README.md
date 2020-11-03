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

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eQSibDDeDLh5lqo6UzrcRg8vqJmW52HPfDwt8F4ZCCek0N0vDdv3Lomg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 1.2、软件框架图

#### 1.2.1 整体框架图



![img](https://mmbiz.qpic.cn/mmbiz_jpg/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66epPeWOs1eLicskMZKWSiaqV0pMiaapTFfsE9AdA6VzBnlsEduWMdZlv7RQ/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2.2 核心软件框架

菜单部分以及传感器部分都是基于表驱动+状态机的方式实现：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eGP1xgicOs9tqb2BwibxLE3IoiaS5foGuTM5MQ0x3630ku5IYIMM0TTNcQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eTv8ianriaPSrQMcYanU5l76pbm2OK65cVD8BSfvChI2dmHMbeb5ZSYJg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 1.3、相对于之前发布文章的功能差异

- 优化UI界面
- TencentOS tiny加持
- 完成记录及记录逻辑
- 完成阈值设置逻辑
- 完成报警设置逻辑
- 完成调试模式逻辑
- 完成仪器信息查看

#### 1.3.1 优化UI界面



![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eZGvucL4oBVRQsnpkt5lMg07FcSDDAeRMXFve86mDyIBpek0UH7HXdA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eVOABv0dHCJEdgnz5kOkkwxFaoA9vVBoufsqNicnf6TI8YwekBaIXUBA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_jpg/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66es10ib347ROf4Neky95olJf2PC3X6euX45KibSiadQUhdMHeyUJiawvYT9A/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eOGvIk27FuKMNcnwAz9d53GxPPPz27L6qG8rhnLLnic99iaicpc2Js2ciaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eTKjveWRkCbAT0Riaib3ZAnVXuEMhLjZ0oF78wCfM4Bz04VKXCh6EE2Ng/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eDeEo7f4RtL7BwXXbXBsOc27p9QhTsj54Dddib19Q2RrqlZor4lD0dEw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etfdmD825bHVxb4Z8U6aicM3ch76jdonTvkfh6LfUbduyiczgwBMMDTzg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66efgwLBOAzEGiaKEbrrMicuqSMnia6qvtI4QAAHF3GSC5PyxibrVjxnW5skQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66egyhIgVVht9Xz6EaNrKCI45cTraduGZZMMmUoWGTIqRibvRWDWCE9SbA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66e0xtbnxgBTicicrmsZLH6WUGHQsBBPg4MGz6J65Tj0LQa0VZDSMqX4ZaQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eiaEg8ZJu33sfINDIZxUKPib68HeIriaRXd2a8Jbmrf39Cb22pE6YzE9aQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_jpg/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etyFagLVmK1MELr9hePhjicGyHa0gccMo3VVQ7UKibvkgNfhzDn1SHbCw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)  ![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66e1kKrNRADc12sriagic6EsFlVPP7xI2lpeLPSsN5vAS8ySLjFZPkoBwRA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etYOvdPVYg0icb6sgX0upw7fzGScib5CPDjnDqliblibBEQDTiaLb78YUFibA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.3.2 TencentOS tiny加持 

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eynoiaQNTx1iaUib8xasmKltRcUE4IcgoaY9hmOQiclQYx5en5P6Ij85e6A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66efVxWeEYffZLLicES5DtSvZDbE6jCic587ib4cF4Ciae8fZ4HNwQCK2ZC1w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

由于有TecentOS tiny RTOS的加持，使得我们编程的行为习惯不能像裸机那么随便了，所以，在多个任务并行的过程中，在一些临界区资源的地方必须要加上调度锁，以防止线程切换的过程中产生一些乱象，比如LCD显示接口，但凡是需要显示的地方，都要做好保护，如果没有做好保护，那你可能会看到类似如下的现象：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ewthibsnOegjWeI6klZ7sK8OnjNUhMLPjB982Mvxnqt9UUqibx5SmNByw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

明明我的软件代码编写的逻辑就没有在这个地方做显示，为啥突然有个莫名其妙的色块产生？？这就是因为任务发生切换导致显示的错乱现象；简单的可能是这样的现象，严重的话产品直接就死机了。那么如何加调度锁呢？

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eP59l4bSXsfp67R0scg0Sic8k9kC5lGOTzwoPicg9X85Z6KPjBcx3R7RA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

例如，给显示一个ASCII码字符串的地方加上调度锁：

```
/**
 * @brief  显示一个ASCII码字符串
 * @param   x,y  显示起始坐标
 * @param   str  需要显示的字符串
 * @param   size 字体大小(支持16/24/32号字体)
 * @return  none
 * @note  1. 需要font.h字库文件的支持
 *      2. 超过指定width不显示超过的字符
 */
void LCD_ShowCharStr(uint16_t x, uint16_t y, uint8_t max_width, char* str, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{
  //锁定系统调度
 tos_knl_sched_lock();
 max_width += x;
 
 while((*str <= '~') && (*str >= ' ')) //判断是否非法字符
 {
   if(x >= max_width)
   {
     //x方向越界，结束
     break;
   }
   
   LCD_ShowChar(x,y,*str,back_color, font_color,font_size);
   x += font_size / 2;
   str++;
 }
  //解锁系统调度
 tos_knl_sched_unlock();
}
```

加调度锁的方法，即是在函数入口处加上`tos_knl_sched_lock`，在函数出口的地方`tos_knl_sched_unlock`解除调度锁，这样就完成了一个显示过程的保护，当然，在对SD卡文件系统读写参数的过程中，我们也需要做好保护，比如：

```
/*用户参数保存处理*/
void User_Para_Save_Process(void)
{
    //锁定系统调度
    tos_knl_sched_lock();
    /*write config.ini parse*/
    retUSER_SYS_CONFIG = f_open(&USER_SYS_CONFIG_File, SETTING_PARA, FA_OPEN_EXISTING | FA_WRITE);

    if(FR_OK != retUSER_SYS_CONFIG)
    {
        printf("iniparser: cannot open %s\n", SETTING_PARA);
        return ;
    }

    printf("参数设置保存成功\n");
    iniparser_dump_ini(Config_ini, &USER_SYS_CONFIG_File);
    f_close(&USER_SYS_CONFIG_File);
    iniparser_freedict(Config_ini);
    Load_Config_ini_File();
    //解锁系统调度
    tos_knl_sched_unlock();
}
```

如果没有做好保护，当你在写入参数到文件系统的时候，此时任务发送了切换，那么很容易就会导致写入错乱进而跳转到：

```
/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}
```

系统有时候就莫名其妙的卡死了；以上这些都是我个人对于RTOS的学习和使用经验，如有说得不合理的地方，欢迎大佬指点迷津。

#### 1.3.3 记录及记录逻辑

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eVOABv0dHCJEdgnz5kOkkwxFaoA9vVBoufsqNicnf6TI8YwekBaIXUBA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_jpg/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etyFagLVmK1MELr9hePhjicGyHa0gccMo3VVQ7UKibvkgNfhzDn1SHbCw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etYOvdPVYg0icb6sgX0upw7fzGScib5CPDjnDqliblibBEQDTiaLb78YUFibA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

记录存储相关数据结构如下：

```
/*文件名大小限制*/
#define FILE_NAME_LEN 20
/*检测数据大小限制*/
#define DETECT_DATA_LEN 50
/*一个文件存储检测记录的条数*/
#define DETECT_DATA_INDEX 100

typedef struct 
{
    int serial_number ;      //序号
    int year ;               //2019-
    uint8_t month ;          //0-12
    uint8_t day ;            //0-31
    uint8_t hour ;           //0-24
    uint8_t minute ;         //0-59
    uint8_t detect_result ;  //检测结果
    /*当前位于文件的哪一行*/
    int Current_Line;
    /*当前文件编号查询索引*/
    int file_number_index ;
    /*当前流水号，每次记录初始化的时候会赋值一次*/
    int Current_Serial_Number ;
} Record_Data;
extern Record_Data csv_file_record ;
```

记录逻辑采用分文件csv存储，将csv文件序号存放在ini文件中，然后通过文件序号快速定位到具体是哪个csv文件的哪一行，该策略支持10000条数据实时查询并能保证流程不卡顿，已在相关产品中量产应用。

#### 1.3.4 完成阈值设置逻辑

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eTKjveWRkCbAT0Riaib3ZAnVXuEMhLjZ0oF78wCfM4Bz04VKXCh6EE2Ng/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eFvHjPlj1Uvut1a3pHjLAOs7G4aa0e3BOsOr4QSCib8ia0pxxTdKCiatJg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

该设置逻辑分为三档，分别是低、中、高灵敏度，分别对应1000、300、200三档阈值设定，该灵敏度对应的阈值与检测逻辑相关联，对应逻辑关系如下：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66egPicKbEWbzWSr6jdnpg7zZK4ZLookGPnE5o1xtmicicAohNtWVMwWqAiaw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ep7CuaaLT5Ppy3NxRUoUzD4mcFFoVnA469PA1Bl4czysdT7ND5hmlPA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



阈值设置是系统配置参数的其中一项，数据结构如下：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66e1A6lRkGg6bO9seRXsTt4vc9JGh4vtOr3W0u7kZGTb3iaPNSgJwNlUKQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eiaxt6BNERBwp4Z2NDdiaaia3f7RrYcdatdNVTxcfU9exap16jfm11mfuA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.3.5 完成报警设置逻辑

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eDeEo7f4RtL7BwXXbXBsOc27p9QhTsj54Dddib19Q2RrqlZor4lD0dEw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

它是系统配置参数的其中一项，数据结构如下：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ex2hO7FdsMPE6XG7nVnXelTK0cYYQByEmdiaDb6eQd9F8pLhsiarJfgsw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ezwbz1Fta1HerLmN8iaw15nbTkDMKA7Tax0spykgUWdPqEDibicArrLFOg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

该设置逻辑分为开关，当打开报警，则检测逻辑跳转到危险时，蜂鸣器会发出响声，否则不会发出响声，它的过程是通过一个标志volume进行控制的。

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66edCiaxFzfyrQjyAzhWkklRo4JF3GebH3yU6NRriaL7UOSz1rz3A8O8ibpA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.3.6 完成调试模式逻辑

**![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66etfdmD825bHVxb4Z8U6aicM3ch76jdonTvkfh6LfUbduyiczgwBMMDTzg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)**

它是系统配置参数的其中一项，数据结构如下：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66es20fyXWZoicnD7icoN95Aiad7tRYNk1N0dgsfqL5fmp4RFBRuYctp9AFw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

当SD卡中如果没有配置文件，它有一个默认的结果，用于表示它开机的状态，这个状态是存储在INI文件里的：

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66erN5OCrx7MFDa0BLr249xafo9TnSNZ7qEaPicQwHwj2N8xCnvq5ThNFg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

该设置逻辑分为开关，当打开调试，则检测逻辑中显示烟感值，否则不会显示烟感值，它的过程是通过一个标志debug_flag进行控制的。

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ePzVQqO7GsOYoDGz3FDJJhYNa8ceFcuwVURFibBdIQjqNoZyU6Y0eabg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



#### 1.3.7 完成仪器信息查看



***\*![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66efgwLBOAzEGiaKEbrrMicuqSMnia6qvtI4QAAHF3GSC5PyxibrVjxnW5skQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)\****

***\*
\****

这个功能在上一篇文章其实已经提及了，这里就不再重复说了，详细请看上一篇推文：

[有关版本等信息的重要性(以STM32产品开发为例)](http://mp.weixin.qq.com/s?__biz=MzA3MjMzNTc4NA==&mid=2649002172&idx=1&sn=55b5b31a1218c7e75867f66cce2dd557&chksm=870fd87bb078516d2bca305d1d7c4c420497d6f29b9599d3f9fc57671bab915dbc3710642208&scene=21#wechat_redirect)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66eEJDWnUnDcu4V3ytujvfzc6hLjA7vnHyOWszM91YmCgGJJ3NppvruHw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



## 2、其它

另外要注意的地方，SD卡内存放的UI为显示界面一些图标存放的地方，其它的文件由软件自动生成：

- Para.ini(配置文件)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66exI5Oub3JAOpEqFanpfTMfmVpuEpyl0cicYgqyDbD3NNaCiaEwEpwoDwg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

- BearPi_Log0.csv(检测记录存储文件)



![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ezwCkCjv1RKiaDabPUxU8kKR35xsBEp1l9RqG5pYOVJpqntW8QFa3yGA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI8LDxDdVJX0OZsz4Io0X66ejbQB6FpqFn1dLNqmnQEDtDoTshyEgNXltYOg3Tiaok9LNCAsYEFWxmA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

本节代码已同步到码云的代码仓库中,获取方法如下：

#### 1、新建一个文件夹

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI9BJibm8uicFlSibicF51WGPlblV3u0wA3aEO13zvnSRsELmQxQ2UEhCF7KFYjAqq2Fw0smnxQnt0ibphA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

#### 2、使用git clone远程获取文初的代码仓库

项目开源仓库：

```
https://gitee.com/morixinguan/tencent-os-tiny-hazardous-gas-detector.git
```



![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI9BJibm8uicFlSibicF51WGPlbl0Fibiah9SIqVbhDNDUqtqMW2nkSGxiaanZ9E8TPWy9bQaUN5spESuibFag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/SYiceJK78CI9BJibm8uicFlSibicF51WGPlbl5YCjEBFJR1hkiaDnOGgm9bGAoWBKY6NqWHeD0ycsOlAa100TOdjCkhg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)