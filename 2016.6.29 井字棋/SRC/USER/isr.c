#include "isr.h"
#include "oled.h"
extern unsigned char j,m,ms,s;
void PIT0_IRQHandler(void)
{ 
	PIT_ClearITPendingBit(PIT0,PIT_IT_TIF);
	++ms;
	if(ms==100){
		s++;
		ms=0;
	}
	if(s==60){
		m++;
		s=0;
	}
	if(m==60){
		m=0;
	}
}

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
