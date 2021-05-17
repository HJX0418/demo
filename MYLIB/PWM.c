#include "PWM.h"

void PWM_GPIO_init()
{
	GPIO_InitTypeDef GPIOB_InitStruct,GPIOB1_InitStruct;

//R_PWM,L_PWM,�˿ڸ��õ�ʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

//TIM3������ӳ�䣬CH1-4��PB4,PB5,PB0,PB1
	GPIO_PinRemapConfig(GPIO_PartialRemap_PWM_TIM, ENABLE);

//����GPIOB�Ķ�ʱ����ӳ��
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

//arr--�Զ���װֵ PSC--ʱ��Ԥ��Ƶ��
void PWM_TIM_init(u16 arr,u16 psc)
{
	
		
	TIM_TimeBaseInitTypeDef PWM_TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef  PWM_TIM_OC3InitStruct,PWM_TIM_OC4InitStruct,PWM_TIM_OC1InitStruct,PWM_TIM_OC2InitStruct;;


	//ʱ��ʹ��,���滹Ҫʹ�ܶ�ʱ����Ԥװ�ؼĴ���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWM_TIM, ENABLE);
	
	//���ö�ʱ��3
	PWM_TIM_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;			 		//����ʱ�ӷ�Ƶ����:0
	PWM_TIM_TimeBaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Up;	 	//������ʽ����������������
	PWM_TIM_TimeBaseInitStruct.TIM_Period 				= arr;									//�Զ����ؼ�������ֵ
	PWM_TIM_TimeBaseInitStruct.TIM_Prescaler			= psc;									//���÷�Ƶϵ��
	
	//(�߼���ʱ��ʹ��)PWM_TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=
	
	TIM_TimeBaseInit(PWM_TIM,&PWM_TIM_TimeBaseInitStruct);

#if	R_PWM_CH == CH1 || L_PWM_CH == CH1

	//��ʼ�� PWM_TIM ͨ��1 PWM ģʽ
	PWM_TIM_OC1InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//���ģʽ2,С�ڼ���ֵʱΪ���ü��Ե��෴��(����Ϊ1��Ϊ0)
	PWM_TIM_OC1InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//����Ϊ��,�ߵ�ƽ��Ч
	PWM_TIM_OC1InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//�Ƚ����ʹ��

	TIM_OC1Init(PWM_TIM, &PWM_TIM_OC1InitStruct);
	TIM_OC1PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH2 || L_PWM_CH == CH2
	
	//��ʼ�� PWM_TIM ͨ��2 PWM ģʽ
	PWM_TIM_OC2InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//���ģʽ2,С�ڼ���ֵʱΪ���ü��Ե��෴��(����Ϊ1��Ϊ0)
	PWM_TIM_OC2InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//����Ϊ��,�ߵ�ƽ��Ч
	PWM_TIM_OC2InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//�Ƚ����ʹ��
	
	TIM_OC2Init(PWM_TIM, &PWM_TIM_OC2InitStruct);
	TIM_OC2PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH3 || L_PWM_CH == CH3
	
	//��ʼ�� PWM_TIM ͨ��3 PWM ģʽ
	PWM_TIM_OC3InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//���ģʽ2,С�ڼ���ֵʱΪ���ü��Ե��෴��(����Ϊ1��Ϊ0)
	PWM_TIM_OC3InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//����Ϊ��,�ߵ�ƽ��Ч
	PWM_TIM_OC3InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//�Ƚ����ʹ��

	TIM_OC3Init(PWM_TIM, &PWM_TIM_OC3InitStruct);
	TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
	
#endif

#if	R_PWM_CH == CH4 || L_PWM_CH == CH4
	
	//��ʼ�� PWM_TIM ͨ��4 PWM ģʽ
	PWM_TIM_OC4InitStruct.TIM_OCMode      = TIM_OCMode_PWM2;   			//���ģʽ2,С�ڼ���ֵʱΪ���ü��Ե��෴��(����Ϊ1��Ϊ0)
	PWM_TIM_OC4InitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;			//����Ϊ��,�ߵ�ƽ��Ч
	PWM_TIM_OC4InitStruct.TIM_OutputState = TIM_OutputState_Enable;	//�Ƚ����ʹ��	

	TIM_OC4Init(PWM_TIM, &PWM_TIM_OC4InitStruct);
	TIM_OC4PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);

#endif	

	//ʹ�ܶ�ʱ��3
	TIM_Cmd(PWM_TIM,ENABLE);
}
 


/*
 Duty������ռ�ձȣ���λΪ�ٷֱ�
*/
int SET_PWM(uint16_t CH,float PWM_Duty)
{
	uint16_t motor_turn;									//motor_turn ��ʾת��,ǰת���ת

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
		//PWM_TIMΪPWM_TIM��������pwm.h���޸�
		case CH1:
			TIM_SetCompare1(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//ͨ��1:PB4			С��arrΪ0�����ֹͣ		100.0�ܹؼ�����
			break;
		
		case CH2:
			TIM_SetCompare2(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//ͨ��2:PB5
			break;
		
		case CH3:
			TIM_SetCompare3(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//ͨ��2:PB5
			break;
		
		case CH4:
			TIM_SetCompare4(PWM_TIM,PWM_Duty/100.0*MY_ARR);			//ͨ��2:PB5
			break;
		default :break;
	}	
			
	return SUCCESS;
}
