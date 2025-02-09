#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

extern char Serial_RxPacket[];
extern uint8_t Serial_RxFlag;
//extern short Angle;
extern short Angle_H;     //传过来数据的16进制,Angle_H5
extern short Angle_H5;     //传过来数据的16进制
extern int16_t Angle_H1;
extern int16_t Angle_H2;
extern int16_t Angle_H3;
extern int16_t Angle_H4;

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

#endif
