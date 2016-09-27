#include "spiflash.h"
#include "gpio.h"
#include "spi.h"
#include "delay.h"
/***********************************************************************************************
//CH_Kinetis������  V2.3   
//����    :YANDLD 
//E-MAIL  :yandld@126.com
//�޸�����:2013/2/14
//�汾��V2.3
//�Ա���http://upcmcu.taobao.com
//QQ    1453363089
//Copyright(C) YANDLD 2012-2022
//All rights reserved
************************************************************************************************/

/***********************************************************************************************
 ���ܣ�SPI Flash��ʼ��
 �βΣ�0       
 ���أ�1ʧ�� 0 �ɹ�
 ��⣺��ʼ��SPI Flash ��ҪKinetisӲ��SPIģ���֧��
       ��ʹ��Ӳ���Դ���CS�źţ���CS����Ϊ��ͨGPIO �������ģ��CS 
************************************************************************************************/
uint8_t SPI_FLASH_Init(void)
{
	//SPI_Init(SPI_FLASH_PORT,SPI_MASTER,SPI_PCS0,8,SPI_SCK_DIV_16);     //��ʼ��SPIӲ�����нӿ�����
	//GPIO_Init(SPI_FLASH_CS_PORT,SPI_FLASH_CS_PIN,GPIO_Mode_Out_PP,Bit_SET,GPIO_IRQC_DISABLE);
	SPI_FLASH_PowerUp();                                //�����豸
	if(SPI_FLASH_GetCapacity() == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/***********************************************************************************************
 ���ܣ�ʹ��Ӳ��SPI��дһ���ֽ�
 �βΣ�0       
 ���أ�0
 ��⣺��ҪKinetisӲ��SPIģ���֧��
************************************************************************************************/
uint8_t SPI_FLASH_ReadWriteByte(uint8_t dat,uint16_t PCS_State)
{
	return SPI_ReadWriteByte(SPI1_PCS0_PB10,dat,PCS_State);
}
/***********************************************************************************************
 ���ܣ���ȡоƬID
 �βΣ�0       
 ���أ�ID
 ��⣺
************************************************************************************************/
uint16_t SPI_FLASH_ReadID(void)
{
	uint16_t Temp = 0;	  
	/*
	SPI_FLASH_CS=0;				    
	SPI_FLASH_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPI_FLASH_ReadWriteByte(0x00); 	    
	SPI_FLASH_ReadWriteByte(0x00); 	    
	SPI_FLASH_ReadWriteByte(0x00); 	 			   
	Temp|=SPI_FLASH_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI_FLASH_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS=1;		
*/
	SPI_FLASH_CS=0;
	SPI_FLASH_ReadWriteByte(0x90,SPI_PCS_Inactive);
	SPI_FLASH_ReadWriteByte(0x00,SPI_PCS_Inactive);
	SPI_FLASH_ReadWriteByte(0x00,SPI_PCS_Inactive);
	SPI_FLASH_ReadWriteByte(0x00,SPI_PCS_Inactive);
	
	Temp |= SPI_FLASH_ReadWriteByte(0xFF,SPI_PCS_Inactive)<<8;
	
	Temp |= SPI_FLASH_ReadWriteByte(0xFF,SPI_PCS_Asserted);
	SPI_FLASH_CS=1;
	return Temp;
}   	
/***********************************************************************************************
 ���ܣ���ȡSPI_FLASH��״̬�Ĵ���
 �βΣ�0       
 ���أ�״̬�Ĵ���ֵ
 ��⣺
			BIT  7    6   5   4   3   2   1   0
		    	SPR  RV  TB BP2 BP1 BP0 WEL BUSY
				SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
				TB,BP2,BP1,BP0:FLASH����д��������
				WEL:дʹ������
				BUSY:æ���λ(1,æ;0,����)
				Ĭ��:0x00
************************************************************************************************/
uint8_t SPI_FLASH_ReadSR(void)   
{  
	uint8_t byte=0;   
	SPI_FLASH_CS=0;
	SPI_FLASH_ReadWriteByte(W25X_ReadStatusReg,SPI_PCS_Inactive);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI_FLASH_ReadWriteByte(0XFF,SPI_PCS_Asserted);             //��ȡһ���ֽ�   
	SPI_FLASH_CS=1;
	return byte;   
} 
/***********************************************************************************************
 ���ܣ�дSPI_FLASH״̬�Ĵ���
 �βΣ�д��ֵ   
 ���أ�0
 ��⣺ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
************************************************************************************************/
void SPI_FLASH_WriteSR(uint8_t sr)   
{   
	SPI_FLASH_CS=0;
	SPI_FLASH_ReadWriteByte(W25X_WriteStatusReg,SPI_PCS_Inactive);   //����дȡ״̬�Ĵ�������    
	SPI_FLASH_ReadWriteByte(sr,SPI_PCS_Asserted);               //д��һ���ֽ�   
	SPI_FLASH_CS=1;	
}   
/***********************************************************************************************
 ���ܣ��ȴ�SPIFLASHæ
 �βΣ�0
 ���أ�0
 ��⣺��SPIFLASH����ʱ����������ȴ�SPIFLASH������ɺ󣬲��ܷ����µ�����
************************************************************************************************/
void SPI_FLASH_WaitBusy(void)   
{   
	while((SPI_FLASH_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
/***********************************************************************************************
 ���ܣ�дʹ��
 �βΣ�0
 ���أ�0
 ��⣺
************************************************************************************************/
void SPI_FLASH_WriteEnable(void)   
{
	SPI_FLASH_CS=0;                            //ʹ������   
  SPI_FLASH_ReadWriteByte(W25X_WriteEnable,SPI_PCS_Asserted);      //����дʹ��  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
} 
/***********************************************************************************************
 ���ܣ�д��ֹ
 �βΣ�0
 ���أ�0
 ��⣺
************************************************************************************************/
void SPI_FLASH_WriteDisable(void)   
{  
	SPI_FLASH_CS=0;                            //ʹ������   
  SPI_FLASH_ReadWriteByte(W25X_WriteDisable,SPI_PCS_Asserted);     //����д��ָֹ��    
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
} 		
/***********************************************************************************************
 ���ܣ���ȡSPI FLASH  
 �βΣ�pBuffer:���ݴ洢��
			 ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
	     NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
 ���أ�0
 ��⣺��ָ����ַ��ʼ��ȡָ�����ȵ�����
************************************************************************************************/
void SPI_FLASH_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	uint16_t i;   										    
	SPI_FLASH_CS=0;                            //ʹ������   
    SPI_FLASH_ReadWriteByte(W25X_ReadData,SPI_PCS_Inactive);         //���Ͷ�ȡ����   
    SPI_FLASH_ReadWriteByte((uint8_t)((ReadAddr)>>16),SPI_PCS_Inactive);  //����24bit��ַ    
    SPI_FLASH_ReadWriteByte((uint8_t)((ReadAddr)>>8),SPI_PCS_Inactive);   
    SPI_FLASH_ReadWriteByte((uint8_t)ReadAddr,SPI_PCS_Inactive);   
    for(i=0;i<NumByteToRead-1;i++)
	  { 
        pBuffer[i]=SPI_FLASH_ReadWriteByte(0XFF,SPI_PCS_Inactive);   //ѭ������  
    }
		SPI_FLASH_ReadWriteByte(pBuffer[NumByteToRead],SPI_PCS_Asserted);
	SPI_FLASH_CS=1;  				    	      
}  
/***********************************************************************************************
 ���ܣ�д1ҳ��SPIFLASH
 �βΣ�pBuffer:���ݴ洢��
			 ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
	     NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
 ���أ�0
 ��⣺NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	
			 1��PAGE(��Сд��λ)256Byte, 16��PAGE���1��Sector(��С������λ)
************************************************************************************************/
void SPI_FLASH_WritePage(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
 	uint16_t i;  
    SPI_FLASH_WriteEnable();                  //SET WEL 
	SPI_FLASH_CS=0;                            //ʹ������   
    SPI_FLASH_ReadWriteByte(W25X_PageProgram,SPI_PCS_Inactive);      //����дҳ����   
    SPI_FLASH_ReadWriteByte((uint8_t)((WriteAddr)>>16),SPI_PCS_Inactive); //����24bit��ַ    
    SPI_FLASH_ReadWriteByte((uint8_t)((WriteAddr)>>8),SPI_PCS_Inactive);   
    SPI_FLASH_ReadWriteByte((uint8_t)WriteAddr,SPI_PCS_Inactive);   
    for(i=0;i<NumByteToWrite-1;i++)SPI_FLASH_ReadWriteByte(pBuffer[i],SPI_PCS_Inactive);//ѭ��д��  
	  SPI_FLASH_ReadWriteByte(pBuffer[NumByteToWrite],SPI_PCS_Asserted);
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ 
	SPI_FLASH_WaitBusy();					   //�ȴ�д�����
} 
/***********************************************************************************************
 ���ܣ�����һ������
 �βΣ�Dst_Addr:������  ���ǵ�ַ �ǵ�ַ/4096
 ���أ�0
 ��⣺����һ������������ʱ��:150ms
************************************************************************************************/
void SPI_FLASH_EraseSector(uint32_t Dst_Addr)   
{  
	Dst_Addr*=4096;
	SPI_FLASH_WriteEnable();                  //SET WEL 	 
	SPI_FLASH_WaitBusy();   
	SPI_FLASH_CS=0;                            //ʹ������   
	SPI_FLASH_ReadWriteByte(W25X_SectorErase,SPI_PCS_Inactive);      //������������ָ�� 
	SPI_FLASH_ReadWriteByte((uint8_t)((Dst_Addr)>>16),SPI_PCS_Inactive);  //����24bit��ַ    
	SPI_FLASH_ReadWriteByte((uint8_t)((Dst_Addr)>>8),SPI_PCS_Inactive);   
	SPI_FLASH_ReadWriteByte((uint8_t)Dst_Addr,SPI_PCS_Asserted);  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
	SPI_FLASH_WaitBusy();   				   //�ȴ��������
}  
/***********************************************************************************************
 ���ܣ��޼���дSPI FLASH 
 �βΣ�pBuffer         : ���ݴ洢��
			 WriteAddr       : ��ʼд��ĵ�ַ(24bit)
	     NumByteToWrite  :Ҫд����ֽ���(���65535)
 ���أ�0
 ��⣺����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
			 �����Զ���ҳ���� 
			 ��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
************************************************************************************************/
void SPI_FLASH_WriteNoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		SPI_FLASH_WritePage(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 
/***********************************************************************************************
 ���ܣ�дSPIFlash(�û��ӿ�)
 �βΣ�pBuffer         : ���ݴ洢��
			 WriteAddr       : ��ʼд��ĵ�ַ(24bit)
	     NumByteToWrite  :Ҫд����ֽ���(���65535)
 ���أ�0
 ��⣺//�ú�������������!
************************************************************************************************/
uint8_t SPI_FLASH_BUFFER[4096];		 
void SPI_FLASH_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t * SPI_FLASH_BUF;	  
	SPI_FLASH_BUF=SPI_FLASH_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   

 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		SPI_FLASH_Read(SPI_FLASH_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			SPI_FLASH_EraseSector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����ԭ��������
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			SPI_FLASH_WriteNoCheck(SPI_FLASH_BUF,secpos*4096,4096);//д����������  
		}else SPI_FLASH_WriteNoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	}	 
}
/***********************************************************************************************
 ���ܣ���������ģʽ
 �βΣ�0
 ���أ�0
 ��⣺
************************************************************************************************/
void SPI_FLASH_PowerDown(void)   
{ 
	SPI_FLASH_CS=0;                            //ʹ������   
	SPI_FLASH_ReadWriteByte(W25X_PowerDown,SPI_PCS_Asserted);        //���͵�������  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
	DelayUs(3);                               //�ȴ�TPD  
}   
/***********************************************************************************************
 ���ܣ��˳�����ģʽ
 �βΣ�0
 ���أ�0
 ��⣺
************************************************************************************************/
void SPI_FLASH_PowerUp(void)   
{  
  SPI_ReadWriteByte(SPI1_PCS0_PB10,W25X_ReleasePowerDown,SPI_PCS_Inactive);
	//SPI_FLASH_CS=0;                            //ʹ������   
	//SPI_FLASH_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	//SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
	DelayUs(3);                               //�ȴ�TRES1
}   
/***********************************************************************************************
 ���ܣ����SPIFlash����
 �βΣ�0
 ���أ���������λΪByte
 ��⣺
************************************************************************************************/
uint32_t SPI_FLASH_GetCapacity(void)
{
	uint16_t id;
	id=SPI_FLASH_ReadID();
	switch (id)
	{
		case W25Q80 : return (1024*1024*1);
		case W25Q16 : return (1024*1024*2);
		case W25Q32 : return (1024*1024*4);
		case W25Q64 : return (1024*1024*8);
		case W25X10 : return (1024*128);
		case W25X20 : return (1024*256);
		case W25X40 : return (1024*512);
		default     : return 0;
	}
}
/***********************************************************************************************
 ���ܣ���������оƬ
 �βΣ�0
 ���أ�0
 ��⣺�ȴ�ʱ�䳬��...
************************************************************************************************/
void SPI_FLASH_EraseChip(void)   
{                                   
	SPI_FLASH_WriteEnable();                  //SET WEL 
	SPI_FLASH_WaitBusy();   
	SPI_FLASH_CS=0;                            //ʹ������   
	SPI_FLASH_ReadWriteByte(W25X_ChipErase,SPI_PCS_Asserted);        //����Ƭ��������  
	SPI_FLASH_CS=1;                            //ȡ��Ƭѡ     	      
	SPI_FLASH_WaitBusy();   				   //�ȴ�оƬ��������	
}   

