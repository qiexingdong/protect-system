//#include "text.h"



///*SIM900A�������ݺͺ���*/
//char English_message[]= {"sos help!"};                            //Ӣ�Ķ�������
//char phonenumber[]= {"19702208120"};                            //���ܶ��ŵĺ���

//// ����USART����ͻ�����
//uint8_t ctrlZ = 0x1A;  // Ctrl+Z��ʮ�����Ʊ�ʾ

//// �Զ��巢�ͺ������Զ����\r\n��
//void Send_AT_Command(UART_HandleTypeDef *huart, const char *cmd) {
//    HAL_UART_Transmit(huart, (uint8_t*)cmd, strlen(cmd), 100);  // ����ָ��
//    HAL_UART_Transmit(huart, (uint8_t*)"\r\n", 2, 100);         // ��ӻس�����
//    HAL_Delay(500);  // ����ʱ�ȴ���Ӧ��ʵ�������ģ����Ӧ�Ż���
//}
///**
//  * ��    �������Ͷ���
//  * ��    ������
//  * �� �� ֵ����
//  * ע��������Ͷ��ŵ�ATָ������
//			AT+CMGF=1
//			AT+CSCS="GSM"
//			AT+CSCA?
//			AT+CSMP=17,167,0,0
//			AT+CMGS="13365113887"
//			sos
//			1A��16���ƣ�
//*/
//void SIM900A_Send_English_Message(void) {
//    // 1. ���ö���Ϊ�ı�ģʽ
//    Send_AT_Command(&huart1, "AT+CMGF=1");
//    
//    // 2. �����ַ���ΪGSM
//    Send_AT_Command(&huart1, "AT+CSCS=\"GSM\"");
//    
//    // 3. ��ѯ�������ĺ��루��ѡ��ʵ��ʹ��ʱ������Ҫ���ã�
//    Send_AT_Command(&huart1, "AT+CSCA?");
//    
//    // 4. ���ö��Ų���
//    Send_AT_Command(&huart1, "AT+CSMP=17,167,0,0");
//    
//    // 5. ָ�����պ���
//    Send_AT_Command(&huart1, "AT+CMGS=\"19702208120\"");
//    
//    // 6. �ȴ�SIM900A���� "> " ��ʾ������ʵ�ʼ�⣬�˴��򻯣�
//    HAL_Delay(1000);
//    
//    // 7. ���Ͷ������� "sos"
//    HAL_UART_Transmit(&huart1, (uint8_t*)"SOS", 3, 100);
//    
//    // 8. ����Ctrl+Z������
//    HAL_UART_Transmit(&huart1, &ctrlZ, 1, 100);
//}
