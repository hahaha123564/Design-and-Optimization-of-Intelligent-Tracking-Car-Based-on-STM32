#include "stm32f10x.h"  
#include "Motor.h"
/**
  * ��    ����ֱ����������ٶ��복���ж�ģʽ
  * ��    ��������Ŀ�������ٶ�Target_V�������������ٶ�Now_V1��Now_V2��Now_V3��Now_V4,��ӦΪR1,R2,L1,L2
			  ������Ϊ�����ٶ�Now_V����main�������ж��л��Լ���ֵ��������Ҫ����ֻ����Ҫָ�����ֵ��ٶ�Target_V
  * �� �� ֵ����
    ��ʱ��ֱ�Ӱ����ຯ��д���ж�����ִ�У���Ϊ���������Motor��������Motor���������PID����
  */
void Car_Stop(void)
{
	MotorR1_SetSpeed(0);
	MotorL1_SetSpeed(0);
	MotorR2_SetSpeed(0);
	MotorL2_SetSpeed(0);
	
}

void Car_Go1(void)     //Ŀ��VΪ-5~5   ���м��Ƕοհ��ٶ���΢��һ��
{
	MotorR1_SetSpeed(2800);
	MotorL1_SetSpeed(2800);	
	MotorR2_SetSpeed(2800);
	MotorL2_SetSpeed(2800);
}

void Car_Go2(void)     //Ŀ��VΪ-5~5     ��һ�οհ���ֱ�ߣ�һ��Ҫ������ֱ��
{
	MotorR1_SetSpeed(2800);
	MotorL1_SetSpeed(2850);	
	MotorR2_SetSpeed(2800);
	MotorL2_SetSpeed(2850);
}

void Car_Go3(void)     //Ŀ��VΪ-5~5   �Ӻ��߳������м��Ƕοհף��ڶ��οհף�����Ҫ��΢����ƫһ�� ���Ը���ʵ���������
{
	MotorR1_SetSpeed(2800);
	MotorL1_SetSpeed(2850);	
	MotorR2_SetSpeed(2800);
	MotorL2_SetSpeed(2850);
}
//void Car_Down(void)
//{
//	MotorR1_SetSpeed(-90);
//	MotorL1_SetSpeed(-90);
//	MotorR2_SetSpeed(-90);
//	MotorL2_SetSpeed(-90);
//}

void Car_TurnRight1(void)          //����Ϊ1-2֮��ÿ���         //����Ӳ��ԭ����ʵ����ת   ԭ���ٶ���20
{	
			MotorL1_SetSpeed(3000);						//	MotorL1_SetSpeed(-40);//r1
			MotorL2_SetSpeed(3000);						//	MotorL2_SetSpeed(40);//l1	
			MotorR1_SetSpeed(-3000);						//	MotorR1_SetSpeed(-40);//r2
			MotorR2_SetSpeed(-3000);						//	MotorR2_SetSpeed(40);//l2
}

void Car_TurnRight2(void)
{
			MotorL1_SetSpeed(3500);						//	MotorL1_SetSpeed(-40);//r1
			MotorL2_SetSpeed(3500);						//	MotorL2_SetSpeed(40);//l1	
			MotorR1_SetSpeed(-3500);						//	MotorR1_SetSpeed(-40);//r2
			MotorR2_SetSpeed(-3500);
}

void Car_TurnLeft1(void)           //����Ϊ1-2֮��ÿ���   //����Ӳ��ԭ����ʵΪ��ת        ԭ���ٶ���20
{
			MotorL1_SetSpeed(-3000);						
			MotorL2_SetSpeed(-3000);						
			MotorR1_SetSpeed(3000);						
			MotorR2_SetSpeed(3000);
//	MotorR1_SetSpeed(40);//r2
//	MotorL1_SetSpeed(40);//r1
//	MotorR2_SetSpeed(-40);//l2
//	MotorL2_SetSpeed(-40);//l1
}
void Car_TurnLeft2()
{
			MotorL1_SetSpeed(-3500);						
			MotorL2_SetSpeed(-3500);						
			MotorR1_SetSpeed(3500);						
			MotorR2_SetSpeed(3500);
}

void Car_Spin(void)                 //����Ϊ2-3֮��ÿ���  //����Ӳ��ԭ����ұ���ת    ԭ���ٶ���30
{
			MotorL1_SetSpeed(-4500);				//�������ת		
			MotorL2_SetSpeed(-4500);						
			MotorR1_SetSpeed(4500);						
			MotorR2_SetSpeed(4500);
//	MotorR1_SetSpeed(47);
//	MotorL1_SetSpeed(47);
//	MotorR2_SetSpeed(-47);
//	MotorL2_SetSpeed(-47);
}
