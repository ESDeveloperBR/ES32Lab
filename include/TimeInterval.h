/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 28/12/2018
  Ultima Alteração: 31/05/2022
  Controla o intervalo de tempo no estilo Thread

  Dica: Há mil microssegundos em um milissegundo e um milhão de microssegundos em um segundo.
*/
#ifndef TimeInterval_H
#define TimeInterval_H

#include <Arduino.h>

#define TIMEINTERVAL_VERSION "0.3.2 update date 06/03/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class TimeInterval{
  private:
    long _start_Millis = millis();
    long _start_Micros = micros();
     
  public:
    // <<<<<<<< Método >>>>>>
    boolean intervalMillis(long millisTime);    // Retorna "true" quando o tempo em milissegundos tiver terminado
    void    updateMillis();                     // Atualizar leitura de milissegundos para a contagem de tempo para o proximo intervalo

    boolean intervalMicros(long microsTime);    // Retorna "true" quando o tempo em microssegundos tiver terminado
    void    updadeMicros();                     // Atualizar leitura de microssegundos para a contagem de tempo para o proximo intervalo

    void    stopwatchStartMillis();             // Inicializa o cronômetro em Milissegundos
    long    stopwatchStopMillis();              // Parar cronômetro em Milissegundos e retornar o valor obtido

    void    stopwatchStartMicros();             // Inicializa o cronômetro em Microssegundos
    long    stopwatchStopMicros();              // Parar cronômetro em Microssegundos e retornar o valor obtido
};
#endif