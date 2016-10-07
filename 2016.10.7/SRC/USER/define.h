#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "sys.h"
#include "data_sent.h"


extern Data_Type *Sent_Data;
extern uint8_t TIME1flag_20ms;

extern unsigned char AverageValue;
//extern int i,q;
extern uint16_t FTMDuty;
extern uint16_t FTMDuty_1;
extern uint16_t FTMDuty_2;
extern uint16_t a1,a2,a3,a4,a5,a6,a7,a8,a9;
extern int8_t pd;

extern uint8_t Pixel[128];
extern uint8_t oled_data[8][128];
extern uint8_t Send_Data[200];
extern int16_t sendData[200];	

extern uint16_t CenterLast[5];//��¼��ȥ�峡����λ��
extern uint16_t Center;//����
extern uint16_t LeftLast;//��¼��ȥ�峡����λ��
extern uint16_t Left;//����
extern uint16_t RightLast;//��¼��ȥ�峡����λ��
extern uint16_t Right;//����

extern uint16_t Budao;
extern uint16_t hang;
extern uint16_t leixin;
extern uint16_t leixin_last[5];
extern uint16_t saoxian;
extern uint8_t flag_black;
extern uint8_t flag_miss;
extern uint8_t flag_miss_record;
extern uint8_t Cross_flag;
extern uint8_t Cross_flag_wan;
extern uint8_t Cross_flag_time;
extern uint16_t jiasuflag;
extern uint16_t jiansuflag;
extern uint16_t zhidaoflag;
extern uint16_t zhidaoflag_save;

extern uint32_t SD_X;
extern uint32_t SD_D;

extern uint8_t Flag;
extern uint8_t SD_Flag;


#endif
