#ifndef	__SERVO_H
#define __SERVO_H
#endif

#include "sys.h"

#if 0

#define servo_up_IO   PB5		
#define servo_down_IO PB0			
#endif

#define servo_up_IO   L_PWM			//PB5
#define servo_down_IO M1PWM			//PB0

#define servo_duty_max 		12.6 
#define servo_duty_min		2.6			

#define servo_up_CH   L_PWM_CH
#define servo_down_CH R_PWM_CH

#define servo_TIM    TIM2
#define RCC_APB1Periph_servo_TIM RCC_APB1Periph_TIM2

#define MODE_TRACK 0 
#define MODE_FIND 1

/*定时100ms 10HZ*/
#define servo_arr 	35999			//周期	不分频：0，频率为72M/36000 = 2KHZ
#define servo_psc		999				//分频系数0：0.5ms 1，1ms，1KHZ   99，50ms，20HZ	39，20ms，50HZ 199，10HZ，100ms

void servo_pwm(uint16_t CH,float PWM_Duty);
void servo_TIM_init(uint16_t arr,uint16_t psc);
void servo_find_target(void);
void servo_track_target(void);


