#include <Arduino.h>
#include "Elevator_System.h"

const int numLinhas = 4;                      // número de linhas do teclado
const int numColunas = 3;                     // número de colunas do teclado
const int debounce = 20;                      // tempo de pausa
const char teclado[numLinhas][numColunas] = { // definição do teclado
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
const int PinosLINHAS[numLinhas] = {7, 2, 3, 5};                                  // pinos do Arduino que
const int PinosCOLUNAS[numColunas] = {6, 8, 4}; // pinos do Arduino que
const char kNADA = 0;                          

char TeclaPressionada();
//---------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); // inicializa a Serial
  // configura as linhas como entradas com padrão em nível lógico alto
  for (int linha = 0; linha < numLinhas; linha++)
  {
    pinMode(PinosLINHAS[linha], INPUT);
    digitalWrite(PinosLINHAS[linha], HIGH); // habilita pull-up
  }
  // configura as colunas como saídas com padrão em nível lógico alto
  for (int coluna = 0; coluna < numColunas; coluna++)
  {
    pinMode(PinosCOLUNAS[coluna], OUTPUT);
    digitalWrite(PinosCOLUNAS[coluna], HIGH);
  }
  Serial.println("--- pressione uma tecla ---");
  Elevator_System__INITIALISATION();
}
//---------------------------------------------------------------------------------
void loop()
{
  char tecla = TeclaPressionada();

  switch (tecla)
  {
    case '1':
      Elevator_System__ground_floor_call_elevator();
      break;
    
    case '2':
      Elevator_System__intermediary_call_elevator(2, Elevator_System__up);
      break;
    
    case '3':
      Elevator_System__intermediary_call_elevator(3, Elevator_System__up);
      break;

    case '4':
      Elevator_System__intermediary_call_elevator(4, Elevator_System__up);
      break;

    case '5':
      Elevator_System__intermediary_call_elevator(5, Elevator_System__up);
      break;

    case '6':
      Elevator_System__intermediary_call_elevator(6, Elevator_System__up);
      break;

    case '7':
      Elevator_System__intermediary_call_elevator(7, Elevator_System__up);
      break;

    case '8':
      Elevator_System__last_floor_call_elevator();
      break;

    case '9':
      Elevator_System__elevator_operation_open_door();
      break;

    case '*':
      Elevator_System__elevator_operation_close_door();
      break;

    case '#':
      Elevator_System__move();
      break;

  }

  // Print dos estados da veriavel

  if (tecla != kNADA)
  {
    Serial.println("\n\n\n-------------------------------------------------------------------------------------------");
    // Historico
    // print_alarm_door();
    // print_ask_to_repair();
    print_behavior();
    // print_btn_actions();
    // print_btn_special();
    // print_cancel();
    // print_current();
    // print_display_directon();
    // print_display_floor();
    // print_floor_leds();
    // print_people_in_elev();
    // print_ptr_qtd();
    // print_sensors();
    //print_state_blink();
    print_status();
    //print_time();
    Serial.println("\n-------------------------------------------------------------------------------------------");
  }

  
}
// Determina qual tecla foi pressionada
char TeclaPressionada()
{
  char tecla = kNADA; // atribui o valor padrão de retorno (nenhuma tecla

  boolean achou = false; //inicialmente considera que nenhuma tecla foi pressionada
  for (int coluna = 0; coluna < numColunas; coluna++)
  {
    digitalWrite(PinosCOLUNAS[coluna], LOW); // muda o estado do pino
    // varre as linhas procurando por uma tecla pressionada
    for (int linha = 0; linha < numLinhas; linha++)
    {
      // lê linha pela primeira vez
      if (digitalRead(PinosLINHAS[linha]) == LOW)
      {                  // tecla está pressionada
        delay(debounce); // insere pausa para descartar ruídos
      }
      // lê linha pela segunda vez
      if (digitalRead(PinosLINHAS[linha]) == LOW)
      { // tecla continua pressionada,

        while (digitalRead(PinosLINHAS[linha]) != HIGH)
          ; // espera soltar o tecla

        tecla = teclado[linha][coluna]; // determina qual foi a tecla pressionada de

        achou = true; // uma tecla foi pressionada
        break;        // sai da varredura das linhas
      }
    }
    digitalWrite(PinosCOLUNAS[coluna], HIGH); // retorna o pino ao seu estado
    if (achou)
    {
      break;
    }
  }
  return tecla; // retorna a tecla pressionada (kNADA se nenhuma foi encontrada)
}