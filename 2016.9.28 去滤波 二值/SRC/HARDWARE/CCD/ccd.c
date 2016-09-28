#include "ccd.h"
#include "gpio.h"
#include "adc.h"
#include "delay.h"
#include "uart.h"
#include "pit.h"
#include "oled.h"
#include "ftm.h"
#include "define.h"
#include "chuinit.h"


unsigned char AverageValue;
/*************************************************************************
*
*  �������ƣ�void DelayNs(void)
*  ����˵����CCD��ʱ���� 200ns
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void DelayNs(void)
{	
	uint8_t i;
	for(i = 0;i < 1;i++)
	{
		__nop();
		__nop();
	}
}
/*************************************************************************
*
*  �������ƣ�PixelAverage
*  ����˵����������ľ�ֵ����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
uint8_t PixelAverage(uint8_t len, uint8_t *data) 
{
  uint8_t i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((uint8_t)(sum / len));
}


/*************************************************************************
*
*  �������ƣ�StartIntegration
*  ����˵����CCD��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void StartIntegration(void)
{
	uint8_t i;
	
	CCD_SI = 1;
	DelayNs();
	CCD_CLK = 1;
	DelayNs();
	CCD_SI = 0;
	DelayNs();
	CCD_CLK = 0;

	for(i=0;i<127;i++)
	{
		DelayNs();
		DelayNs();
		CCD_CLK = 1;
		DelayNs();
		DelayNs();
		CCD_CLK = 0;
	}		
	DelayNs();
  DelayNs();
  CCD_CLK = 1;           /* CLK = 1 */
  DelayNs();
  DelayNs();
  CCD_CLK = 0;         /* CLK = 0 */
}

/*************************************************************************
*
*  �������ƣ�ImageCapture
*  ����˵����CCD��������
*  ����˵����* ImageData   ��������
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/
void ImageCapture(uint8_t * ImageData) 
{
    uint8_t i;
    extern uint8_t AtemP ;

    CCD_SI=1;            /* SI  = 1 */
    DelayNs();
		CCD_CLK=1;           /* CLK = 1 */
    DelayNs();
    CCD_SI=0;            /* SI  = 0 */
    DelayNs();

    //Delay 10us for sample the first pixel
    /**/
		DelayUs(10);

    //Sampling Pixel 1

    *ImageData =  ADC_GetConversionValue(ADC1_SE10_PB4);
    ImageData ++ ;
    CCD_CLK=0;            /* CLK = 0 */

    for(i=0; i<127; i++) 
		{
      DelayNs();
      DelayNs();
      CCD_CLK=1;        /* CLK = 1 */
      DelayNs();
      DelayNs();

      *ImageData =  ADC_GetConversionValue(ADC1_SE10_PB4);
      ImageData ++ ;
      CCD_CLK=0;       /* CLK = 0 */
    }
    DelayNs();
    DelayNs();
    CCD_CLK=1;           /* CLK = 1 */
    DelayNs();
    DelayNs();
    CCD_CLK=0;           /* CLK = 0 */
}

