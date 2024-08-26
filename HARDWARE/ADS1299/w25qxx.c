#include "w25qxx.h"
#include "usart.h"
#include "delay.h"
#include "spi.h"
#include <stdio.h>
#include <string.h>
extern unsigned int rec_gain;

extern uint8_t RDATA_ADS[8][24];

void ADS_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, ADS_START);
	GPIO_SetBits(GPIOB, ADS_RESET_p);
	GPIO_SetBits(GPIOB, ADS_PWDN_H);
	delay_ms(100);
}


/**ADS1299�ϵ縴λ **/
void ADS_PowerOnInit(void)
{	
	uint8_t ch;
	GPIO_ResetBits(GPIOB, ADS_RESET_p);
	delay_ms(10);
	GPIO_SetBits(GPIOB, ADS_RESET_p);
	delay_ms(10);
	
	ADS_SPI(SDATAC);
	delay_ms(1);
	
	/*fc for bias test*/
	ADS_REG_W(CONFIG1,0x96);	//  ��	250Hz 0x96;500hz,0x95
//	ADS_REG_W(CONFIG2,0xD0);//�����ź��ڲ�����
	ADS_REG_W(CONFIG2,0XC0);//�����ⲿ�ź�
	ADS_REG_W(CONFIG3,0XE0);	//ʹ���ڲ��ο���ѹ
	ch=ADS_REG_R(CONFIG3);
	printf("%02x\n",ch);
	delay_ms(10);
	
	ADS_REG_W(CH1SET,0X00);	
	ADS_REG_W(CH2SET,0X00);
	ADS_REG_W(CH3SET,0X00);
	ADS_REG_W(CH4SET,0X00);
	ADS_REG_W(CH6SET,0X00);
	ADS_REG_W(CH6SET,0X00);
	ADS_REG_W(CH7SET,0X00);
	ADS_REG_W(CH8SET,0X00);
	ADS_REG_W(GPIO,0);
	
	ADS_REG_W(CH1SET,0X00);	
	ADS_REG_W(CH2SET,0X00);
	ADS_REG_W(CH3SET,0X00);
	ADS_REG_W(CH4SET,0X00);
	ADS_REG_W(CH6SET,0X00);
	ADS_REG_W(CH6SET,0X00);
	ADS_REG_W(CH7SET,0X00);
	ADS_REG_W(CH8SET,0X00);
	
	GPIO_SetBits(GPIOB, ADS_START);
	delay_ms(10);
	ADS_SPI(RDATAC);
}

/**��ADS1299�ڲ��Ĵ������в��� **/
void ADS_REG_W(unsigned char com,unsigned data)
{
	SPI_CS_LOW;//Low to communicated
	ADS_SPI(WREG|com);
	delay_ms(2);
	ADS_SPI(0);
	delay_ms(2);
	ADS_SPI(data);
	delay_ms(1);
	SPI_CS_HIGH;
}

/**��ADS1299�ڲ��Ĵ������в��� **/
char ADS_REG_R(unsigned char com)
{
	char data_return;
	SPI_CS_LOW;//Low to communicated
	ADS_SPI(RREG|com);
	delay_ms(2);
	ADS_SPI(0X00);
	delay_ms(2);
	data_return=ADS_SPI(0);
	delay_ms(1);
	SPI_CS_HIGH;
	return (data_return);
}

/**ͨ��SPI������ADS1299ͨ��**/
unsigned char ADS_SPI(unsigned char com)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0);//��ⷢ�ͼĴ����Ƿ�Ϊ�գ���һ�����ݷ������
	SPI_I2S_SendData(SPI1, com);//��������      
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == 0);//�����ձ�־�Ƿ�ǿգ��������  
	return (SPI_I2S_ReceiveData(SPI1));	//���ؽ��յ�������
}

	
void ADS_Read(uint8_t *data)
{	
	unsigned char i;
	SPI_CS_LOW;
	for (i=0;i<27;i++)
	{
		*data=ADS_SPI(RDATAC);
		data++;
	}
	SPI_CS_HIGH;
}

