#include "ccd.h"
#include "sys.h"
#include "gpio.h"
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "Mydefine.h"
#include "math.h"
#include "dma.h"


/***********************************************************************************************
 ���ܣ���ʼ��
 �βΣ�0
 ���أ�0
 ��⣺ccd���ų�ʼ��
************************************************************************************************/

void ccd_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct1;
	
	GPIO_InitStruct1.GPIO_Pin = CCD_SWITCH_PIN;             
	GPIO_InitStruct1.GPIO_InitState = Bit_SET; //һ��Ҫ��ʼ���ر� ������
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD_SWITCH_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	ccdSwitch = 1;
	
	GPIO_InitStruct1.GPIO_Pin = CCD2_SWITCH_PIN;            
	GPIO_InitStruct1.GPIO_InitState = Bit_SET; //һ��Ҫ��ʼ���ر� ������
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD2_SWITCH_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	ccd2Switch = 1;
	
	GPIO_InitStruct1.GPIO_Pin = CCD_CLK_PIN;                    //  ccd clk0
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD_CLK_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = CCD_SI_PIN;                    //    ccd si0
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD_SI_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_19;                    // beep
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = PTA;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = CCD_CLK2_PIN;                    //  ccd clk1
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD_CLK2_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = CCD_SI2_PIN;                    //    ccd si1
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
	GPIO_InitStruct1.GPIOx = CCD_SI2_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (7);                 
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = (6);                    
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	GPIO_InitStruct1.GPIO_Pin = (5);                    
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (4);                   
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (3);                
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (2);                   
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (1);                 
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
	
	GPIO_InitStruct1.GPIO_Pin = (0);             
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct1.GPIOx = PTD;
	GPIO_Init(&GPIO_InitStruct1);
	
}

/***********************************************************************************************
 ���ܣ�ccd�ɼ�
 �βΣ�0
 ���أ�0
 ��⣺�ɼ�128��ADֵ
************************************************************************************************/
void ccd_collect()
{
	uint8_t i;
	
	ccdSwitch = 0;//�򿪿���
	
	whichCcd = 1;
	ccdNumber = 0;
	
	ccd_clk=1;               
	ccd_SI=0;                 
	DelayUs(1);
	
	ccd_clk=0;
	ccd_SI=1;
	DelayUs(1);
	
	ccd_clk=1;
	ccd_SI=0;
	
	for(i=0;i<=127;i++)
	{
		ccd_clk=0;
		ccd_clk=1;
		DelayUs(1);
		DMA_SetEnableReq(DMA_CH0,ENABLE);
	}
	
	ccdSwitch = 1; //����ر�
	//��������Ҳ����������
	whichCcd = 0;
}

void ccd2_collect()
{
	uint8_t i;
	
	ccd2Switch = 0;//�򿪿���
	
	whichCcd = 2;
	ccdNumber = 0;
	
	ccd_clk2=1;               
	ccd_SI2=0;                 
	DelayUs(1);
	
	ccd_clk2=0;
	ccd_SI2=1;
	DelayUs(1);
	
	ccd_clk2=1;
	ccd_SI2=0;
	
	for(i=0;i<=127;i++)
	{
		ccd_clk2=0;
		ccd_clk2=1;
		DelayUs(1);
		DMA_SetEnableReq(DMA_CH0,ENABLE);
		
	}
	
	ccd2Switch = 1;//�ر�
	whichCcd = 0;
}
/***********************************************************************************************
 ���ܣ�oled�ɼ�
 �βΣ�0
 ���أ�0
 ��⣺��ccd��ADֵת����oled��ʾ��ֵ
************************************************************************************************/
void oled_collect()
{
	uint8_t i,j,flag,flag1;
	for(i=0;i<=127;i++)
	{
		flag=(255-P[i])/32;
		flag1=(255-P[i])%32/4;
	  for(j=0;j<=7;j++)
			{
				if(j>flag)
					oled_data[j][i]=0xff;
				if(j==flag)
					oled_data[j][i]=0xff<<flag1;
				if(j<flag)
					oled_data[j][i]=0x00;
			}
		}
	oled_data[7][center]=0x00;
}

void oled_collect2()
{
	uint8_t i,j,flag,flag1;
	for(i=0;i<=127;i++)
	{
		flag=(255-P2[i])/32;
		flag1=(255-P2[i])%32/4;
	  for(j=0;j<=7;j++)
			{
				if(j>flag)
					oled_data[j][i]=0xff;
				if(j==flag)
					oled_data[j][i]=0xff<<flag1;
				if(j<flag)
					oled_data[j][i]=0x00;
			}
		}
	oled_data[7][center2]=0x00;
}
/***********************************************************************************************
 ���ܣ�oled��ʾ
 �βΣ�0
 ���أ�0
 ��⣺0
************************************************************************************************/

void oled_show()
{
	uint8_t i,j;
	for(i=0;i<=7;i++)
	{
		OLED_Set_XY(0,i);
	  for(j=4;j<=124;j++)
	    {
				OLED_WrDat(oled_data[i][j]);
			}
	}
	OLED_Write_Num2(0,2,center2);
	OLED_Write_Num2(0,0,center);
}
/***********************************************************************************************
 ���ܣ�ͼ����
 �βΣ�0
 ���أ�0
 ��⣺0
************************************************************************************************/\

