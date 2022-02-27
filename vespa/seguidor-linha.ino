// adiciona a biblioteca de controle de motores ao codigo
#include <RoboCore_Vespa.h>

// declaracao do objeto "motores"
VespaMotors motores;

// declaracao dos pinos conectados aos sensores de linha
const int SENSOR_LINHA_ESQUERDO = 36;
const int SENSOR_LINHA_DIREITO = 39;

// declaracao das variaveis que armazenam as leituras dos sensores
int leitura_esquerdo = 0;
int leitura_direito = 0;

// declaracao da variavel que armazena o valor de corte para as leituras dos sensores
const int LEITURA_LINHA = 3000;
// declaracao da variavel que armazena a velocidade em linha reta do robo
const int VELOCIDADE = 70;
// declaracao da variavel que armazena o valor que sera somado a velocidade de rotacao dos motores
const int VELOCIDADE_SOMA = 30;
// declaracao da variavel que armazena o valor que sera subtraido da valocidade de rotacao dos motores
const int VELOCIDADE_SUBTRACAO = 50;
// declaracao da variavel que armazena o valor maximo de contagem de parada
const int CONTAGEM_MAXIMA = 10000;
// declaracao da variavel do contador para parar o robo caso ele fuja da pista
int contador_parada = 0;

void setup()
{

    // configuracao dos pinos conectados aos sensores como entrada
    pinMode(SENSOR_LINHA_ESQUERDO, INPUT);
    pinMode(SENSOR_LINHA_DIREITO, INPUT);
}

void loop()
{

    // realiza a leitura dos sensores
    leitura_esquerdo = analogRead(SENSOR_LINHA_ESQUERDO);
    leitura_direito = analogRead(SENSOR_LINHA_DIREITO);

    // verifica se ambas as leituras dos sensores sao maiores que o valor de leitura de corte
    // ou seja se os dois sensores estao sobre a linha da pista
    if ((leitura_esquerdo > LEITURA_LINHA) && (leitura_direito > LEITURA_LINHA))
    { // se for verdadeiro
        // movimenta o robo para frente
        motores.forward(VELOCIDADE);
        contador_parada = 0; // zera o contador de parada
    }

    // verifica se ambas as leituras dos sensores sao menores que o valor de leitura de corte
    // ou seja se os dois sensores estao fora da linha da pista
    else if ((leitura_esquerdo < LEITURA_LINHA) && (leitura_direito < LEITURA_LINHA))
    {                      // se for verdadeiro
        contador_parada++; // incrementa o contador de parada
    }

    // verifica se apenas a leitura do sensor da direita e menor que o valor de leitura de corte
    // ou seja se apenas o sensor da direta esta sobre a linha da pista
    else if (leitura_direito > LEITURA_LINHA)
    { // se for verdadeiro
        // gira o robo para a esquerda ajustando a velocidade dos motores
        motores.turn(VELOCIDADE + VELOCIDADE_SOMA, VELOCIDADE - VELOCIDADE_SUBTRACAO);
        contador_parada = 0; // zera o contador de parada
    }

    // verifica se apenas a leitura do sensor da esquerda e menor que o valor de leitura de corte
    // ou seja se apenas o sensor da esquerda esta sobre a linha da pista
    else if (leitura_esquerdo > LEITURA_LINHA)
    {
        // gira o robo para a direita ajustando a velocidade dos motores
        motores.turn(VELOCIDADE - VELOCIDADE_SUBTRACAO, VELOCIDADE + VELOCIDADE_SOMA);
        contador_parada = 0; // zera o contador de parada
    }

    // verifica se o contador de parada e maior ou igual que o valor de contagem maxima
    // ou seja se o robo ficou muito tempo fora da pista
    if (contador_parada >= CONTAGEM_MAXIMA)
    {                                      // se for verdadeiro
        motores.stop();                    // para o robo
        contador_parada = CONTAGEM_MAXIMA; // fixa a contagem de parada
    }

    // realiza um tempo de espera na execucao do codigo
    delay(0); // altere esse valor caso queira diminuir a sensibilidade do robo
}
