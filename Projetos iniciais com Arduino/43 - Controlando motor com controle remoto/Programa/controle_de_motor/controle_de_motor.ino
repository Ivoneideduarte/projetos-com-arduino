#include <IRremote.h> // Inclusão da biblioteca

#define receptor 11
#define mp1 2 // Motor pino 1
#define mp2 4 // Motor pino 2
IRrecv recIR(receptor);
decode_results resultado; // Decodificação do resultado

void setup()
{
  pinMode(mp1, OUTPUT);
  pinMode(mp2, OUTPUT);
  Serial.begin(9600);
  recIR.enableIRIn(); // Inicializar receptor IR
}

void loop()
{
  if (recIR.decode(&resultado))
  { // Verifica se houve envio de um sinal
    Serial.print("Valor: ");
    Serial.println(resultado.value, HEX); // Faz a impressão do valor do sinal recebido em hexadecimal
    
    switch (resultado.value)
    {
      case 0xFD50AF: // Cima  
        frente();
        break;
      case 0xFD10EF: // Baixo
        tras();
        break;
      case 0xFDA05F: // OK - Parar
        parar();
        break;
    }
    recIR.resume(); // Prepara para receber um novo comando
  }
  
}

void parar()
{
  digitalWrite(mp1, LOW);
  digitalWrite(mp2, LOW);
}

void frente()
{
  digitalWrite(mp1, HIGH);
  digitalWrite(mp2, LOW);
}

void tras()
{
  digitalWrite(mp1, LOW);
  digitalWrite(mp2, HIGH);
}
