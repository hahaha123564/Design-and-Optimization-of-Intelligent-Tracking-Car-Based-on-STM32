#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);		//开启GPIOC的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);						//将PC1和PC2和PC3和PC4和PC5和PC6引脚初始化为上拉输入
}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~4，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;		//定义变量，默认键码值为0
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0)			//读PC1输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
												//延时消抖
		KeyNum = 1;												//置键码为1
	}
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0)			//读PC2输入寄存器的状态，如果为0，则代表按键2按下
	{
		Delay_ms(20);											//延时消抖
												//延时消抖
		KeyNum = 2;												//置键码为2
	}
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0)			//读PC3输入寄存器的状态，如果为0，则代表按键3按下
	{
		Delay_ms(20);											//延时消抖
													//延时消抖
		KeyNum = 3;												//置键码为3
	}
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == 0)			//读PC4输入寄存器的状态，如果为0，则代表按键4按下
	{
		Delay_ms(20);											//延时消抖
													//延时消抖
		KeyNum = 4;												//置键码为4
	}
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == 0)			//读PC5输入寄存器的状态，如果为0，则代表按键5按下
	{
		Delay_ms(20);											//延时消抖
													//延时消抖
		KeyNum = 5;												//置键码为5
	}
	
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 0)			//读PC6输入寄存器的状态，如果为0，则代表按键6按下
	{
		Delay_ms(20);											//延时消抖
													//延时消抖
		KeyNum = 6;												//置键码为6
	}
	return KeyNum;			//返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}
