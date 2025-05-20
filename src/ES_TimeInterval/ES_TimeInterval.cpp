#include "ES_TimeInterval.h"
// <<<<<<<<< Retorna "true" quando o tempo em milissegundos tiver terminado >>>>>>>>>>
/*
Returns “true” when the time in milliseconds passed by parameter (millisTime) reaches the end;
--- (Português BR) ---
Retorna “verdadeiro” quando o tempo em milissegundos passado por parâmetro (millisTime) chegar ao final;
*/
boolean ES_TimeInterval::intervalMillis(long millisTime){
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
void ES_TimeInterval::resetMillis(){
    _start_Millis = millis();
}

// <<<<<<<<< Retorna "true" quando o tempo em microssegundos tiver terminado >>>>>>>>>>
/*
Returns “true” when the time in microseconds passed by parameter (microsTime) reaches the end;
--- (Português BR) ---
Retorna “verdadeiro” quando o tempo em microssegundos passado por parâmetro (microsTime) chegar ao final;
*/
boolean ES_TimeInterval::intervalMicros(long microsTime){
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
void ES_TimeInterval::resetMicros(){
    _start_Micros = micros();
}

// <<<<<<<<<< Inicializa um cronômetro em Milissegundos. >>>>>>>>>>>>>>>
/*
Initializes the stopwatch in milliseconds.
--- (Português BR) ---
Inicializa um cronômetro em Milissegundos.
*/
void ES_TimeInterval::stopwatchStartMillis(){
    _start_Millis = millis();
}

// <<<<<<<<<<<<<< Parar cronômetro - Retornar o valor obtido em milissegundos. >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
Stop stopwatch - Return the obtained value in milliseconds.
--- (Português BR) ---
Parar cronômetro - Retornar o valor obtido em milissegundos.
*/
long ES_TimeInterval::stopwatchStopMillis(){
    return  millis() - _start_Millis; 
}

// <<<<<<<<<< Inicializa um cronômetro em Microssegundos >>>>>>>>>>>>>>>
/* Initializes the stopwatch in microseconds
--- (Português BR) ---
Inicializa um cronômetro em Microssegundos.
*/
void ES_TimeInterval::stopwatchStartMicros(){
    _start_Micros = micros();
}

// <<<<<<<<<<<<<< Parar cronômetro - Retornar o valor obtido em microssegundos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
Stop stopwatch - Return the value obtained in microseconds.
--- (Português BR) ---
Parar cronômetro - Retornar o valor obtido em microssegundos.
*/
long ES_TimeInterval::stopwatchStopMicros(){
    return  micros() - _start_Micros; 
}
// <<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>