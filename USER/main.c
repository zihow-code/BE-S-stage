#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "exti.h"
#include "spi.h"
#include "w25qxx.h"
#include "math.h" 
#include "arm_math.h" 
#include "NRF24L01.h"
#include "adc.h"

float voltage[8];

int main(void)
{ 
	int i;
	uint8_t key,key_val,mode;
	uint16_t t;
	u8 tmp_buf[33]={3,'a','b','c'};
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	delay_init(168);
	KEY_Init();
	SPI1_Init();
	SPI2_Init();
	EXTIX_Init();      
	
 	ADS_Init();
 	ADS_PowerOnInit();
	
	NRF24L01_Init();
	printf("ready\n");
	
	while(NRF24L01_Check())
	{
		printf("ERROR ");
		delay_ms(500);
	}
	printf("NRF24L01 OK\n");
	
	NRF24L01_TX_Mode();
	while (1)
	{
		if(NRF24L01_TxPacket(tmp_buf)==TX_OK)// ·¢ËÍ
		{
			tmp_buf[0]=3;
			tmp_buf[1]='1';
			tmp_buf[2]='2'; 
			tmp_buf[3]='3';
			for(i=1;i<4;i++)
				printf("%c \n",tmp_buf[i]);
		}
		else
		{										   	
			printf("fail");
		}
		delay_ms(500);

//		if(NRF24L01_IRQ==0)	 	// ½ÓÊÕ
//		{		
//			printf("exti success");
//			if(NRF24L01_RxPacket(tmp_buf)==0)
//			{			   
//				for(i=0;i<5;i++)
//				{
//					printf("%c ",tmp_buf[i]);
//				}
//			}
//		}
	}
}

