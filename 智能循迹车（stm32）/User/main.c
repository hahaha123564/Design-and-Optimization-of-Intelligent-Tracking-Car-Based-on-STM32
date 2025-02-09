#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
//#include "Encoder.h"
#include "Motor.h"
#include "Key.h"
#include "PWM.h"
#include "Car.h"
#include "XunJi.h"
#include "LED.h"
#include "Serial.h"


int16_t encoder1,encoder2,encoder3,encoder4;			//������ת/��Ϊ��λ�������ٶȱ���
extern int16_t Speed2;
extern int16_t Speed3;
extern int16_t Speed4;
float a,b;
float Angle;                         //��λ��mm��
float kp=100, ki= 4, kd = 0,error=0, lastError=0,integral, maxIntegral=10,output, maxOutput = 1500 ,dout;
float reference,feedback; //Ŀ��ֵ��ʵ��ֵ
uint8_t KeyNum;			//�������ڽ��ռ���ı���
uint8_t count1=1;         //�ڶ���״̬����
uint8_t count2=1;         //������״̬����
uint8_t x=0,y=0;
uint8_t r=0;
float f=0,c=0,k=0,w=0,h=0;
void qingling();
int main(void)
{
	/*ģ���ʼ��*/
	LED_Init();
	OLED_Init();		//OLED��ʼ��
	Timer_Init();		//��ʱ����ʼ��
//	Encoder_Init_TIM2();		//��������ʼ��
//	Encoder_Init_TIM3();
//	Encoder_Init_TIM4();
//	Encoder_Init_TIM8();
	Motor_Init();
	PWM_Init(); 
	Key_Init();			//������ʼ��
	XunJi_Init();
	Serial_Init();
	
	
	
	while (1)
	{
		
	
		if(Key_GetNum()==0)
		{}
		else if((Key_GetNum()==1)||(Key_GetNum()==2)||(Key_GetNum()==3)||(Key_GetNum()==4)){
			KeyNum = Key_GetNum();}			//��ȡ��������
			
	if (KeyNum == 1)				//����1����
	{
		while (KeyNum == 1)
		{
				Car_Go1();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
		 if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0) ||
				(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0) ||
					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0) ||
						(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0) || 
							(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0) || 
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) ||
								  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0) ||    //����
									(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0))    //����
			{	
				Car_Stop();
				LED_ON();
				FMQ_ON();
				x=1;
				KeyNum=0;
			}
		}
	}
	if (KeyNum == 2)				//����2����
		{	
			while(count1 == 1)	   //��һ�οհף�״̬1
			{
				Car_Go2();
				
				if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
					  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
					    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
					      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
						    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
						      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )        
				{		
					
						x=1;
						LED_ON();  //B������ʾ
						FMQ_ON();
//						//Delay_ms(200);
//						LED_OFF();
//						FMQ_OFF();
						count1 = count1 + 1;		
				}
			}	
			while(count1 == 2)         //��һ�κ��ߣ�״̬2      || count1 == 3 || count1 == 4 || count1 == 5 || count1 == 6 || count1 == 7 || count1 == 8 || count1 == 9
			{
				
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
						Car_TurnRight1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight1();              //��
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
						Car_Stop();
//						Delay_ms(300);
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		
						Car_Stop();

						LED_ON();  //c������ʾ
						FMQ_ON();
						x=1;

						count1 = count1 +1;
				}
			}
			
			while(count1 == 3)
			{
				
			if(((feedback>=-3) && (feedback<=3)))
				{
						count1 = count1 +1;
				}
			}
			
			while(count1 == 4)         //�ڶ��οհײ��֣�״̬��
			{	
				
					Car_Go3(); 
				
				if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
					  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
					    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
					      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
						    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
						      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )          
				{		
						LED_ON();  //D������ʾ
						FMQ_ON();
						x=1;
					
						count1 = count1 + 1;		
			
//				}	
				
			}
			while(count1 == 5)      //�ڶ��κ��ߣ�״̬��
			{
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
						Car_TurnRight1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight1();              //��
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
						Car_Stop();
//						Delay_ms(300);
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		
//						Car_Go2();
//						Delay_ms(100);
						Car_Stop();
					
						LED_ON();  //A������ʾ
						FMQ_ON();
						x=1;
						count1 = count1 + 1;	
				}
			}

		}
	}
	if (KeyNum == 3)				//����3����
	{	
			while(count2 == 1)	   //���Ƕȣ�״̬1
			{
				
				if((feedback >= -34) && (feedback <= -27))   
				{
					count2 = 2;
					r=0;
					OLED_ShowSignedNum(1,1,feedback,6);
				}		
				
			}
			while(count2 == 2)	   
			{
				Car_Go2();
			
				if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
					  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
					    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
					      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
						    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
						      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )        
				{		
						LED_ON();  //C������ʾ
						FMQ_ON();
						x=1;
						count2 = count2 + 1;		
				}
			}
			while(count2 == 3)  //ѭ��
			{	
				f=1;
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
						Car_TurnRight1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight1();              //��
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
						Car_Stop();
//						Delay_ms(300);
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		
//						Car_Go2();
//						Delay_ms(100);
						if(c<=20)
						{
							Car_TurnLeft2();
							w=1;
						}
						else
						{
							if(c<=30)
							{
							Car_TurnLeft2();
							}
							else{
							c=0;
							f=0;
						
							LED_ON();  	//B������ʾ
							FMQ_ON();
							x=1;
							w=2;
							count2 = count2 +1;}
						}
				}
				while(count2 == 4)
				{
					if((feedback>=-5)&&(feedback<=5))
					{
						r=1;
					}
					if((feedback <= 40) && (feedback >= 32))   //��Ҫ-51.340912����+-0.1�����
					{
						count2 = count2 +1;
						r=0;
					}
				}
				while(count2 == 5)
				{
					Car_Go2();
			
					if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
						(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
						  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
							(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
							  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
								  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
									(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )        
					{		
							LED_ON();  //D������ʾ
							FMQ_ON();
							x=1;
							count2 = count2 + 1;		
					}
				}
				while(count2 == 6)
				{
					f=1;
					if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
						Car_TurnRight1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight1();              //��
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
						
						if(c<=30)
						{
							Car_TurnRight2();
						}
						else
						{
							Car_Stop();
						
						}
//						Delay_ms(300);
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		
						if(c<=30)
						{
							Car_TurnRight2();
						}
						else
						{
							f=0;
							c=0;
							Car_Stop();
					
							LED_ON();  //A������ʾ
							FMQ_ON();
							x=1;
							count2 = count2 + 1;
						}							
				}
				}
			}
	}
	if(KeyNum==4)
	{
			qingling();
		     while(count2 == 1)	   //���Ƕȣ�״̬1
			{
				if((feedback>=-5)&&(feedback<=5))
				{
					r=1;
				}
				
				if((feedback >= -34) && (feedback <= -27))   
				{
					count2 = 2;
					r=0;
					OLED_ShowSignedNum(1,1,feedback,6);
				}		
				
			}
			while(count2 == 2)	   
			{
				
				Car_Go2();
			
				if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
					  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
					    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
					      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
						    (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
						      (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )        
				{		
						LED_ON();  //C������ʾ
						FMQ_ON();
						x=1;
						count2 = count2 + 1;
						r=0;
				}
			}
			qingling();
			while(count2 == 3)  //ѭ��
			{	
				
				if((feedback>=-5)&&(feedback<=5))
				{
					Car_Go2();
					r=1;
					
				}
				if(r==1)
				{
				f=1;
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
					
						Car_TurnRight1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
					
						Car_TurnRight1();              //��
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
					
						Car_TurnRight2();              //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
					
						Car_TurnRight2();             //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{		
						Car_TurnRight2();             //�Ҵ�
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
						
						
							Car_TurnLeft2();
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		

						if(c<=100)
						{
							Car_TurnLeft1();
						}
						else if(c>100)
						{
							c=0;
							f=0;
						
							LED_ON();  	//B������ʾ
							FMQ_ON();
							x=1;
							r=0;

							count2 = count2 +1;
						}
				}
			}
				qingling();
				while(count2 == 4)
				{
					
					
					if((feedback <= 41) && (feedback >= 32.5))   //��Ҫ-51.340912����+-0.1�����
					{
						count2 = count2 +1;
						r=0;
						OLED_ShowSignedNum(2,1,feedback,6);
					}
					
				}
				while(count2 == 5)
				{	
					
					Car_Go2();
					
					if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0)||
						(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0)||
						  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0)||
							(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0)||
							  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)||
								(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)||
								  (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0) || 
									(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) )        
					{		
							LED_ON();  //D������ʾ
							FMQ_ON();
							x=1;
							count2 = count2 + 1;
							r=0;
					}
				}
				qingling();
				while(count2 == 6)
				{
					if((feedback>=-2)&&(feedback<=2))
					{
						Car_Go2();
						r=1;
					}
					if(r==1)
					{
					f=1;
					if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)       
				{
						Car_Go2();                  		//��Ҫ�ܶ���Լ����ã����õ�ֵ��V  ��ΧΪ-5~5ת/��
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //���
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft1();              //��С
				}else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)   
				{
						Car_TurnLeft2();              //��
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)  
				{
						Car_TurnRight1(); 
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						Car_TurnRight1(); 
				}
				
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						
						Car_TurnRight2(); 
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1) 
				{
						
						Car_TurnRight2(); 
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{
						
						Car_TurnRight2(); 
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==0) 
				{	
					
						
							Car_TurnRight2();
						
						
				}
				else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==1)      //ʶ�𵽵ڶ��οհײ���
				{		
						if(c<=100)
						{
							Car_TurnRight1();
						}
						else if(c>100)
						{
							k++;
							f=0;
							c=0;
							//Car_Stop();
					
							LED_ON();  //A������ʾ
							FMQ_ON();
							x=1;
							if(k==4)
							{
							     count2++;
								Car_Stop();
								KeyNum=0;
							}
							else
							{
							    count2 = 1;
							}
							r=0;
							OLED_Clear();
						}							
				}
			}
				}
			}
	}
	}
}

	

