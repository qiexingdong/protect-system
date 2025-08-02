#ifndef __SOUND_H__
#define __SOUND_H__
#include "main.h"
#include "OLED.h"
#include "string.h"
#include "shock.h"

extern char voice[];
extern char shock[];

typedef struct {
    uint32_t seconds;  // �ܵ���ʱ����
    uint8_t is_running;      // ����ʱ״̬��־
} CountdownTimer;
extern volatile CountdownTimer cdt; // volatile��֤�໷�����ʰ�ȫ

void LM393_Run(void);



#endif
