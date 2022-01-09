int frequencia = 400;

void setup(){
  pinMode(10, OUTPUT); // configura o pino com o buzzer como saída
}

void loop(){
  tone(10, frequencia); // gera frequencia de 2000Hz no buzzer
  delay(400);
  noTone(10); // para frequencia no buzzer
  delay(6000);
}