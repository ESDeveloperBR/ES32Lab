# Classe ES_Buzzer

A classe ES_Buzzer fornece uma interface simples para controlar um circuito de buzzer usando PWM em uma placa ESP32.

## Construtor

### ES_Buzzer(pinBuzzer)

Construtor da classe ES_Buzzer.

- `pinBuzzer` (u_int8_t): O pino no controlador que suporta PWM a ser usado para o circuito do buzzer.

## Métodos

### begin(channel)

Inicializa a instância do ES_Buzzer que será responsável pela reprodução de sons.

- `channel` (u_int8_t): O canal PWM a ser utilizado. Se não especificado, será utilizado o canal PWM 15 como padrão.

### pitch(percentage)

Ajusta a velocidade de reprodução da melodia gerada.

- `percentage` (u_int8_t): O valor em porcentagem para ajustar a velocidade da melodia. Valores abaixo de 100% tornam a melodia mais lenta, enquanto valores acima de 100% a tornam mais rápida.

### end(pause)

Finaliza a melodia e segura a última nota musical por um determinado tempo.

- `pause` (u_int16_t): O tempo em milissegundos para segurar a última nota musical.

### sound(note, duration)

Reproduz uma nota musical com uma duração especificada.

- `note` (int): A nota musical a ser reproduzida.
- `duration` (int): A duração em milissegundos da nota musical escolhida.

### distortion(noteFrom, noteTo)

Aplica um efeito de distorção entre duas notas musicais.

- `noteFrom` (int): A nota musical inicial.
- `noteTo` (int): A nota musical final.

