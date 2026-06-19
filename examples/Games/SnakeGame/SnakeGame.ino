/**
 * @brief Snake game for ES32Lab using TFT display and analog keyboard.
 * | Jogo da Minhoquinha para ES32Lab usando display TFT e teclado analógico.
 *
 * This example creates a classic Snake-style game, similar to old mobile phones.
 * The snake moves on a grid, eats food, grows, scores points and loses when it
 * touches the wall or itself.
 *
 * | Este exemplo cria um jogo clássico da minhoquinha, parecido com os jogos dos
 * celulares antigos. A minhoquinha anda em uma grade, come a comida, cresce,
 * ganha pontos e perde quando bate na parede ou no próprio corpo.
 *
 * Controls:
 * - KEY_CENTER: start or restart the game
 * - KEY_UP:     move up
 * - KEY_DOWN:   move down
 * - KEY_LEFT:   move left
 * - KEY_RIGHT:  move right
 *
 * | Controles:
 * - KEY_CENTER: inicia ou reinicia o jogo
 * - KEY_UP:     move para cima
 * - KEY_DOWN:   move para baixo
 * - KEY_LEFT:   move para a esquerda
 * - KEY_RIGHT:  move para a direita
 *
 * Display target:
 * - Width:  160 pixels
 * - Height: 128 pixels
 *
 * | Display utilizado:
 * - Largura: 160 pixels
 * - Altura:  128 pixels
 *
 * Important:
 * The game area does not use the whole display height. The top 16 pixels are
 * reserved for the score. The snake moves only below this header area.
 *
 * | Importante:
 * A área do jogo não usa a altura inteira do display. Os 16 pixels superiores
 * ficam reservados para o placar. A minhoquinha se movimenta apenas abaixo
 * dessa faixa.
 *
 * Required libraries:
 * - ES32Lab
 * - TFT_eSPI_ES32Lab
 *
 * | Bibliotecas necessárias:
 * - ES32Lab
 * - TFT_eSPI_ES32Lab
 */

#include <Arduino.h>
#include <ES32Lab.h> // Library ES32Lab | Biblioteca ES32Lab

// <<<<<<<<<<<<<<<<<< OBJECTS | OBJETOS >>>>>>>>>>>>>>>>>>

// Display TFT da ES32Lab.
// Para usar ES_TFT, a biblioteca TFT_eSPI_ES32Lab deve estar instalada.
ES_TFT display;

// Teclado analógico integrado da ES32Lab.
// Ele permite usar as teclas UP, DOWN, LEFT, RIGHT e CENTER.
ES_AnalogKeyboard keyboard(P_KEYBOARD);

// Temporizador usado para controlar a velocidade da minhoquinha sem travar o loop().
ES_TimeInterval intervaloJogo;


// <<<<<<<<<<<<<<<<<< DISPLAY SETTINGS | CONFIGURAÇÕES DO DISPLAY >>>>>>>>>>>>>>>>>>

/**
 * Cada parte da minhoquinha ocupa um quadrado de 8 x 8 pixels.
 *
 * Com display de 160 x 128:
 * - largura: 160 / 8 = 20 colunas
 * - altura útil: (128 - 16) / 8 = 14 linhas
 */
const int TAMANHO_BLOCO = 8;

// Altura reservada para o placar no topo da tela.
const int ALTURA_PLACAR = 16;

// Tamanho máximo reservado para a cobra.
// Para 20 x 14, seriam 280 posições.
// Deixei 400 para ter margem de segurança.
const int TAMANHO_MAXIMO_COBRA = 400;


// <<<<<<<<<<<<<<<<<< GAME VARIABLES | VARIÁVEIS DO JOGO >>>>>>>>>>>>>>>>>>

// Tamanho real do display, lido depois do display.init() e display.setRotation().
int larguraDisplay = 160;
int alturaDisplay = 128;

// Quantidade de colunas e linhas dentro da área útil do jogo.
int colunas = 20;
int linhas = 14;

// Posição inicial da área do jogo.
// O jogo começa abaixo da faixa do placar.
int jogoX = 0;
int jogoY = ALTURA_PLACAR;

// Tamanho da área útil do jogo em pixels.
int jogoLargura = 160;
int jogoAltura = 112;

// Vetores que guardam a posição X e Y de cada pedaço da minhoquinha.
// A cabeça fica sempre na posição 0.
int cobraX[TAMANHO_MAXIMO_COBRA];
int cobraY[TAMANHO_MAXIMO_COBRA];

// Tamanho atual da minhoquinha.
int tamanhoCobra = 3;

// Posição da comida dentro da grade.
int comidaX = 0;
int comidaY = 0;

// Direção atual da minhoquinha.
// Começa andando para a direita.
int direcaoX = 1;
int direcaoY = 0;

