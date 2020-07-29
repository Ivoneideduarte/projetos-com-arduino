#include <LedControl.h>

int DIN = 12;
int CS =  10;
int CLK = 11;

LedControl myMatrix = LedControl(DIN, CLK, CS, 1);

int column = 1, row = random(8) + 1; // decide em que ponto a bola deve iniciar
int directionX = 1, directionY = 1;  // certifica-se de que ela vai primeiro da esquerda para a direita
int paddle1 = A0, paddle1Val;        // pino e valor do potenciômetro
int speed = 300;                     // velocidade
int counter = 0, mult = 10;          // variáveis auxiliares para controle de velocidade
unsigned long delayTime = 500;       // Tempo de espera para os caracteres

byte smile[] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

//Caracteres para o Game Over
byte invaders1a[] =
{
  B00100100,
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100
};

byte invaders1b[] =
{
  B00100100,
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};

void setup()
{
  myMatrix.shutdown(0, false); // habilita o display
  myMatrix.setIntensity(0, 1); // define o brilho dos leds
  myMatrix.clearDisplay(0);    // limpa o display
  randomSeed(analogRead(0));   // cria séries genuinamente aleatórias
} // end setup

void loop()
{
  paddle1Val = analogRead(paddle1);              //lê valor do potenciômetro
  paddle1Val = map(paddle1Val, 200, 1024, 1, 6); //mapeia valor entre 1 e 6

  column += directionX;     //atualiza valor da coluna
  row += directionY;        //atualiza valor da linha

  //verifica se boa atingiu a raquete
  if (column == 6 && directionX == 1 && (paddle1Val == row || paddle1Val + 1 == row
                                         || paddle1Val + 2 == row))
  {
    directionX = -1; //rebate bola
  }

  //verica se bola atingiu paredes: topo, base ou lateral esquerda
  if (column == 0 && directionX == -1 )
  {
    directionX = 1;
  }
  if (row == 7 && directionY == 1 )
  {
    directionY = -1;
  }
  if (row == 0 && directionY == -1 )
  {
    directionY = 1;
  }

  //caso tenha atingido a coluna 7, significa que ultrapassou a raquete
  if (column == 7)
  {
    gameOver();  //chama a função gameOver, para finalizar o jogo
  }

  myMatrix.clearDisplay(0); // limpa a tela para o próximo quadro de animação
  myMatrix.setLed(0, column, row, HIGH);            //desenha bola na linha e coluna atual

  //desenha raquete na coluna 7
  myMatrix.setLed(0, 7, paddle1Val, HIGH);
  myMatrix.setLed(0, 7, paddle1Val + 1, HIGH);
  myMatrix.setLed(0, 7, paddle1Val + 2, HIGH);

  if (!(counter % mult))
  {
    speed -= 5;
    mult * mult;
  }
  delay(speed);
  counter++;
} //end loop

void gameOver()
{
  setSprite(invaders1a); // exibe carinha triste
  delay(1000);
  myMatrix.clearDisplay(0);
  setSprite(invaders1b); // exibe carinha triste
  delay(1000);
  myMatrix.clearDisplay(0);

  newGame();
}

void newGame()
{
  for (byte x = 0; x < 3; x++) 
  {
    myMatrix.clearDisplay(0);
    delay(250);
    for (int y = 0; y < 8; y++) 
    {
      myMatrix.setRow(0, y, 255);
    }
    delay(250);
  } //end for

  setSprite(smile); // exibe carinha com riso
  delay(1000);
  myMatrix.clearDisplay(0);

  counter = 0;  //reinicia todos os valores
  speed = 300;
  column = 1;
  row = random(8) + 1;
} //end newGame

void setSprite(byte sprite[]) 
{
  for (byte r = 0; r < 8; r++) 
  {
    myMatrix.setRow(0, r, sprite[r]);
  }
} // end setSprite
