// <<<<<<<<< Retorna "true" quando o tempo em milissegundos tiver terminado >>>>>>>>>>
/*Returns "true" when the time in milliseconds has elapsed
- millisTime: Time in milliseconds
*/
boolean TimeInterval::intervalMillis(long millisTime){
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
void TimeInterval::updateMillis(){
    _start_Millis = millis();
}

// <<<<<<<<< Retorna "true" quando o tempo em microssegundos tiver terminado >>>>>>>>>>
/* Returns "true" when the time in microseconds has elapsed
- microsTime: Time in microseconds
*/
boolean TimeInterval::intervalMicros(long microsTime){
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
void TimeInterval::updadeMicros(){
    _start_Micros = micros();
}
// <<<<<<<<<< Inicializa o cronômetro em Milissegundos >>>>>>>>>>>>>>>
/* Initializes the stopwatch in milliseconds
*/
void TimeInterval::stopwatchStartMillis(){
    _start_Millis = millis();
}
// <<<<<<<<<<<<<< Parar cronômetro em Milissegundos e retornar o valor obtido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Stop stopwatch - Milliseconds and return the obtained value
*/
long TimeInterval::stopwatchStopMillis(){
    return  millis() - _start_Millis; 
}
// <<<<<<<<<< Inicializa o cronômetro em Microssegundos >>>>>>>>>>>>>>>
/* Initializes the stopwatch in microseconds
*/
void TimeInterval::stopwatchStartMicros(){
    _start_Micros = micros();
}
// <<<<<<<<<<<<<< Parar cronômetro em Microssegundos e retornar o valor obtido >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Stop stopwatch - Microseconds and return the obtained value
*/
long TimeInterval::stopwatchStopMicros(){
    return  micros() - _start_Micros; 
}
// <<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>