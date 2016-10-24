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
unsigned char AverageValue_last = 0;
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
  PixelAverageValue = PixelAverage(128,P1);
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
		flag  = (255 - P1[i]) / 32;
		flag1 = (255 - P1[i]) % 32 / 4;
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
	uint8_t i,value_max,value_min,x1,x2,j;
		
	P1[0] = P1[6];
	P1[1] = P1[6];
	P1[2] = P1[6];
	P1[3] = P1[6];
	P1[4] = P1[6];
	P1[5] = P1[6];
	P1[22] = (P1[21] + P1[23]) / 2;
	
	value_max = P1[0];
	for (i = 2;i < 126;i++) 
  {
    if (value_max <= P1[i]) 
		{
			value_max = P1[i];
			j = i;
			if (P1[i] >= 250  && P1[i + 1] >= 250 && P1[i - 1] >= 250) Valuemax_flag = 1;
		}
  }
	value_max = (P1[j - 2] + P1[j - 1] + P1[j] + P1[j + 1] + P1[j + 2]) / 5 - 4;
	value_min = P1[0];
	for (i = 2;i < 126;i++) 
  {
    if (value_min >= P1[i]) value_min = P1[i];
		if (P1[i] >= value_max) P1[i] = value_max;
  }
	if (value_min <= 60) value_min = 60;
	
	if (Valuemax_flag) AverageValue = AverageValue_last;
	else AverageValue = (value_max + value_min * 2) / 3 + 3;
	
	AverageValue_last = AverageValue;
	
	/********************************��ֵɨ��********************************/
	
	for (i = saoxian;i <= 122;i++)
	{
		Right = i; 
		if (P1[i - 2] - P1[i] >= 8 && P1[i - 3] - P1[i - 1] >= 8 && P1[i] <= AverageValue) break;
	}
	for (i = saoxian;i >= 6;i--)
	{
		Left = i;
		if (P1[i + 2] - P1[i] >= 8 && P1[i + 3] - P1[i + 1] >= 8 && P1[i] <= AverageValue) break;
	}
	if (Left != 6 && Right != 122 && leixin == 0) Budao = (Right - Left) / 2;
	
	if (Left == 6 && Center == 10)
	{
		for (j = Right;j <= 122;j++)
		{
			P1[j] = value_min;
		}
	}
	if (Right == 122 && Center == 118)
	{
		for (j = Left;j >= 6;j--)
		{
			P1[j] = value_min;
		}
	}
	/********************************���ߴ���********************************/
	
	if (Left != 6 && Right == 122)
	{
		for (i = saoxian; i <= 122; i++)
		{
			Right = i;
			if (P1[i - 4] - P1[i] >= 6 && P1[i - 5] - P1[i - 1] >= 6 && P1[i] <= AverageValue + 3) break;
		}
		if (Right != 122) Center = (Right + Left) / 2;
		else
		{
			Center = Left + Budao;
			if (Center > 122) Center = 122;
			if (Center < (Right + Left) / 2) Center = (Right + Left) / 2;
		}
	}

	if (Left == 6 && Right != 122)
	{
		for (i = saoxian; i >= 6; i--)
		{
			Left = i;
			if (P1[i + 4] - P1[i] >= 6 && P1[i + 5] - P1[i + 1] >= 6 && P1[i] <= AverageValue + 3) break;
		}
		if (Left != 6) Center = (Right + Left ) / 2;
		else
		{
			if (Right >= Budao) Center = Right - Budao;
			else Center = 6;
			if (Center > (Right + Left) / 2) Center = (Right + Left) / 2;
		}
	}
	
	if (Left != 6 && Right != 122) Center = (Right + Left) / 2;
	
	/********************************���ߴ���********************************/
	
	if (Left == 6 && Right == 122 && AverageValue <= black_Value)
	{
		if (flag_black == 0) flag_miss = 1;
	}		
	if (flag_miss == 1)
	{
		for(i = saoxian;i <= 122;i++)
		{
			Right = i;
			if(P1[i - 5] - P1[i] >= 10 && P1[i - 6] - P1[i - 1] >= 10 && P1[i] <= AverageValue)
			{
				flag_miss = 0;
				break;
			}
		}
		for(i = saoxian;i >= 6;i--)
		{
			Left = i;
			if(P1[i + 5] - P1[i] >= 10 && P1[i + 6] - P1[i + 1] >= 10 && P1[i] <= AverageValue)
			{
				flag_miss = 0;
				break;
			}
		}
		if (Left != 6 && Right == 122)
		{
			Center = Left + Budao;
			if (Center > 122) Center = 122;
			if (Center < (Right + Left) / 2) Center = (Right + Left) / 2;
		}

		if (Left == 6 && Right != 122)  
		{
			if (Right >= Budao) Center = Right - Budao;
			else Center = 6;
			if (Center > (Right + Left) / 2) Center = (Right + Left) / 2;
		}
		if (Left != 6 && Right != 122) Center = (Right + Left) / 2;
		
		if (Left == 6 && Right == 122 && AverageValue <= black_Value)
		{
			flag_black = 0;
			flag_miss = 0;
			if(CenterLast[0] <= 64) Center = 10;
			if(CenterLast[0] >  64) Center = 118;
			Left = Left_last;
			Right = Right_last;
		}
	}
	
	/********************************ccd��������********************************/
	
 	if (Valuemax_flag == 1)
	{
		Left = Left_last;
		Right = Right_last;
		Center = CenterLast[0];
		Valuemax_flag = 0;
	}
	
	/********************************ʮ�ִ���********************************/
	
						
	if (AverageValue >= white_Value && Left <= 8 && Right >= 120 && Cross_flag_wan == 1 && AverageValue <= 200)
	{
		Cross_flag = 0;
		Cross_flag_time = 0;
		Center = 64;
	}
	if (AverageValue >= white_Value && Left <= 8 && Right >= 120 && Cross_flag_wan == 0 && AverageValue <= 200)
	{
		Cross_flag = 1;
		Cross_flag_time = 0;
		Center = 64;
	}
	if (Cross_flag)
	{		
		if (leixin == 1) Cross_flag_wan = 1;
		if (Cross_flag_time >= 40)
		{
			if (leixin == 0 && leixin_last[0] == 0) 
			{
				Cross_flag_wan = 0;
				Cross_flag 		 = 0;
			}
		}
		x1 = Left_p2;
		x2 = Right_p2;
	}	
	else
	{
		x1 = Left_p1;
		x2 = Right_p1;
		if (leixin == 0) Cross_flag_wan = 0;
	}
	
	/********************************����********************************/
	if (((Left_last - Left >= 10 && Left_last - Left <= 25)|| (Right - Right_last >= 10 && Right - Right_last <= 25)) && Cross_flag == 0)
	{
		if (CenterLast[0] <= 63) Center = 40;
		if (CenterLast[0] >  63) Center = 86;
	}
	if (CenterLast[0] - Center >= 60 || Center - CenterLast[0] >= 60)
	{
		Center = CenterLast[0];
	}
	if (Center > 44 && Center < 88 && CenterLast[0] > 44 && CenterLast[0] < 88)
	{
		leixin = 0;//zhidao 
		jiansuflag = 0;
	}
	else zhidaoflag = 0;
	
	if ((Center <= 44 && Left <= 13) || (Center >=84 && Right >= 115))
	{
		leixin = 1;//wandao
		jiasuflag = 0;
	}
	if (leixin == 0)
	{
		zhidaoflag_save = zhidaoflag;
	}
	/****************************************************************************/
	
	CenterLast[1] = CenterLast[0];
	CenterLast[0] = Center;
	
	Left_last = Left;
	Right_last = Right;

	leixin_last[0] = leixin;
		
	
	if (Center  > 122)   Center = 122;
	if (Center  < 6) 	  Center = 6;
	
	saoxian = Center;
	
	if (Center <= 63) FTMDuty = 4880 - (63 - Center) * (63 - Center) * x1 / 100;
	if (Center >= 64) FTMDuty = 4880 + (Center - 64) * (Center - 64) * x2 / 100;
	
	if (FTMDuty <= 3970) FTMDuty = 3970;
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
	for (m = 0;m < 3;m++)
	{
		OLED_Set_XY(Center,m);
		OLED_WrDat(0xff);
	}
	for (m = 0;m < 3;m++)
	{
		OLED_Set_XY(Center,m);
		OLED_WrDat(0x00);
	}
}

