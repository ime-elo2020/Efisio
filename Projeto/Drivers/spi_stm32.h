#pragma once


//#include <stm32f4xx_spi.h>
#include<stm32f1xx_hal_spi.h>
#include <spi.h>
#include <io_pin.h>

class SPI_STM32: public SPI
{
public:
	SPI_STM32(SPI_HandleTypeDef &spi, IO_Pin &SS_PIN);
	SPI_STM32(const SPI_STM32 &spi_stm32, IO_Pin &SS_PIN);
	uint8_t WriteByte(uint8_t byte);
	uint8_t WriteBuffer(uint8_t *buffer, uint16_t size);
	void Assert();
	void Release();
	uint8_t SelfTest();

protected:
	uint8_t Timeout();
	static const uint32_t SPI_TIMEOUT;
	SPI_HandleTypeDef *_spi;
	IO_Pin *_SS_PIN;
};
