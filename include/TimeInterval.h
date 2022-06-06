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

#define TIMEINTERVAL_VERSION "0.3.5 update 06/06/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class TimeInterval{
  private:
    long _start_Millis = millis();
    long _start_Micros = micros();
     
  public:
    // <<<<<<<<< Retorna "true" quando o tempo em milissegundos tiver terminado >>>>>>>>>>
    /*
    Returns “true” when the time in milliseconds passed by parameter (millisTime) reaches the end;
    --- (Português BR) ---
    Retorna “verdadeiro” quando o tempo em milissegundos passado por parâmetro (millisTime) chegar ao final;
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

    // <<<<<< Reiniciar o contador de milissegundos associado ao método intervalMillis() >>>>>>>>>>>>>>>>>>>>>>
    /* 
    Reset millisecond counter associated with intervalMillis() method.
    --- (Português BR) ---
    Reiniciar o contador de milissegundos associado ao método intervalMillis().
    */
    void resetMillis(){
        _start_Millis = millis();
    }

    // <<<<<<<<< Retorna "true" quando o tempo em microssegundos tiver terminado >>>>>>>>>>
    /*
    Returns “true” when the time in microseconds passed by parameter (microsTime) reaches the end;
    --- (Português BR) ---
    Retorna “verdadeiro” quando o tempo em microssegundos passado por parâmetro (microsTime) chegar ao final;
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

    // <<<<<< Reiniciar o contador de microssegundos associado ao método intervalMicros() >>>>>>>>>>>>>>>>>>>>>>
    /* 
    Reset the microseconds counter associated with the intervalMicros() method.
    --- (Português BR) ---
    Reiniciar o contador de microssegundos associado ao método intervalMicros().
    */
    void resetMicros(){
        _start_Micros = micros();
    }

    // <<<<<<<<<< Inicializa um cronômetro em Milissegundos. >>>>>>>>>>>>>>>
    /*
    Initializes the stopwatch in milliseconds.
    --- (Português BR) ---
    Inicializa um cronômetro em Milissegundos.
    */
    void stopwatchStartMillis(){
        _start_Millis = millis();
    }

    // <<<<<<<<<<<<<< Parar cronômetro - Retornar o valor obtido em milissegundos. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /*
    Stop stopwatch - Return the obtained value in milliseconds.
    --- (Português BR) ---
    Parar cronômetro - Retornar o valor obtido em milissegundos.
    */
    long stopwatchStopMillis(){
        return  millis() - _start_Millis; 
    }

    // <<<<<<<<<< Inicializa um cronômetro em Microssegundos >>>>>>>>>>>>>>>
    /* Initializes the stopwatch in microseconds
    --- (Português BR) ---
    Inicializa um cronômetro em Microssegundos.
    */
    void stopwatchStartMicros(){
        _start_Micros = micros();
    }

    // <<<<<<<<<<<<<< Parar cronômetro - Retornar o valor obtido em microssegundos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /*
    Stop stopwatch - Return the value obtained in microseconds.
    --- (Português BR) ---
    Parar cronômetro - Retornar o valor obtido em microssegundos.
    */
    long stopwatchStopMicros(){
        return  micros() - _start_Micros; 
    }
    // <<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>
};

#endif