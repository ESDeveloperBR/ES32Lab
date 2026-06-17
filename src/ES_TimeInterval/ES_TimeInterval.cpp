#include "ES_TimeInterval.h"

// <<< Checks elapsed time in milliseconds | Verifica tempo decorrido em milissegundos >>>
boolean ES_TimeInterval::intervalMillis(unsigned long millisTime){
    unsigned long tempMillisAtual = millis();
    if( (tempMillisAtual - _start_Millis) >= millisTime ){
        _start_Millis = millis();
        return true;
    }else{
        return false;
    }
}


// <<< Resets the millisecond interval counter | Reinicia o contador de intervalo em milissegundos >>>
void ES_TimeInterval::resetMillis(){
    _start_Millis = millis();
}


// <<< Checks elapsed time in microseconds | Verifica tempo decorrido em microssegundos >>>
boolean ES_TimeInterval::intervalMicros(unsigned long microsTime){
    unsigned long tempMicrosAtual = micros();

    if( (tempMicrosAtual - _start_Micros) >= microsTime ){
        _start_Micros = micros();
        return true;
    }else{
        return false;
    }
}


// <<< Resets the microsecond interval counter | Reinicia o contador de intervalo em microssegundos >>>
void ES_TimeInterval::resetMicros(){
    _start_Micros = micros();
}


// <<< Starts the millisecond stopwatch | Inicia o cronômetro em milissegundos >>>
void ES_TimeInterval::stopwatchStartMillis(){
    _start_Millis = millis();
}


// <<< Stops the millisecond stopwatch | Para o cronômetro em milissegundos >>>
unsigned long ES_TimeInterval::stopwatchStopMillis(){
    return  millis() - _start_Millis; 
}


// <<< Starts the microsecond stopwatch | Inicia o cronômetro em microssegundos >>>
void ES_TimeInterval::stopwatchStartMicros(){
    _start_Micros = micros();
}


// <<< Stops the microsecond stopwatch | Para o cronômetro em microssegundos >>>
unsigned long ES_TimeInterval::stopwatchStopMicros(){
    return  micros() - _start_Micros; 
}
