#ifndef __SIM900A_H__
#define __SIM900A_H__

#include "main.h"
#include "GPS.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "stdarg.h"
#include "stdbool.h"
#include "ATGM336H.h"

// ����ATָ��Ļ���������ֹ�����
#define AT_BUFFER_SIZE 128
extern char at_buffer[AT_BUFFER_SIZE];
extern char English_message[];  //Ӣ�Ķ�������
extern char phonenumber[];      //���ܶ��ŵĺ���
// ����USART����ͻ�����
extern UART_HandleTypeDef huart1;
extern uint8_t ctrlZ;  // Ctrl+Z��ʮ�����Ʊ�ʾ

typedef struct {
    uint32_t seconds;  // �ܵ���ʱ����
    uint8_t is_running;      // ����ʱ״̬��־
} CountDelay;
extern volatile CountDelay cd; // volatile��֤�໷�����ʰ�ȫ

// �����㹻��Ļ��������洢��ʽ�������Ϣ
extern char message_buffer[100];
void SIM900A_Send_English_Message(const char *number, const char *message);
void TriggerEmergencySMS(void);
#endif
