#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);

void MotorL1_UP(void);	//L1轮的前进，后退和停止	
void MotorL1_STOP(void);
void MotorL1_DOWN(void);

void MotorL2_UP(void);  //L2轮的前进，后退和停止
void MotorL2_STOP(void);
void MotorL2_DOWN(void);


void MotorR1_UP(void);  //R1轮的前进，后退和停止
void MotorR1_STOP(void);
void MotorR1_DOWN(void);

void MotorR2_UP(void);  //R2轮的前进，后退和停止
void MotorR2_STOP(void);
void MotorR2_DOWN(void);

//void Motor_SetSpeed(int8_t Speed);
void MotorL1_SetSpeed(int16_t Speed3);   //这里面的speed是ccr来调制占空比的，main函数里面的V是以转/秒为单位的物理速度
void MotorR1_SetSpeed(int16_t Speed1);
void MotorL2_SetSpeed(int16_t Speed4);        
void MotorR2_SetSpeed(int16_t Speed2);

#endif
