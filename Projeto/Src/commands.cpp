#include "commandline.h"

extern CommandLine cmdline;

extern int estado;
extern int speed_saida_0;
extern int speed_saida_1;
extern int speed_usb_0;
extern int speed_usb_1;
extern int desired_speed;
extern int desired_speed0;
extern int desired_speed1;

extern int kp_usb;
extern int ki_usb;
extern int kd_usb;

//arcg==1: enviar pra porta serial os valores atuais de kp ki e kd
//argc==2: se o segundo argumento for M1, enviar pra portal serial a velocidade atual da roda do motor M1, se for M0...
//argc==3: o segundo argumento vai ser "M1" ou "M0" e o terceiro, o valor de velocidade q deve ser enviado pro respectivo motor
//argc==4: os argumentos 2, 3 e 4 devem ser kp ki e kd, respectivamente


uint16_t cmd_info(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];
	static char roda;
	roda= argv8[3][0];

	if(argc==1){// ler os valores das contantes PID

estado=1;


		size+=sprintf(buffer+size,"%d %d %d / %d %d\r\n",kp_usb,ki_usb,kd_usb,speed_usb_0, speed_usb_1); //--Ler as constantes PID
		
	}

	else if(argc==2){//Ler a velocidade de cada motor
			

		size+=sprintf(buffer+size, "%d %d\r\n",  speed_usb_0, speed_usb_1);




		}
	else if(argc==3){// manda velocidade para uma das rodas escolhidas

		desired_speed0 = atoi((char*)argv8[1]);

		desired_speed1 = atoi((char*)argv8[2]);


		size+=sprintf(buffer+size, "%d %d\r\n",  speed_usb_0*10, speed_usb_1*10);



			}

	else if(argc==4){//manda as constantes PID
				
			kp_usb= atoi((char*)argv8[1]);
			ki_usb= atoi((char*)argv8[2]);
			kd_usb= atoi((char*)argv8[3]);

			size+=sprintf(buffer+size, "%d %d\r\n",  speed_usb_0, speed_usb_1);

	}

	else {//error
		size+=sprintf(buffer+size, "Syntax: info\r\n");
	}

	return size;
}


CommandLine cmdline({"[A"},
					{cmd_info});
