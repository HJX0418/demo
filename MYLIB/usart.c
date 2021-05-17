#include "usart.h"

//NVIC配置
/*sys.c中配置*/

//初始化:  GPIO + 串口 + 中断 
void MY_USART_Init(void)
{
//PA9 -> TX;PA10 -> RX
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	
	
	//使能GPIOA和USART1时钟
	RCC_APB2PeriphClockCmd(UART_CLK_GPIO_PORT | UART_CLK, ENABLE);

	//GPIO初始化
	//PA9 --> TX , 复用推挽输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = UART_Pin_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO_PORT,&GPIO_InitStructure);
	
	//PA10 --> RX , 浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = UART_Pin_RX;

	GPIO_Init(UART_GPIO_PORT,&GPIO_InitStructure);
	
	//对串口进行初始化
	USART_InitStruct.USART_BaudRate   = UART_BAUDRATE; 								//设置波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件控制流
	USART_InitStruct.USART_Mode 			= USART_Mode_Rx | USART_Mode_Tx;//模式：RX/TX
	USART_InitStruct.USART_Parity 		= USART_Parity_No;							//奇偶校验
	USART_InitStruct.USART_StopBits 	= USART_StopBits_1;							//停止位
	USART_InitStruct.USART_WordLength = 8;														//字长
	
	USART_Init(UART_USER,&USART_InitStruct);
	
	//使能串口
	USART_Cmd(UART_USER,ENABLE);
	
	//使能接收中断
	USART_ITConfig(UART_USER,USART_IT_RXNE,ENABLE);	//IT是interrupt的缩写
}

void UART_SendByte(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx,data);
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_TC));
}

void UART_SendString(USART_TypeDef* USARTx,char* String)
{
	char* str = String;
	while(*str)
	{
		UART_SendByte(USARTx,*(str++));
	}
}


//----字符串转换为浮点型---//
void trans_ctof(unsigned char *str)
{
	unsigned char x_error[10],y_error[10];
	int i = 0, j = 0;
	float x_sign = 1,y_sign = 1,error_x,error_y;
	while(str[i] != '+')
	{
		if(!i&&str[0] == '-')
		{
			i++;
			x_sign = -1;
		}
		x_error[j] = str[i];
		j ++;
		i ++;
	}
	i += 1;
	j =  0;
	while(str[i+j] != '\r' )
	{
		if(str[i] == '-')
		{
			i++;
			y_sign = -1;
		}
		y_error[j] = str[i+j];
		j ++;
	}
	
	/*将字符串翻译为float*/
	error_x  = x_sign*( (float)( (int)( (atof(x_error) + 0.005)*100 ) ) )/100;
	error_y  = y_sign*( (float)( (int)( (atof(y_error) + 0.005)*100 ) ) )/100;
}

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
