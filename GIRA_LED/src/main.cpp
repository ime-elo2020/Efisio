#include "stm32f4xx.h"

#include "stm32f4_discovery.h"



volatile int ticks=0;

extern "C" void SysTicks_Handler(){

	ticks++;

}

void delay_ms(int interval){

	int temp=ticks+interval;

	while (ticks<temp);

}



int main(void)

{

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //habilitar o periférico

	GPIO_InitTypeDef LED1,LED2,LED3,LED4;    // inicializar os objetos


	LED1.GPIO_Mode=GPIO_Mode_OUT;    // configurar o 'LED1'

	LED1.GPIO_OType=GPIO_OType_PP;

	LED1.GPIO_PuPd=GPIO_PuPd_NOPULL;

	LED1.GPIO_Speed=GPIO_Speed_2MHz;

	LED2.GPIO_Mode=GPIO_Mode_OUT;    // configurar o 'LED2'

	LED2.GPIO_OType=GPIO_OType_PP;

	LED2.GPIO_PuPd=GPIO_PuPd_NOPULL;

	LED2.GPIO_Speed=GPIO_Speed_2MHz;

	LED3.GPIO_Mode=GPIO_Mode_OUT;    // configurar o 'LED3'

	LED3.GPIO_OType=GPIO_OType_PP;

	LED3.GPIO_PuPd=GPIO_PuPd_NOPULL;

	LED3.GPIO_Speed=GPIO_Speed_2MHz;

	LED4.GPIO_Mode=GPIO_Mode_OUT;    // configurar o 'LED4'

	LED4.GPIO_OType=GPIO_OType_PP;

	LED4.GPIO_PuPd=GPIO_PuPd_NOPULL;

	LED4.GPIO_Speed=GPIO_Speed_2MHz;


	LED1.GPIO_Pin=GPIO_Pin_13;

	LED2.GPIO_Pin=GPIO_Pin_12;

	LED3.GPIO_Pin=GPIO_Pin_15;

	LED4.GPIO_Pin=GPIO_Pin_14;





	GPIO_Init(GPIOD, &LED1);     // inicializar os pinos

	GPIO_Init(GPIOD, &LED2);

	GPIO_Init(GPIOD, &LED3);

	GPIO_Init(GPIOD, &LED4);



	SysTick_Config(168000);





  while (1)

  {
		GPIO_SetBits(GPIOD, GPIO_Pin_13);

		delay_ms(1000);

		GPIO_ResetBits(GPIOD, GPIO_Pin_13);



		GPIO_SetBits(GPIOD, GPIO_Pin_12);

		delay_ms(1000);

		GPIO_ResetBits(GPIOD, GPIO_Pin_12);



		GPIO_SetBits(GPIOD, GPIO_Pin_15);

		delay_ms(1000);

		GPIO_ResetBits(GPIOD, GPIO_Pin_15);



		GPIO_SetBits(GPIOD, GPIO_Pin_14);

		delay_ms(1000);

		GPIO_ResetBits(GPIOD, GPIO_Pin_14);


  }

}


extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){


  return;

}



/*

 * Callback used by stm324xg_eval_audio_codec.c.

 * Refer to stm324xg_eval_audio_codec.h for more info.

 */

extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){


  return -1;

}

