#include "usart.h"

//NVIC����
/*sys.c������*/

//��ʼ��:  GPIO + ���� + �ж� 
void MY_USART_Init(void)
{
//PA9 -> TX;PA10 -> RX
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	
	
	//ʹ��GPIOA��USART1ʱ��
	RCC_APB2PeriphClockCmd(UART_CLK_GPIO_PORT | UART_CLK, ENABLE);

	//GPIO��ʼ��
	//PA9 --> TX , �����������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = UART_Pin_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO_PORT,&GPIO_InitStructure);
	
	//PA10 --> RX , ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = UART_Pin_RX;

	GPIO_Init(UART_GPIO_PORT,&GPIO_InitStructure);
	
	//�Դ��ڽ��г�ʼ��
	USART_InitStruct.USART_BaudRate   = UART_BAUDRATE; 								//���ò�����
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������
	USART_InitStruct.USART_Mode 			= USART_Mode_Rx | USART_Mode_Tx;//ģʽ��RX/TX
	USART_InitStruct.USART_Parity 		= USART_Parity_No;							//��żУ��
	USART_InitStruct.USART_StopBits 	= USART_StopBits_1;							//ֹͣλ
	USART_InitStruct.USART_WordLength = 8;														//�ֳ�
	
	USART_Init(UART_USER,&USART_InitStruct);
	
	//ʹ�ܴ���
	USART_Cmd(UART_USER,ENABLE);
	
	//ʹ�ܽ����ж�
	USART_ITConfig(UART_USER,USART_IT_RXNE,ENABLE);	//IT��interrupt����д
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


//----�ַ���ת��Ϊ������---//
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
	
	/*���ַ�������Ϊfloat*/
	error_x  = x_sign*( (float)( (int)( (atof(x_error) + 0.005)*100 ) ) )/100;
	error_y  = y_sign*( (float)( (int)( (atof(y_error) + 0.005)*100 ) ) )/100;
}

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
