#include "sys.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "wdog.h"
#include "pit.h"
#include "rtc.h"
#include "dma.h"
#include "ftm.h"
#include "lptm.h"
#include "adc.h"
#include "dac.h"
#include "tsi.h"
#include "spi.h"
#include "enet.h"
#include "i2c.h"
#include "pdb.h"
#include "can.h"
#include "sd.h"
#include "flash.h"
#include "spiflash.h"
#include "spilcd.h"
#include "stdio.h"
#include "mma845x.h"
#include "oled.h"
#include "ccd.h"
#include "data_sent.h"
#include "menu.h"
#include "define.h"
#include "all.h"

uint16_t FTMDuty=4400;//���ռ�ձ�
uint16_t FTMDuty_1=1700;//���ռ�ձ�
uint16_t FTMDuty_2=1500;
uint16_t FTMDuty_3=1300;
int8_t a1=1,a2=5,a3=10,a4=15,a5=15,a6=15,a7=15;//pֵ
int16_t Value=200;//��ֵ

uint8_t P1[128];//�ɼ�����
uint8_t Send_Data[200];
uint8_t oled_data[8][128];
int16_t sendData[200];

uint8_t Center=63;//����
uint8_t Left;//����
uint8_t Right;//����
uint8_t Width;//�������

uint8_t flag_test=0;//���Ա�־λ
uint8_t flag_run=0;//���б�־λ
uint8_t flag_sd_d=0;//sd����ȡ��־λ
uint8_t flag_sd_x=0;//sd��д���־λ
uint8_t flag_20ms=0;//�ɼ��жϱ�־λ
uint8_t flag_JianSu=0;//���ٱ�־λ

uint32_t SD_D=0;//SD������
uint32_t SD_X=0;

int8_t yw=0;

int main(void)
{
	//int q = 0;
	int i;	
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M);
	
	YinJiao_Init();
	DelayInit();
	OLED_Init();
	DataInit();
	Data_Uart_Init();
	Sd_Init();	
	
	while(1)
	{
		//�˵�
		Menu_Show();
/*******************************����*********************************/		
		while(flag_test)
		{
			Menu_SD_X();
			if(flag_20ms==1)
			{
				flag_20ms=0;
				CCD_ImageCapture(P1);
				if(flag_sd_x == 1)
				{
					Sd_X();
				}
				oled_collect();
				oled_show();
				erzhi();
				LB();				
			}
			OLED_Write_Num3(13,0,Value);
			//Value
			CCD_Image();			
//			OLED_Write_Num4(0,0,FTMDuty);
			//�˳�
			Menu_Quit();
		}
/*********************************�ܳ�************************************/		
		while(flag_run)
		{
			if(flag_20ms==1)
			{
				flag_20ms=0;
				CCD_ImageCapture(P1);
				for(i = 0; i < 128; i++)
				{
					Sent_Data->Pixels[i] = P1[i];
				}
				UART_Send_Con();
				erzhi();
				LB();
			}
			CCD_Image();
		}
/*********************************�ϴ���λ��*************************************/
		while(flag_sd_d==1)
		{
			Sd_D();
			UART_Send_Con();
		}
/**********************************************************************/
	}
}


void assert_failed(uint8_t* file, uint32_t line)
{
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}




