#include "stm32f10x.h"  
#include "Motor.h"
/**
  * 函    数：直流电机设置速度与车的行动模式
  * 参    数：输入目标物理速度Target_V，和现在物理速度Now_V1，Now_V2，Now_V3，Now_V4,对应为R1,R2,L1,L2
			  但是因为现在速度Now_V，在main函数的中断中会自己赋值，所以需要我们只是需要指定保持的速度Target_V
  * 返 回 值：无
    到时候直接把这类函数写到中断里面执行，因为里面包含了Motor函数，而Motor里面包含了PID函数
  */
void Car_Stop(void)
{
	MotorR1_SetSpeed(0);
	MotorL1_SetSpeed(0);
	MotorR2_SetSpeed(0);
	MotorL2_SetSpeed(0);
	
}

void Car_Go1(void)     //目标V为-5~5   走中间那段空白速度稍微快一点
{
	MotorR1_SetSpeed(2800);
	MotorL1_SetSpeed(2800);	
	MotorR2_SetSpeed(2800);
	MotorL2_SetSpeed(2800);
}

void Car_Go2(void)     //目标V为-5~5     第一段空白走直线，一定要调成走直线
{
	MotorR1_SetSpeed(2800);
	MotorL1_SetSpeed(2850);	
	MotorR2_SetSpeed(2800);
	MotorL2_SetSpeed(2850);
}

void Car_Go3(void)     //目标V为-5~5   从黑线出来走中间那段空白（第二段空白），需要稍微往右偏一点 可以根据实际情况调整
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

void Car_TurnRight1(void)          //建议为1-2之间好控制         //由于硬件原因其实是左转   原来速度是20
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

void Car_TurnLeft1(void)           //建议为1-2之间好控制   //由于硬件原因其实为右转        原来速度是20
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

void Car_Spin(void)                 //建议为2-3之间好控制  //由于硬件原因从右边自转    原来速度是30
{
			MotorL1_SetSpeed(-4500);				//从左边自转		
			MotorL2_SetSpeed(-4500);						
			MotorR1_SetSpeed(4500);						
			MotorR2_SetSpeed(4500);
//	MotorR1_SetSpeed(47);
//	MotorL1_SetSpeed(47);
//	MotorR2_SetSpeed(-47);
//	MotorL2_SetSpeed(-47);
}
