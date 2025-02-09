//#ifndef __Car_H
//#define __Car_H

void Car_Stop(void);

void Car_Go1(void);     //目标V为-5~5
void Car_Go2(void);     //目标V为-5~5
void Car_Go3(void);    //目标V为-5~5   从黑线出来走中间那段空白，需要稍微往右偏一点 可以根据实际情况调整

void Car_TurnRight1(void);         //建议为1-2之间好控制   
void Car_TurnRight2(void);
void Car_TurnLeft2(void);
void Car_TurnLeft1(void);         //建议为1-2之间好控制 

void Car_Spin(void);         //建议为2-3之间好控制 


////void Car_Stop(void);
////void Car_Up(void);
////void Car_Down(void);
////void Car_TurnRight1(void);
////void Car_TurnLeft1(void);

////void Car_Spin(void);

//#endif
