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

void key_scan();								//�������
uint8_t i = 0;									//��λ��ͷ��λ��
uint32_t flag = 0;							//���뿴ռ�ձ�
uint8_t run = 0;
uint16_t FTMDuty_left = 8000;   //����ռ�ձ�
uint16_t FTMDuty_right = 8000;

uint16_t x1,x2,x3,x4;

uint16_t FTMDuty_reverse_left = 8000;   //����ռ�ձ�
uint16_t FTMDuty_reverse_right = 8000;

uint8_t p = 0;									//ָ�����ҵ�ռ�ձ�
uint16_t sub = 1400;

//uint8_t buffer1,buffer2;
//uint8_t a,b;

int main(void)
{
	//*******************************************************
	//TypeDef
	FTM_InitTypeDef FTM_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct1;
	//*******************************************************	
	
	//��ʼ��ϵͳʱ�� ʹ���ⲿ50M���� PLL��Ƶ��100M
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M);
		
	//*******************************************************
	//������ʼ��
	GPIO_InitStruct1.GPIOx=PTB;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;  
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_2;                  
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(&GPIO_InitStruct1);
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_4; 
	GPIO_Init(&GPIO_InitStruct1);
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_6; 
	GPIO_Init(&GPIO_InitStruct1);
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_11; 
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTB;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_28;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTA;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_16;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTA;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIOx = PTA;
	GPIO_Init(&GPIO_InitStruct1);
	//*********************************************************
	
	
	//**********************************************************
	//FTMģ��
	FTM_InitStruct1.Frequency = 1000;                // 1KHZ
	FTM_InitStruct1.FTMxMAP = FTM1_CH0_PB0;          //��ߵĵ��
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned; //���ض���ģʽ
	FTM_InitStruct1.InitalDuty = 0;               //��ʼ�������0%��ռ�ձ�
	FTM_Init(&FTM_InitStruct1);
	
	FTM_InitStruct1.Frequency = 1000;                // 1KHZ
	FTM_InitStruct1.FTMxMAP = FTM0_CH4_PD4 ;          //�ұߵĵ��
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned; //���ض���ģʽ
	FTM_InitStruct1.InitalDuty = 0;               //��ʼ�������0%��ռ�ձ�
	FTM_Init(&FTM_InitStruct1);
	
	FTM_InitStruct1.Frequency = 1000;                // 1KHZ
	FTM_InitStruct1.FTMxMAP = FTM1_CH1_PB1;          //�ұߵĵ��
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned; //���ض���ģʽ
	FTM_InitStruct1.InitalDuty = 0;               //��ʼ�������0%��ռ�ձ�
	FTM_Init(&FTM_InitStruct1);
	
	FTM_InitStruct1.Frequency = 1000;                // 1KHZ
	FTM_InitStruct1.FTMxMAP = FTM0_CH0_PC1 ;          //��ߵĵ��
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned; //���ض���ģʽ
	FTM_InitStruct1.InitalDuty = 0;               //��ʼ�������0%��ռ�ձ�
	FTM_Init(&FTM_InitStruct1);
	//***********************************************************
	
	
	//*********************************************************
	//��ʼ��
	OLED_Init();
	DelayInit();
	//FLASH_Init();
	//*********************************************************
	
	
	//*********************************************************
	//OLED�����ʼ��
	OLED_Write_Char(0,0,43);
	OLED_Write_String(2,0,"Mode");
	OLED_Write_Char(6,0,1);
	OLED_Write_String(2,2,"Mode");
	OLED_Write_Char(6,2,2);
	OLED_Write_String(2,4,"Mode");
	OLED_Write_Char(6,4,3);
