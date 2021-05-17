#ifndef __PWM_H
#define __PWM_H
#endif

#include "stm32f10x.h"

#define MY_ARR 	35999							//周期	不分频：0，频率为72M/36000 = 2KHZ
#define MY_PSC 	39								//分频系数0：0.5ms 1，1ms，1KHZ   99，50ms，20HZ	39，20ms，50HZ

#define PWM_TIM TIM3
#define GPIO_PartialRemap_PWM_TIM   GPIO_PartialRemap_TIM3
#define RCC_APB1Periph_PWM_TIM      RCC_APB1Periph_TIM3
//端口---	通道
// 1	---	4
// 0	---	3
// 5	--- 2
// 4  --- 1
//PB4不行。。。
#define R_PWM  	GPIO_Pin_5			  //UP
#define L_PWM  	GPIO_Pin_0				//DOWN

#define R_PWM_CH   CH2
#define L_PWM_CH   CH3

#define M1A    	GPIO_Pin_13				//PB13   0
#define M1B    	GPIO_Pin_14 			//PB14		1
#define M2A    	GPIO_Pin_15				//PB15   0
#define M2B    	GPIO_Pin_11				//PB11		1

#define CH1 		1
#define CH2   	2
#define CH3 		3
#define CH4   	4

#define Turn_Positive SUCCESS
#define Turn_Reverse	!SUCCESS

void PWM_GPIO_init(void);
void PWM_TIM_init(u16 arr,u16 psc);
int  SET_PWM(uint16_t CH,float PWM_Duty);
	
