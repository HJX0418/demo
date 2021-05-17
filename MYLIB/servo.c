#include "servo.h"

/*��������ж�*/
void servo_TIM_init(uint16_t arr,uint16_t psc)
{
	/*��ʱ��4�жϳ�ʼ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_servo_TIM, ENABLE); 

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/*�����ж�*/
	TIM_ITConfig(servo_TIM,TIM_IT_Update,ENABLE);
	
	/*ʱ��ʹ��*/
		
	TIM_TimeBaseStructure.TIM_Period 					= arr;
	TIM_TimeBaseStructure.TIM_Prescaler				=	psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode			= TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(servo_TIM, &TIM_TimeBaseStructure);
	
	TIM_Cmd(servo_TIM, ENABLE); //ʹ�� TIMx ����	
	
}

/*�����г���*/
void servo_find_target(void)
{
	static uint16_t servo_x_turn = Turn_Positive,servo_y_turn = Turn_Positive;
	/*x�����С����ת*/
	if(servo_x_turn)
	{
		if(current_duty_x +0.5 < servo_duty_max)
			current_duty_x += 0.5;
		else if(current_duty_x +0.5 > servo_duty_max)
		{
			current_duty_x += 0;
			current_duty_y  =	servo_duty_max;
			servo_x_turn = Turn_Reverse;
		}
	}
	/*x����Ӵ�Сת*/
	else if(!servo_x_turn)
	{
		if(!servo_x_turn&&current_duty_x -1 > servo_duty_min)
			current_duty_x -= 0.5;
		else if(current_duty_x -1 < servo_duty_min)
		{
			current_duty_x -= 0.5;
			current_duty_y  =	servo_duty_min;
			servo_x_turn = Turn_Positive;
		}
	}
}

/*�������PWM*/
void servo_pwm(uint16_t CH,float PWM_Duty)
{
	switch (CH)
	{
		case servo_down_CH :
			SET_PWM(servo_down_CH,PWM_Duty);
			break;
		
		case servo_up_CH :
			SET_PWM(servo_up_CH,PWM_Duty);
			break;
		
		default :
			break;
	}	

}

void servo_track_target()
{
	int j = 0;
	printf("ok");
	error_flag = 0;
				
	/*���뺯��-----�������洢��error_x��error_y*/
	if(double_data_flag)
	{
		trans_ctof(error);			
		
		/*���׷��*/
		if(current_duty_x+error_x<10&&current_duty_x+error_x>1)
		{
			current_duty_x += error_x;
			current_duty_y += error_y;			
		}
		while(error[j])
		{
			error[j] = '\0';
			j++;
		}
	}
}
