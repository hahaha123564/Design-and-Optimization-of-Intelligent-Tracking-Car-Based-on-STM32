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
  * ��    ����ֱ�������ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Motor_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);       ////����GPIOC��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//��PB0,PB1,PB10��PB11���������ų�ʼ��Ϊ�������	
	
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_13;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure2);						//��PA2���������ų�ʼ��Ϊ�������	
	
	GPIO_InitTypeDef GPIO_InitStructure3;
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure3);
	
	PWM_Init();													//��ʼ��ֱ������ĵײ�PWM
}

/**
  * ��    ����ÿ�����ӵ�ǰ�������˺�ֹͣ
  * ��    ������
  * �� �� ֵ����
  */
void MotorL1_UP(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);//�����ת
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
		
void MotorL1_STOP(void)

{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
}

void MotorL1_DOWN(void)

{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);//�����ת
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
}


void MotorR1_UP(void)
{
		
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//�����ת
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);

}

void MotorR1_STOP(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

void MotorR1_DOWN(void)
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//�����ת
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		
}

void MotorL2_UP(void)
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);//�����ת
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
}
		
void MotorL2_STOP(void)

{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
}

void MotorL2_DOWN(void)

{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);//�����ת
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
}


void MotorR2_UP(void)
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);//�����ת
		GPIO_SetBits(GPIOE, GPIO_Pin_6);	
}

void MotorR2_STOP(void)
{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		GPIO_SetBits(GPIOE, GPIO_Pin_6);
}

void MotorR2_DOWN(void)
{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);//�����ת
		GPIO_ResetBits(GPIOE, GPIO_Pin_6);
}

/**
  * ��    ����ֱ����������ٶ�
  * ��    ��������Ŀ�������ٶ�Target_V�������������ٶ�Now_V���˺����ڲ�����pid�������Զ�ת��ΪSpeed Ҫ���õ��ٶȣ���Χ��-7280~7280
  * �� �� ֵ����
    ��ʱ��ֱ�Ӱ����ຯ��д���ж�����ִ�У���Ϊ���������PID����
  */

void MotorL1_SetSpeed(int16_t Speed3)
{
	if (Speed3 > 0)//SpeedֵΪ��
	{
		MotorL1_UP();
		PWM_SetCompare3(Speed3);//����Speedת��
	}
	else if(Speed3==0)
	{
		MotorL1_STOP();
		PWM_SetCompare3(Speed3);
	}
	else//SpeedֵΪ��
	{
		MotorL1_DOWN();
		PWM_SetCompare3(-Speed3);//��Ϊ-Speedת��
	}
}

void MotorL2_SetSpeed(int16_t Speed4)
{
	if (Speed4 > 0)//SpeedֵΪ��
	{
		MotorL2_UP();
		PWM_SetCompare4(Speed4);//����Speedת��
	}
	else if(Speed4==0)
	{
		MotorL2_STOP();
		PWM_SetCompare4(Speed4);
	}
	else//SpeedֵΪ��
	{
		MotorL2_DOWN();
		PWM_SetCompare4(-Speed4);//��Ϊ-Speedת��
	}
}

void MotorR1_SetSpeed(int16_t Speed1)
{
	if (Speed1 > 0)//SpeedֵΪ��
	{
		MotorR1_UP();
		PWM_SetCompare1(Speed1);//����Speedת��
	}
	else if(Speed1==0)
	{
		MotorR1_STOP();
		PWM_SetCompare1(Speed1);
	}
	else//SpeedֵΪ��
	{
		MotorR1_DOWN();
		PWM_SetCompare1(-Speed1);//��Ϊ-Speedת��
	}
}
                        
void MotorR2_SetSpeed(int16_t Speed2)
{

	if (Speed2 > 0)//SpeedֵΪ��
	{
		MotorR2_UP();
		PWM_SetCompare2(Speed2);//����Speedת��
	}
	else if(Speed2==0)
	{
		MotorR2_STOP();
		PWM_SetCompare2(Speed2);
	}
	else//SpeedֵΪ��
	{
		MotorR2_DOWN();
		PWM_SetCompare2(-Speed2);//��Ϊ-Speedת��
	}
}
