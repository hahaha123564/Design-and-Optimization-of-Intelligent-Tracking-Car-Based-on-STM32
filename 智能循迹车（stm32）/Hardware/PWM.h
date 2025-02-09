#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
//void PWM_SetCompare3(uint16_t Compare);
void PWM_SetCompare1(float Compare);

void PWM_SetCompare3(float Compare);

void PWM_SetCompare2(float Compare);

void PWM_SetCompare4(float Compare);

//void PWM_SetCompare22(uint16_t Compare);  //舵机TIM2的2通道

//void PWM_SetCompare24(uint16_t Compare);  //舵机TIM2的4通道

#endif
