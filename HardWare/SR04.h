#ifndef __SR04_H__
#define __SR04_H__
#include "main.h"
#include "tim.h"
#include "led.h"
#include "OLED.h"
#include "buzzer.h"
#include "string.h"
// ��ȫ�ֶ�����ֵ����
#define THRESHOLD_NEAR   0.10f  
#define THRESHOLD_FAR   0.20f   
extern float distance;
extern char buzzer[];

void SR04_Run(void);

#endif
