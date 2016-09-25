/**
  ******************************************************************************
  * @file    key.h
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   ����ԭ�Ӻ˺��İ� BSP���� KEY����
  ******************************************************************************
  */
#ifndef _KEY_H_
#define _KEY_H_

#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

//LEDͷ�ļ�
//IO ��
#define KEY1_PORT  PTB
//����
#define KEY1_PIN  (9)
//λ��
#define KEY1      PBin(KEY1_PIN)
//������ƽֵ����
#define KEY_STATE_DOWN  (1)  //����ʱ�Ǹߵ�ƽ
#define KEY_STATE_UP    (!KEY_STATE_DOWN)

//KEY����ֵ ���� 
#define KEY_NO_KEY   (uint8_t)(0)           //�޼� 
#define KEY_SINGLE   (uint8_t)(1)           //���� 
#define KEY_DOUBLE   (uint8_t)(2)           //˫�� 
#define KEY_LONG     (uint8_t)(3)           //���� 

//��������ʵ�ֵĽӿں���	 
void KEY_Init(void);
uint8_t KEY_GetKeyValue(void);
uint8_t KEY_Scan(void);

#ifdef __cplusplus
}
#endif

#endif
