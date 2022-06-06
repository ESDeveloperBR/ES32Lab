/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 28/12/2018
  Ultima Alteração: 31/05/2022
  Controla o intervalo de tempo no estilo Thread

  Dica: Há mil microssegundos em um milissegundo e um milhão de microssegundos em um segundo.
*/
#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include <Arduino.h>

#define TIMEINTERVAL_VERSION "0.3.6 update 06/06/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class TimeInterval{
  private:
    long _start_Millis = millis();
    long _start_Micros = micros();
     
  public:
    boolean intervalMillis(long millisTime);
    void resetMillis();
    boolean intervalMicros(long microsTime);
    void resetMicros();
    void stopwatchStartMillis();
    long stopwatchStopMillis();
    void stopwatchStartMicros();
    long stopwatchStopMicros();
};

#endif