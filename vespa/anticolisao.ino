//adiciona a biblioteca de controle de motores ao codigo
#include <RoboCore_Vespa.h>

//declaracao do objeto "motores"
VespaMotors motores;

//declaracao dos pinos do sensor
const int PINO_TRIGGER = 25;
const int PINO_ECHO = 26;
//declaracao da variavel que armazena a distancia do obstaculo
const int DISTANCIA_OBSTACULO = 25;
//declaracao das variaveis que armazenam a velocidade de giro e de reta dos motores do robo
const int VELOCIDADE = 80;
//declaracao da variavel que armazena o tempo de espera entre leituras do sensor
const int ESPERA = 60;
//declaracao da variavel que armazena o tempo que os movimentos de desvio irao durar
const int ESPERA_MOVIMENTO = 250;
//declaracao da variavel que armazena a distancia medida pelo sensor
int distancia;

void setup() {

pinMode(PINO_TRIGGER,OUTPUT); //configuracao do pino trigger como saida
pinMode(PINO_ECHO,INPUT); //configuracao do pino echo como entrada

digitalWrite(PINO_TRIGGER, LOW); //inicia o pino trigger com o nivel logico baixo

}

void loop() {

delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
//armazena a distancia lida pelo sensor a variavel distancia
distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO);

//verifica se a distancia lida pelo sensor e menor ou igual ao valor configurado na variavel "DISTANCIA_OBSTACULO"
if (distancia <= DISTANCIA_OBSTACULO) { //se for verdadeiro

    delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
    distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO); //atualiza a leitura do sensor

    //confirma se a distancia lida pelo sensor e menor ou igual ao valor configurado na variavel "DISTANCIA_OBSTACULO"
    if (distancia <= DISTANCIA_OBSTACULO) {

      motores.stop(); //para os motores do robo
      motores.backward(VELOCIDADE); //recua o robo girando os motores para tras
      delay(ESPERA_MOVIMENTO); //matem o movimento do robo
      motores.stop(); //para os motores do robo

      //verifica se o tempo de execucao do codigo e par ou impar
      if (millis() % 2 == 0) {  //se for par

        motores.turn(VELOCIDADE, -VELOCIDADE); //gira o robo para a direita
        delay(ESPERA_MOVIMENTO); //matem o movimento do robo
        motores.stop(); //para os motores do robo
        distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO); //atualiza a leitura do sensor

        //enquanto a leitura do sensor for menor que o valor da variavel "DISTANCIA_OBSTACULO"
        while (distancia <= DISTANCIA_OBSTACULO) {

          motores.turn(VELOCIDADE, -VELOCIDADE); //mantem o robo girando para a direita
          delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
          distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO); //atualiza a leitura do sensor

        }
      } else { //se o tempo de execucao do codigo for impar

        motores.turn(-VELOCIDADE, VELOCIDADE); //gira o robo para a esquerda
        delay(ESPERA_MOVIMENTO); //matem o movimento do robo
        motores.stop(); //para os motores do robo
        distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO); //atualiza a leitura do sensor

        //enquanto a leitura do sensor for menor que o valor da variavel "DISTANCIA_OBSTACULO"
        while (distancia <= DISTANCIA_OBSTACULO) {

          motores.turn(-VELOCIDADE, VELOCIDADE); //mantem o robo girando para a direita
          delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
          distancia = sensor_ultrassonico(PINO_TRIGGER,PINO_ECHO); //atualiza a leitura do sensor

        }
      }
    }

} else { //caso a distancia do sensor não seja menor que o valor "DISTANCIA_OBSTACULO" na primeira verificacao

    motores.forward(VELOCIDADE); //mantem o robo andando para frente

}
}

//funcao para a leitura do sensor
int sensor_ultrassonico(int pinotrigger,int pinoecho){

//realiza o pulso de 10 microsegundos no trigger do sensor
digitalWrite(pinotrigger,HIGH);
delayMicroseconds(10);
digitalWrite(pinotrigger,LOW);

//mede o pulso em microsegundos retornado para o echo do sensor
//e converte o tempo para distancia divindo por 58
return pulseIn(pinoecho,HIGH)/58;

}
