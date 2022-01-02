void setup(){
  // Configura os pinos dos LEDs como saída
  pinMode(11, OUTPUT); // LED verde no pino 11
  pinMode(12, OUTPUT); // LED amarelo no pino 12
  pinMode(13, OUTPUT); // LED vermelho no pino 13
}

void loop(){
  // Sinal aberto: apaga LED vermelho, acende LED verde
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(3000);
  
  // Sinal fechado: apaga LED verde, acende LED amarelo
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delay(2000);
  
  // Sinal fechado: apaga LED amarelo, acende LED vermelho
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(5000);
}