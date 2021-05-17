#include "PWM.h"

void PWM_GPIO_init()
{
	GPIO_InitTypeDef GPIOB_InitStruct,GPIOB1_InitStruct;

//R_PWM,L_PWM,端口复用的时钟树
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

//TIM3部分重映射，CH1-4：PB4,PB5,PB0,PB1
	GPIO_PinRemapConfig(GPIO_PartialRemap_PWM_TIM, ENABLE);

//配置GPIOB的定时器重映射
	GPIOB_InitStruct.GPIO_Pin   = R_PWM|L_PWM;
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	
	GPIO_Init(GPIOB,&GPIOB_InitStruct);

//M1A,M1B,M2A,M2B
	GPIOB1_InitStruct.GPIO_Pin   = M1A|M1B|M2A|M2B;
	GPIOB1_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB1_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;

	
	GPIO_Init(GPIOB,&GPIOB1_InitStruct);
}	

//arr--自动重装值 PSC--时钟预分频数
void PWM_TIM_init(u16 arr,u16 psc)
{
	
		
	TIM_TimeBaseInitTypeDef PWM_TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef  PWM_TIM_OC3InitStruct,PWM_TIM_OC4InitStruct,PWM_TIM_OC1InitStruct,PWM_TIM_OC2InitStruct;;


	//时钟使能,后面还要使能定时器与预装载寄存器
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWM_TIM, ENABLE);
	
	//配置定时器3
	PWM_TIM_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;			 		//设置时钟分频因子:0
	PWM_TIM_TimeBaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Up;	 	//计数方式，常用向上与向下
	PWM_TIM_TimeBaseInitStruct.TIM_Period 				= arr;									//自动重载计数周期值
	PWM_TIM_TimeBaseInitStruct.TIM_Prescaler			= psc;									//设置分频系数
	
	//(高级定时器使用)PWM_TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=
	
	TIM_TimeBaseInit(PWM_TIM,&PWM_TIM_TimeBaseInitStruct);

#if	R_PWM_CH == CH1 || L_PWM_CH == CH1

	//初始化 PWM_TIM 通道1 PWM 模式
	PWM_TIM_OC1InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//输出模式2,小于计数值时为设置极性的相反数(极性为1则为0)
	PWM_TIM_OC1InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//极性为高,高电平有效
	PWM_TIM_OC1InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能

	TIM_OC1Init(PWM_TIM, &PWM_TIM_OC1InitStruct);
	TIM_OC1PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH2 || L_PWM_CH == CH2
	
	//初始化 PWM_TIM 通道2 PWM 模式
	PWM_TIM_OC2InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//输出模式2,小于计数值时为设置极性的相反数(极性为1则为0)
	PWM_TIM_OC2InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//极性为高,高电平有效
	PWM_TIM_OC2InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	
	TIM_OC2Init(PWM_TIM, &PWM_TIM_OC2InitStruct);
	TIM_OC2PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH3 || L_PWM_CH == CH3
	
	//初始化 PWM_TIM 通道3 PWM 模式
	PWM_TIM_OC3InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//输出模式2,小于计数值时为设置极性的相反数(极性为1则为0)
	PWM_TIM_OC3InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//极性为高,高电平有效
	PWM_TIM_OC3InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能

	TIM_OC3Init(PWM_TIM, &PWM_TIM_OC3InitStruct);
	TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH4 || L_PWM_CH == CH4
	
	//初始化 PWM_TIM 通道4 PWM 模式
	PWM_TIM_OC4InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//输出模式2,小于计数值时为设置极性的相反数(极性为1则为0)
	PWM_TIM_OC4InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//极性为高,高电平有效
	PWM_TIM_OC4InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能	

	TIM_OC4Init(PWM_TIM, &PWM_TIM_OC4InitStruct);
	TIM_OC4PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);

#endif	

	//使能定时器3
	TIM_Cmd(PWM_TIM,ENABLE);
}
 


/*
 Duty：配置占空比，单位为百分比
*/
int SET_PWM(uint16_t CH,float PWM_Duty)
{
	uint16_t motor_turn;									//motor_turn 表示转向,前转或后转

	if(PWM_Duty>100|PWM_Duty < -100)
		return ERROR;
	
	if(PWM_Duty < 0)
	{
		motor_turn = Turn_Reverse;
		PWM_Duty   = -PWM_Duty;
	}	
	else 
		motor_turn = Turn_Positive;
	
	switch (CH)
	{
		//PWM_TIM为PWM_TIM，可以在pwm.h中修改
		case CH1:
			TIM_SetCompare1(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//通道1:PB4			小于arr为0，电机停止		100.0很关键！！
			break;
		
		case CH2:
			TIM_SetCompare2(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//通道2:PB5
			break;
		
		case CH3:
			TIM_SetCompare3(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//通道2:PB5
			break;
		
		case CH4:
			TIM_SetCompare4(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//通道2:PB5
			break;
		default :break;
	}	
			
	return SUCCESS;
}
