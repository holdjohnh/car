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
#include "flash.h"
#include "spilcd.h"
#include "stdio.h"
#include "nrf2401.h"
#include "uart.h"
#include "mma845x.h"


uint8_t NRF2401TXBuffer[TX_PLOAD_WIDTH] = "NRF2401 TestData:KEY ";
uint8_t NRF2401RXBuffer[RX_PLOAD_WIDTH];
uint8_t ScanTimeFlag = FALSE;  //10MSɨ�����ڱ�־
int main(void)
{
	uint8_t key_res = 0;
	PIT_InitTypeDef PIT_InitStruct1;
	//��ʼ��ϵͳʱ�� ʹ���ⲿ50M���� PLL��Ƶ��100M
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M);
	//��ʼ��Ĭ�ϵĵ��Դ���
	UART_DebugPortInit(UART2_RX_D2_TX_D3,115200);
	//��ӡMCU��Ϣ
	DisplayCPUInfo();
	//��ʼ����ʱģ��
	DelayInit();
	//��ʼ��LED
	LED_Init();
  //��ʼ��SPILCD
	SPILCD_Init();
	//OLED��ʼ��
	OLED_Clear();
	OLED_Init();
	//��ʼ������
	KEY_Init();
	//����һ��10MS��ʱ������ɨ�谴��
	PIT_InitStruct1.PITx = PIT0;
	PIT_InitStruct1.PIT_Interval = 10;
	PIT_Init(&PIT_InitStruct1);
	PIT_ITConfig(PIT0,PIT_IT_TIF,ENABLE);
	NVIC_EnableIRQ(PIT0_IRQn);
	//��ʼ��NRF24L01
	if(NRF2401_Init() == NRF_OK)
	{
		LED2 = 1;
		UART_printf("NREF2401 ��ʼ���ɹ�\r\n");
		OLED_Write_Char(4,4,1);
	}
	else
	{
		UART_printf("NREF2401 ��ʼ��ʧ��\r\n");
	}
//	//������Ϊ����ģʽ
//	NRF2401_SetRXMode(); 
	while(1)
	{
//		if(ScanTimeFlag == TRUE)
//		{
//			key_res =KEY_Scan();
//			ScanTimeFlag = FALSE;
//		}
//		switch(key_res) //��֤Key_Scan�Դ�Լ100HZ��Ƶ�ʱ�����
//		{
//			case KEY_NO_KEY: //�޼�
//				break;
//			case KEY_SINGLE: //����
				NRF2401_SetTXMode();
				NRF2401TXBuffer[20] = '1';
				if(NRF2401_SendData(NRF2401TXBuffer) == TX_OK)
				{
					UART_printf("�ɹ�����\r\n");
					OLED_Write_Char(6,6,3);
				}
				else
				{
					UART_printf("����ʧ��\r\n");
				}
				DelayMs(300);
				
//				NRF2401_SetRXMode();
//				key_res = KEY_NO_KEY;
//				break;
//			case KEY_DOUBLE: //˫��
//				NRF2401_SetTXMode();
//				NRF2401TXBuffer[20] = '2';
//				if(NRF2401_SendData(NRF2401TXBuffer) == TX_OK)
//				{
//					UART_printf("���ͳɹ�\r\n");
//				}
//				else
//				{
//					UART_printf("����ʧ��\r\n");
//				}
//				NRF2401_SetRXMode(); 
//				key_res = KEY_NO_KEY;
//				break;
//			case KEY_LONG:  //����
//				NRF2401_SetTXMode();
//				NRF2401TXBuffer[20] = '3';
//				if(NRF2401_SendData(NRF2401TXBuffer) == TX_OK)
//				{
//					UART_printf("���ͳɹ�\r\n");
//				}
//				else
//				{
//					UART_printf("����ʧ��\r\n");
//				}
//				NRF2401_SetRXMode(); 
//				key_res = KEY_NO_KEY;
//				break;
//			default:break;
//		}	
//		//����
//		if(NRF2401_RecData(NRF2401RXBuffer) == NRF_OK) //���յ�������
//		{
//			UART_printf("���յ���������:%s\r\n",NRF2401RXBuffer);
//		}
	}
}


void assert_failed(uint8_t* file, uint32_t line)
{
	//����ʧ�ܼ��
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}

