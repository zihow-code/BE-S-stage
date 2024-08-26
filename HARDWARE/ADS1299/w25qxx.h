#ifndef _W25QXX_H_
#define _W25QXX_H_

#include "spi.h"
#include "delay.h"
#include "sys.h"

/*�ӿں궨��*/
  #define SPI_CS_HIGH              GPIO_SetBits(GPIOB, SPI_CS)
  #define SPI_CS_LOW               GPIO_ResetBits(GPIOB, SPI_CS)
	//#define ADS_PWDN_G		GPIOA	  //���硢��λ���ƣ��͵�ƽ��Ч
	
	#define ADS_DRDY_G		GPIOD	  //ת�����ָʾ���͵�ƽ��Ч
	#define ADS_SCLK_G		GPIOB	  //SPIͨ��ʱ����
  #define ADS_DIN_G			GPIOB	  //ADS1292������������
	#define ADS_DOUT_G		GPIOB	  //ADS1292�����������
  
	//#define ADS_PWDN	GPIO_Pin_12
	
	#define ADS_DRDY	GPIO_Pin_6  	//PD6
	#define ADS_SCLK	GPIO_Pin_3  	//PB3
	#define ADS_DIN		GPIO_Pin_5
	#define ADS_DOUT	GPIO_Pin_4
	#define SPI_CS     	GPIO_Pin_7    	/*GPIOB.7*/
	#define ADS_START   GPIO_Pin_6  	/*GPIOB.6*/
	#define ADS_RESET_p	GPIO_Pin_8    	/*GPIOB.8*/
	#define ADS_PWDN_H	GPIO_Pin_9
	
	#define ADS_DRDY_H	GPIO_SetBits(ADS_DRDY_G	,	ADS_DRDY)
	#define ADS_SCLK_H	GPIO_SetBits(ADS_SCLK_G	,	ADS_SCLK)
	#define ADS_DIN_H	GPIO_SetBits(ADS_DIN_G	,	ADS_DIN) 
	#define ADS_DOUT_H	GPIO_SetBits(ADS_DOUT_G	,	ADS_DOUT)


/*ADS1292�����*/
	/*ϵͳ����*/
	#define WAKEUP		0X02	//�Ӵ���ģʽ����
	#define STANDBY		0X04	//�������ģʽ
	#define ADS_RESET	0X06	//��λADS1292R
	#define START			0X08	//������ת��
	#define STOP			0X0A	//ֹͣת��
	//#define OFFSETCAL	0X1A	//ͨ��ƫ��У׼
	/*���ݶ�ȡ����*/
	#define RDATAC		0X10	//�������������ݶ�ȡģʽ,Ĭ��ʹ�ô�ģʽ
	#define SDATAC		0X11	//ֹͣ���������ݶ�ȡģʽ
	#define RDATA			0X12	//ͨ�������ȡ����;֧�ֶ��ֶ��ء�
	/*�Ĵ�����ȡ����*/
	#define	RREG			0X20	//��ȡ001r rrrr 000n nnnn  ���ﶨ���ֻ�и߰�λ����8λ�ڷ�������ʱ����
	#define WREG			0X40	//д��010r rrrr 000n nnnn
	/*	r rrrr=Ҫ����д�ļĴ�����ַ
			n nnnn=Ҫ����д������*/
/*ADS1292�ڲ��Ĵ�����ַ����*/
	#define ID			0X00	//ID���ƼĴ���
	#define CONFIG1		0X01	//���üĴ���1
	#define CONFIG2		0X02	//���üĴ���2
	#define CONFIG3 	0X03	//���üĴ���3
	#define LOFF		0X04	//����������ƼĴ���
	#define CH1SET		0X05	//ͨ��1���üĴ���
	#define CH2SET		0X06	//ͨ��2���üĴ���
	#define CH3SET		0X07	//ͨ��3���üĴ���
	#define CH4SET		0X08	//ͨ��4���üĴ���
	#define CH5SET		0X09	//ͨ��5���üĴ���
	#define CH6SET		0X0A	//ͨ��6���üĴ���
	#define CH7SET		0X0B	//ͨ��7���üĴ���
	#define CH8SET		0X0C	//ͨ��8���üĴ���
	#define	BIAS_SENSP	0X0D//
	#define	BIAS_SENSN	0X0E
	#define	LOFF_SENSP	0X0F
	#define	LOFF_SENSN	0X10
	#define	LOFF_FLIP		0X11
	
	#define	LOFF_STATP	0X12
	#define	LOFF_STATN	0X13//����״̬�Ĵ�����ַ��ֻ����
	
	#define	GPIO				0X14	//GPIO���ƼĴ���
	#define	MISC1				0X15
	#define	MISC2				0X16
	#define	CONFIG4			0X17

unsigned char ADS_SPI(unsigned char com);//ͨ��SPI������ADS1292ͨ��
void ADS_REG_W(unsigned char com,unsigned data);//��ADS1292�ڲ��Ĵ������в���
char ADS_REG_R(unsigned char com);
void sendspi(uint8_t b);
void ADS_PowerOnInit(void);//ADS1292�ϵ縴λ
void ADS_Read(uint8_t *data);//��ȡ72λ������
void ADS_Init(void); //��ʼ��ADS1292


#endif
