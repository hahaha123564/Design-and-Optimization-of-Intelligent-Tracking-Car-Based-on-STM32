#include "stm32f10x.h"                  // Device header

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWM_Init(void)     
{    /*电机PWM配置*/
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);			//开启TIM5的时钟    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                 //之前TIM2用的是GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;    //查询引脚定义表，TIM5的四个通道对应的是pb0.1.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							//将PA2引脚初始化为复用推挽输出	
																	//受外设控制的引脚，均需要配置为复用模式
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM5);		//选择TIM5为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
 	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 7200 - 1;                 //计数周期，即ARR的值   为了限制v<5,speed(就是ccr) = 1456*v  所以ccr最大值也就是arr = 1456*5=7280
	TIM_TimeBaseInitStructure.TIM_Prescaler = 100 - 1;               //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM5的时基单元
	
	/*输出比较初始化*/ 
	TIM_OCInitTypeDef TIM_OCInitStructure;							//定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);                         //结构体初始化，若结构体没有完整赋值
//	       TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	                                                         //则最好执行此函数，给结构体所有成员都赋一个默认值
	                                                                //避免结构体初值不确定的问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //输出比较模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								//初始的CCR值
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);                        //将结构体变量交给TIM_OC1Init，配置TIM5的输出比较通道1
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);                        //将结构体变量交给TIM_OC3Init，配置TIM5的输出比较通道3
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);                       
	TIM_OC4Init(TIM5, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);   //输出极性:TIM输出比较极性高
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);   //使能TIM5在CCR3上的预装载寄存器
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
		/*TIM使能*/
	TIM_ARRPreloadConfig(TIM5,ENABLE);//开启预装载
	TIM_Cmd(TIM5, ENABLE);	
	//使能TIM4，定时器开始运行
//	TIM4->CCR1 = 0;//设置输出比较值
//	TIM4->CCR2 = 0;
//	TIM4->CCR3 = 0;//设置输出比较值
//	TIM4->CCR4 = 0;

/*现在只是单独写编码器电机的小车，用不到舵机，先注释掉*/
//	/*舵机PWM配置*/
//	/*开启时钟*/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//开启TIM2的时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			//开启GPIOA的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure2;
//	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
//	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure2);							//将PA1,3引脚初始化为复用推挽输出	
//																	//受外设控制的引脚，均需要配置为复用模式
//	
//	/*配置时钟源*/
//	TIM_InternalClockConfig(TIM2);		//选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
//	
//	/*时基单元初始化*/
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure2;				//定义结构体变量
//	TIM_TimeBaseInitStructure2.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
//	TIM_TimeBaseInitStructure2.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
//	TIM_TimeBaseInitStructure2.TIM_Period = 20000 - 1;				//计数周期，即ARR的值
//	TIM_TimeBaseInitStructure2.TIM_Prescaler = 72 - 1;				//预分频器，即PSC的值
//	TIM_TimeBaseInitStructure2.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure2);             //将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元
//	
//	/*输出比较初始化*/ 
//	TIM_OCInitTypeDef TIM_OCInitStructure2;							//定义结构体变量
//	TIM_OCStructInit(&TIM_OCInitStructure2);                         //结构体初始化，若结构体没有完整赋值
//	                                                                //则最好执行此函数，给结构体所有成员都赋一个默认值
//	                                                                //避免结构体初值不确定的问题
//	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;               //输出比较模式，选择PWM模式1
//	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，选择为高，若选择极性为低，则输出高低电平取反
//	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
//	TIM_OCInitStructure2.TIM_Pulse = 0;								//初始的CCR值
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure2);                        //将结构体变量交给TIM_OC2Init，配置TIM2的输出比较通道2
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure2);
//	
//	/*TIM使能*/
//	TIM_Cmd(TIM2, ENABLE);			//使能TIM2，定时器开始运行
}
void PWM_SetCompare1(float Compare)	
{
	TIM_SetCompare1(TIM5, Compare);//TIM_SetCompare1(TIM4, Compare=Compare/2+50);		//设置CCR1的值
}
void PWM_SetCompare3(float Compare)
{
	TIM_SetCompare3(TIM5, Compare);//TIM_SetCompare3(TIM4, Compare=Compare/2+50);		//设置CCR3的值
}
void PWM_SetCompare2(float Compare)
{
	TIM_SetCompare2(TIM5, Compare);//TIM_SetCompare2(TIM4, Compare=Compare/2+50);		//设置CCR2的值
}
void PWM_SetCompare4(float Compare)
{
	TIM_SetCompare4(TIM5, Compare);//TIM_SetCompare4(TIM4, Compare=Compare/2+50);		//设置CCR4的值
}

//void PWM_SetCompare22(uint16_t Compare)
//{
//	TIM_SetCompare2(TIM2, Compare);		//设置舵机TIM2的CCR2的值
//}
//void PWM_SetCompare24(uint16_t Compare)
//{
//	TIM_SetCompare4(TIM2, Compare);		//设置舵机TIM2的CCR4的值
//}
