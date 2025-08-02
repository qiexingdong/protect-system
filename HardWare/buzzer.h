#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "main.h"
#include "tim.h"
//�ṹ��
typedef struct {
    uint8_t State;      // ������״̬��־,0Ϊ�رգ�1Ϊ����
	uint32_t seconds;  // �ܵ���ʱ����
    uint8_t is_running;      // ����ʱ״̬��־
} BuzzerStatus;
extern volatile BuzzerStatus buz; // volatile��֤�໷�����ʰ�ȫ
void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void SetBuzz(uint8_t num);
#endif
