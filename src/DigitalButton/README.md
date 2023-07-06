| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----





### Classe DigitalButton

A classe _DigitalButton_ tem como objetivo criar uma estrutura de botão utilizando uma GPIO digital, sendo assim, é possível identificar se o objeto instanciado derivado da classe _DigitalButton_ está “pressionado”, “solto” ou “segurando”.

#### Construtor

_**DigitalButton(int pin):**_ Cria o objeto a ser usado como botão digital e atribui a GPIO a ser utilizada.
* pin: GPIO do botão;

_**DigitalButton():**_ Cria o objeto a ser usado como botão digital **sem a atribuição** da GPIO a ser utilizada.


#### Métodos

* _**begin():**_ Inicializar o botão instanciado. Atenção: Para a utilização do "begin()" dessa forma, será necessário a declaração do pino (GPIO) no momento da instanciação do objeto;
* _**begin(int pin):**_ Inicializar o botão instanciado e atribui um pino (GPIO);
* _**setPino(int pin):**_ Atribui qual o pino (GPIO) será utilizada no objeto;
* _**boolean press():**_ Retorna verdadeiro quando estiver **pressionado** o botão digital;
* _**boolean relasse():**_ Retorna verdadeiro quando o botão for **solto**;
* _**boolean hold():**_ Retorna verdadeiro **enquanto o botão estiver pressionado**;


#### Exemplo prático
Esse exemplo mostra como utilizar todos os estágios de um botão:
* Pressionar;
* Soltar;
* Segurar;
Obs.: A GPIO utilizada para fazer a leitura digital, foi a GPIO 12 (_#define PIN_BUTTON 12_).

```C++
#include <ES32Lab.h>
DigitalButton testButton(12);

void setup() {
  Serial.begin(115200);
  testButton.begin();
}
void loop() {
  if(testButton.press()){
    Serial.println("Button - Press");
  }
  if(testButton.release()){
    Serial.println("Button - Release");
  }
  if(testButton.hold()){
    Serial.println("Button - Hold");
  }
  delay(100);
}
```






-----
| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |