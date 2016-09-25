#ifndef __MYDEFINE_H__
#define __MYDEFINE_H__

#include "sys.h"

#define beep     PAout(19)       //����
/****************************/
//ccd1
#define CCD_SI_PORT    PTB
#define CCD_SI_PIN     (5)
#define ccd_SI         PBout(5)

#define CCD_CLK_PORT   PTB
#define CCD_CLK_PIN    (6)
#define ccd_clk        PBout(6)

#define CCD_SWITCH_PORT PTC
#define CCD_SWITCH_PIN  (3)
#define ccdSwitch       PCout(3) 

//ccd2

#define CCD_SI2_PORT   PTB
#define CCD_SI2_PIN    (8)
#define ccd_SI2        PBout(8)

#define CCD_CLK2_PORT  PTB
#define CCD_CLK2_PIN   (9)
#define ccd_clk2       PBout(9)

#define CCD2_SWITCH_PORT PTC
#define CCD2_SWITCH_PIN  (2)
#define ccd2Switch       PCout(2)
/**************************/

#define Key_left_PORT     PTD
#define Key_left_PIN      (11)
#define Key_left          PDin(11)

#define Key_right_PORT    PTD
#define Key_right_PIN     (9)
#define Key_right         PDin(9)

#define Key_up_PORT       PTD
#define Key_up_PIN        (8)
#define Key_up            PDin(8)

#define Key_down_PORT     PTD
#define Key_down_PIN      (10)
#define Key_down          PDin(10)

//#define Key_in_PORT       PTD
//#define Key_in_PIN        (12)
//#define Key_in            PDin(12)

#define Key_1_PORT        PTD
#define Key_1_PIN         (12)
#define Key_1             PDin(12)

/*************/
#define steer_pin         FTM2_CH0_PA10
/****************/
///*�����ֵ ����ֵ*/
#define pwm_steer_min    1195
#define pwm_steer_center 1344
#define pwm_steer_max    1530

////shuaiShuai
//#define pwm_steer_min    1347
//#define pwm_steer_center 1479
//#define pwm_steer_max    1607

/**************/

#define Turn 1
#define Straight 0


#define differentialL 2
#define differentialR 3
#define differentialSmallL 4
#define differentialSmallR 5

extern uint16_t Mode;              //ģʽ
extern uint16_t protect;           //�Ƿ񱣻�
extern uint8_t time_set;           //ʱ���趨
extern uint32_t time;              //ʱ�����
extern uint32_t k;                 //sd����
extern uint8_t Dummy;              //DMA�ɼ���bug
extern uint8_t ccd_show;           //ccd��ʾ����
extern uint8_t flag_longstraight;  //�Ƿ��������


extern uint8_t flag_ccd_10ms;          //�ж�ccd�ɼ���־
extern uint8_t flag_v_20ms;             //�ж��ٶȿ��Ʊ�־2



extern uint8_t P[128];             //ccd�ɼ����ĵ�
extern uint8_t P2[128];            //ccd2�ɼ����ĵ�
extern uint8_t Send_Data[292];     //��������
extern uint8_t oled_data[8][128];  //oled����ʾ�ĵ�
extern uint8_t center;             //����
extern uint8_t value;            //ccd��ֵ
extern uint8_t valueLast;       //��һ����ֵ
extern uint8_t minLast;          //��һ����Сֵ
extern uint8_t max , min ;
extern uint8_t leftLast;        //��һ������
extern uint8_t rightLast;       //��һ������
extern uint8_t s;                  //�������
extern uint8_t saoxian;            //ɨ����ʼ��
extern uint8_t flagCrossEnter;   //ʮ��ģʽ
extern uint8_t flagCrossCenter;   //ʮ�ָ�64��־
extern uint8_t flagCrossClear;    //ʮ�������־
extern uint8_t flagDiu;         //���߱�־
extern uint8_t flagDiu2;        //
extern uint8_t flag_obstruct;      //�ϰ�
extern uint8_t flag_obstruct_cntL; //�ϰ�����
extern uint8_t flag_obstruct_cntR; //�ϰ�����
extern uint16_t straight;          //ֱ���ж���־
extern uint8_t flag_out;           //ȫ������ ����
extern uint8_t element;            //����Ԫ��
extern uint8_t centerRecord[10];  //����ʮ������
extern uint8_t flagCrossRecord;
extern uint8_t average_value[5];
extern uint8_t average_over;
extern uint8_t flagMissRecord;
extern uint8_t lineValueMax;
extern uint8_t lineValueMin;
extern uint8_t endLeftLine;
extern uint8_t endRightLine;
extern uint8_t end;


extern uint8_t center2;             //ccd2������
extern uint8_t value2;              //ccd2��ֵ
extern uint8_t value2_last;         //ccd2��ֵ
extern uint8_t left2_last;          //
extern uint8_t right2_last;         //
extern uint8_t s2;                  //ccd2�������
extern uint8_t flag_miss;           //ccd2���߱��
extern uint8_t flag_miss_record;    //
extern uint8_t flag_cross2;         //ccd2ʮ��
extern uint8_t flag_cross2_deal;    //ccd2ʮ�ִ���
extern uint8_t flag_cross2_record;  //��¼ʮ�ֵ�ת��
extern uint8_t saoxian2;
extern uint8_t max2;
extern uint8_t min2;
extern uint8_t min2_last;           //
extern uint8_t center2_record[10];  //ccd2��ȥʮ��
extern uint8_t flag_black2;
extern uint8_t average_value2[5];
extern uint8_t valueLast2;
extern uint8_t flagBlackCnt;

extern uint8_t center_new;
extern uint8_t center_new_last;
extern uint8_t flag_cross_ture;
extern uint8_t staticS; 
extern uint8_t staticS2;
extern uint8_t averageS[5];
extern uint8_t averageS2[5];
extern uint8_t flagRamp;
extern uint8_t flagObstructAvoid;
extern uint16_t flagRampAvoid;
extern uint8_t turnRecord;
extern uint8_t valueUpdata;
extern uint8_t rampCnt;
extern uint8_t valueAvoid;
extern uint8_t maxRecord;
extern uint8_t max2Record;
extern uint16_t endTime;
extern uint8_t endCnt;
extern uint8_t endLineValue;
extern uint8_t flagObstructL;
extern uint8_t flagObstructR;


extern uint16_t pwm_steer;         //���
extern uint16_t pwm_steer_last;    //��һ�����ռ�ձ�
extern uint16_t pwm_ten;           //ʮ��ռ�ձ�
extern int16_t pwm_left;               //����ռ�ձ�
extern int16_t pwm_right;              //����ռ�ձ�
extern int16_t pwm_left_last;          //��һ����·ռ�ձ�
extern int16_t pwm_right_last;         //��һ����·ռ�ձ�
extern int16_t e2L;                    //�ٶ�ǰ����ƫ��
extern int16_t e1L;                    //�ٶ�ǰһ��ƫ��
extern int16_t e2R;                    //�ٶ�ǰ����ƫ��
extern int16_t e1R;                    //�ٶ�ǰһ��ƫ��
extern uint16_t dmacntl;           //�����ٶ�CNT
extern uint16_t dmacntr;           //�����ٶ�CNT
extern uint16_t cntl[4];           //�Ĵβɼ�
extern uint16_t cntr[4];           //�Ĵβɼ�
extern uint16_t Pv_into;         //�ٶ�P
extern uint16_t Iv_into;         //�ٶ�I
extern uint16_t Pv_straight;     //�ٶ�P
extern uint16_t Iv_straight;     //�ٶ�I
extern uint16_t PvL_turn;         //�ٶ�P
extern uint16_t IvL_turn;         //�ٶ�I
extern uint16_t PvR_turn;         //�ٶ�P
extern uint16_t IvR_turn;         //�ٶ�I
extern uint16_t Dv;                //�ٶ�D
extern uint16_t PtR;               //��תP
extern uint16_t DtR;               //��תD
extern uint16_t PtL;               //��תP
extern uint16_t DtL;               //��תD
extern uint16_t ZD_P;
extern uint16_t ZD_D;
extern uint16_t Pvdif;             //����
extern uint16_t speed_set_l;       //�����趨Ŀ��
extern uint16_t speed_set_r;       //�����趨Ŀ��
extern uint16_t speed_s;           //ֱ���ٶ�
extern uint16_t speed_turn;        //ת���ٶ�
extern uint8_t  flag_differential; //����
extern uint8_t  into;
extern uint8_t  speed_recordL[3];      //
extern uint8_t  speed_recordR[3];      //
extern uint16_t speed_now;
extern uint16_t speedInto;
extern uint16_t pwmSteerObstructL;
extern uint16_t pwmSteerObstructR;
extern uint16_t ZA_changshuL;
extern uint16_t ZA_changshuR;
extern uint8_t flag_into;       //�����
extern uint16_t Pv_slow;
extern uint16_t Iv_slow; 
extern uint8_t flag_pidfenduanL;
extern uint8_t flag_pidfenduanR;
extern uint16_t rampSpeed;
extern uint8_t speedSlowCntL;
extern uint8_t speedSlowCntR;
extern uint16_t PvOutsideWheel;
extern uint16_t IvOutsideWheel;
extern uint8_t beforeRampCnt;
extern uint8_t left,right;
extern uint8_t left2,right2;
extern int8_t kLeft[5];
extern int8_t kRight[5];
extern int8_t kSumLeft;
extern int8_t kSumRight;
extern uint8_t flagObstructL2;
extern uint8_t flagObstructR2;
extern uint8_t isFlagObstruct;
extern uint16_t pwmSteerObstructLeft;
extern uint16_t pwmSteerObstructRight;
extern uint16_t pwmSteerObstructLeft2;
extern uint16_t pwmSteerObstructRight2;
extern uint8_t ccdTemp[5];
extern uint8_t whichCcd;
extern uint8_t ccdNumber;
#endif