/**
  * ��    ����TIM2�жϺ���
  * ��    ������
  * �� �� ֵ����
  * ע������˺���Ϊ�жϺ�����������ã��жϴ������Զ�ִ��
  *           ������ΪԤ����ָ�����ƣ����Դ������ļ�����
  *           ��ȷ����������ȷ���������κβ��죬�����жϺ��������ܽ���
  */
void TIM1_UP_IRQHandler(void)   //��ʱΪ0.01S
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)		//�ж��Ƿ���TIM2�ĸ����¼��������ж�
	{	
		OLED_ShowSignedNum(1, 10, KeyNum, 5);	//����ˢ����ʾ��������õ������ٶ�
		OLED_ShowSignedNum(2, 10, r, 5);
		OLED_ShowSignedNum(3, 10, c, 5);
		OLED_ShowSignedNum(4, 10, count2, 5);
		a = Angle_H;
		Angle = a / 32768 * 180;
		if(f==1)
		{
			c++;
		}
		if((Angle>90))
		{
			Angle=-180+Angle;
		}
		else if(Angle<-90)
		{
			Angle=180+Angle;
		}
		feedback=Angle;
		if(x==1)
		{
			y++;
		}
		if(y>=10)
		{
			LED_OFF();
			FMQ_OFF();
			x=0;
			y=0;
		}
//				feedback = Angle;
//		feedback = Angle;
//		error = feedback-reference;
//		
//		dout = (error - lastError) *kd;
//		//�������
//		float pout = error * kp;
//		//�������
//		integral += error * ki;
//		//�����޷�
//		if(integral > maxIntegral) integral = maxIntegral;
//		else if(integral < -maxIntegral) integral = -maxIntegral;
		
//		if((error<5)&&(error>-5))
//		{
//			integral=integral/2;
//			pout=pout/2;
//		}
		//�������
//		output = pout + dout + integral;
//		if(output > maxOutput) output =  maxOutput;
//		else if(output < -maxOutput) output = -maxOutput;
//		lastError = error;
//		if((error<3)&&(error>-3))
//		{
//			Servo_SetAngle(90);
//		}
//		else
//		{
//			Servo_SetAngle(90-output);
//		}
//		Servo_Set(2800-output);

		if(count1 == 3)   		//�ڶ��ʵ�״̬�����Ƕ�
		{
		reference = 0;    
		
		error = feedback-reference;
		
		dout = (error - lastError) *kd;
		//�������
		float pout = error * kp;
		//�������
		integral += error * ki;
		
		
//		if((error<5)&&(error>-5))
//		{
//			integral=integral/2;
//			pout=pout/2;
//		}
		//�������
		output = pout + dout + integral;
		if(output > maxOutput) output =  maxOutput;
		else if(output < -maxOutput) output = -maxOutput;
		lastError = error;
		
			MotorL1_SetSpeed(0 + output);			//���߲���Ϊ2 * output	
			MotorL2_SetSpeed(0 + output);							
			MotorR1_SetSpeed(0 - output);					
			MotorR2_SetSpeed(0 - output);
			
		}
		///////////////////////
		if((r == 0)&&((KeyNum==4))&&((count2==1)||(count2 ==3)||(count2 ==6)))   	
		{
		reference = 0;    
		
		error = feedback-reference;
		
		dout = (error - lastError) *kd;
		//�������
		float pout = error * kp;
		//�������
		integral += error * ki;
		//�����޷�
		
		
//		if((error<5)&&(error>-5))
//		{
//			integral=integral/2;
//			pout=pout/2;
//		}
		//�������
		output = pout + dout + integral;
		if(output > maxOutput) output =  maxOutput;
		else if(output < -maxOutput) output = -maxOutput;
		lastError = error;
		
			MotorL1_SetSpeed(0 + output);			//���߲���Ϊ2 * output	
			MotorL2_SetSpeed(0 + output);							
			MotorR1_SetSpeed(0 - output);					
			MotorR2_SetSpeed(0 - output);
			
		}
		
		
		if(((KeyNum==3) && (count2 ==1))||((KeyNum==4) && (count2 ==1)&&(r == 1)) )  		//�����ʵ�״̬1���Ƕ�
		{
		
		reference = -32;    
		error = feedback-reference;
		
		dout = (error - lastError) *kd;
		//�������
		float pout = error * kp;
		//�������
		integral += error * ki;
		//�����޷�
		

		//�������
		output = pout + dout + integral;
		if(output > maxOutput) output =  maxOutput;
		else if(output < -maxOutput) output = -maxOutput;
		lastError = error;
		
			MotorL1_SetSpeed(0 + output);			//���߲���Ϊ2 * output	
			MotorL2_SetSpeed(0 + output);							
			MotorR1_SetSpeed(0 - output);					
			MotorR2_SetSpeed(0 - output);
			
		}
		
		if(count2 == 4)   		//�����ʵ�״̬4���Ƕ�
		{
		reference = 39;    
		error = feedback-reference;
		
		dout = (error - lastError) *kd;
		//�������
		float pout = error * kp;
		//�������
		integral += error * ki;
		//�����޷�
	
		
//		if((error<5)&&(error>-5))
//		{
//			integral=integral/2;
//			pout=pout/2;
//		}
		//�������
		output = pout + dout + integral;
		if(output > maxOutput) output =  maxOutput;
		else if(output < -maxOutput) output = -maxOutput;
		lastError = error;
		
			MotorL1_SetSpeed(0 + 1.1*output);			//���߲���Ϊ2 * output	
			MotorL2_SetSpeed(0 + output);							
			MotorR1_SetSpeed(0 - output);					
			MotorR2_SetSpeed(0 - 1.15*output);
			
		}
		
//		OLED_Clear();
////		OLED_ShowNum(1,1,output,5);
////		OLED_ShowNum(2,1,Angle,6);
////		OLED_ShowNum(2,8,feedback,6);
		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);			//���TIM2�����¼����жϱ�־λ
															//�жϱ�־λ�������
															//�����жϽ��������ϵش�����������������
	}
}
void qingling(void)
{
	
	error=0;
	lastError=0;
	integral=0;
}