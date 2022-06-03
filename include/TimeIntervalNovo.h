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

#define TIMEINTERVAL_VERSION "0.3.3 update 06/03/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class TimeInterval{
  private:
    long _start_Millis = millis();
    long _start_Micros = micros();
     
  public:
    // <<<<<<<<< Retorna "true" quando o tempo em milissegundos tiver terminado >>>>>>>>>>
    /*Returns "true" when the time in milliseconds has elapsed
    - millisTime: Time in milliseconds
    */
    boolean intervalMillis(long millisTime){
        long tempMillisAtual = millis();

        if( (tempMillisAtual - _start_Millis) >= millisTime ){
            _start_Millis = millis();
            return true;
        }else{
            return false;
        }
    }

    // <<<<<< Atualizar leitura de milissegundos para a contagem de tempo para o proximo intervalo >>>>>>>>>>>>>>>>>>>>>>
    /* Update millisecond reading for time count for next interval
    */
    void updateMillis(){
        _start_Millis = millis();
    }

    // <<<<<<<<< Retorna "true" quando o tempo em microssegundos tiver terminado >>>>>>>>>>
    /* Returns "true" when the time in microseconds has elapsed
    - microsTime: Time in microseconds
    */
    boolean intervalMicros(long microsTime){
        long tempMicrosAtual = micros();

        if( (tempMicrosAtual - _start_Micros) >= microsTime ){
            _start_Micros = micros();
            return true;
        }else{
            return false;
        }
    }

    // <<<<<< Atualizar leitura de microssegundos para a contagem de tempo para o proximo intervalo >>>>>>>>>>>>>>>>>>>>>>
    /* Update microsecond reading for time count for next interval
    */
    void updadeMicros(){
        _start_Micros = micros();
    }

    // <<<<<<<<<< Inicializa o cronômetro em Milissegundos >>>>>>>>>>>>>>>
    /* Initializes the stopwatch in milliseconds
    */
    void stopwatchStartMillis(){
        _start_Millis = millis();
    }

    // <<<<<<<<<<<<<< Parar cronômetro em Milissegundos e retornar o valor obtido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Stop stopwatch - Milliseconds and return the obtained value
    */
    long stopwatchStopMillis(){
        return  millis() - _start_Millis; 
    }

    // <<<<<<<<<< Inicializa o cronômetro em Microssegundos >>>>>>>>>>>>>>>
    /* Initializes the stopwatch in microseconds
    */
    void stopwatchStartMicros(){
        _start_Micros = micros();
    }

    // <<<<<<<<<<<<<< Parar cronômetro em Microssegundos e retornar o valor obtido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Stop stopwatch - Microseconds and return the obtained value
    */
    long stopwatchStopMicros(){
        return  micros() - _start_Micros; 
    }
    // <<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>
};

#endif