// Próxima direção solicitada pelo jogador.
// Usamos isso para evitar viradas erradas entre um passo e outro.
int proximaDirecaoX = 1;
int proximaDirecaoY = 0;

// Pontuação do jogador.
int pontos = 0;

// Velocidade do jogo em milissegundos.
// Quanto menor o valor, mais rápido o jogo fica.
unsigned long velocidadeMs = 190;

// Estados do jogo.
bool jogoRodando = false;
bool gameOver = false;


// <<<<<<<<<<<<<<<<<< DRAW FUNCTIONS | FUNÇÕES DE DESENHO >>>>>>>>>>>>>>>>>>

/**
 * @brief Draws the start screen.
 * | Desenha a tela inicial.
 */
void desenharTelaInicial() {
  display.fillScreen(TFT_BLACK);

  display.setTextSize(2);
  display.setTextColor(TFT_GREEN, TFT_BLACK);
  display.drawCentreScreenString("MINHOQUINHA", 18, 2);

  display.setTextSize(1);
  display.setTextColor(TFT_WHITE, TFT_BLACK);
  display.drawCentreScreenString("CENTER: iniciar", 55, 1);

  display.setTextColor(TFT_CYAN, TFT_BLACK);
  display.drawCentreScreenString("Use as setas", 75, 1);

  display.setTextColor(TFT_YELLOW, TFT_BLACK);
  display.drawCentreScreenString("ES32Lab", 102, 1);
}

/**
 * @brief Draws the game over screen.
 * | Desenha a tela de fim de jogo.
 */
void desenharGameOver() {
  display.fillScreen(TFT_BLACK);

  display.setTextSize(2);
  display.setTextColor(TFT_RED, TFT_BLACK);
  display.drawCentreScreenString("GAME OVER", 25, 2);

  display.setTextSize(1);
  display.setTextColor(TFT_YELLOW, TFT_BLACK);

  String textoPontos = "Pontos: " + String(pontos);
  display.drawCentreScreenString(textoPontos, 62, 1);

  display.setTextColor(TFT_WHITE, TFT_BLACK);
  display.drawCentreScreenString("CENTER: reiniciar", 92, 1);
}

/**
 * @brief Draws the score bar at the top of the display.
 * | Desenha o placar na faixa superior do display.
 */
void desenharPlacar() {
  // Limpa somente a faixa superior, sem apagar o jogo.
  display.fillRect(0, 0, larguraDisplay, ALTURA_PLACAR, TFT_BLACK);

  display.setTextSize(1);
  display.setTextColor(TFT_WHITE, TFT_BLACK);

  String texto = "Pontos: " + String(pontos);
  display.drawString(texto, 4, 4, 1);

  // Linha separando o placar da área do jogo.
  display.drawLine(0, ALTURA_PLACAR - 1, larguraDisplay - 1, ALTURA_PLACAR - 1, TFT_BLUE);
}

/**
 * @brief Draws the border around the game area.
 * | Desenha a borda da área útil do jogo.
 */
void desenharBordaDoJogo() {
  display.drawRect(jogoX, jogoY, jogoLargura, jogoAltura, TFT_BLUE);
}

/**
 * @brief Draws the food.
 * | Desenha a comida da minhoquinha.
 */
void desenharComida() {
  int x = jogoX + comidaX * TAMANHO_BLOCO;
  int y = jogoY + comidaY * TAMANHO_BLOCO;

  display.fillCircle(
    x + TAMANHO_BLOCO / 2,
    y + TAMANHO_BLOCO / 2,
    TAMANHO_BLOCO / 2 - 1,
    TFT_RED
  );
}

/**
 * @brief Draws the whole snake.
 * | Desenha a minhoquinha inteira.
 */
void desenharCobra() {
  for (int i = 0; i < tamanhoCobra; i++) {
    int x = jogoX + cobraX[i] * TAMANHO_BLOCO;
    int y = jogoY + cobraY[i] * TAMANHO_BLOCO;

    if (i == 0) {
      // Cabeça da minhoquinha.
      display.fillRoundRect(x, y, TAMANHO_BLOCO, TAMANHO_BLOCO, 2, TFT_YELLOW);
    } else {
      // Corpo da minhoquinha.
      display.fillRect(x, y, TAMANHO_BLOCO, TAMANHO_BLOCO, TFT_GREEN);
    }
  }
}

/**
 * @brief Draws all game elements.
 * | Desenha todos os elementos do jogo.
 */
void desenharJogoCompleto() {
  display.fillScreen(TFT_BLACK);

  desenharPlacar();
  desenharBordaDoJogo();
  desenharComida();
  desenharCobra();
}


// <<<<<<<<<<<<<<<<<< GAME LOGIC | LÓGICA DO JOGO >>>>>>>>>>>>>>>>>>

