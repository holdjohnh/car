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
#include "spi.h"
#include "i2c.h"
#include "pdb.h"
#include "sd.h"
#include "flash.h"
#include "spilcd.h"
#include "stdio.h"
#include "nrf2401.h"
#include "uart.h"
#include "oled.h"
#include "data_sent.h"
#include "math.h"
#include "L3G4200D.h"
#include "menu.h"
#include "dmacnt.h"
#include "Mydefine.h"
#include "ccd.h"

uint16_t Mode = 0;           //ģʽ
uint16_t protect = 0;        //�Ƿ񱣻�
uint8_t time_set = 20;       //ʱ���趨
uint32_t time=0;             //ʱ�����
uint32_t k;                  //sd����
uint8_t Dummy = 0;           //DMA�ɼ���bug
uint8_t ccd_show = 1;        //ccd��ʾ����
uint8_t flag_longstraight;   //�Ƿ��������


uint8_t flag_ccd_10ms=0;          //�ж�ccd�ɼ���־
uint8_t flag_v_20ms;             //�ж��ٶȿ��Ʊ�־2


uint8_t P[128];              //ccd1�ɼ����ĵ�
uint8_t P2[128];             //ccd2�ɼ����ĵ�
uint8_t Send_Data[292];      //��������
uint8_t oled_data[8][128];   //oled����ʾ�ĵ�
uint8_t center=64;           //����
uint8_t value;             //ccd��ֵ
uint8_t valueLast;        //��һ����ֵ
uint8_t max, min;            //
uint8_t minLast;           //��һ����Сֵ
uint8_t leftLast=0;       //��һ������
uint8_t rightLast=128;    //��һ������
uint8_t s=20;                //�������
uint8_t saoxian=64;          //ɨ����ʼ��
uint8_t flagCrossEnter = 0;  //ʮ��ģʽ
uint8_t flagCrossCenter=0;  //ʮ�ָ�64��־
uint8_t flagCrossClear=0;   //ʮ�������־
uint8_t flagDiu=0;        //���߱�־
uint8_t flagDiu2;         //
uint8_t flag_obstruct;       //�ϰ�
uint8_t flag_obstruct_cntL;  //�ϰ�����
uint8_t flag_obstruct_cntR;  //�ϰ�����
uint16_t straight=0;         //ֱ���ж���־
uint8_t flag_out;            //ȫ������ ����
uint8_t element=0;           //����Ԫ��
uint8_t centerRecord[10] = {64,64,64,64,64,64,64,64,64,64};  //����ʮ������
uint8_t flagCrossRecord = 0;
uint8_t average_value[5];
uint8_t average_over = 0;     //ƽ����ֵ�������
uint8_t flagMissRecord = 0;
uint8_t lineValueMax = 0;
uint8_t lineValueMin = 0;
uint8_t endLeftLine = 0;
uint8_t endRightLine = 0;
uint8_t end = 0;
uint16_t endTime = 12;
uint8_t endCnt = 0;
uint8_t endLineValue = 0;

uint8_t center2 = 64;        //ccd2������
uint8_t value2;              //ccd2��ֵ
uint8_t value2_last;         //ccd2��ֵ
uint8_t left2_last;          //
uint8_t right2_last;         //
uint8_t s2;                  //ccd2�������
uint8_t flag_miss;           //ccd2���߱��
uint8_t flag_miss_record;    //
uint8_t flag_cross2;         //ccd2ʮ��
uint8_t flag_cross2_deal;    //ccd2ʮ�ִ���
uint8_t flag_cross2_record;  //��¼ʮ�ֵ�ת��
uint8_t min2_last;           //
uint8_t max2 = 0;            //
uint8_t min2 = 255;          //
uint8_t saoxian2 = 64;       //ccd2ɨ��
uint8_t center2_record[10] = {64,64,64,64,64,64,64,64,64,64};  //ccd2��ȥʮ��
uint8_t flag_black2;
uint8_t average_value2[5];
uint8_t valueLast2;
uint8_t flagBlackCnt = 0;

uint8_t center_new = 64;
uint8_t center_new_last = 64;
uint8_t flag_cross_ture = 0;
uint8_t staticS = 0;  
uint8_t staticS2 = 0;
uint8_t averageS[5];
uint8_t averageS2[5];
uint8_t flagRamp = 0;
uint8_t flagObstructAvoid = 0;
uint16_t flagRampAvoid = 0;
uint8_t turnRecord = 0;
uint8_t valueUpdata = 0;
uint8_t rampCnt = 25;
uint8_t valueAvoid = 0;
uint8_t maxRecord = 0;
uint8_t max2Record = 0;



uint16_t pwm_steer=pwm_steer_center;     //���
uint16_t pwm_steer_last=pwm_steer_center;//��һ�����ռ�ձ�
uint16_t pwm_ten=5000;       //ʮ��ռ�ձ�
int16_t pwm_left=5000;           //����ռ�ձ�
int16_t pwm_right=5000;          //����ռ�ձ�
int16_t pwm_left_last=4000;      //��һ����·ռ�ձ�
int16_t pwm_right_last=4000;     //��һ����·ռ�ձ�
int16_t e2L;                     //�ٶ�ǰ����ƫ��
int16_t e1L;                     //�ٶ�ǰһ��ƫ��
int16_t e2R;                     //�ٶ�ǰ����ƫ��
int16_t e1R;                     //�ٶ�ǰһ��ƫ��
uint16_t dmacntl;            //�����ٶ�CNT
uint16_t dmacntr;            //�����ٶ�CNT
uint16_t cntl[4];            //�Ĵβɼ�
uint16_t cntr[4];            //�Ĵβɼ�
uint16_t Pv_into=75;         //�ٶ�P
uint16_t Iv_into=45;         //�ٶ�I
uint16_t Pv_straight=110;     //�ٶ�P
uint16_t Iv_straight=45;     //�ٶ�I
uint16_t PvL_turn=60;         //�ٶ�P
uint16_t IvL_turn=30;         //�ٶ�I
uint16_t PvR_turn=60;         //�ٶ�P
uint16_t IvR_turn=30;         //�ٶ�I
uint16_t Dv=0;               //�ٶ�D
uint16_t PtR=28;             //��תP
uint16_t DtR=27;             //��תD
uint16_t PtL=28;             //��תP
uint16_t DtL=27;             //��תD
uint16_t ZD_P = 11;          //ֱ��P
uint16_t ZD_D = 10;          //ֱ��D
uint16_t Pvdif=10;           //����
uint16_t speed_set_l=0;      //�����趨Ŀ��
uint16_t speed_set_r=0;      //�����趨Ŀ��
uint16_t speed_s=210;        //ֱ���ٶ�
uint16_t speed_turn=150;     //ת���ٶ�
uint8_t  flag_differential;  //����
uint8_t  into = 17;          //
uint8_t  speed_recordL[3];      //
uint8_t  speed_recordR[3];      //
uint16_t speed_now;           //�������ٶȺ�
uint16_t speedInto=90;        //�����ٶ�
uint16_t pwmSteerObstructL=125;        
uint16_t pwmSteerObstructR=125;       
uint16_t ZA_changshuL = 8;    //�ϰ�����
uint16_t ZA_changshuR = 8;    //
uint8_t flag_into = 0;       //�����
uint16_t Pv_slow = 50;
uint16_t Iv_slow = 30;
uint8_t flag_pidfenduanL = 0;
uint8_t flag_pidfenduanR = 0;
uint16_t rampSpeed = 90;
uint8_t speedSlowCntL = 0;
uint8_t speedSlowCntR = 0;
uint16_t PvOutsideWheel = 90;
uint16_t IvOutsideWheel = 45;
uint8_t flagObstructL = 0;
uint8_t flagObstructR = 0;
uint8_t beforeRampCnt = 0;
uint8_t left,right;
uint8_t left2,right2;
int8_t kLeft[5];
int8_t kRight[5];
int8_t kSumLeft = 0;
int8_t kSumRight = 0;
uint8_t flagObstructL2 = 0;
uint8_t flagObstructR2 = 0;
uint8_t isFlagObstruct = 0;
//uint16_t pwmSteerObstructLeft = 60;
//uint16_t pwmSteerObstructRight = 60;
//uint16_t pwmSteerObstructLeft2 = 50;
//uint16_t pwmSteerObstructRight2 = 50;
uint16_t pwmSteerObstructLeft = 35;
uint16_t pwmSteerObstructRight = 35;
uint16_t pwmSteerObstructLeft2 = 50;
uint16_t pwmSteerObstructRight2 = 50;


uint8_t ccdTemp[5];
uint8_t whichCcd;
uint8_t ccdNumber;

Data_Type DATA_ALL;
extern Data_Type *Sent_Data;

/***************************************************/
void pit_init()
{
	PIT_InitTypeDef PIT_InitStruct1;
	PIT_InitStruct1.PITx = PIT1;          
	PIT_InitStruct1.PIT_Interval = 10;   
	PIT_Init(&PIT_InitStruct1);
	PIT_ITConfig(PIT1,PIT_IT_TIF,ENABLE);
	NVIC_DisableIRQ(PIT1_IRQn);
	
}
/**************************************************/
void DmaInit()
{
	DMA_InitTypeDef DMA_InitStruct1;
	DMA_InitStruct1.Channelx = DMA_CH0;                         //ʹ��DMA0ͨ��  (0-15)
	DMA_InitStruct1.DMAAutoClose = ENABLE;                      //������Ϻ��Զ��ر�
	DMA_InitStruct1.EnableState = DISABLE;                       //��ʼ����������ʼ����
	DMA_InitStruct1.MinorLoopLength = 5;                      //����10��
	DMA_InitStruct1.PeripheralDMAReq  = DMA_MUX2;               //����Ҫ����Դ �����Ŭ������
	DMA_InitStruct1.TransferBytes = 1;                          //ÿ�δ���һ���ֽ�
	//����Ŀ�ĵ�ַ�������
	DMA_InitStruct1.DestBaseAddr = (uint32_t)&ccdTemp;     //ָ��Ŀ�ĵ�ַ
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;                //����Ϊ1Byte
	DMA_InitStruct1.DestMajorInc = 0;                           //ִֻ��һ�δ�ѭ��
	DMA_InitStruct1.DestMinorInc = 1;                           //ÿ�δ������ַ+1
 
	//����Դ��ַ�������
	DMA_InitStruct1.SourceBaseAddr = (uint32_t)&(PTD->PDIR);
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 0;
	DMA_Init(&DMA_InitStruct1);
	 
	DMA_ITConfig(DMA0, DMA_IT_MAJOR, DMA_CH0,ENABLE); //������������ж�
}
/*****************************************************/
void dmacnt_init()
{
	DMACNT_InitTypeDef DMACNT_InitStruct1;
	DMACNT_InitStruct1.DMACNT_Mode = DMACNT_MODE_RISING;  //�����ؼ���
	DMACNT_InitStruct1.DMA_Chl = DMA_CH2;                 //ʹ��ͨ�� 0
	DMACNT_InitStruct1.GPIOx = PTB;                       
	DMACNT_InitStruct1.GPIO_Pin =  GPIO_Pin_10;
	DMACNT_Init(&DMACNT_InitStruct1);
	
	DMACNT_InitStruct1.DMACNT_Mode = DMACNT_MODE_RISING;
	DMACNT_InitStruct1.DMA_Chl = DMA_CH1;
	DMACNT_InitStruct1.GPIOx = PTC;
	DMACNT_InitStruct1.GPIO_Pin = GPIO_Pin_4;
	DMACNT_Init(&DMACNT_InitStruct1);
}
/**********************ת���ٶȿ���*****************************/
int main(void)
{
	//��ʼ��ϵͳʱ�� ʹ���ⲿ50M���� PLL��Ƶ��100M
	SystemClockSetup(ClockSource_EX50M,CoreClock_100M);
	
	DmaInit();
	OLED_Init();
	DelayInit();
	pit_init();
	dmacnt_init();
	ccd_Init();
	
	DataInit();
	Data_Uart_Init();
	
	DelayMs(1000);
	
	NVIC_EnableIRQ(PIT1_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);
	
	if(Mode==1)    //ģʽ1   ccdͼ��
	{
		OLED_Clear();
		while(1)
		{
			if(flag_ccd_10ms == 1)
			{
				flag_ccd_10ms = 0;
				ccd_collect();//ccd1�ɼ�
				ccd2_collect();//ccd2�ɼ�
				CCDImage_process();//ͼ����
				oled_collect();//128��ת��Ϊ��λƽ��
				oled_show();//oled��ʾ
			}
		}
	}
		

	return 0;
}
void assert_failed(uint8_t* file, uint32_t line)
{
	//����ʧ�ܼ��
	UART_printf("assert_failed:line:%d %s\r\n",line,file);
	while(1);
}

