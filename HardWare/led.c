 #include "led.h"

/**
  * ��    ����PC13��0
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PC13_On(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}
/**
  * ��    ����PC13��1
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PC13_Off(void) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}
/**
  * ��    ������תPC13����
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PC13_Reverse(void) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
/**
  * ��    ����PA5��0
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PA5_On(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
/**
  * ��    ����PA5��1
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PA5_Off(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}
/**
  * ��    ������תPA5����
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void LED_PA5_Reverse(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
