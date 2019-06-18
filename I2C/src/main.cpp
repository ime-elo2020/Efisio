
/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


#define endereco 0x1C
#define eixoX 0x29
#define eixoY 0x2B




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
void init_i2c(){
    // Initialization struct
    I2C_InitTypeDef i;
    GPIO_InitTypeDef g;

    // Inicializando I2C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    i.I2C_ClockSpeed = 100000;
    i.I2C_Mode = I2C_Mode_I2C;
    i.I2C_DutyCycle = I2C_DutyCycle_2;
    i.I2C_OwnAddress1 = 0x00;
    i.I2C_Ack = I2C_Ack_Disable;
    i.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &i);
    I2C_Cmd(I2C2, ENABLE);

    // Inicilaizando GPIO
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    g.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    g.GPIO_Mode = GPIO_Mode_AF;
    g.GPIO_OType=GPIO_OType_OD;
    g.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &g);
}

void i2c_start()
{
    // Wait until I2C2 is not busy anymore
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

    // Generate start condition
    I2C_GenerateSTART(I2C2, ENABLE);

    // Wait for I2C EV5.
    // It means that the start condition has been correctly released
    // on the I2C bus (the bus is free, no other devices is communicating))
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
}

void i2c_stop()
{
    // Generate I2C stop condition
    I2C_GenerateSTOP(I2C2, ENABLE);
    // Wait until I2C stop condition is finished
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));
}

void i2c_address_direction(uint8_t address, uint8_t direction)
    {
        // Send slave address
        I2C_Send7bitAddress(I2C2, address, direction);

        // Wait for I2C EV6
        // It means that a slave acknowledges his address
        if (direction == I2C_Direction_Transmitter)
        {
            while (!I2C_CheckEvent(I2C2,
                I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
        }
        else if (direction == I2C_Direction_Receiver)
        {
            while (!I2C_CheckEvent(I2C2,
                I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
        }
    }

    void i2c_transmit(uint8_t byte)
    {
        // Send data byte
        I2C_SendData(I2C2, byte);
        // Wait for I2C EV8_2.
        // It means that the data has been physically shifted out and
        // output on the bus)
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    uint8_t i2c_receive_ack()
    {
        // Enable ACK of received data
        I2C_AcknowledgeConfig(I2C2, ENABLE);
        // Wait for I2C EV7
        // It means that the data has been received in I2C data register
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));

        // Read and return data byte from I2C data register
        return I2C_ReceiveData(I2C2);
    }

    uint8_t i2c_receive_nack()
    {
        // Disable ACK of received data
        I2C_AcknowledgeConfig(I2C2, DISABLE);
        // Wait for I2C EV7
        // It means that the data has been received in I2C data register
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));

        // Read and return data byte from I2C data register
        return I2C_ReceiveData(I2C2);
    }

    void i2c_write(uint8_t address, uint8_t data, bool stop_condition = false)
    {
        i2c_start();
        i2c_address_direction(address << 1, I2C_Direction_Transmitter);
        i2c_transmit(data);
        if (stop_condition){
        	i2c_stop();
        }
    }

    void i2c_read(uint8_t address, uint8_t* data)
    {
        i2c_start();
        i2c_address_direction(address << 1, I2C_Direction_Receiver);
        *data = i2c_receive_nack();
        i2c_stop();
    }

int main(void)
{
  uint8_t x_acc;
  uint8_t y_acc;
  init_i2c();
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  while (1){
	  i2c_write(endereco, eixoX);
	  i2c_read(endereco,&x_acc);
	  i2c_write(endereco, eixoY);
	  i2c_read(endereco,&y_acc);
	  // -128(-2g) a 127(2g)
	  if (int8_t(x_acc)>25) {
		  STM_EVAL_LEDOn(LED3);
	  }
	  else {
		  STM_EVAL_LEDOff(LED3);
	  }
	  if (int8_t(y_acc)>25) {
		  STM_EVAL_LEDOn(LED4);
	  }
	  else {
		  STM_EVAL_LEDOff(LED4);
	  }
	  if (int8_t(x_acc)<-25) {
		  STM_EVAL_LEDOn(LED5);
	  }
	  else {
		  STM_EVAL_LEDOff(LED5);
	  }
	  if (int8_t(y_acc)<-25) {
		  STM_EVAL_LEDOn(LED6);
	  }
	  else {
		  STM_EVAL_LEDOff(LED6);
	  }




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
