#include "isr.h"
#include "Mydefine.h"
#include "ftm.h"
#include "oled.h"

void PIT1_IRQHandler(void)
{
	flag_ccd_10ms=1;
	time++;
	PIT_ClearITPendingBit(PIT1,PIT_IT_TIF);
}



void DMA0_IRQHandler(void)
{
	uint8_t i;
	uint8_t maxTempRecord = 0;
	uint8_t maxTemp = 0;
	
	
	for(i = 0;i <= 4;i++)   //��λ�仯
	{
		ccdTemp[i]=(ccdTemp[i]<<4)|(ccdTemp[i]>>4);  
	  ccdTemp[i]=((ccdTemp[i]<<2)&0xcc)|((ccdTemp[i]>>2)&0x33);  
	  ccdTemp[i]=((ccdTemp[i]<<1)&0xaa)|((ccdTemp[i]>>1)&0x55); 
	}
	
	for(i = 0; i<= 4 ;i++)
	{
		if(ccdTemp[i] >= maxTemp)
		{
			maxTemp = ccdTemp[i];
			maxTempRecord = i;
			
		}	
	}
	ccdTemp[maxTempRecord] = 0;   //�����ֵ��ȥ
	
	if(whichCcd == 1)
	{
		P[ccdNumber] = ccdTemp[0] + ccdTemp[1] + ccdTemp[2] + ccdTemp[3] + ccdTemp[4];
		P[ccdNumber] = P[ccdNumber] >> 2;
	}
	if(whichCcd == 2)
	{
		P2[ccdNumber] = ccdTemp[0] + ccdTemp[1] + ccdTemp[2] + ccdTemp[3] + ccdTemp[4];
		P2[ccdNumber] = P2[ccdNumber] >> 2;
	}
	ccdNumber ++;

	DMA0->TCD[DMA_CH0].DADDR = (uint32_t)ccdTemp;

	DMA_ClearITPendingBit(DMA0,DMA_IT_MAJOR,DMA_CH0);
}

/**************************************оƬ��������*******************************************/
#define  CHIP_DEBUG         ON		//��оƬ�����������Ų����ⷽ���������ڵ���������ʹ��
#if(CHIP_DEBUG==ON)
__asm void wait()
{
  BX lr	//���ط��������λ��
}
#endif

void HardFault_Handler(void)//�ڴ���ջ�������
{
	OLED_Clear();
	FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,0);
	FTM_PWM_ChangeDuty(FTM1_CH0_PA8,0);
	FTM_PWM_ChangeDuty(FTM1_CH1_PA9,0);
	ccd2Switch = 1;//�ر�
	ccdSwitch = 1;//�ر�
	OLED_Write_String(0,0,(uint8_t *)"The memory");
	
	OLED_Write_String(0,2,(uint8_t *)"or Stacks");	
	
	OLED_Write_String(0,4,(uint8_t *)"overflows");
	
	#if(CHIP_DEBUG==ON)
	wait();
	#endif
	while(1);
}

void NMI_Handler(void)//���������ж�
{
	OLED_Clear();
	FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,0);
	FTM_PWM_ChangeDuty(FTM1_CH0_PA8,0);
	FTM_PWM_ChangeDuty(FTM1_CH1_PA9,0);
	ccd2Switch = 1;//�ر�
	ccdSwitch = 1;//�ر�

	OLED_Write_String(0,0,(uint8_t *)"The Chip");
	
	OLED_Write_String(0,2,(uint8_t *)"have big");	
	
	OLED_Write_String(0,4,(uint8_t *)"error");
	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
	while(1);
}

void MemManage_Handler(void)//�洢��������
{
	FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,0);
	FTM_PWM_ChangeDuty(FTM1_CH0_PA8,0);
	FTM_PWM_ChangeDuty(FTM1_CH1_PA9,0);
	ccd2Switch = 1;//�ر�
	ccdSwitch = 1;//�ر�

	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}

void BusFault_Handler(void)//���߷�������
{
	FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,0);
	FTM_PWM_ChangeDuty(FTM1_CH0_PA8,0);
	FTM_PWM_ChangeDuty(FTM1_CH1_PA9,0);
	ccd2Switch = 1;//�ر�
	ccdSwitch = 1;//�ر�

	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}

void UsageFault_Handler(void)//�÷���������
{
	FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,0);
	FTM_PWM_ChangeDuty(FTM1_CH0_PA8,0);
	FTM_PWM_ChangeDuty(FTM1_CH1_PA9,0);
	ccd2Switch = 1;//�ر�
	ccdSwitch = 1;//�ر�

	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}