//	FLASH_ReadByte(101,1,&a);//����ռ�ձ�
//	FTMDuty_left =(uint16_t)250*a;
//	FLASH_ReadByte(102,1,&b);//����ռ�ձ�
//	FTMDuty_right =250*(uint16_t)b;
	//**********************************************************
	while(1)
	{
		if(run == 0) key_scan();
		
		while(run == 1)
		{
			if((GPIO_ReadInputDataBit(PTD, GPIO_Pin_10) == 1 || GPIO_ReadInputDataBit(PTD,GPIO_Pin_8) == 1 ) && (GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==0))
			{//����ת
				if((GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==1&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==1)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==0))
				{
					FTMDuty_left = 9000;
					FTMDuty_right = 1;
					FTMDuty_reverse_left = 1;
					FTMDuty_reverse_right = 9000;
				}
				else 
				{
					FTMDuty_left = x1;
					FTMDuty_right = 1;
					FTMDuty_reverse_left = 1;
					FTMDuty_reverse_right = 1;					
					FTM_PWM_ChangeDuty(FTM0_CH4_PD4,(uint32_t)FTMDuty_right);
					FTM_PWM_ChangeDuty(FTM1_CH0_PB0,(uint32_t)FTMDuty_left);
					FTM_PWM_ChangeDuty(FTM0_CH0_PC1,(uint32_t)FTMDuty_reverse_left);
					FTM_PWM_ChangeDuty(FTM1_CH1_PB1,(uint32_t)FTMDuty_reverse_right);
					while(!(GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==0));
				}
			}
			if((GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==0))
			{//ֱ��
				FTMDuty_right = x2;
				FTMDuty_left = x1;
				FTMDuty_reverse_right = 1;
				FTMDuty_reverse_left = 1;
			}
			if((GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==1||GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==1))
			{
				if((GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==1&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==1))
				{
					FTMDuty_left = 1;
					FTMDuty_right = 9000;
					FTMDuty_reverse_left = 9000;
					FTMDuty_reverse_right = 1;
				}
				else 
				{
					FTMDuty_left = 1;
					FTMDuty_right = x2;
					FTMDuty_reverse_left = 1;
					FTMDuty_reverse_right = 1;					
				}
				FTM_PWM_ChangeDuty(FTM0_CH4_PD4,(uint32_t)FTMDuty_right);
				FTM_PWM_ChangeDuty(FTM1_CH0_PB0,(uint32_t)FTMDuty_left);
				FTM_PWM_ChangeDuty(FTM0_CH0_PC1,(uint32_t)FTMDuty_reverse_left);
				FTM_PWM_ChangeDuty(FTM1_CH1_PB1,(uint32_t)FTMDuty_reverse_right);
				while(!(GPIO_ReadInputDataBit(PTD, GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTD,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(PTB,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(PTA, GPIO_Pin_28)==0));
			}
			
//			if(FTMDuty_left<=1500) FTMDuty_left=2000;
//			if(FTMDuty_right<=1500) FTMDuty_right=2000;
			
			FTM_PWM_ChangeDuty(FTM0_CH4_PD4,(uint32_t)FTMDuty_right);
			FTM_PWM_ChangeDuty(FTM1_CH0_PB0,(uint32_t)FTMDuty_left);
			FTM_PWM_ChangeDuty(FTM0_CH0_PC1,(uint32_t)FTMDuty_reverse_left);
			FTM_PWM_ChangeDuty(FTM1_CH1_PB1,(uint32_t)FTMDuty_reverse_right);
			
			
			
			
			OLED_Write_Char(1,0, GPIO_ReadInputDataBit(PTB,GPIO_Pin_10));	
			OLED_Write_Char(2,0, GPIO_ReadInputDataBit(PTA,GPIO_Pin_28));	
			OLED_Write_Char(3,0, GPIO_ReadInputDataBit(PTD,GPIO_Pin_10));	
			OLED_Write_Char(4,0, GPIO_ReadInputDataBit(PTD,GPIO_Pin_8));	
			OLED_Write_Char(5,0, GPIO_ReadInputDataBit(PTA,GPIO_Pin_16));	
			OLED_Write_Char(6,0, GPIO_ReadInputDataBit(PTA,GPIO_Pin_14));	
			OLED_Write_String(2,2,"left:");
			OLED_Write_Num5(8,2, FTMDuty_left);
			OLED_Write_String(2,4,"right:");
			OLED_Write_Num5(8,4, FTMDuty_right);
			__nop();
		}
	}
}

void assert_failed(uint8_t* file, uint32_t line)
{
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}



void key_scan()
{
	if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_2) == 0)
	{
		DelayMs(10);
		if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_2) == 0)
		{
				//��ѡ��ģʽ����ʱ��һ�ΰ�����ѡ���ͷ������һ��
				if(flag % 2 == 0)
				{
					OLED_Write_Char(0,2 * i,' ');
					i++;
					if(i == 3) i = 0;
					OLED_Write_Char(0,2 * i,43);
				}
				//����ʾռ�ձȽ��水һ����3�����
				else
				{
					if(i == 0)
					{
						run = 1;
						x1 = FTMDuty_left;
						x2 = FTMDuty_right;
						OLED_Write_Char(0,p * 2,' ');
						OLED_Write_String(0,4,"runing......");
						DelayMs(2500);
						OLED_Clear();
						FTM_PWM_ChangeDuty(FTM1_CH0_PB0,(uint32_t)FTMDuty_left);
						FTM_PWM_ChangeDuty(FTM0_CH4_PD4,(uint32_t)FTMDuty_right);
					}
				}
			while(!GPIO_ReadInputDataBit(PTB,GPIO_Pin_2));      	
		}
	}
	if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_4) == 0)
	{
		DelayMs(10);
		if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_4) == 0)
		{
			if(i == 1)
			{
				//�����ڽ������ʱ��run==0ʱ������һ���л�����
				flag++;
				if(flag % 2 == 0)
				{
					OLED_Clear();
					OLED_Write_Char(0,2 * i,43);
					OLED_Write_String(2,0,"Mode");
					OLED_Write_Char(6,0,1);
					OLED_Write_String(2,2,"Mode");
					OLED_Write_Char(6,2,2);
					OLED_Write_String(2,4,"Mode");
					OLED_Write_Char(6,4,3);
				}
				//ͬ�ϣ����������໥�л�
				if(flag % 2 == 1)
				{
					OLED_Clear();
					OLED_Write_String(0,0,"sub:");
					OLED_Write_Num3(4,0,sub);
				}
			}
			if(i == 0)
			{
				//�����ڽ������ʱ��run==0ʱ������һ���л�����
				flag++;
				if(flag % 2 == 0)
				{
					OLED_Clear();
					OLED_Write_Char(0,2 * i,43);
					OLED_Write_String(2,0,"Mode");
					OLED_Write_Char(6,0,1);
					OLED_Write_String(2,2,"Mode");
					OLED_Write_Char(6,2,2);
					OLED_Write_String(2,4,"Mode");
					OLED_Write_Char(6,4,3);
				}
				//ͬ�ϣ����������໥�л�
				if(flag % 2 == 1)
				{
					OLED_Clear();
					OLED_Write_Char(0,0,43);
					OLED_Write_String(2,0,"left:");
					OLED_Write_Num5(8,0, FTMDuty_left);
					OLED_Write_String(2,2,"right:");
					OLED_Write_Num5(8,2, FTMDuty_right);
				}
			}
			while(!GPIO_ReadInputDataBit(PTB,GPIO_Pin_4));
		}
	}
	if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_6) == 0)
	{
		DelayMs(10);
		if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_6) == 0)
		{
			if(i == 0)
			{
				//��������ʾռ�ձȵĽ����ʱ�򣬿��ư���ʹռ�ձȼӼ���
				if(flag % 2 == 1)
				{
					if(p % 2 == 0)
					{
						FTMDuty_left += 250;
//						buffer1=(uint8_t)(FTMDuty_left / 250);
//						FLASH_WriteSector(101,1,&buffer1);
						if(FTMDuty_left == 10250)
						{
							FTMDuty_left = 6000;
						}
						OLED_Write_Num5(8,0, FTMDuty_left);
					}
					if(p % 2 == 1)
					{
						FTMDuty_right += 250;
//						buffer2=(uint8_t)(FTMDuty_right / 250);
//						FLASH_WriteSector(102,1,&buffer2);
						if(FTMDuty_right == 10250)
						{
							FTMDuty_right = 6000;
						}
						OLED_Write_Num5(8,2, FTMDuty_right);
					}
				}
			}
			if(i == 1)
			{
				sub += 100;
				OLED_Clear();
				OLED_Write_String(0,0,"sub:");
				OLED_Write_Num4(4,0,sub);
			}
			while(!GPIO_ReadInputDataBit(PTB,GPIO_Pin_6));
		}
	}
	if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_11) == 0)
	{
		DelayMs(10);
		if(GPIO_ReadInputDataBit(PTB,GPIO_Pin_11) == 0)
		{
			if(i == 0)
			{
				//��ʾռ�ձȽ��������ѡ��
				if(flag % 2 == 1)
				{
					p++;
					OLED_Write_Char(0,2 * ((p-1) % 2),' ');
					OLED_Write_Char(0,2 * (p % 2),43);
					while(!GPIO_ReadInputDataBit(PTB,GPIO_Pin_11));
				}
			}
		}
	}
}





