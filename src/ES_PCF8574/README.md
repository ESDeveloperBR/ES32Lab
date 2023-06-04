| [Retornar ao Índece da LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#%C3%ADndice) |
| :------: |
-----

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


## Exemplos Práticos
### digitalWrite(uint8_t pin, boolean value)
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


### digitalRead(uint8_t pin)
Aqui está um exemplo prático completo que demonstra o uso da classe ES_PCF8574 para fazer a leitura digital de uma determinada GPIO.

Exemplo:
```C++
#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab
ES_PCF8574 expander(0x38); // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  Serial.begin(115200); // Initializes the serial communication | Inicializa a comunicação serial
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  boolean readExpander; // Variable to store the GPIO read value from the expander | Variável para armazenar o valor lido da GPIO do expansor
  readExpander = expander.digitalRead(EX0); // Reads the GPIO 0 of the ES32Lab expander | Lê a GPIO 0 do expansor ES32Lab
  Serial.println(readExpander); // If the GPIO EX0 of the expander receives a logic high signal, the number 1 will be displayed on the serial terminal | Se a GPIO EX0 do expansor receber um sinal lógico alto, o número 1 será exibido no terminal serial
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
}
```


### Digital Button

Este código utiliza o expansor I2C PCF8574 da ES32Lab para conectar botões às suas GPIOs e ler os estados do botão, como pressionado, segurando e solto.


Exemplo:
```C++
#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

int GPIO_EX = EX4;

void setup() {
  Serial.begin(115200);
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
}

void loop() {
  // ---- Button 0 ----
  if(expander.btPress(EX0)){  // When the button connected to the expansion GPIO is pressed, execute: | Quando o botão conectado à GPIO de expansão for pressionado, execute:
    Serial.println("Button 0 Press");  // Display on the serial monitor. | Exibe no monitor serial.
  }

  if(expander.btHold(EX0)){  // When the button connected to the expansion GPIO is pressed, execute: | Quando o botão conectado à GPIO de expansão estiver pressionado, execute:
    Serial.println("Button 0 Hold");  // Display on the serial monitor. | Exibe no monitor serial.
    delay(500);  // Wait for 500 milliseconds. | Aguarda 500 milissegundos.
  }

  if(expander.btRelease(EX0)){  // When the button connected to the expansion GPIO is released, execute: | Quando o botão conectado à GPIO de expansão for solto, execute:
    Serial.println("Button 0 released");  // Display on the serial monitor. | Exibe no monitor serial.
  }
}
```


-----
| [Retornar ao Índece da LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#%C3%ADndice) |
| :------: |