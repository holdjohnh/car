#include "sys.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "wdog.h"
#include "pit.h"
#include "dma.h"
#include "ftm.h"
#include "lptm.h"
#include "key.h"
#include "adc.h"
#include "tsi.h"
#include "dac.h"
#include "spi.h"
#include "i2c.h"
#include "pdb.h"
#include "sd.h"
#include "oled.h"
#include "flash.h"
#include "spilcd.h"
#include "stdio.h"
#include "nrf2401.h"
#include "uart.h"

#include "dmacnt.h"
int main(void)
{
	uint32_t FTMDuty = 0, DMA_Value0 = 0,DMA_Value1 = 0;
	int speed_num=0;
	FTM_InitTypeDef FTM_InitStruct1;
	GPIO_InitTypeDef GPIO_InitStruct1;
	DMACNT_InitTypeDef DMACNT_InitStruct1;
	//��ʼ��ϵͳʱ�� ʹ���ⲿ50M���� PLL��Ƶ��100M
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M);
	//��ʼ��Ĭ�ϵĵ��Դ���
	UART_DebugPortInit(UART0_RX_PA14_TX_PA15,115200);
	//��ӡMCU��Ϣ
	DisplayCPUInfo();
	DelayInit();
	OLED_Init();

	GPIO_InitStruct1.GPIOx = PTA;                             
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;                
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;            
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_27;  	
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_Init(&GPIO_InitStruct1); 
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_28;  	      
	GPIO_Init(&GPIO_InitStruct1); 			
																									 //�Ӽ��ٶ�
																									 //��ʼ��FTM
	FTM_InitStruct1.Frequency = 1000;                // 1KHZ
	FTM_InitStruct1.FTMxMAP = FTM1_CH1_PB1;          //FTM0_CH0 PC1����
	FTM_InitStruct1.FTM_Mode = FTM_Mode_EdgeAligned; //���ض���ģʽ
	FTM_InitStruct1.InitalDuty = 10000;               
	FTM_Init(&FTM_InitStruct1);

//	FTM_InitStruct1.InitalDuty = 0;               
//	FTM_InitStruct1.FTMxMAP = FTM1_CH0_PB0;
//	FTM_Init(&FTM_InitStruct1);

	DMACNT_InitStruct1.DMACNT_Mode = DMACNT_MODE_RISING;  //�����ؼ���
	DMACNT_InitStruct1.DMA_Chl = DMA_CH0;                 //ʹ��ͨ�� 0
	DMACNT_InitStruct1.GPIOx = PTC;                       //PTC5
	DMACNT_InitStruct1.GPIO_Pin = GPIO_Pin_5;
	DMACNT_Init(&DMACNT_InitStruct1);

	while(1)
	{
		DMA_Value0 = DMACNT_GetValue(DMA_CH0);
		DMA_Value1 = DMACNT_GetValue(DMA_CH1);
		UART_printf("DMACNT_CH0_Value:%d ",DMA_Value0);
		UART_printf("DMACNT_CH1_Value:%d\r\n",DMA_Value1);
		if(GPIO_ReadInputDataBit(PTA,GPIO_Pin_28)==0)
			{
				DelayMs(60);
				if(GPIO_ReadInputDataBit(PTA,GPIO_Pin_28)==0)
					{
						FTMDuty += 500;
						FTMDuty %= 10000;
						while(!GPIO_ReadInputDataBit(PTA,GPIO_Pin_28));
					}
			}
			if(GPIO_ReadInputDataBit(PTA,GPIO_Pin_27)==0)
			{
				DelayMs(60);
				if(GPIO_ReadInputDataBit(PTA,GPIO_Pin_27)==0)
					{
						FTMDuty -= 500;
						FTMDuty %= 10000;
						while(!GPIO_ReadInputDataBit(PTA,GPIO_Pin_27));
					}
			}
			DelayMs(50);
			speed_num = FTMDuty/100;
			OLED_Write_String(2,2,"speed");
			OLED_Write_Num3(4,4,speed_num);
			FTM_PWM_ChangeDuty(FTM1_CH1_PB1,FTMDuty); //FTMDUTY�仯
	}
}


void assert_failed(uint8_t* file, uint32_t line)
{
	//����ʧ�ܼ��
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}

