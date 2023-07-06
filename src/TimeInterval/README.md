| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----






### Classe TimeInterval
A classe _TimeInterval_ tem como objetivo facilitar a utilização dos comandos _”micros()”_ e _“millis()”_, tornando assim mais intuitivo o controle de tempo sem a paralização do programa principal.

#### Métodos
* _**boolean intervalMillis(long millisTime):**_ Retorna “verdadeiro” quando o tempo em milissegundos passado por parâmetro _(millisTime)_ chegar ao final;
* _**resetMillis():**_ Reiniciar o contador de milissegundos associado ao método intervalMillis();
* _**boolean intervalMicros(long microsTime):**_ Retorna “verdadeiro” quando o tempo em microssegundos passado por parâmetro _(microsTime)_ chegar ao final;
* _**void resetMicros():**_ Reiniciar o contador de microssegundos associado ao método _intervalMicros()_;
* _**void stopwatchStartMillis():**_ **Inicializa** um cronômetro em Milissegundos.
* _**long stopwatchStopMillis():**_ **Parar cronômetro** - Retornar o valor obtido em milissegundos.
* _**void stopwatchStartMicros():**_ **Inicializa** um cronômetro em Microssegundos.
* _**long stopwatchStopMicros():**_ **Parar cronômetro** - Retornar o valor obtido em microssegundos.


#### Exemplos práticos

**Exemplo 1:** O exemplos abaixo utiliza a classe "TimeInterval" para gerencia o tempo através do comando "intervalMillis()", não parando o código em execução

```C++
#include <ES32Lab.h>

TimeInterval intervalTest;
void setup() {
  Serial.begin(115200);
}
void loop() {
  /*
    boolean TimeInterval::intervalMillis(long millisTime)
    Returns "true" when the time in milliseconds has elapsed
    - millisTime: Time in milliseconds
  */
  if(intervalTest.intervalMillis(2000)){  // Execute command every 2000 milliseconds
    Serial.println("It's not stopping the main loop.");
  }

}
```

**Exemplo 2:** Utilizar a classe "TimeInterval" para criar um cronometro para identificar quanto tempo leva para executar alguns comandos "Serial.print()".

```C++
#include <ES32Lab.h>

TimeInterval intervalTest;
void setup() {
  Serial.begin(115200);
}
void loop() {
  /*
    void TimeInterval::stopwatchStartMicros()
    Initializes the stopwatch in microseconds
  */
  intervalTest.stopwatchStartMicros();

  Serial.println("*************");
  Serial.println("Hello World");
  Serial.println("*************");

  /*
    long TimeInterval::stopwatchStopMicros()
    Stop stopwatch - Microseconds and return the obtained value  
  */
  long returnStopwatch = intervalTest.stopwatchStopMicros();

  Serial.print("Execution of all previous println commands takes ");
  Serial.print(returnStopwatch);
  Serial.println(" microsconds.");
  Serial.println("");
  delay(5000);
}

```








-----
| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |