| [Retornar ao Índece da LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#%C3%ADndice) |
| :------: |

# Classe ES_PCF8574
A classe ES_PCF8574 é responsável pelo controle de um expansor de GPIO baseado no PCF8574. Ela fornece métodos para configurar e controlar os pinos de entrada/saída do expansor.


## Construtor
### ES_PCF8574(uint8_t address)
Cria uma instância da classe ES_PCF8574 com o endereço específico do expansor de GPIO PCF8574.

Parâmetros:

* `address:` O endereço I2C do expansor de GPIO PCF8574.

Exemplo:
```C++
ES_PCF8574 expander(0x38);
```


## Métodos
### void begin()
Inicializa o expansor de GPIO PCF8574. Deve ser chamado no início do programa, antes de utilizar os métodos de controle.

Exemplo:
```C++
expander.begin();
```


### void digitalWrite(uint8_t pin, uint8_t value)
Define o valor lógico `HIGH` ou `LOW` para um pino específico do expansor de GPIO PCF8574.

Parâmetros:

* `pin:` O número do pino a ser controlado.
* `value:` O valor lógico a ser atribuído ao pino (HIGH ou LOW).

Exemplo:
```C++
expander.digitalWrite(EX0, HIGH);
```


### int digitalRead(uint8_t pin)
Realiza a leitura do valor lógico presente em um pino específico do expansor de GPIO PCF8574.

Parâmetros:

* `pin:` O número do pino a ser lido.

Retorno:

* Retorna o valor lógico lido (`HIGH` ou `LOW`).

Exemplo:
```C++
int value = expander.digitalRead(EX0);
```


### boolean btHold(uint8_t pin)

A condição 'true' é retornada enquanto a GPIO da expansão estiver sendo utilizada como entrada de botão e permanecer pressionada, ou seja, mantendo-se em nível lógico alto.

- `pin`: O número da GPIO do botão a ser verificado.

Retorna `true` se o botão estiver sendo pressionado, `false` caso contrário.



### boolean btPress(uint8_t pin)

A condição `true` é retornada no exato momento em que a GPIO da expansão é utilizada como entrada de botão e ocorre a transição do nível lógico de baixo para alto, ou seja, quando o botão é pressionado.

- `pin`: O número da GPIO do botão a ser verificado.

Retorna `true` no exato momento em que o botão é pressionado, ou seja, quando ocorre a transição do nível lógico de baixo para alto. Retorna `false` caso contrário.


### boolean btRelease(uint8_t pin)

A condição `true` é retornada no exato momento em que a GPIO da expansão é utilizada como entrada de botão e ocorre a transição do nível lógico de alto para baixo, ou seja, quando o botão é solto.

- `pin`: O número da GPIO do botão a ser verificado.

Retorna `true` no exato momento em que o botão é solto, ou seja, quando ocorre a transição do nível lógico de alto para baixo. Retorna `false` caso contrário.


## Exemplo Prático
Aqui está um exemplo prático completo que demonstra o uso da classe ES_PCF8574 para controlar dois LEDs intermitentes:

Exemplo:
```C++
#include <Arduino.h>
#include <ES_PCF8574.h>

ES_PCF8574 expander(0x38);

void setup() {
  expander.begin();
  expander.digitalWrite(EX0, LOW);  // Define o pino 0 como LOW
  expander.digitalWrite(EX1, LOW);  // Define o pino 1 como LOW
}

void loop() {
  expander.digitalWrite(EX0, HIGH); // Define o pino 0 como HIGH
  expander.digitalWrite(EX1, LOW);  // Define o pino 1 como LOW
  delay(1000);
  
  expander.digitalWrite(EX0, LOW);  // Define o pino 0 como LOW
  expander.digitalWrite(EX1, HIGH); // Define o pino 1 como HIGH
  delay(1000);
}
```

Neste exemplo, os pinos EX0 e EX1 são configurados como saídas e alternam entre os valores HIGH e LOW a cada 1 segundo, resultando no piscar intermitente de dois LEDs conectados aos respectivos pinos.

| [Retornar ao Índece da LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#%C3%ADndice) |
| :------: |