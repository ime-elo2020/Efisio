#include "utils/commandline.h"

#include "stm32f4_discovery.h"

extern CommandLine cmdline;



uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];
	static char palavra;



	if(argc==2){

		int numero= atoi((char*)argv8[1]);

		if(numero== atoi((char*)'toggle') ){

			 STM_EVAL_LEDToggle(LED6);

		}


	}

	else {
		size+=sprintf(buffer+size, "Syntax: Comando Invalido\r\n");
	}

	return size;
}


CommandLine cmdline({"led"},
					{cmd_info});
