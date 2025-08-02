#include "SR04.h"

char buzzer[] = "��";
float distance = 0;

/**
  * ��    ��������������������
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void SR04_Run(void) {
    //�ü�����cnt����
    __HAL_TIM_SET_COUNTER(&htim1,0);
    //���cc1/cc2��־λ
    __HAL_TIM_CLEAR_FLAG(&htim1,TIM_FLAG_CC1);
    __HAL_TIM_CLEAR_FLAG(&htim1,TIM_FLAG_CC2);
    //�������벶��
    HAL_TIM_IC_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim1,TIM_CHANNEL_2);
    //��trig��������
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
    for(uint32_t i = 0; i < 10; i++);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
    //�ȴ���������
    uint8_t success  = 0;
    uint32_t expireTime = HAL_GetTick() + 50;
    while(expireTime > HAL_GetTick()) {
        uint32_t cc1Flag = __HAL_TIM_GET_FLAG(&htim1,TIM_FLAG_CC1);
        uint32_t cc2Flag = __HAL_TIM_GET_FLAG(&htim1,TIM_FLAG_CC2);
        if(cc1Flag && cc2Flag) {
            success = 1;
            break;
        }
    }
    //�رն�ʱ��
    HAL_TIM_IC_Stop(&htim1,TIM_CHANNEL_1);
    HAL_TIM_IC_Stop(&htim1,TIM_CHANNEL_2);
    //����������
    if(success == 1) {
        uint16_t ccr1 = __HAL_TIM_GET_COMPARE(&htim1,TIM_CHANNEL_1);
        uint16_t ccr2 = __HAL_TIM_GET_COMPARE(&htim1,TIM_CHANNEL_2);
        float fulseWidth = (ccr2-ccr1) * 1e-6f;
        distance = 340.0f * fulseWidth / 2.0f;

        if (distance <= THRESHOLD_NEAR) {
            if (buz.State != 2) { // ״̬��������Ϊ2
                buz.State = 2;
                buz.is_running = 0;
                buz.seconds = 1; // ��ʼ����ȷ���״δ���
				HAL_TIM_Base_Start_IT(&htim2);
            }
        } else if (distance <= THRESHOLD_FAR) {
            if (buz.State != 1) { // ״̬��������Ϊ1
                buz.State = 1;
                buz.is_running = 0;
                buz.seconds = 2; // ��ʼ��
				HAL_TIM_Base_Start_IT(&htim2);
            }
        } else {
            if (buz.State != 0) { // ״̬��������Ϊ0
                buz.State = 0;
                buz.is_running = 0;
                buz.seconds = 0;
            }
        }
        switch(buz.State) {
        case 0:
            LED_PA5_Off();
            strcpy(buzzer,"��");
            break;
        case 1:
            LED_PA5_On();
            strcpy(buzzer,"��");
            break;
        case 2:
            LED_PA5_On();
            strcpy(buzzer,"��");
            break;
        }
    }
    OLED_Printf(0,0,8,"����:%.2fm               ",distance);
    OLED_Printf(0,16,8,"������:%s               ",buzzer);
    OLED_Update();
}