/**
 * @brief Checks if a grid position is occupied by the snake.
 * | Verifica se uma posição da grade está ocupada pela minhoquinha.
 *
 * @param x Column in the grid. | Coluna na grade.
 * @param y Row in the grid.    | Linha na grade.
 *
 * @return true if occupied. | true se estiver ocupada.
 */
bool posicaoOcupadaPelaCobra(int x, int y) {
  for (int i = 0; i < tamanhoCobra; i++) {
    if (cobraX[i] == x && cobraY[i] == y) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Creates food in a random empty position.
 * | Cria a comida em uma posição aleatória livre.
 */
void criarComida() {
  bool posicaoValida = false;

  while (!posicaoValida) {
    comidaX = random(0, colunas);
    comidaY = random(0, linhas);

    if (!posicaoOcupadaPelaCobra(comidaX, comidaY)) {
      posicaoValida = true;
    }
  }
}

/**
 * @brief Configures the game area based on the real display size.
 * | Configura a área do jogo com base no tamanho real do display.
 */
void configurarAreaDoJogo() {
  larguraDisplay = display.width();
  alturaDisplay = display.height();

  // A área útil começa logo abaixo do placar.
  jogoX = 0;
  jogoY = ALTURA_PLACAR;

  // Ajusta a largura e altura para múltiplos exatos de TAMANHO_BLOCO.
  // Isso evita que a última linha ou coluna fique cortada.
  colunas = larguraDisplay / TAMANHO_BLOCO;
  linhas = (alturaDisplay - ALTURA_PLACAR) / TAMANHO_BLOCO;

  jogoLargura = colunas * TAMANHO_BLOCO;
  jogoAltura = linhas * TAMANHO_BLOCO;

  // Centraliza a área do jogo se sobrar algum pixel.
  jogoX = (larguraDisplay - jogoLargura) / 2;
  jogoY = ALTURA_PLACAR + ((alturaDisplay - ALTURA_PLACAR - jogoAltura) / 2);

  if (jogoX < 0) jogoX = 0;
  if (jogoY < ALTURA_PLACAR) jogoY = ALTURA_PLACAR;
}

/**
 * @brief Starts or restarts the game.
 * | Inicia ou reinicia o jogo.
 */
void iniciarJogo() {
  pontos = 0;
  velocidadeMs = 190;
  jogoRodando = true;
  gameOver = false;

  // Direção inicial: direita.
  direcaoX = 1;
  direcaoY = 0;
  proximaDirecaoX = 1;
  proximaDirecaoY = 0;

  // Tamanho inicial da minhoquinha.
  tamanhoCobra = 3;

  // Posição inicial próxima ao centro da grade.
  int inicioX = colunas / 2;
  int inicioY = linhas / 2;

  cobraX[0] = inicioX;
  cobraY[0] = inicioY;

  cobraX[1] = inicioX - 1;
  cobraY[1] = inicioY;

  cobraX[2] = inicioX - 2;
  cobraY[2] = inicioY;

  criarComida();
  desenharJogoCompleto();

  // Reinicia o temporizador para o primeiro movimento.
  intervaloJogo.resetMillis();
}

/**
 * @brief Reads the analog keyboard buttons.
 * | Lê os botões do teclado analógico.
 */
void lerControles() {
  /**
   * Regra importante:
   * A minhoquinha não pode inverter diretamente o sentido.
   *
   * Exemplo:
   * Se ela está indo para a direita, não pode ir imediatamente para a esquerda,
   * porque isso faria a cabeça bater no próprio corpo.
   */

  if (keyboard.press(KEY_UP) && direcaoY != 1) {
    proximaDirecaoX = 0;
    proximaDirecaoY = -1;
  }

  if (keyboard.press(KEY_DOWN) && direcaoY != -1) {
    proximaDirecaoX = 0;
    proximaDirecaoY = 1;
  }

  if (keyboard.press(KEY_LEFT) && direcaoX != 1) {
    proximaDirecaoX = -1;
    proximaDirecaoY = 0;
  }

  if (keyboard.press(KEY_RIGHT) && direcaoX != -1) {
    proximaDirecaoX = 1;
    proximaDirecaoY = 0;
  }

  // CENTER inicia ou reinicia o jogo.
  if (keyboard.press(KEY_CENTER)) {
    iniciarJogo();
  }
}

/**
 * @brief Checks collision with the snake body.
 * | Verifica colisão com o próprio corpo da minhoquinha.
 *
 * @param novaCabecaX New head column. | Nova coluna da cabeça.
 * @param novaCabecaY New head row.    | Nova linha da cabeça.
 * @param comeu true if snake is eating food. | true se a minhoquinha está comendo.
 */
bool bateuNoCorpo(int novaCabecaX, int novaCabecaY, bool comeu) {
  /**
   * Detalhe importante:
   * Quando a minhoquinha NÃO come a comida, o último pedaço do rabo vai sair.
   * Por isso, nesse caso, ignoramos o último pedaço na verificação de colisão.
   *
   * Isso evita uma colisão falsa quando a cabeça entra exatamente onde o rabo
   * estava antes de se mover.
   */
  int limite = tamanhoCobra;

  if (!comeu) {
    limite = tamanhoCobra - 1;
  }

  for (int i = 0; i < limite; i++) {
    if (cobraX[i] == novaCabecaX && cobraY[i] == novaCabecaY) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Updates the game state.
 * | Atualiza a lógica do jogo.
 */
void atualizarJogo() {
  // Se o jogo não estiver rodando, não atualiza nada.
  if (!jogoRodando || gameOver) {
    return;
  }

  // Só move a minhoquinha quando o intervalo de tempo for atingido.
  if (!intervaloJogo.intervalMillis(velocidadeMs)) {
    return;
  }

  // Aplica a direção escolhida pelo jogador.
  direcaoX = proximaDirecaoX;
  direcaoY = proximaDirecaoY;

  // Calcula a próxima posição da cabeça.
  int novaCabecaX = cobraX[0] + direcaoX;
  int novaCabecaY = cobraY[0] + direcaoY;

  // Verifica se bateu nas paredes.
  if (novaCabecaX < 0 || novaCabecaX >= colunas || novaCabecaY < 0 || novaCabecaY >= linhas) {
    jogoRodando = false;
    gameOver = true;
    desenharGameOver();
    return;
  }

  // Verifica se encontrou a comida.
  bool comeu = (novaCabecaX == comidaX && novaCabecaY == comidaY);

  // Verifica se bateu no próprio corpo.
  if (bateuNoCorpo(novaCabecaX, novaCabecaY, comeu)) {
    jogoRodando = false;
    gameOver = true;
    desenharGameOver();
    return;
  }

  // Se não comeu, apaga o rabo antigo antes de mover.
  if (!comeu) {
    int raboX = jogoX + cobraX[tamanhoCobra - 1] * TAMANHO_BLOCO;
    int raboY = jogoY + cobraY[tamanhoCobra - 1] * TAMANHO_BLOCO;

    display.fillRect(raboX, raboY, TAMANHO_BLOCO, TAMANHO_BLOCO, TFT_BLACK);
  }

  // Se comeu, aumenta o tamanho da minhoquinha.
  if (comeu && tamanhoCobra < TAMANHO_MAXIMO_COBRA) {
    tamanhoCobra++;
  }

  // Move o corpo: cada pedaço recebe a posição do pedaço anterior.
  for (int i = tamanhoCobra - 1; i > 0; i--) {
    cobraX[i] = cobraX[i - 1];
    cobraY[i] = cobraY[i - 1];
  }

  // Atualiza a cabeça.
  cobraX[0] = novaCabecaX;
  cobraY[0] = novaCabecaY;

  // Se comeu, aumenta pontos, acelera um pouco e cria nova comida.
  if (comeu) {
    pontos++;

    // Acelera aos poucos, mas mantém um limite mínimo para não ficar impossível.
    if (velocidadeMs > 80) {
      velocidadeMs -= 5;
    }

    criarComida();
    desenharPlacar();
    desenharComida();
  }

  // Redesenha a minhoquinha na nova posição.
  desenharCobra();

  // Redesenha a borda para manter a área do jogo bem definida.
  desenharBordaDoJogo();
}


// <<<<<<<<<<<<<<<<<< SETUP | CONFIGURAÇÃO INICIAL >>>>>>>>>>>>>>>>>>

void setup() {
  Serial.begin(115200); // Starts serial communication. | Inicia a comunicação serial.

  display.init(); // Starts the TFT display. | Inicializa o display TFT.

  /**
   * Pela sua montagem anterior, a rotação 3 estava funcionando.
   *
   * Se a imagem ficar de ponta cabeça, troque para:
   *     display.setRotation(1);
   *
   * Se ficar em pé, teste:
   *     display.setRotation(0);
   * ou:
   *     display.setRotation(2);
   */
  display.setRotation(3);

  // Calcula a área do jogo com base na resolução real do display.
  configurarAreaDoJogo();

  // Usa uma leitura analógica para variar a sequência aleatória da comida.
  randomSeed(analogRead(P_POT1));

  desenharTelaInicial();

  Serial.println("Jogo da minhoquinha pronto. | Snake game ready.");
  Serial.println("Pressione CENTER para iniciar. | Press CENTER to start.");
}


// <<<<<<<<<<<<<<<<<< LOOP | REPETIÇÃO PRINCIPAL >>>>>>>>>>>>>>>>>>

void loop() {
  // Lê continuamente os botões do teclado analógico.
  lerControles();

  // Atualiza o jogo quando o intervalo de tempo permitir.
  atualizarJogo();
}