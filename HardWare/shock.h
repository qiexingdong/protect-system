#ifndef __SHOCK_H__
#define __SHOCK_H__
#include "main.h"
#include "tim.h"

//�ṹ��
typedef struct {
    uint8_t Motor;      //�����״̬��־,0Ϊ�رգ�1Ϊ����
} MotorStatus;
extern volatile MotorStatus mot; // volatile��֤�໷�����ʰ�ȫ

void Motor_Init(void);
void Motor_ON(void);
void Motor_OFF(void);

#endif




