/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2019-05-15

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;

SPI_InitTypeDef s;

s.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_16;
s.SPI_CPHA=SPI_CPHA_2Edge;
s.SPI_CPOL=SPI_CPOL_High;
s.SPI_DataSize=SPI_DataSize_8b;
s.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
s.SPI_FirstBit=SPI_FirstBit_MSB;
s.SPI_Mode=SPI_Mode_Master;
s.SPI_NSS=SPI_NSS_Soft;
s.SPI_CRCPolynomial=0;

SPI_Init(SPI1,&s);

I2C_DeInit(I2Cx);

I2C_InitTypeDef j;
j.I2C_ClockSpeed=300;
j.I2C_Mode= I2C_Mode_I2C;
j.I2C_DutyCycle=I2C_DutyCycle_16_9;
j.I2C_OwnAddress1=0xA0;
j.I2C_Ack=I2C_Ack_Enable;
j.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;

I2C_Init(I2Cx, &I2C_InitStructure);



RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

USART_InitTypeDef u;

u.USART_BaudRate = 115200;
u.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
u.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
u.USART_Parity=USART_Parity_No;
u.USART_StopBits=USART_StopBits_1;
u.USART_WordLength=USART_WordLength_8b;
USART_Init(USART1,&u);

USART_SendData(USART1, 'a');

GPIO_InitTypeDef g;

RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

g.GPIO_Mode=GPIO_Mode_AF;    // configurar

g.GPIO_OType=GPIO_OType_PP;

g.GPIO_Pin=GPIO_Pin_9;

g.GPIO_PuPd=GPIO_PuPd_NOPULL;

g.GPIO_Speed=GPIO_Speed_50MHz;
  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used.
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;
  */

  /* TODO - Add your application code here */

  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* Turn on LEDs */
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);

  /* Infinite loop */
  while (1)
  {
	i++;
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}