void CCDImage_process()
{
	uint8_t i;
	
	if(time % 100 == 0 || time <= 150)
		beep=0;
	
	if(time <= 5)
		return;
	/**************ccd2*****************/
	
	min2_last = min2;
	max2 = 0;
	min2 = 250;
	
	 for (i = 10; i <= 120; i++)
		{
				if (P2[i] < min2)
						min2 = P2[i];
				if (P2[i] > max2)
				{
						max2 = P2[i];
						max2Record = i;
				}
		}
	max2 = (P2[max2Record - 2] +P2[max2Record + 2] + P2[max2Record - 1] +P2[max2Record + 1] + P2[max2Record]) / 5;
	if(min2 < 40)
	{
		min2 = 40;
	}
	value2 = (0.3 * max2 + 0.7 * min2);//��ֵ
	
	average_value2[4] = average_value2[3];
	average_value2[3] = average_value2[2];
	average_value2[2] = average_value2[1];
	average_value2[1] = average_value2[0];
	average_value2[0] = value2;
	if(valueLast2 == 0)
		valueLast2 = value2;

	for (i = saoxian2; i <= 122; i++)//���м�����
	{
			right2 = i;
			if (P2[i - 2] - P2[i] >= 8 && P2[i - 3] - P2[i - 1] >= 8 && P2[i] <= value2)
					break;
	}

	for (i = saoxian2; i >= 6; i--)
	{
			left2 = i;
			if (P2[i + 2] - P2[i] >= 8 && P2[i + 3] - P2[i + 1] >= 8 && P2[i] <= value2)
					break;
	}
	/*******************�������***********************/
	if(left2 != 6 && right2 != 122 && element == Straight)  //????????
	{
			s2 = (right2 - left2) / 2;
	}

	/*************����************/
	 if (left2 != 6 && right2 == 122)  //???
		{
				for (i = saoxian2; i <= 122; i++)//���м�����
				{
						right2 = i;
						if (P2[i - 4] - P2[i] >= 8 && P2[i - 5] - P2[i - 1] >= 8 && P2[i] <= value2)  
								break;
				}
				if(right2 != 122)
					center2 = (right2 + left2 ) / 2;
				else
				{
				  center2 = left2 + s2;
					if (center2 > 128)
							center2 = 128;
					if (center2 < (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}
		}

		if (left2 == 6 && right2 != 122)  //��߶���
		{
				for (i = saoxian2; i >= 6; i--)
				{
						left2 = i;
						if (P2[i + 4] - P2[i] >= 8 && P2[i + 5] - P2[i + 1] >= 8 && P2[i] <= value2)
								break;
				}
				if(left2 != 6)
					center2 = (right2 + left2 ) / 2;
				else
				{
					if (right2 >= s2)
							center2 = right2 - s2;
					else
							center2 = 0;
					if (center2 > (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}
		}

	if (left2 != 6 && right2 != 122)  //
	{
			center2 = (left2 + right2) / 2;
	}
	/****************ʮ���ж�**********************/
	if(value2 - valueLast2 >= 15 && flagBlackCnt <= 5)
	{
		if(flag_cross2_deal == 0 && max < 200)
		{
				center2 = 64;
				flag_cross2_deal = 15;
				flagRampAvoid = 20;
			  flagObstructAvoid = 20;
				if(center2_record[4] <=64 && center2_record[5] <= 64)   //��ת
					flag_cross2_record = 1;
				if(center2_record[4] > 64 && center2_record[5] > 64) //��ת
					flag_cross2_record = 2;
	  }
	}
	
/******************���ߴ���*************************/
	if (left2 == 6 && right2 == 122)   //ɨ�����������ȫ��
	{
			if (flag_black2 == 0)
					flag_miss = 1;
	}

	if (flag_miss == 1)
	{
			for (i = saoxian2; i <= 122; i++)//��ɨһ��
			{
					right2 = i;
					if (P2[i - 8] - P2[i] >= 10 && P2[i - 9] - P2[i - 1] >= 10 && P2[i] <= value2)
					{
							flag_miss = 0;
							break;
					}
			}

			for (i = saoxian2; i >= 6; i--)
			{
					left2 = i;
					if (P2[i + 8] - P2[i] >= 10 && P2[i + 8] - P2[i + 1] >= 10 && P2[i] <= value2)
					{
							flag_miss = 0;
							break;
					}
			}
			
			if (left2 != 6 && right2 == 122)  //�ұ߶���
			{
					center2 = left2 + s2;
					if (center2 > 128)
							center2 = 128;
					if (center2 < (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 == 6 && right2 != 122)  //��߶���
			{
					if (right2 >= s2)
							center2 = right2 - s2;
					else
							center2 = 0;
					if (center2 > (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 != 6 && right2 != 122)  //
			{
					center2 = (left2 + right2) / 2;
			}
			/**/
			/*��¼ȫ��ʱ��״̬*/
			if (left2 == 6 && right2 == 122)
			{
					flag_black2 = 1;
				  flag_miss = 0;
					if (center2_record[0] < 64)
					{
							flag_miss_record = 1;//��ת
					}
					if (center2_record[0] >= 64)
					{
							flag_miss_record = 2;//��ת
					}
			}
	}
	if(flag_black2 ==1)
	{
		 flagBlackCnt ++;
		 if(center >= 104 && flag_miss_record == 1)
		 {
			 flag_miss_record = 2;
			 if(center2_record[0] < 50 && center2_record[0] > 20)
			 {
				 flag_miss_record = 1;
				 //center2 = 0;
			 }
		 }
		 
		 if(center <= 24 && flag_miss_record == 2)
		 {
			 flag_miss_record = 1;
			 if(center2_record[0] > 78 && center2_record[0] < 108)
			 {
				 flag_miss_record = 2;
				 //center2 = 128;
			 }
		 }
		 
			if (flag_miss_record == 1)//��ת
			{
					if (right2 >= 64)
					{
//						if(center2 > 5)
//						{
//							center2 = center2 - 5;
//						}
//						if(center2 <= 5)
								center2 = 0;
					}
					else
							flag_black2 = 0;
			}
			if (flag_miss_record == 2)//��ת
			{
					if (left2 <= 64)
					{
//						if(center2 < 123)
//							center2 = center2 + 5;
//						if(center2 >= 123)
							center2 = 128;
					}
					else
							flag_black2 = 0;
			}
	}
	if(flag_black2 == 0)
	{
		flagBlackCnt = 0;
	}
	/****ȫ����***/
	/**********cross_road*******/
	if(flag_cross2_deal > 0)
	{
		flag_cross2_deal --;
		flag_black2 = 0;
		if(flag_cross2_record == 1)  //��ת
		{ 
			for (i = 20; i <= 110; i++)
			{
					right2 = i;
					if (P2[i - 3] - P2[i] >= 8 && P2[i - 4] - P2[i - 1] >= 8 && P2[i] <= valueLast2)
							break;
			}
			for (i = right2 - 3; i >= 20; i--)
			{
					left2 = i;
					if (P2[i + 3] - P2[i] >= 8 && P2[i + 4] - P2[i + 1] >= 8 && P2[i] <= valueLast2)
							break;
			}
			
		}
		
		if(flag_cross2_record == 2)
		{
			for (i = 110; i >= 20; i--)
			{
					left2 = i;
					if (P2[i + 3] - P2[i] >= 8 && P2[i + 4] - P2[i + 1] >= 8 && P2[i] <= valueLast2)
							break;
			}
			for (i = left2 + 3; i <= 110; i++)
			{
					right2 = i;
					if (P2[i - 3] - P2[i] >= 8 && P2[i - 4] - P2[i - 1] >= 8 && P2[i] <= valueLast2)
							break;
			}
		}
		
		if (left2 == 20 && right2 != 110) //???
			{
					if (right2 >= s2)
							center2 = right2 - s2;
					else
							center2 = 0;
					if (center2 > (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
					if(right2 <= 84)
						flag_cross2_deal = 0;
			}
			if (right2 == 110 && left2 != 20) //???   //����������
			{
					center2 = left2 + s2;
					if (center2 > 128)
							center2 = 128;
					if (center2 < (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
					if(left2 >= 44)
						flag_cross2_deal = 0;
			}
			
			if (right2 != 110 && left2 != 20) //???
			{
					center2 = (left2 + right2) / 2;
					flag_cross2_deal = 0;
			}
	}

	/********************************/

	
	
	
	/******************ccd1*************************/
	minLast = min;
	max = 0;
	min = 255;

	for (i = 12; i <= 118; i++)
	{
			if (P[i] < min)
			{
					min = P[i];
			}
			if (P[i] > max)
			{
					max = P[i];
					maxRecord = i;
			}
	}
	if(min < 35)
		min = 35;
	max = (P[maxRecord - 3] + P[maxRecord + 3]) / 2;
	//min = (P[minRecord - 3] + P[minRecord + 3]) / 2;
	value = ( 2 * max + 3 * min) / 5;
	
	average_value[4] = average_value[3];
	average_value[3] = average_value[2];
	average_value[2] = average_value[1];
	average_value[1] = average_value[0];
	average_value[0] = value;
	if(valueLast == 0)
		valueLast = value;
	

  for (i = saoxian; i >= 6; i--)  //????????
	{
			left = i;
			if (P[i + 2] - P[i] >= 12 && P[i + 3] - P[i + 1] >= 12 && P[i] <= value)
					break;
	}
	for (i = saoxian; i <= 122; i++)  //???????
	{
			right = i;
			if (P[i - 2] - P[i] >= 12 && P[i - 3] - P[i - 1] >= 12 && P[i] <= value)
					break;
	}

		if(element == Straight)
		{
			if(center >= 44 && center <= 84 && left >= 8 && right <=120)
				s = (right - left);   //???????
		}
/**************����********/
	  if (left != 6 && right != 122)
		{
			center = (left + right) / 2;
		}
			

		if (left == 6 && right != 122) //???
		{
				if (right >= s / 2)
						center = right - s / 2;
				else
						center = 0;
				if (center > (right + left) / 2)
						center = (right + left) / 2;
		}
		if (right == 122 && left != 6) //???
		{
				center = left + s / 2;
				if (center > 128)
						center = 128;
				if (center < (right + left) / 2)
						center = (right + left) / 2;
		}
/***********������************/
		if(element == Straight && flagRampAvoid == 0)
		{
				lineValueMax = (P[left + 6] + P[right - 6] + P[left + 5] + P[right - 5]) / 4;
				lineValueMin = (P[left - 6] + P[right + 6]) / 2;
				endLineValue = (lineValueMax * 4 + lineValueMin * 1) / 5;
				for (i = saoxian; i <= 122; i++) 
				{
						endRightLine = i;
						if (P[i - 2] - P[i] >= 8 && P[i - 3] - P[i - 1] >= 8 && P[i] <= endLineValue)
								break;
				}

				for (i = saoxian; i >= 6; i--)
				{
						endLeftLine = i;
						if (P[i + 2] - P[i] >= 8 && P[i + 3] - P[i + 1] >= 8 && P[i] <= endLineValue) 
								break;
				}

				if (endLeftLine - left >10  && endLeftLine < 64 && endRightLine > 64 && right - endRightLine>10 && time >= endTime * 100)
				{
						end = 1;
					endCnt = 55;
					if(dmacntr + dmacntl < 380 && dmacntr + dmacntl >= 350)
						endCnt = 50;
					if(dmacntr + dmacntl >= 380)
						endCnt = 40;

				}
	  }
		if(endCnt > 0)
		{
			endCnt --;
		}

/*****************ʮ���ж�*******************/
	if (value - valueLast >= 15 && center > 10 && center < 118) //????
	{
			if (max < 200 && flagCrossCenter == 0)   //?????
			{
				flagRampAvoid = 25;
				flag_obstruct = 0;       //������Ϊ�ϰ�
				flagObstructAvoid = 25;
					if (flagCrossEnter == 0 )   //???
					{
							flagCrossEnter = 1;
							flagCrossCenter = 15;   //
						if (centerRecord[4] <= 64 && centerRecord[5] <= 64) //??
								flagCrossRecord = 1;
						if (centerRecord[4] > 64 && centerRecord[5] > 64)//??
								flagCrossRecord = 2;
					}
					if (flagCrossCenter == 0 && flagCrossEnter == 1)
					{
							flagCrossEnter = 0;
							flagCrossCenter = 15;
						if (centerRecord[4] <= 64 && centerRecord[5] <= 64) //??
								flagCrossRecord = 1;
						if (centerRecord[4] > 64 && centerRecord[5] > 64)//??
								flagCrossRecord = 2;
					}
			}
	}
 /****************���ߴ���******************/
	if (left == 6 && right == 122)
	{
			flagDiu = 1;
			if(centerRecord[1] <= 64)
			{
					flagMissRecord = 1;//??
			}
			else
			{
					flagMissRecord = 2;//??
			}
	}
	if (left != 6 || right != 122)
	{
			if (max - min >= 15)
			{
					 if(flagDiu == 1)
						{ 
								flagDiu = 0;
								flagDiu2 = 1;
						}
			}
	}
 if (flagDiu == 1)
	{
			center = centerRecord[0];
			if (center <= 35 && flagCrossCenter == 0)
			{
					center = centerRecord[0] - 3;
					if (center <= 0)
							center = 0;
			}
			else 
				if (center <= 44 && center_new <= 33 && flagCrossCenter == 0)
				{
						center = centerRecord[0] - 3;
						if (center <= 0)
								center = 0;
				}
				
			if (center >= 93 && flagCrossCenter == 0)
			{
					center = centerRecord[0] + 3;
					if (center >= 128)
							center = 128;
			}
			else
				if (center >= 84 && center_new >= 95 && flagCrossCenter == 0)
				{
						center = centerRecord[0] + 3;
						if (center >= 128)
								center = 128;
				}
			
			if (leftLast - left > 20 || right - rightLast >= 20)
			{
					for (i = saoxian; i >= 6; i--)  //????????
					{
							left = i;
							if (P[i + 6] - P[i] >= 15 && P[i + 7] - P[i + 1] >= 15 && P[i] <= value)
									break;
					}
					for (i = saoxian; i <= 122; i++)  //???????
					{
							right = i;
							if (P[i - 6] - P[i] >= 15 && P[i - 7] - P[i - 1] >= 15 && P[i] <= value)
									break;
					}
					if (left == 6 && right != 122) //???
					{
							if (right >= s / 2)
									center = right - s / 2;
							else
									center = 0;
							
							if (center > (right + left) / 2)
								 center = (right + left) / 2;
					}
					if (right == 122 && left != 6) //???
					{
							center = left + s / 2;
							if (center > 128)
									center = 128;
							if (center < (right + left) / 2)
								 center = (right + left) / 2;
					}
					if (right != 122 && left != 6)
					{
							center = (left + right) / 2;
					}
					//????
//					if (flagMissRecord == 1)  //��ת
//					{
//							if (	right > 64)
//							{
//									center = centerRecord[0];
//							}
//					}
//					if (flagMissRecord == 2)//��ת
//					{
//							if (left < 64)
//							{
//									center = centerRecord[0];
//							}
//					}
					if(left != 6 && leftLast - left >= 20)
					{
							if (P[left + 8] - P[left - 8] <= 15) 
							{
									center = centerRecord[0];
									left = leftLast;
							}
							
					}
							
					if (right != 122 && right - rightLast >= 20)
					{
							if (P[right - 8] - P[right + 8] <= 15) 
							{
									center = centerRecord[0];
									right = rightLast;
							}
					}
			}
	}
	if (flagDiu2 == 1)
	{
			flagDiu2 = 0;
			if (fabs(center - centerRecord[0]) >= 30)
			{
					center = centerRecord[0];
					flagDiu = 1;
			}
	}
/**************ʮ�ִ���****************/
	if (flagCrossCenter >= 1)
	{
			center = 64;
			flagCrossCenter--;
			if (flagCrossRecord == 1)    //��ת
			{
					for (i = 20; i <= 110; i++)
					{
							right = i;
							if (P[i - 3] - P[i] >= 18 && P[i - 4] - P[i - 1] >= 18 && P[i] <= valueLast)
									break;
					}
					for (i = right - 3; i >= 20; i--)
					{
							left = i;
							if (P[i + 3] - P[i] >= 18 && P[i + 4] - P[i + 1] >= 18 && P[i] <= valueLast)
									break;
					}
			}
			if(flagCrossRecord == 2)  //��ת
			{
					for (i = 110; i >= 20; i--)
					{
							left = i;
							if (P[i + 3] - P[i] >= 18 && P[i + 4] - P[i + 1] >= 18 && P[i] <= valueLast)
									break;
					}
					for (i = left + 3; i <= 110; i++)
					{
							right = i;
							if (P[i - 3] - P[i] >= 18 && P[i - 4] - P[i - 1] >= 18 && P[i] <= valueLast)
									break;
					}
			}
			if (left == 20 && right != 110) //???
			{
					if (right >= s / 2)
							center = right - s / 2;
					else
							center = 0;
					if (center > (right + left) / 2)
							center = (right + left) / 2;
					
					if(right <= 84)
					{
						flagCrossCenter = 0;
						flagObstructAvoid = 10;
					}
			}
			if (right == 110 && left != 20) //???
			{
					center = left + s / 2;
					if (center > 128)
							center = 128;
					if (center < (right + left) / 2)
							center = (right + left) / 2;
					
					if(left >= 44)
					{
						flagCrossCenter = 0;
						flagObstructAvoid = 10;
					}
			}
			
			if (right != 110 && left != 20) //???
			{
					center = (left + right) / 2;
					flagCrossCenter = 0;
				 flagObstructAvoid = 10;
			}
			
			if(flagCrossRecord == 1)//�����תʮ�� ͻȻ��ת
			{
				if(center >= 110)
				{
					center = 64;
					flagCrossCenter = 15;
				}
			}
			if(flagCrossRecord == 2) //��תʮ�� ������ת
			{
				if(center <= 10)
				{
					center = 64;
					flagCrossCenter = 15;
				}
			}
			
	}
	else
	{
		flag_obstruct = 1;
	}
	/**********ccd2ʮ��ͼ����*******************/
	if(flagCrossCenter >= 1) //ccd2��ʮ�ִ���
	{
		flag_black2 = 0;
		if(flagCrossRecord == 1)//��ת
		{
			for (i = 15; i <= 110; i++)
				{
						right2 = i;
						if (P2[i - 3] - P2[i] >= 10 && P2[i - 4] - P2[i - 1] >= 10 && P2[i] <= valueLast2)
								break;
				}
				for (i = right2 - 3; i >= 15; i--)
				{
						left2 = i;
						if (P2[i + 3] - P2[i] >= 10 && P2[i + 4] - P2[i + 1] >= 10 && P2[i] <= valueLast2)
								break;
				}
		}
		
		if(flagCrossRecord == 2)//��ת
		{
			for (i = 110; i >= 15; i--)
				{
						left2 = i;
						if (P2[i + 3] - P2[i] >= 10 && P2[i + 4] - P2[i + 1] >= 10 && P2[i] <= valueLast2)
								break;
				}
				for (i = left2 + 3; i <= 110; i++)
				{
						right2 = i;
						if (P2[i - 3] - P2[i] >= 10 && P2[i - 4] - P2[i - 1] >= 10 && P2[i] <= valueLast2)
								break;
				}
		}
		
		if (left2 != 15 && right2 == 110)  //�ұ߶���
			{
					center2 = left2 + s2;
					if (center2 > 128)
							center2 = 128;
					if (center2 < (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 == 15 && right2 != 110)  //��߶���
			{
					if (right2 >= s2)
							center2 = right2 - s2;
					else
							center2 = 0;
					if (center2 > (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 != 15 && right2 != 110)  //
			{
					center2 = (left2 + right2) / 2;
			}
			
			/****�ж��Ƿ���ȷ****/
//			if(flagCrossRecord == 1)
//			{
//				if(center2 <= 90)
//				{
//					flag_cross_ture = 1;
//					flag_black2 = 0;  //���ȫ����־
//				}
//				else
//					flag_cross_ture = 0;
//			}
//			
//			if(flagCrossRecord == 2)
//			{
//				if(center2 >= 30)
//				{
//					flag_cross_ture = 1;
//					flag_black2 = 0;  //���ȫ����־
//				}
//				else 
//					flag_cross_ture = 0;
//			}
			
	}
	/*****************/
	if (left != 6 && right != 122)    
	{
			if (flagCrossEnter > 0)
					flagCrossClear++;
			if (flagCrossClear >= 40)
			{
					flagCrossEnter = 0;
					flagCrossClear = 0;
				  isFlagObstruct = 0;  //Զ���ϰ���־
			}
	}

	
	/***********�µ�*******************/
	if (element == Straight && s >= 75  && flagRampAvoid == 0 && time >= 50 && flagCrossCenter == 0 && 
		beforeRampCnt >= 5 && flag_cross2_deal == 0) 
	{
		if(center >= 44 && center <= 84)
		{
			for (i = 64; i <= 122; i++)//���м�����
			{
					right2 = i;
					if (P2[i - 2] - P2[i] >= 8 && P2[i - 3] - P2[i - 1] >= 8 && P2[i] <= value2)
							break;
			}

			for (i = 64; i >= 6; i--)
			{
					left2 = i;
					if (P2[i + 2] - P2[i] >= 8 && P2[i + 3] - P2[i + 1] >= 8 && P2[i] <= value2)
							break;
			}
			if (left2 != 6 && right2 == 122)  //�ұ߶���
			{
					center2 = left2 + s2;
					if (center2 > 128)
							center2 = 128;
					if (center2 < (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 == 6 && right2 != 122)  //��߶���
			{
					if (right2 >= s2)
							center2 = right2 - s2;
					else
							center2 = 0;
					if (center2 > (right2 + left2) / 2)
							center2 = (right2 + left2) / 2;
			}

			if (left2 != 6 && right2 != 122)  //
			{
					center2 = (left2 + right2) / 2;
			}
			if (center2 >=44 && center2 <= 84)  //
			{
				flagRamp = rampCnt;
				flagRampAvoid = 200;
				flagObstructAvoid = 80;
				valueAvoid = 50;
			}
		}
	}
	/*********б��**********/
	kLeft[4] = kLeft[3];
	kLeft[3] = kLeft[2];
	kLeft[2] = kLeft[1];
	kLeft[1] = kLeft[0];

	kRight[4] = kRight[3];
	kRight[3] = kRight[2];
	kRight[2] = kRight[1];
	kRight[1] = kRight[0];

	kLeft[0] = leftLast - left;
	kRight[0] = right - rightLast;
	if (kLeft[0] >= 5 || kLeft[0] <= -5)
			kLeft[0] = 0;
	if (kRight[0] >= 5 || kRight[0] <= -5)
			kRight[0] = 0;
	kSumLeft = kLeft[0] + kLeft[1] + kLeft[2] + kLeft[3] + kLeft[4];
	kSumRight = kRight[0] + kRight[1] + kRight[2] + kRight[3] + kRight[4];
	
	if (element == Straight && flagRampAvoid == 0 && time >= 50 && flagCrossCenter == 0 && 
		beforeRampCnt >= 5 && flag_cross2_deal == 0)
	{
		if (kSumLeft >= 5 && kSumRight >= 5 && s >= 57)
		{
			flagRamp = rampCnt;
			flagRampAvoid = 200;
			flagObstructAvoid = 80;
			valueAvoid = 50;
		}
	}
	
	if(flagRampAvoid >= 1)
	{
		flagRampAvoid --;
	}
	if(valueAvoid > 0)
	{
		valueAvoid --;
		straight = 0;
	}
	
	/*****************�ϰ�*****************/
	if(flagObstructR == 1)
	{
		flagObstructR = 0;
		if(fabs(rightLast - right) <= 5)
		{
			flag_obstruct_cntR = ZA_changshuR;
			if(isFlagObstruct == 1)
			{
				flagObstructL2 = 0;
			  flagObstructR2 = 0;
			}
		}
	}
	if(flagObstructL == 1)
	{
		flagObstructL = 0;
		if(fabs(left - leftLast) <= 5)
		{
			flag_obstruct_cntL = ZA_changshuL;
			if(isFlagObstruct == 1)
			{
				flagObstructL2 = 0;
			  flagObstructR2 = 0;
			}
		}
	}
	if(element == Straight && flagCrossCenter == 0 && left >= 35 && right != 122 && time >= 50 
		&& flagObstructAvoid == 0)
	{
		if(left - leftLast >= 15 && leftLast >= 10) //���ϰ�
		{
			flagObstructL = 1;
			flagRampAvoid = 20;
		}
	}
	if(element == Straight && flagCrossCenter == 0 && right <= 93 && left != 6 && time >= 50 
		&& flagObstructAvoid == 0)
	{
		if(rightLast - right >= 15 && rightLast <= 118)
		{
			flagObstructR = 1;
			flagRampAvoid = 20;
		}
	}
	if(element == Straight && flag_cross2_deal == 0 && left2 >= 20 && right2 != 122 && time >= 40 
		&& flagObstructAvoid == 0)
	{
		if(left2 - left2_last >= 15 && left2_last >= 10) //���ϰ�
		{
			flagObstructL2 = 10;
			isFlagObstruct = 1;
		}
	}
	if(element == Straight && flag_cross2_deal == 0 && right2 <= 108 && left2 != 6 && time >= 40 
		&& flagObstructAvoid == 0)
	{
		if(right2_last - right2 >= 15 && right2_last <= 118)
		{
			flagObstructR2 = 10;
			isFlagObstruct = 1;
		}
	}
	
	if(flagObstructAvoid > 0) //���������ϰ�
	{
		flagObstructAvoid --;
	}

	/*******************����*****************/
	if(left <= 8&&right >= 120&&!flagCrossEnter)   //���Ҷ���
	{
		flag_out++;
	}
	if(dmacntl <= 20 || dmacntr <= 20)
	{
		flag_out ++;
	}
	
	if(flag_out&&(left >= 8||right <= 120) && dmacntl >= 20 && dmacntr >= 20)
	{
		flag_out--;
	}
	if(flag_out>=50&&protect && end == 0)   //����������
	{
		end = 1;
		endCnt = 25;
	}
	if(time>=(time_set*100) && end == 0)    //��ʱ
	{
		end = 1;
		endCnt = 25;
	}
	
	/***********************�ٶȲɼ�****************/
	speed_now = (dmacntl +  dmacntr) / 2;
	/****************************����Ԫ���ж�***************************************/

	if(center2 > 44 && center2 < 88 && center2_record[0] > 44 && center2_record[0] < 88)
		 if(center > 44 && center < 88)
			{
					element = Straight;
					flag_differential = 0;
			}
			
	if((center2 <= 44 && left2 <= 10) || (center2 >= 84 && right2 >= 118))
	{	
		element = Turn;
		flag_differential = 0;
	}
	if(dmacntr + dmacntl >= 400)
	{
		if(left2 <= 15 || right2 >= 113)
		{
			element = Turn;
			flag_differential = 0;
		}
	}
	
	if(element == Turn)
	{
			if(center >40 && center <88)   //ȫ����bug
			{
				if(center2 > 32 && center2 < 96)
					center_new = center * 0.7 + center2 * 0.3;
				if(center2 <= 32 && center2 > 1 && center <= 64)
					center_new = center * 0.65 + center2 * 0.35;
				if(center2 >= 96 && center < 127 && center >= 64)
					center_new = center * 0.65 + center2 * 0.35;
				
				if(center2 <= 1 && center <= 64)
				{
					center_new = center * 0.6;
				}
				if(center2 >= 127 && center >= 64)
				{
					center_new = center * 0.6 + 128 * 0.4;
				}
			}
			else
			{
				if(center <= 40)
				{
					center_new = center * 0.5;
					
					if(center2 <= 1)
					{
						center_new = center * 0.35;
						if(flag_black2 == 0)
							center_new = center * 0.5;
					}
					if(center2 >1 && center2 <= 54)
						center_new = center * 0.5 + center2 * 0.5;
					if(center2 > 54 && center2 <= 108)
						center_new = center * 0.7 + center2 * 0.3;
				}
				if(center >= 88)
				{
					center_new = center * 0.5 + 128 * 0.5;
					if(center2 >= 127)
					{
						center_new = center * 0.35 + 128 * 0.65;
						if(flag_black2 == 0)
							center_new = center * 0.5 + 128 * 0.5;
					}
					if(center2 >= 74 && center2 < 127)
						center_new = center * 0.5 + center2 * 0.5;
					
					if(center2 <74 && center2 >= 20)
						center_new = center * 0.7 + center2 * 0.3;
					
					if(center_new > 128)
						center = 128;
				}
			}
		beforeRampCnt = 0;
		average_over = 0;    //ת�������¼���
		valueUpdata = 0;
		straight = 0;
		
//		if(speed_now - speed_turn >= 25)  //�ٶȽϿ�
//			flag_into = into;
//		if(speed_now - speed_turn >= 15)
//			flag_turn_down = 10;
	}
	if(element == Straight)
	{
		valueUpdata ++;
		if(beforeRampCnt < 8)
		 beforeRampCnt ++;
		if(valueUpdata >= 30)
		{
			valueUpdata = 0;
			average_over = 0;//��һ������������ֵ
		}
		center_new = 0.6 *center2 + 0.4 * center;
		if(average_over == 0 && flagCrossCenter == 0 && flag_cross2_deal == 0)//���û����
			straight++;
		if(center < 64 && center2 > 64 && fabs(center2 - center) > 40)
			center_new = center;
		if(center > 64 && center2 < 64 && fabs(center2 - center) > 40)
			center_new = center;
	}
	/**********����ʮ�ֵ��ж� Զ�����*****************/
	
	if(flag_cross2_deal >= 1)
	{
		  center_new = center2 * 0.5 + center * 0.5;
	}
	if(flagCrossCenter > 0)
	{
			center_new = center2 * 0.5 + center * 0.5;
	}
	
	
	if(element == Turn && flag_black2 == 1)
	{
			if(center_new <= 44)
			{
				flag_differential = differentialL;
			}
			if(center_new >= 84)
			{
				flag_differential = differentialR;
			}
	}
	/*********�µ�����*************/
	if (flagRamp > 0)
	{
			beep = 1;
		  flag_black2 = 0;
		  flag_miss = 0;	
			flagRamp--;
		  center = 64;
		  center2 = 64;
		  center_new = 64;
		  for( i = saoxian; i >= 6; i --)
			{
				left = i;
				if (P[i + 2] - P[i] >= 15 && P[i + 3] - P[i + 1] >= 15 && P[i] <= 60)
						break;
			}
			if(left != 6)
			{
				for( i = left; i <= 122; i ++)
				{
					right = i;
					if (P[i - 2] - P[i] >= 15 && P[i - 3] - P[i - 1] >= 15 && P[i] <= 60)
						break;
				}
			}
			/*�ж��Ƿ���ȷ*/
			if(right - left >= 10 && right - left <= 50)
			{
				center = (right + left) / 2;
				center_new = center;
			}		
	}
	/***********ʮ����ֵ���� �Լ�������ȵļ���***************/
	if(straight >= 10)
	{
		valueLast = (average_value[4] + average_value[3] + average_value[2] 
		+ average_value[1] + average_value[0])/5;
		
		valueLast2 = (average_value2[4] + average_value2[3] + average_value2[2] 
		+ average_value2[1] + average_value2[0])/5;
		
//		staticS = (averageS[4] + averageS[3]+averageS[2] + averageS[1]+averageS[0])/5;
//		staticS2 = (averageS2[4] + averageS2[3] + averageS2[2] + averageS2[1] + averageS2[0]) / 5;
		
		straight = 0;
		average_over = 1;//����ƽ��ֵ���
	}
	/*************�ϰ�����***********8*/
	if(flag_obstruct_cntL > 0)
	{
		flag_obstruct_cntL --;
		beep = 1;
	}
	
	if(flag_obstruct_cntR > 0)
	{
		flag_obstruct_cntR --;
		beep = 1;
	}
	if(flagObstructR2 >= 1)
	{
		flagObstructR2--;
		beep = 1;
	}
	if(flagObstructL2)
	{
		flagObstructL2--;
		beep = 1;
	}
		
	
//	if(flagObstructL > 0)
//	{
//		flagObstructL--;
//		beep = 1;
//	}
//	if(flagObstructR > 0)
//	{
//		flagObstructR --;
//		beep = 1;
//	}
	
	center_new_last = center_new;
	/*******************/
		
	centerRecord[9] = centerRecord[8];
	centerRecord[8] = centerRecord[7];
	centerRecord[7] = centerRecord[6];
	centerRecord[6] = centerRecord[5];
	centerRecord[5] = centerRecord[4];
	centerRecord[4] = centerRecord[3];
	centerRecord[3] = centerRecord[2];
	centerRecord[2] = centerRecord[1];
	centerRecord[1] = centerRecord[0];
	centerRecord[0] = center;
		
		
	center2_record[9]=center2_record[8];
	center2_record[8]=center2_record[7];
	center2_record[7]=center2_record[6];
	center2_record[6]=center2_record[5];
	center2_record[5]=center2_record[4];
	center2_record[4]=center2_record[3];
	center2_record[3]=center2_record[2];
	center2_record[2]=center2_record[1];
	center2_record[1]=center2_record[0];
	center2_record[0]=center2;
	
	left2_last = left2;
	right2_last = right2;
	/*********************************/

	
	saoxian2 = center2;
	
	if(saoxian2 < 6)
		saoxian2 = 6;
	if(saoxian2 > 122)
		saoxian2 = 122;
	
	if(center2 <= 0)
		center2 = 0;
	if(center2 > 128)
		center2 = 128;
	
				/*ɨ��λ��*/
	saoxian=center;
	
	if(saoxian>=122)     //�޷�
		saoxian=122;
	if(saoxian<=6)
		saoxian=6;
	
	
	leftLast=left;
	rightLast=right;
	
	Send_Data[256]=left;
	Send_Data[257]=center;
	Send_Data[258]=right;
	Send_Data[259]=value;
	Send_Data[260]=flagCrossCenter;
	Send_Data[261]=valueLast2;
	Send_Data[262] = valueLast;
	Send_Data[263] = center_new;
	Send_Data[278] = left2;
	Send_Data[279] = center2;
	Send_Data[280] = right2;
	Send_Data[281] = value2;
	//Send_Data[282] = flag_turn_downL + flag_turn_downR;
	Send_Data[283] = element;
	Send_Data[285] = endLineValue;
	Send_Data[284] = flag_into;
	Send_Data[286] = s;
	Send_Data[287] = speed_now>>8;
	Send_Data[288] = flag_obstruct_cntL + flag_obstruct_cntR + flagObstructR2 + flagObstructL2;
	Send_Data[289] = flag_cross2_deal;
}

