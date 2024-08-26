#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "usart.h" 
#include "key.h"
#include "w25qxx.h"
#include "usart.h"
#include "NRF24L01.h"

uint8_t DATA_ADS[27];
uint8_t DATA_ADS_OUT[27];
uint32_t DATA_DIV[9];
extern float voltage[8];
float LSB=0.0000004804134368896484375;

//外部中断9_5服务程序
void EXTI9_5_IRQHandler(void)
{
	int i,j=0;
	delay_ms(1);
	if (EXTI_GetFlagStatus(EXTI_Line6)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		delay_ms(50);
		ADS_Read(DATA_ADS);
		
		for(i=1;i<9;i++)
		{
			DATA_DIV[j]=DATA_ADS[i*3]<<16 | DATA_ADS[i*3+1]<<8 | DATA_ADS[i*3+2];
			if (DATA_DIV[j] & 0x00800000) // 检查符号位
			{
				DATA_DIV[j] |= 0xFF000000; // 扩展为32位有符号数
			} 
			voltage[j]=(float)((int)DATA_DIV[j])*LSB;
			j++;
		}
//		for(i=0;i<8;i++)
//		{
			printf("%8d:%f ",i+1,voltage[0]);
//		}
		printf("\n");
	} 
}

//外部中断9_5服务程序
void EXTI4_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(EXTI_Line4)==SET)
	{
		printf("send");
		EXTI_ClearITPendingBit(EXTI_Line4);
	} 
}
	   
//外部中断初始化程序
void EXTIX_Init(void)
{         
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);//PE2 连接到中断线2
	
	/* 配置EXTI_Line6 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断9_5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
}

//外部中断初始化程序
void EXTI2_Init(void)
{         
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource8);//PE2 连接到中断线2
	
	/* 配置EXTI_Line6 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断9_5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
}










