#include "stm32f10x.h"                  // Device header

/**
  * ��    ����PWM��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void PWM_Init(void)     
{    /*���PWM����*/
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);			//����TIM5��ʱ��    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                 //֮ǰTIM2�õ���GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;    //��ѯ���Ŷ����TIM5���ĸ�ͨ����Ӧ����pb0.1.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//��PA2���ų�ʼ��Ϊ�����������	
																	//��������Ƶ����ţ�����Ҫ����Ϊ����ģʽ
	
	/*����ʱ��Դ*/
	TIM_InternalClockConfig(TIM5);		//ѡ��TIM5Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
	
	/*ʱ����Ԫ��ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//����ṹ�����
 	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 7200 - 1;                 //�������ڣ���ARR��ֵ   Ϊ������v<5,speed(����ccr) = 1456*v  ����ccr���ֵҲ����arr = 1456*5=7280
	TIM_TimeBaseInitStructure.TIM_Prescaler = 100 - 1;               //Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM5��ʱ����Ԫ
	
	/*����Ƚϳ�ʼ��*/ 
	TIM_OCInitTypeDef TIM_OCInitStructure;							//����ṹ�����
	TIM_OCStructInit(&TIM_OCInitStructure);                         //�ṹ���ʼ�������ṹ��û��������ֵ
//	       TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	                                                         //�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ
	                                                                //����ṹ���ֵ��ȷ��������
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //����Ƚ�ģʽ��ѡ��PWMģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //������ԣ�ѡ��Ϊ�ߣ���ѡ����Ϊ�ͣ�������ߵ͵�ƽȡ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;								//��ʼ��CCRֵ
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC1Init������TIM5������Ƚ�ͨ��1
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC3Init������TIM5������Ƚ�ͨ��3
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);                       
	TIM_OC4Init(TIM5, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);   //�������:TIM����Ƚϼ��Ը�
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);   //ʹ��TIM5��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
		/*TIMʹ��*/
	TIM_ARRPreloadConfig(TIM5,ENABLE);//����Ԥװ��
	TIM_Cmd(TIM5, ENABLE);	
	//ʹ��TIM4����ʱ����ʼ����
//	TIM4->CCR1 = 0;//��������Ƚ�ֵ
//	TIM4->CCR2 = 0;
//	TIM4->CCR3 = 0;//��������Ƚ�ֵ
//	TIM4->CCR4 = 0;

/*����ֻ�ǵ���д�����������С�����ò����������ע�͵�*/
//	/*���PWM����*/
//	/*����ʱ��*/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//����TIM2��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//����GPIOA��ʱ��
//	
//	/*GPIO��ʼ��*/
//	GPIO_InitTypeDef GPIO_InitStructure2;
//	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
//	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure2);							//��PA1,3���ų�ʼ��Ϊ�����������	
//																	//��������Ƶ����ţ�����Ҫ����Ϊ����ģʽ
//	
//	/*����ʱ��Դ*/
//	TIM_InternalClockConfig(TIM2);		//ѡ��TIM2Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
//	
//	/*ʱ����Ԫ��ʼ��*/
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure2;				//����ṹ�����
//	TIM_TimeBaseInitStructure2.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
//	TIM_TimeBaseInitStructure2.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
//	TIM_TimeBaseInitStructure2.TIM_Period = 20000 - 1;				//�������ڣ���ARR��ֵ
//	TIM_TimeBaseInitStructure2.TIM_Prescaler = 72 - 1;				//Ԥ��Ƶ������PSC��ֵ
//	TIM_TimeBaseInitStructure2.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure2);             //���ṹ���������TIM_TimeBaseInit������TIM2��ʱ����Ԫ
//	
//	/*����Ƚϳ�ʼ��*/ 
//	TIM_OCInitTypeDef TIM_OCInitStructure2;							//����ṹ�����
//	TIM_OCStructInit(&TIM_OCInitStructure2);                         //�ṹ���ʼ�������ṹ��û��������ֵ
//	                                                                //�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ
//	                                                                //����ṹ���ֵ��ȷ��������
//	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;               //����Ƚ�ģʽ��ѡ��PWMģʽ1
//	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;       //������ԣ�ѡ��Ϊ�ߣ���ѡ����Ϊ�ͣ�������ߵ͵�ƽȡ��
//	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ��
//	TIM_OCInitStructure2.TIM_Pulse = 0;								//��ʼ��CCRֵ
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure2);                        //���ṹ���������TIM_OC2Init������TIM2������Ƚ�ͨ��2
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure2);
//	
//	/*TIMʹ��*/
//	TIM_Cmd(TIM2, ENABLE);			//ʹ��TIM2����ʱ����ʼ����
}
void PWM_SetCompare1(float Compare)	
{
	TIM_SetCompare1(TIM5, Compare);//TIM_SetCompare1(TIM4, Compare=Compare/2+50);		//����CCR1��ֵ
}
void PWM_SetCompare3(float Compare)
{
	TIM_SetCompare3(TIM5, Compare);//TIM_SetCompare3(TIM4, Compare=Compare/2+50);		//����CCR3��ֵ
}
void PWM_SetCompare2(float Compare)
{
	TIM_SetCompare2(TIM5, Compare);//TIM_SetCompare2(TIM4, Compare=Compare/2+50);		//����CCR2��ֵ
}
void PWM_SetCompare4(float Compare)
{
	TIM_SetCompare4(TIM5, Compare);//TIM_SetCompare4(TIM4, Compare=Compare/2+50);		//����CCR4��ֵ
}

//void PWM_SetCompare22(uint16_t Compare)
//{
//	TIM_SetCompare2(TIM2, Compare);		//���ö��TIM2��CCR2��ֵ
//}
//void PWM_SetCompare24(uint16_t Compare)
//{
//	TIM_SetCompare4(TIM2, Compare);		//���ö��TIM2��CCR4��ֵ
//}
