#include "atgm336h.h"


char rxdatabufer;
u16 point1 = 0;

_SaveData Save_Data;
LatitudeAndLongitude_s g_LatAndLongData =
{
	.E_W = 0,
	.N_S = 0,
	.latitude = 0.0,
	.longitude = 0.0
};

// ����1�жϷ������
// ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
char USART_RX_BUF[USART_REC_LEN];	// ���ջ���,���USART_REC_LEN���ֽ�.
uint8_t uart_A_RX_Buff;

// ����״̬
// bit15��	������ɱ�־
// bit14��	���յ�0x0d
// bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;	// ����״̬���

void atgm336h_init(void)
{
	clrStruct();
	HAL_UART_Receive_IT(&huart2, &uart_A_RX_Buff, 1);
}

void atgm336h_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
//		printf("%c", uart_A_RX_Buff);
		if(uart_A_RX_Buff == '$')
		{
			point1 = 0;
		}
		USART_RX_BUF[point1++] = uart_A_RX_Buff;

		if(USART_RX_BUF[0] == '$' && USART_RX_BUF[4] == 'M' && USART_RX_BUF[5] == 'C')	//ȷ���Ƿ��յ�"GPRMC/GNRMC"��һ֡����
		{
			if(uart_A_RX_Buff == '\n')
			{
				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
				memcpy(Save_Data.GPS_Buffer, USART_RX_BUF, point1); 	//��������
				Save_Data.isGetData = true;
				point1 = 0;
				memset(USART_RX_BUF, 0, USART_REC_LEN);      //���
			}
		}
		if(point1 >= USART_REC_LEN)
		{
			point1 = USART_REC_LEN;
		}

		HAL_UART_Receive_IT(&huart2, &uart_A_RX_Buff, 1);
	}
}

u8 Hand(char *a)	// ��������ʶ����
{
    if(strstr(USART_RX_BUF, a)!=NULL)
	    return 1;
	else
		return 0;
}

void CLR_Buf(void)	// ���ڻ�������
{
	memset(USART_RX_BUF, 0, USART_REC_LEN);	//���
  point1 = 0;
}

void clrStruct(void)
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);	//���
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
}

void errorLog(int num)
{

	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer(void)
{
	char *subString;
	char *subStringNext;
	char i = 0;

	uint16_t Number=0, Integer=0, Decimal=0;


	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
//		printf("**************\r\n");
//		printf("%s\r\n", Save_Data.GPS_Buffer);

		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2];
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W

						default:break;
					}
					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2);	//��������
				}
			}
		}

		if (Save_Data.isParseData)
		{
			if(Save_Data.isUsefull)
			{
				// ��ȡ N/S �� E/W
				g_LatAndLongData.N_S = Save_Data.N_S[0];
				g_LatAndLongData.E_W = Save_Data.E_W[0];

				// ��ȡγ��
				for(uint8_t i=0; i<9; i++)
				{
					if(i<2)
					{
						Number *= 10;
						Number += Save_Data.latitude[i]-'0';
					}
					else if(i<4)
					{
						Integer *= 10;
						Integer += Save_Data.latitude[i]-'0';
					}
					else if(i==4);
					else if(i<9)
					{
						Decimal *= 10;
						Decimal += Save_Data.latitude[i]-'0';
					}
				}
				g_LatAndLongData.latitude = 1.0*Number + (1.0*Integer+1.0*Decimal/10000)/60;

				Number = 0;
				Integer = 0;
				Decimal = 0;

				// ��ȡ����
				for(uint8_t i=0; i<10; i++)
				{
					if(i<3)
					{
						Number *= 10;
						Number += Save_Data.longitude[i]-'0';
					}
					else if(i<5)
					{
						Integer *= 10;
						Integer += Save_Data.longitude[i]-'0';
					}
					else if(i==5);
					else if(i<10)
					{
						Decimal *= 10;
						Decimal += Save_Data.longitude[i]-'0';
					}
				}
				g_LatAndLongData.longitude = 1.0*Number + (1.0*Integer+1.0*Decimal/10000)/60;
			}
		}
	}
}

void printGpsBuffer(void)
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;

//		printf("Save_Data.UTCTime = %s\r\n", Save_Data.UTCTime);

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("Save_Data.latitude = %s\r\n", Save_Data.latitude);
			printf("Save_Data.N_S = %s", Save_Data.N_S);
			printf("Save_Data.longitude = %s", Save_Data.longitude);
			printf("Save_Data.E_W = %s\r\n", Save_Data.E_W);
			printf("latitude: %c,%.4f\r\n", g_LatAndLongData.N_S, g_LatAndLongData.latitude);
			printf("longitude: %c,%.4f\r\n", g_LatAndLongData.E_W, g_LatAndLongData.longitude);
			
		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
	}
}