/*************************************************************************
*
*  �������ƣ�CalculateIntegrationTime
*  ����˵���������ع�ʱ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
/* �ع�ʱ�䣬��λms */
uint8_t IntegrationTime = 100;
void CalculateIntegrationTime(void)
{						
	/* 128�����ص��ƽ��ADֵ */
	uint8_t PixelAverageValue;							
	/* 128�����ص��ƽ����ѹֵ��10�� */
	uint8_t PixelAverageVoltage;						
	/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
	uint16_t TargetPixelAverageVoltage = 23;			
	/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
	uint16_t PixelAverageVoltageError = 0;				
	/* �趨Ŀ��ƽ����ѹֵ�����ƫ�ʵ�ʵ�ѹ��10�� */
	uint16_t TargetPixelAverageVoltageAllowError = 2;

  /* ����128�����ص��ƽ��ADֵ */
  PixelAverageValue = PixelAverage(128,Pixel);
  /* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
  PixelAverageVoltage = (uint8_t)((int)PixelAverageValue * 26 / 200);

  PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
  if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError) IntegrationTime--;
  if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)  IntegrationTime++;
  if(IntegrationTime <= 1)	 IntegrationTime = 1;
  if(IntegrationTime >= 100) IntegrationTime = 100;
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
	for(i = 0;i <= 127;i++)
	{
		flag  = (255 - Pixel[i]) / 32;
		flag1 = (255 - Pixel[i]) % 32 / 4;
	  for(j = 7;j >= 4;j--)
			{
				if(j >  flag) oled_data[j][i]=0xff;
				if(j == flag) oled_data[j][i]=0xff<<flag1;
				if(j <  flag) oled_data[j][i]=0x00;
			}
		}
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
	for(i = 7;i >= 4;i--)
	{
		OLED_Set_XY(0,i);
	  for(j = 0;j <= 127;j++) OLED_WrDat(oled_data[i][j]);
	}
}
/****************************��̬ȷ����ֵ******************************/
//void DT(void)
//{
//	uint8_t i,value_max = 0,value_min = 255,maxvalue;
////	
//	for(i = 10;i <= 120;i++) 
//  {
//    if(value_max <= Pixel[i]) 
//		{
//			value_max = Pixel[i];
//			maxvalue = i;
//		}
//    if(value_min >= Pixel[i])	value_min = Pixel[i];
//  }
//	value_max = (Pixel[maxvalue] + Pixel[maxvalue + 1] + Pixel[maxvalue + 2] + Pixel[maxvalue - 1] + Pixel[maxvalue - 2]) / 5;
//	if(value_min < 40) value_min = 40;
//	AverageValue = (0.3 * value_max + 0.7 * value_min);
//}
//void DT(void)
//{
//	uint8_t i,value_max,value_min;
//	
//	value_max = Pixel[0];
//	for(i = 2;i < 126;i++) 
//  {
//    if(value_max <= Pixel[i]) value_max = Pixel[i];
//  }
//	value_min = Pixel[0];
//	for(i = 2;i < 126;i++) 
//  {
//    if(value_min >= Pixel[i]) value_min = Pixel[i];
//  }
//	AverageValue = (value_max+value_min) / 2 + 10;
//}
///****************************��ֵ��******************************/
//void erzhi(void)
//{
//	uint8_t i;
//	DT();
//	for(i = 0;i <= 128;i++)
//  {
//    if(Pixel[i] > AverageValue) Pixel[i] = 255;
//    else 												Pixel[i] = 0;
//  }
//}
///*******************************�˲�*************************/
//void LB(void)
//{
//  uint8_t i;
//  for(i = 1;i <= 127;i++)
//  {
//    if(Pixel[i] == 0 && Pixel[i] != Pixel[i-1] && Pixel[i] != Pixel[i+1]) 			 Pixel[i] = 255;
//    else if(Pixel[i] == 255 && Pixel[i] != Pixel[i-1] && Pixel[i] != Pixel[i+1]) Pixel[i] = 0;
//	}
//  for(i = 1;i <= 127;i++)
//  {
//    if(Pixel[i] == 0 && Pixel[i] == Pixel[i+1] && Pixel[i] != Pixel[i-1] && Pixel[i] != Pixel[i+2])
//    {
//      Pixel[i]   = 255;
//      Pixel[i+1] = 255;
//    }
//    if(Pixel[i] == 255 && Pixel[i] == Pixel[i+1] && Pixel[i] != Pixel[i-1] && Pixel[i] != Pixel[i+2])            
//    {
//      Pixel[i]   = 0;
//      Pixel[i+1] = 0;
//    }
//	}
//}

/*****************************
*
*  �������ƣCCCD_HeiXian
*  ����˵�����ɼ�����λ�ý��к��ߵ�������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void CCD_HeiXian(void)
{
	uint8_t i,value_max,value_min,maxvalue;
	
//	value_max = Pixel[0];
//	for(i = 2;i < 126;i++) 
//  {
//    if(value_max <= Pixel[i]) value_max = Pixel[i];
//  }
//	value_min = Pixel[0];
//	for(i = 2;i < 126;i++) 
//  {
//    if(value_min >= Pixel[i]) value_min = Pixel[i];
//  }
//	AverageValue = (value_max+value_min) / 2 + 20;
	
	
	for(i = 10;i <= 120;i++)
  {
    if(value_max <= Pixel[i])
		{
			value_max = Pixel[i];
			maxvalue = i;
		}
    if(value_min >= Pixel[i])	value_min = Pixel[i];
  }
	value_max = (Pixel[maxvalue] + Pixel[maxvalue + 1] + Pixel[maxvalue + 2] + Pixel[maxvalue - 1] + Pixel[maxvalue - 2]) / 5;
	
	if(value_min < 40) value_min = 40;
	
	AverageValue = (0.3 * value_max + 0.7 * value_min);

	for(i = saoxian;i <= 122;i++)
	{
		Right = i;
		if(Pixel[i - 2] - Pixel[i] >= 8 && Pixel[i - 3] - Pixel[i - 1] >= 8 && Pixel[i] <= AverageValue) break;
	}
	for(i = saoxian;i >= 6;i--)
	{
		Left = i;
		if(Pixel[i + 2] - Pixel[i] >= 8 && Pixel[i + 3] - Pixel[i + 1] >= 8 && Pixel[i] <= AverageValue) break;
	}
	if (Left != 6 && Right != 122 && leixin == 0) Budao = (Right - Left) / 2;
	
/***********************buxianchuli*************************************/
	
	if (Left != 6 && Right == 122)
		{
				for (i = saoxian; i <= 122; i++)
				{
						Right = i;
						if(Pixel[i - 4] - Pixel[i] >= 8 && Pixel[i - 5] - Pixel[i - 1] >= 8 && Pixel[i] <= AverageValue) break;
				}
				if(Right!= 122) Center = (Right + Left) / 2;
				else
				{
				  Center = Left + Budao;
					if (Center > 128) Center = 128;
					if (Center < (Right + Left) / 2) Center = (Right + Left) / 2;
				}
		}

	if (Left == 6 && Right != 122)  
		{
				for (i = saoxian; i >= 6; i--)
				{
						Left = i;
						if(Pixel[i + 4] - Pixel[i] >= 8 && Pixel[i + 5] - Pixel[i + 1] >= 8 && Pixel[i] <= AverageValue) break;
				}
				if(Left != 6) Center = (Right + Left ) / 2;
				else
				{
					if (Right >= Budao) Center = Right - Budao;
					else Center = 0;
					if (Center > (Right + Left) / 2) Center = (Right + Left) / 2;
				}
		} 
	
	if (Left != 6 && Right != 122) Center = (Right + Left) / 2;

/*	if (Left == 6 && Right == 122)
//	{
//		if (flag_black == 0) flag_miss = 1;
//	}		
//
//	
//	if (flag_miss == 1)
//	{
//			for(i = shaoxian;i <= 122;i++)
//		{
//			Right = i;
//			if(Pixel[i] == 0)
//			{
//				flag_miss = 0;
//				break;
//			}
//		}
//		for(i = shaoxian;i >= 6;i--)
//		{
//			Left = i;
//			if(Pixel[i] == 0)
//			{
//				flag_miss = 0;
//				break;
//			}
//		}
//		if (Left != 6 && Right == 122)
//			{
//						Center = Left + Budao;
//						if (Center > 128) Center = 128;
//						if (Center < (Right + Left) / 2) Center = (Right + Left) / 2;
//			}

//		if (Left == 6 && Right != 122)  
//			{
//						if (Right >= Budao) Center = Right - Budao;
//						else Center = 0;
//						if (Center > (Right + Left) / 2) Center = (Right + Left) / 2;
//			}
//			
//		
//		if (Left != 6 && Right != 122) Center = (Right + Left) / 2;
//		
//		if (Left == 6 && Right == 122)
//			{
//					flag_black = 1;
//				  flag_miss = 0;
//					if (CenterLast[0] < 64)  flag_miss_record = 1;//��ת
//					if (CenterLast[0] >= 64) flag_miss_record = 2;//��ת
//			}
//	}
//		if(Left <= 12 && Right >= 120 && CenterLast[0] < 70 && CenterLast[0] > 55)
//		{
//			DelayNs();
//			Center = 64;
//		}	
//		*/

		
	if (Right == Left)
		{
			Left = LeftLast;
			Right = RightLast;
			Center = (Left + Right) / 2;
		}
	
	if (Center > 44 && Center <88 && CenterLast[0] > 44 && CenterLast[0] < 88 )
	{
		leixin = 0;//zhidao
	}
	
	if ((Center <= 44 && Left <= 13) || (Center >=84 && Right >= 115))
	{
		leixin = 1;//wandao
	}
	
	/*********************************************************************/	

		LeftLast = Left;
		RightLast = Right;

		CenterLast[1] = CenterLast[0];
		CenterLast[0] = Center;
		
		saoxian = Center;
	
		if(saoxian >= 122) saoxian = 122;
	  if(saoxian <= 6) 	 saoxian = 6;
		if(Center  >= 122)  Center = 122;
	  if(Center  <= 6) 	  Center = 6;
		
	if (Center <= 63) FTMDuty = 4910 - (63 - Center)*(63 - Center) * a1 / 10;
	if (Center >= 64) FTMDuty = 4910 + (Center - 64)*(Center - 64) * a1 / 10;
	
	if (FTMDuty <= 4000) FTMDuty = 4000;
	if (FTMDuty >= 5800) FTMDuty = 5800;
	FTM_PWM_ChangeDuty(FTM0_CH4_PA7,FTMDuty);
}

/*************************************************************************
*
*  �������ƣCOLED_ZhongXian
*  ����˵������ʾ���ߵ�λ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/
void OLED_ZhongXian(void)
{
	uint8_t m;
	for(m = 0;m < 3;m++)
	{
		OLED_Set_XY(Center,m);
		OLED_WrDat(0xff);
	}
	for(m = 0;m < 3;m++)
	{
		OLED_Set_XY(Center,m);
		OLED_WrDat(0x00);
	}
}

