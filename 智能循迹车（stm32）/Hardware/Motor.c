#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "PID.h"
#include "Motor.h"

int16_t Speed1,Speed2,Speed3,Speed4;
extern int16_t encoder1;
extern int16_t encoder2;
extern int16_t encoder3;
extern int16_t encoder4;
/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);       ////开启GPIOC的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB0,PB1,PB10和PB11等六个引脚初始化为推挽输出	
	
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_13;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure2);						//将PA2等两个引脚初始化为推挽输出	
	
	GPIO_InitTypeDef GPIO_InitStructure3;
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure3);
	
	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：每个轮子的前进，后退和停止
  * 参    数：无
  * 返 回 值：无
  */
void MotorL1_UP(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);//电机正转
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
		
void MotorL1_STOP(void)

{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
}

void MotorL1_DOWN(void)

{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);//电机反转
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
}


void MotorR1_UP(void)
{
		
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//电机正转
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);

}

void MotorR1_STOP(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

void MotorR1_DOWN(void)
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//电机反转
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		
}

void MotorL2_UP(void)
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);//电机正转
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
}
		
void MotorL2_STOP(void)

{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
}

void MotorL2_DOWN(void)

{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);//电机反转
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
}


void MotorR2_UP(void)
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);//电机正转
		GPIO_SetBits(GPIOE, GPIO_Pin_6);	
}

void MotorR2_STOP(void)
{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		GPIO_SetBits(GPIOE, GPIO_Pin_6);
}

void MotorR2_DOWN(void)
{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);//电机反转
		GPIO_ResetBits(GPIOE, GPIO_Pin_6);
}

/**
  * 函    数：直流电机设置速度
  * 参    数：输入目标物理速度Target_V，和现在物理速度Now_V，此函数内部用了pid函数，自动转换为Speed 要设置的速度，范围：-7280~7280
  * 返 回 值：无
    到时候直接把这类函数写到中断里面执行，因为里面包含了PID函数
  */

void MotorL1_SetSpeed(int16_t Speed3)
{
	if (Speed3 > 0)//Speed值为正
	{
		MotorL1_UP();
		PWM_SetCompare3(Speed3);//设置Speed转速
	}
	else if(Speed3==0)
	{
		MotorL1_STOP();
		PWM_SetCompare3(Speed3);
	}
	else//Speed值为负
	{
		MotorL1_DOWN();
		PWM_SetCompare3(-Speed3);//设为-Speed转速
	}
}

void MotorL2_SetSpeed(int16_t Speed4)
{
	if (Speed4 > 0)//Speed值为正
	{
		MotorL2_UP();
		PWM_SetCompare4(Speed4);//设置Speed转速
	}
	else if(Speed4==0)
	{
		MotorL2_STOP();
		PWM_SetCompare4(Speed4);
	}
	else//Speed值为负
	{
		MotorL2_DOWN();
		PWM_SetCompare4(-Speed4);//设为-Speed转速
	}
}

void MotorR1_SetSpeed(int16_t Speed1)
{
	if (Speed1 > 0)//Speed值为正
	{
		MotorR1_UP();
		PWM_SetCompare1(Speed1);//设置Speed转速
	}
	else if(Speed1==0)
	{
		MotorR1_STOP();
		PWM_SetCompare1(Speed1);
	}
	else//Speed值为负
	{
		MotorR1_DOWN();
		PWM_SetCompare1(-Speed1);//设为-Speed转速
	}
}
                        
void MotorR2_SetSpeed(int16_t Speed2)
{

	if (Speed2 > 0)//Speed值为正
	{
		MotorR2_UP();
		PWM_SetCompare2(Speed2);//设置Speed转速
	}
	else if(Speed2==0)
	{
		MotorR2_STOP();
		PWM_SetCompare2(Speed2);
	}
	else//Speed值为负
	{
		MotorR2_DOWN();
		PWM_SetCompare2(-Speed2);//设为-Speed转速
	}
}
