/*
JOGO DA MEMORIA - COM ARDUINO E SERIAL
Arnaldo Viana @2021
inspirado em: http://jeknowledge.github.io/academy-articles/jogo-da-memoria
*/

String recebido;
String sequenciaNumerica = "";
int led;
long numeroGerado;
char stateGame = 0;
int sequencia;
const int botao = 12; //define o apelido botao para o valor 5
const int botaoY = 2;
const int botaoR = 3;
const int botaoG = 4;
const int botaoB = 5;



void setup() {
  // Iniciar comunicacao serie
  Serial.begin(9600);
   pinMode(botao, INPUT_PULLUP);
  // Definir LEDs como OUTPUTs pinos 8,9 e 10
  for(int led = 7; led <= 10; led++){
    pinMode(led, OUTPUT);
  } 
  for(int bot = 2; bot <= 5; bot++){
    pinMode(bot, INPUT_PULLUP);
  } 
  // Definir a seed do gerador de números aleatórios
  randomSeed(analogRead(0));

}
/*
stateGame = 0 -- inicio do jogo
stateGame = 1 -- jogo nivel1
stateGame = 2 -- jogo nivel2
stateGame = 3 -- fim de jogo "Game over"
stateGame = 4 -- jogar novamente?
*/
void loop() {
  switch (stateGame) {
    case 0:
      // inicio de jogo
      Serial.println("* INICIO *");
      Serial.println("Comecar? (s/n)");
      leserial(0);
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo começando...");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo não iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 1:
      // Nivel 1 
      Serial.println("* Nivel 1 *");
      geraSequencia(1000, 3); 
      leserial(1);
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Errooooo!!!"); 
        piscaled(300,5);     
      }
      break;
    case 2:
      // Nivel 2 
      Serial.println("* Nivel 2 *");
      geraSequencia(1000, 5); 
      leserial(1);
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Errooooo!!!"); 
        piscaled(300,5);     
      }
      break;
    case 3:
      // Game over!!!
      Serial.println("Game Over"); 
      piscaled(100,5);
      tone(11,2000);
      delay(400);
      noTone(11);
      tone(11,1000);
      delay(800);
      noTone(11);
      tone(11,500);
      delay(1200);
      noTone(11);
      
      stateGame = 4;
      break;
    case 4:
      Serial.println("jogar novamente? (s/n)"); 
      leserial(0);
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
  }
}

void leserial(char started){
 Serial.println("* Insera sua resposta *");
  recebido = "";
  // Aguardar a resposta do usuario
  while (Serial.available() == 0){
    unsigned long tempResp = millis();
    while (millis() - tempResp <= 5000){
      while (started == 0) {
        if (digitalRead(botao) == LOW) {
           recebido = "s";
           started = 1;
           break;
        }
      }
      
      for(int bot = 2; bot <= 5; bot++){
        if (digitalRead(bot) == LOW){
            if (bot == 2) {
              digitalWrite(7, HIGH);
              tone(11,2000);
              delay(500);
              digitalWrite(7, LOW);
              noTone(11);
            } else if (bot == 3){
              digitalWrite(8, HIGH);
              tone(11,3000);
              delay(500);
              digitalWrite(8, LOW);
              noTone(11);
            } else if (bot == 4) {
              digitalWrite(9, HIGH);
              tone(11,4000);
              delay(500);
              digitalWrite(9, LOW);
              noTone(11); 
            } else {
              digitalWrite(10, HIGH);
              tone(11,5000);
              delay(500);
              digitalWrite(10, LOW);
              noTone(11);
            }
            tempResp = millis();
            recebido = recebido + (bot-1);
            delay(300);
        }
      }   
    }
    Serial.print("valor recebido: ");
    Serial.println(recebido);
    break;
  }
 
  // Guardar o valor introduzido pelo utilizador no Serial Monitor numa String user
  if (Serial.available())
  {
    recebido = Serial.readString();
  }

  
}

void piscaled(int tempo, int vezes){
  for(int i = 0;i < vezes; i++){
    for(int led = 7; led <= 10; led++){
      digitalWrite(led, HIGH);
    }
    delay(tempo);
    for(int led = 7; led <= 10; led++){
      digitalWrite(led, LOW);
    }
    delay(tempo);
  }
}

void geraSequencia (int tempo, int sequencia){
  // Criar uma lista de inteiros com o tamanho que e passado como argumento
  int ordemLeds[sequencia];

  // Gerar sequencia aleatoria
  for (int i = 0; i < sequencia; i++){
    numeroGerado = random(1, 5);
    ordemLeds[i] = numeroGerado;
  }

  // Inicialmente, a String sequenciaNumerica é uma String vazia
  sequenciaNumerica = "";

  // Pisca os LEDs na sequencia gerada
  for (int j = 0; j < sequencia; j++){
    led = ordemLeds[j];
    if (led == 1){
      digitalWrite(7, HIGH);
      tone(11,2000);
      delay(tempo);
      digitalWrite(7, LOW);
      noTone(11);
      delay(tempo);
    }else if (led == 2){
      digitalWrite(8, HIGH);
      tone(11,3000);
      delay(tempo);
      digitalWrite(8, LOW);
      noTone(11);
      delay(tempo);
    }else if (led == 3){
      digitalWrite(9, HIGH);
      tone(11,4000);
      delay(tempo);
      digitalWrite(9, LOW);
      noTone(11);
      delay(tempo);
    }else if (led == 4){
      digitalWrite(10, HIGH);
      tone(11,5000);
      delay(tempo);
      digitalWrite(10, LOW);
      noTone(11);
      delay(tempo);
    }
    // Converte a lista numa String   
    sequenciaNumerica = sequenciaNumerica + led;
  }
}
