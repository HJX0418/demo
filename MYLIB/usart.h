#ifndef __USART_H
#define __USART_H

#include "sys.h"  

#define UART_CLK_GPIO_PORT RCC_APB2Periph_GPIOA 
#define UART_CLK           RCC_APB2Periph_USART1
#define UART_GPIO_PORT     GPIOA
#define UART_Pin_TX        GPIO_Pin_9
#define UART_Pin_RX        GPIO_Pin_10
#define UART_USER					 USART1
#define UART_BAUDRATE      9600

void MY_USART_Init(void);
void UART_SendByte(USART_TypeDef* USARTx,uint8_t data);
void UART_SendString(USART_TypeDef* USARTx,char* String);

/*翻译函数*/
void trans_ctof(unsigned char *error);
//将字符翻译为float类型的小数

#endif
