#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);

void MotorL1_UP(void);	//L1�ֵ�ǰ�������˺�ֹͣ	
void MotorL1_STOP(void);
void MotorL1_DOWN(void);

void MotorL2_UP(void);  //L2�ֵ�ǰ�������˺�ֹͣ
void MotorL2_STOP(void);
void MotorL2_DOWN(void);


void MotorR1_UP(void);  //R1�ֵ�ǰ�������˺�ֹͣ
void MotorR1_STOP(void);
void MotorR1_DOWN(void);

void MotorR2_UP(void);  //R2�ֵ�ǰ�������˺�ֹͣ
void MotorR2_STOP(void);
void MotorR2_DOWN(void);

//void Motor_SetSpeed(int8_t Speed);
void MotorL1_SetSpeed(int16_t Speed3);   //�������speed��ccr������ռ�ձȵģ�main���������V����ת/��Ϊ��λ�������ٶ�
void MotorR1_SetSpeed(int16_t Speed1);
void MotorL2_SetSpeed(int16_t Speed4);        
void MotorR2_SetSpeed(int16_t Speed2);

#endif
