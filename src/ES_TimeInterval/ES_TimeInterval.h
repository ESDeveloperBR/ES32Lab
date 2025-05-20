/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 28/12/2018
  Controla o intervalo de tempo no estilo Thread

  Dica: Há mil microssegundos em um milissegundo e um milhão de microssegundos em um segundo.
*/
#ifndef ES_TIMEINTERVAL_H
#define ES_TIMEINTERVAL_H

#include <Arduino.h>

#define ES_TIMEINTERVAL_VERSION "0.4.0 update 05/20/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class ES_TimeInterval{
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