//*******************************************************************************	 
//Ӳ��    :���˵���Kinetis���İ� V2.2
//������  :K10DN512VLL10  K60X256VLL10
//����    :YANDLD @ UPC
//E-MAIL  :yandld@126.com
//�޸�����:2012/6/10
//�汾��V2.2
//�Ա���http://upcmcu.taobao.com
//��̳: http://www.tinychip.net
//Copyright(C) YANDLD 2012-2022
//All rights reserved
//********************************************************************************
#ifndef __SPILCD_H__
#define __SPILCD_H__
#include "sys.h"
#include "gpio.h"


#define SPILCD_HARDWARE_SUPPORT  (1)
//�Ƿ�ʹ��Ӳ��SPI�������� ��ҪSPI������֧��

//SPILCD����ͷ�ļ�
//�˿ں궨��
#define SPILCD_CS_PORT    PTA
#define SPILCD_SDA_PORT   PTA
#define SPILCD_SCL_PORT   PTA
#define SPILCD_RS_PORT    PTE
#define SPILCD_RST_PORT   PTA

#define SPILCD_CS_PIN    14
#define SPILCD_SDA_PIN   16
#define SPILCD_SCL_PIN   15
#define SPILCD_RS_PIN    24
#define SPILCD_RST_PIN   13

#define SPILCD_CS     PAout(SPILCD_CS_PIN)
#define SPILCD_SDA    PAout(SPILCD_SDA_PIN)
#define SPILCD_SCL    PAout(SPILCD_SCL_PIN)
#define SPILCD_RS     PEout(SPILCD_RS_PIN)
#define SPILCD_RST    PAout(SPILCD_RST_PIN)

//Һ�����ߴ綨��
#define SPILCD_W 128
#define SPILCD_H 160



//TFTLCD������Ҫ���õĺ���		   
extern uint16_t  POINT_COLOR;//ǰ��ɫ   
extern uint16_t  BACK_COLOR; //����ɫ
//////////////////////////////////////////////////////////////////////
//����
#define ASCII1206	  0
#define ASCII1608	  1
#define ASCII1608C	2
//////////////////////////////////////////////////////////////////////
//������ɫ
#define WHITE						0xFFFF
#define BLACK						0x0000	  
#define BLUE						0x001F  
#define BRED						0XF81F
#define GRED						0XFFE0
#define GBLUE						0X07FF
#define RED							0xF800
#define MAGENTA					0xF81F
#define GREEN						0x07E0
#define CYAN						0x7FFF
#define YELLOW					0xFFE0
#define BROWN						0XBC40 //��ɫ
#define BRRED						0XFC07 //�غ�ɫ
#define GRAY						0X8430 //��ɫ
//GUI��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY							0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
////////////////////////////
//������ʵ�ֵĽӿں���
void LCD_InvDisplayOn(void);
void LCD_InvDisplayOff(void);
void SPILCD_Init(void);
void SPILCD_DrawPoint(uint16_t x,uint16_t y);
void SPILCD_Clear(uint16_t Color);
void SPILCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void SPILCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void SPILCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void SPIDraw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void SPILCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t font,uint8_t mode);
void SPILCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t font);
void LCD_ShowString(uint16_t x,uint16_t y,const char *p);
#endif
