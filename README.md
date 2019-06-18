# Efisio

Descrição: Fazer um programa no PC que adquira a resposta do robô a um degrau enviado como velocidade para uma de suas rodas.

Motivação: Melhorar a movimentação dos robôs do projeto de futebol de robôs Very Small Size (VSS), através do cálculo das constantes PID.   
Função: O programa irá enviar uma velocidade para uma das rodas, através da interface USB. Pela mesma interface, o programa irá receber a
velocidade calculada pelo microcontrolador e irá plotar um gráfico que será a resposta do robô a um degrau. Com essa curva gerada, o 
usuário pode extimar as constantes PID do motor.

Fluxograma da Eletrônica:

<img src="Imagens/Diagrama_Eletronico.PNG" width="500">

Fluxograma:

<img src="Imagens/Fluxograma.PNG" width="500">

No início do programa, os periféricos são configurados e incicializados conforme a seguinte pinagem do stm32 blue pill:


<img src="Imagens/Pinagem.PNG" width="500">

E a configuração de Clock foi feita da seguinte forma:

<img src="Imagens/Clock.PNG" width="500">

Para a interface gráfica, foram pensadas nas seguintes classes:


Diagrama de Classes:

<img src="Imagens/Diagrama_de_Classes1.PNG " width="300">


Esboço da interface: usando a interface gráfica do LabVIEW, foi criado um esboço de como ficará o projeto:


<img src="Imagens/interface_20grafica.jpeg.jpg " width="500">

No programa, a interface irá enviar os dados de constantes PID e velocidade para determinada roda. Com o comando enviado, a placa irá enviar o comando de pwm para o módulo de motor para o motor executar determinada velocidade. O encoder irá medir a velocidade da roda e a placa executará o controle PID com as constantes definidas pelo LabView. O controle PID funciona da seguinte forma:

<img src="Imagens/Diagrama.PNG " width="500">

E o código que executa isso é o seguinte:

                    pwm_m0 = 300.0f*velocidade_des0 + kp*e_m0 + ki*ierror_m0 + kd*derror_m0;

			speed_saida_0 = pwm_m0*1000;

			pwm_m1 = 300.0f*velocidade_des1 + kp*e_m1 + ki*ierror_m1 + kd*derror_m1;

			speed_saida_1 = pwm_m1*1000;

			pwm_m1=-pwm_m1;


O código foi implementado na seguinte interface, mas o teste não foi filmado:

<img src="Imagens/Interface_definitiva.jpeg " width="500">






