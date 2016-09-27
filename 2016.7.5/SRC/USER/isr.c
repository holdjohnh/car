#include "isr.h"

#include "led.h"


void UART4_RX_TX_IRQHandler(void)
{
	uint8_t ch;
	//�жϷ��ʹ������
	UART_SendDataIntProcess(UART4);
	//����ɹ����յ�������
	if(UART_ReceiveData(UART4,&ch))
	{
		//�ѽ��յ�����Ϣ���ͻ�ȥ
		UART_SendData(UART4,ch);
	}
}

void PIT0_IRQHandler(void)
{
	UART_printf("PIT0 Int\r\n");
	LED2 = !LED2;
	PIT_ClearITPendingBit(PIT0,PIT_IT_TIF);
}

void PORTB_IRQHandler(void)
{
	
	LED4 = !LED4;
	GPIO_ClearITPendingBit(PTB,GPIO_Pin_9);
}

uint16_t TSIStatues = TRUE;    //��¼�ϴε�״̬
void TSI0_IRQHandler(void)
{
	uint16_t Status = 0;
	Status = TSI_GetChannelOutOfRangleFlag(TSI0,TSI0_CH5);
	if((Status == TRUE) && (TSIStatues == FALSE))
	{
		LED3 = !LED3;
		UART_printf("TSI EnterInt \r\n");
	}
		TSIStatues = Status; //��¼�ϴ�״̬
	TSI_ClearAllITPendingFlag(TSI0);
	
}


void LPTimer_IRQHandler(void)
{
	UART_printf("!!\r\n");
	LPTM_ClearITPendingBit(LPTMR0,LPTM_IT_TCF);
}
