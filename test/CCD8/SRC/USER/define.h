#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "sys.h"
#include "data_sent.h"

extern uint16_t FTMDuty;//���ռ�ձ�
extern uint16_t FTMDuty_1;//���ռ�ձ�
extern uint16_t FTMDuty_2;
extern uint16_t FTMDuty_3;
extern int8_t a1,a2,a3,a4,a5,a6,a7;//pֵ
extern int16_t Value;//��ֵ

extern uint8_t P1[128];//�ɼ�����
extern uint8_t Send_Data[200];
extern uint8_t oled_data[8][128];

extern uint8_t CenterLast[5];//��¼��ȥ�峡����λ��
extern uint8_t Center;//����
extern uint8_t LeftLast[5];//��¼��ȥ�峡����λ��
extern uint8_t Left;//����
extern uint8_t RightLast[5];//��¼��ȥ�峡����λ��
extern uint8_t Right;//����
extern uint8_t Width;//�������

extern uint8_t flag_test;//���Ա�־λ
extern uint8_t flag_run;//���б�־λ
extern uint8_t flag_sd_d;//sd����ȡ��־λ
extern uint8_t flag_sd_x;//sd��д���־λ
extern uint8_t flag_20ms;//�ɼ��жϱ�־λ
extern uint8_t flag_JianSu;//���ٱ�־λ
extern uint8_t flag_ShiZi;//ʮ�ֱ�־λ

extern uint32_t SD_D;//SD������
extern uint32_t SD_X;

extern int8_t yw;//�˵���λ

extern Data_Type *Sent_Data;

#endif