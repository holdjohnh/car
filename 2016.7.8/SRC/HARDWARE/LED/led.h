/***********************************************************************************************
//CH_Kinetis������  V2.3   
//����    :YANDLD 
//E-MAIL  :yandld@126.com
//�޸�����:2013/2/14
//�汾��V2.3
//�Ա���http://upcmcu.taobao.com
//QQ    1453363089
//Copyright(C) YANDLD 2012-2022
//All rights reserved
************************************************************************************************/
#ifndef __LED_H__
#define __LED_H__
#include "gpio.h"

//LEDͷ�ļ�
//IO ��
#define LED0_PORT PTD
#define LED1_PORT PTD
//����
#define LED0_PIN  7
#define LED1_PIN  0
//λ��
#define LED0      PDout(LED0_PIN) 
#define LED1      PDout(LED1_PIN) 
void LED_Init(void);
#endif
