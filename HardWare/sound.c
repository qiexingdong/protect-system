#include "sound.h"

char voice[] = "��";
char shock[] = "��";
volatile CountdownTimer cdt;
/**
  * ��    ������������������
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LM393_Run(void) {
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET) {
		cdt.is_running = 1;
		cdt.seconds = 2;
		__HAL_TIM_SET_COUNTER(&htim4, 0);//��ʱ������
        HAL_TIM_Base_Start_IT(&htim4);//��ʼ3��������
        strcpy(voice,"��");
        strcpy(shock,"��");
        Motor_ON();
    }
    else {
		if(cdt.is_running == 0){
		strcpy(voice,"��");
        strcpy(shock,"��");
        Motor_OFF();
		}
    }
//		OLED_Printf(0,48,8,"�����:%s               ",shock);
        OLED_Printf(0,32,8,"�쳣����:%s               ",voice);
        OLED_Update();
}
