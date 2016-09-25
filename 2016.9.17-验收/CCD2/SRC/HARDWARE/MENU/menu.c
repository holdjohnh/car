#include "menu.h"
#include "oled.h"
#include "define.h"
#include "delay.h"
#include "pit.h"
#include "ftm.h"
#include "yinjiao.h"


unsigned char yiwei(int8_t x,int8_t i)
{
		if(i<=6&i>=0) return(x);
		if(i>=8) 			return(x+6-i);
}


/******************************��������ʾ********************************/
void Menu_Init(void)
{
	OLED_Write_Char(0, yiwei(i,i), 43);
	OLED_Write_String(2,yiwei(0,i),"AI ");
	OLED_Write_String(2,yiwei(2,i),"BI ");
	OLED_Write_String(2,yiwei(4,i),"CI ");
	OLED_Write_String(2,yiwei(6,i),"DI ");
	OLED_Write_String(2,yiwei(8,i),"F1 ");
	OLED_Write_String(2,yiwei(10,i),"F2 ");
	OLED_Write_String(2,yiwei(12,i),"SD ");
	OLED_Write_Num2(7,yiwei(0,i),a1);
	OLED_Write_String(9,yiwei(0,i),"  ");
	OLED_Write_Num2(7,yiwei(2,i),a2);
	OLED_Write_String(9,yiwei(2,i),"  ");
	OLED_Write_Num2(7,yiwei(4,i),a3);
	OLED_Write_String(9,yiwei(4,i),"  ");
	OLED_Write_Num2(7,yiwei(6,i),a4);
	OLED_Write_String(9,yiwei(6,i),"  ");
	OLED_Write_Num4(7,yiwei(8,i),FTMDuty_1);
	OLED_Write_Num4(7,yiwei(10,i),FTMDuty_2);
	OLED_Write_String(7,yiwei(12,i),"    ");
	
	//����
	if(Key_up == 0)
	{
		DelayMs(100);
		if(Key_up == 0)
		{
			OLED_Write_Char(0,yiwei(i,i), ' ');
			i = i - 2;
			if(i == -2) i = 12;
		}
	}
	
	//����
	if(Key_down == 0)
	{
		DelayMs(100);
		if(Key_down == 0)
		{
			OLED_Write_Char(0,yiwei(i,i), ' ');
			i = i + 2;
			if(i == 14) i = 0;
		}
	}
	
	//a1
	if(yiwei(i,i) == yiwei(0,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				a1++;
				if(a1 >= 50) a1 = 0;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				a1--;
				if(a1 <= 0) a1 = 50;
			}
		}
	}
	//a2
	if(yiwei(i,i) == yiwei(2,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				a2++;
				if(a2 >= 50) a2 = 0;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				a2--;
				if(a2 <= 0) a2 = 50;
			}
		}
	}
	//a3
	if(yiwei(i,i) == yiwei(4,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				a3++;
				if(a3 >= 50) a3 = 0;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				a3--;
				if(a3 <= 0) a3 = 50;
			}
		}
	}
	//a4
	if(yiwei(i,i) == yiwei(6,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				a4++;
				if(a4 >= 50) a4 = 0;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				a4--;
				if(a4 <= 0) a4 = 50;
			}
		}
	}

	//FTMDuty_1
	if(yiwei(i,i) == yiwei(8,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				FTMDuty_1 += 50;
				if(FTMDuty_1 >= 3000) FTMDuty_1 = 3000;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				FTMDuty_1 -= 50;
				if(FTMDuty_1 <= 0) FTMDuty_1 = 0;
			}
		}
	}
	
	//FTMDuty_2
	if(yiwei(i,i) == yiwei(10,i))
	{
		//��
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				FTMDuty_2 += 50;
				if(FTMDuty_2 >= 3000) FTMDuty_2 = 3000;
			}
		}
		//��
		if(Key_left == 0)
		{
			DelayMs(50);
			if(Key_left == 0)
			{
				FTMDuty_2 -= 50;
				if(FTMDuty_2 <= 0) FTMDuty_2 = 0;
			}
		}
	}
	
	//SD
	if(yiwei(i,i) == yiwei(12,i))
	{
		if(Key_right == 0)
		{
			DelayMs(50);
			if(Key_right == 0)
			{
				OLED_Clear();
				SD_D = 0;
				flag_sd_d = 1;
			}
		}
	}
	//��ccd����
	if(Key_2 == 0)
	{
		DelayMs(100);
		if(Key_2 == 0)
		{
			OLED_Clear();
			flag_test = 1;
			SD_X = 0;
			PIT_Start(PIT1);
			FTM_PWM_ChangeDuty(FTM0_CH3_PA6,FTMDuty_1);
		}
	}
	//����
	if(Key_1 == 0)
	{
		DelayMs(50);
		if(Key_1 == 0)
		{
			OLED_Clear();
			flag_run = 1;
			PIT_Start(PIT1);
			FTM_PWM_ChangeDuty(FTM0_CH3_PA6,FTMDuty_1);
		}
	}
	
}

//�˳�
void Menu_Quit(void)
{
	if(Key_2  ==  0)
	{
		DelayMs(100);
		if(Key_2  ==  0)
		{
			OLED_Clear();
			flag_test = 0;
			PIT_Stop(PIT1);
			FTM_PWM_ChangeDuty(FTM0_CH3_PA6,0);
		}
	}
}

