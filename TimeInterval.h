/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 28/12/2018
  Ultima Alteração: 31/05/2022
  Versão: 0.3.0
  Controla o intervalo de tempo no estilo Thread

  Dica: Há mil microssegundos em um milissegundo e um milhão de microssegundos em um segundo.
*/

#ifndef TimeInterval_H
#define TimeInterval_H

#include <Arduino.h>

// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class TimeInterval{
  private:
    long _temp_Millis_Inicial = millis();
    long _temp_Micros_Inicial = micros();
     
  public:
    // <<<<<<<< Método >>>>>>
    boolean intervalMillis(long millisTime);    // Retorna "true" quando o tempo em milissegundos tiver terminado
    void    updateMillis();                     // Atualizar leitura de milissegundos para a contagem de tempo para o proximo intervalo

    boolean intervalMicros(long microsTime);   // Retorna "true" quando o tempo em microssegundos tiver terminado
    void    atualizarMicros();                  // Atualizar leitura de microssegundos para a contagem de tempo para o proximo intervalo

    void    cronometroInicioMillis();           // Marca o inicio para uma contagem em um cronometroInicioMillis
    long    cronometroFinalMillis();            // Marca o final da marcação de tempo e retorna o valor em millis       

    void    cronometroInicioMicros();           // Marca o inicio para uma contagem em um cronometroInicioMicros
    long    cronometroFinalMicros();            // Marca o final da marcação de tempo e retorna o valor em Micros       
};
// <<<<<<<<< Retorna "true" quando o tempo em milissegundos tiver terminado >>>>>>>>>>
/*Returns "true" when the time in milliseconds has elapsed
- millisTime: Time in milliseconds
*/
boolean TimeInterval::intervalMillis(long millisTime){
    long tempMillisAtual = millis();

    if( (tempMillisAtual - _temp_Millis_Inicial) >= millisTime ){
        _temp_Millis_Inicial = millis();
        return true;
    }else{
        return false;
    }
}
// <<<<<< Atualizar leitura de milissegundos para a contagem de tempo para o proximo intervalo >>>>>>>>>>>>>>>>>>>>>>
/* Update millisecond reading for time count for next interval
*/
void TimeInterval::updateMillis(){
    _temp_Millis_Inicial = millis();
}

// <<<<<<<<< Retorna "true" quando o tempo em microssegundos tiver terminado >>>>>>>>>>
/* Returns "true" when the time in microseconds has elapsed
- microsTime: Time in microseconds
*/
boolean TimeInterval::intervalMicros(long microsTime){
    long tempMicrosAtual = micros();

    if( (tempMicrosAtual - _temp_Micros_Inicial) >= microsTime ){
        _temp_Micros_Inicial = micros();
        return true;
    }else{
        return false;
    }
}










// <<<<<< Atualizar leitura de microssegundos para a contagem de tempo para o proximo intervalo >>>>>>>>>>>>>>>>>>>>>>
void TimeInterval::atualizarMicros(){
    _temp_Micros_Inicial = micros();
}
// <<<<<<<<<< Inicializa o cronometro em Millis segundos >>>>>>>>>>>>>>>
void TimeInterval::cronometroInicioMillis(){
    _temp_Millis_Inicial = millis();
}
// <<<<<<<<<<<<<< Finaliza a marcação de tempo do cronometro em Millis >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
long TimeInterval::cronometroFinalMillis(){
    return  millis() - _temp_Millis_Inicial; 
}
// <<<<<<<<<< Inicializa o cronometro em Micros segundos >>>>>>>>>>>>>>>
void TimeInterval::cronometroInicioMicros(){
    _temp_Micros_Inicial = micros();
}
// <<<<<<<<<<<<<< Finaliza a marcação de tempo do cronometro em Millis >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
long TimeInterval::cronometroFinalMicros(){
    return  micros() - _temp_Micros_Inicial; 
}
// <<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>
#endif