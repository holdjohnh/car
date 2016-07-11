/**
  ******************************************************************************
  * @file    key.c
  * @author  YANDLD
  * @version V2.4
  * @date    2013.5.23
  * @brief   ����ԭ�Ӻ˺��İ� BSP���� KEY����
  ******************************************************************************
  */

#include "key.h"

//KEY״̬������
#define _KEY_STATE_0  (0)
#define _KEY_STATE_1  (1)
#define _KEY_STATE_2  (2)
#define _KEY_STATE_3  (3)

/***********************************************************************************************
 ���ܣ�������ʼ��
 �βΣ�0
 ���أ�0
 ��⣺��ʼ�������ϵ�KEY ����GPIO����
************************************************************************************************/
void KEY_Init(void)
{
	//����GPIO��ʼ���ṹ
	GPIO_InitTypeDef GPIO_InitStruct1;	
	
	GPIO_InitStruct1.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_RESET;
	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
	if(KEY_STATE_DOWN == 1)
	{
		GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPD; //��������
	}
	else
	{
		GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_IPU; //��������
	}
	GPIO_InitStruct1.GPIOx = KEY1_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
}

/***********************************************************************************************
 ���ܣ���ð���״̬
 �βΣ�0
 ���أ�@arg KEY_STATE_DOWN: ����������
       @arg KEY_STATE_UP  : ����δ������
 ��⣺0
************************************************************************************************/
uint8_t KEY_GetKeyValue(void)
{
	return KEY1;
}

//������ɨ���м�㺯�� �����Ÿ��û�
static uint8_t SKEY_Driver(void)
{
	static uint8_t key_time;
	static uint8_t key_state;
	uint8_t key_press;
	uint8_t key_return = KEY_NO_KEY;
	//���״̬
	key_press = KEY_GetKeyValue();
	//��ʼ״̬��
	switch(key_state)
	{
		case _KEY_STATE_0:            //������ʼ״̬
			if(key_press == KEY_STATE_DOWN) 
			{
				key_state = _KEY_STATE_1;
			}
		break; 
		case _KEY_STATE_1:            //����������ȷ��̬
			if(key_press == KEY_STATE_DOWN)
			{
				key_time = 0;
				key_state = _KEY_STATE_2;
			}
			else
			{
				key_state = _KEY_STATE_0;
			}
		break;
		case _KEY_STATE_2:
			if(key_press == KEY_STATE_UP)  // ��ʱ�����ͷţ�˵���ǲ���һ�ζ̲���������S_key 
			{
				key_return = KEY_SINGLE;
				key_state = _KEY_STATE_0;
			}
			else if (++key_time > 100)  //�������£���ʱ��10ms��10msΪ������ѭ��ִ�м���� 
			{
				key_return = KEY_LONG;
				key_state = _KEY_STATE_3;
			}
			break;
		case _KEY_STATE_3: // �ȴ������ͷ�״̬����״ֻ̬�����ް����¼� 
			if(key_press == KEY_STATE_UP)           
			{
				key_state = _KEY_STATE_0;  // ת�����ȴ������ͷ�״̬ 
			}
		break;
	}
	return key_return; 
}

/***********************************************************************************************
 ���ܣ���ð���״̬
 �βΣ�0
 ���أ�@arg KEY_NO_KEY  :  �ް���
       @arg KEY_SINGLE  :  ����
       @arg KEY_DOUBLE  :  ˫��
       @arg KEY_LONG    :  ������
 ��⣺������10MS��Ƶ�ʵ�������������ܷ�����ȷ��ֵ 
************************************************************************************************/
uint8_t KEY_Scan(void)
{
	uint8_t key_return = KEY_NO_KEY;
	uint8_t key_temp = KEY_NO_KEY;
	static uint8_t key_time;
	static uint8_t key_state;
	key_temp = SKEY_Driver();
		switch(key_state)
		{
			case _KEY_STATE_0:
				if(key_temp == KEY_SINGLE)
				{
					key_time = 0;
					key_state = _KEY_STATE_1;
				}
				else
				{
					key_return = key_temp;
				}
			break;
			case _KEY_STATE_1:
				if(key_temp == KEY_SINGLE)// ��һ�ε��� (����϶�<500ms)
				{
					key_return = KEY_DOUBLE;
					key_state = _KEY_STATE_0;
				}
				else
				{
					if(++key_time > 25)
					{
						key_return = KEY_SINGLE;
						key_state = _KEY_STATE_0;
					}
				}
			break;
		}
	return key_return;
}
