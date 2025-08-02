#ifndef __ATGM336H_H
#define __ATGM336H_H

#include "usart.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
#include "OLED.h"

#define USART_REC_LEN  		200	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define false 0
#define true 1

//�������鳤��
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2



typedef struct SaveData
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//�Ƿ��ȡ��GPS����
	char isParseData;	//�Ƿ�������
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//����
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//��λ��Ϣ�Ƿ���Ч
} _SaveData;

// ��γ������
typedef struct _LatitudeAndLongitude_s
{
	float latitude;			// γ��
	float longitude;		// ����

	char N_S;	// ����
	char E_W;	// ����
}LatitudeAndLongitude_s;

extern char rxdatabufer;
extern u16 point1;
extern _SaveData Save_Data;
extern LatitudeAndLongitude_s g_LatAndLongData;
// ���봮�ڽ����ж���
void atgm336h_UART_RxCpltCallback(UART_HandleTypeDef *huart);

// ��ʼ��
void atgm336h_init(void);

// ����ṹ������
void clrStruct(void);

// �������
void parseGpsBuffer(void);

// ��ӡ����
void printGpsBuffer(void);

#endif	// __ATGM336H_H


