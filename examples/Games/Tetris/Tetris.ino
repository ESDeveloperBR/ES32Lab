/**
 * @brief Tetris for ES32Lab using TFT Display and Analog Keyboard
 * | Tetris para ES32Lab usando Display TFT e Teclado Analógico
 *
 * This example creates a complete Tetris-style game for the ES32Lab board.
 * | Este exemplo cria um jogo estilo Tetris completo para a placa ES32Lab.
 *
 * It uses:
 * | Ele utiliza:
 *
 * - ES_TFT to draw the game on the TFT display.
 *   | ES_TFT para desenhar o jogo no display TFT.
 *
 * - ES_AnalogKeyboard to control the pieces.
 *   | ES_AnalogKeyboard para controlar as peças.
 *
 * - ES_TimeInterval to control timing without delay().
 *   | ES_TimeInterval para controlar o tempo sem usar delay().
 *
 * Controls:
 * | Controles:
 *
 * - LEFT: move the piece left.
 *   | ESQUERDA: move a peça para a esquerda.
 *
 * - RIGHT: move the piece right.
 *   | DIREITA: move a peça para a direita.
 *
 * - DOWN: speed up the falling piece.
 *   | BAIXO: acelera a queda da peça.
 *
 * - UP: rotate the piece.
 *   | CIMA: gira a peça.
 *
 * - CENTER: hard drop.
 *   | CENTRO: queda rápida.
 *
 * - CENTER on Game Over: restart the game.
 *   | CENTRO no Game Over: reinicia o jogo.
 *
 * @warning The TFT_eSPI_ES32Lab library is required to use the ES32Lab TFT display.
 * | A biblioteca TFT_eSPI_ES32Lab é obrigatória para usar o display TFT da ES32Lab.
 *
 * @warning This example was made for the ES32Lab board using the ES32Lab library.
 * | Este exemplo foi feito para a placa ES32Lab usando a biblioteca ES32Lab.
 *
 * @see Official ES32Lab board | Placa oficial ES32Lab:
 * https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h> // ES32Lab library | Biblioteca ES32Lab

ES_TFT display;                         // TFT display object | Objeto do display TFT
ES_AnalogKeyboard keyboard(P_KEYBOARD); // Analog keyboard object | Objeto do teclado analógico
ES_TimeInterval quedaTimer;             // Falling timer object | Objeto temporizador da queda
ES_TimeInterval entradaTimer;           // Input timer object | Objeto temporizador dos comandos

const int TELA_LARGURA = 160; // Display width in pixels | Largura do display em pixels
const int TELA_ALTURA  = 128; // Display height in pixels | Altura do display em pixels

const int COLUNAS = 10; // Board columns | Colunas do tabuleiro
const int LINHAS  = 16; // Board rows | Linhas do tabuleiro

const int TAM_BLOCO = 7; // Block size in pixels | Tamanho do bloco em pixels

const int TAB_X = 4; // Board X position | Posição X do tabuleiro
const int TAB_Y = 8; // Board Y position | Posição Y do tabuleiro

const int PAINEL_X = 82; // Side panel X position | Posição X do painel lateral

byte tabuleiro[LINHAS][COLUNAS];     // Fixed board blocks | Blocos fixos do tabuleiro
byte telaAnterior[LINHAS][COLUNAS];  // Previous screen buffer | Memória da tela anterior

int pontosAnterior = -1;      // Last displayed score | Última pontuação exibida
int nivelAnterior = -1;       // Last displayed level | Último nível exibido
int proximaPecaAnterior = -1; // Last displayed next piece | Última próxima peça exibida

int pecaAtual;     // Current piece index | Índice da peça atual
int rotacaoAtual;  // Current piece rotation | Rotação atual da peça
int pecaX;         // Current piece X position | Posição X da peça atual
int pecaY;         // Current piece Y position | Posição Y da peça atual

int proximaPeca;   // Next piece index | Índice da próxima peça

unsigned long intervaloQueda = 550; // Initial falling interval in ms | Intervalo inicial da queda em ms

int pontos = 0;        // Current score | Pontuação atual
int linhasFeitas = 0; // Cleared lines counter | Contador de linhas removidas
int nivel = 1;        // Current level | Nível atual

bool gameOver = false;              // Game over status | Estado de fim de jogo
bool telaGameOverDesenhada = false; // Game over screen flag | Controle da tela de Game Over

// --- Tetris pieces encoded in 4x4 binary matrices | Peças do Tetris codificadas em matrizes 4x4 ---
const uint16_t PECAS[7][4] = {
  // --- I piece | Peça I ---
  {
    0b0000111100000000,
    0b0010001000100010,
    0b0000000011110000,
    0b0100010001000100
  },

  // --- O piece | Peça O ---
  {
    0b0000011001100000,
    0b0000011001100000,
    0b0000011001100000,
    0b0000011001100000
  },

  // --- T piece | Peça T ---
  {
    0b0000111001000000,
    0b0000010001100100,
    0b0000010011100000,
    0b0000010011000100
  },

  // --- S piece, green piece corrected | Peça S, peça verde corrigida ---
  {
    0b0000011011000000, // .XX. / XX.. | .XX. / XX..
    0b0100011000100000, // .X.. / .XX. / ..X. | .X.. / .XX. / ..X.
    0b0000011011000000, // .XX. / XX.. | .XX. / XX..
    0b0100011000100000  // .X.. / .XX. / ..X. | .X.. / .XX. / ..X.
  },

  // --- Z piece | Peça Z ---
  {
    0b0000110001100000, // XX.. / .XX. | XX.. / .XX.
    0b0010011001000000, // ..X. / .XX. / .X.. | ..X. / .XX. / .X..
    0b0000110001100000, // XX.. / .XX. | XX.. / .XX.
    0b0010011001000000  // ..X. / .XX. / .X.. | ..X. / .XX. / .X..
  },

  // --- J piece | Peça J ---
  {
    0b0000111000100000,
    0b0000011001000100,
    0b0000100011100000,
    0b0000010001001100
  },

  // --- L piece | Peça L ---
  {
    0b0000111010000000,
    0b0000010001000110,
    0b0000001011100000,
    0b0000110001000100
  }
};

// --- Piece colors | Cores das peças ---
const uint16_t CORES[8] = {
  TFT_BLACK,   // Empty cell | Célula vazia
  TFT_CYAN,    // I piece color | Cor da peça I
  TFT_YELLOW,  // O piece color | Cor da peça O
  TFT_MAGENTA, // T piece color | Cor da peça T
  TFT_GREEN,   // S piece color | Cor da peça S
  TFT_RED,     // Z piece color | Cor da peça Z
  TFT_BLUE,    // J piece color | Cor da peça J
  TFT_ORANGE   // L piece color | Cor da peça L
};

bool celulaDaPeca(int tipo, int rotacao, int x, int y) {
  uint16_t forma = PECAS[tipo][rotacao % 4]; // Select piece shape | Seleciona o formato da peça
  int bit = 15 - (y * 4 + x);                // Calculate bit position | Calcula a posição do bit
  return (forma >> bit) & 0x01;              // Return cell state | Retorna o estado da célula
}

void desenharBloco(int x, int y, uint16_t cor) {
  display.fillRect(x, y, TAM_BLOCO, TAM_BLOCO, cor);              // Draw filled block | Desenha o bloco preenchido
  display.drawRect(x, y, TAM_BLOCO, TAM_BLOCO, TFT_DARKGREY);     // Draw block border | Desenha a borda do bloco
}

void limparTabuleiro() {
  // --- Clear fixed board matrix | Limpa a matriz de blocos fixos ---
  for (int y = 0; y < LINHAS; y++) {
    for (int x = 0; x < COLUNAS; x++) {
      tabuleiro[y][x] = 0; // Set cell as empty | Define a célula como vazia
    }
  }
}

void limparTelaAnterior() {
  // --- Clear previous screen buffer | Limpa a memória da tela anterior ---
  for (int y = 0; y < LINHAS; y++) {
    for (int x = 0; x < COLUNAS; x++) {
      telaAnterior[y][x] = 255; // Force first redraw | Força o primeiro redesenho
    }
  }

  pontosAnterior = -1;      // Force score redraw | Força redesenho da pontuação
  nivelAnterior = -1;       // Force level redraw | Força redesenho do nível
  proximaPecaAnterior = -1; // Force next piece redraw | Força redesenho da próxima peça
}

bool colisao(int novoX, int novoY, int novaRotacao) {
  // --- Check piece collision | Verifica colisão da peça ---
  for (int py = 0; py < 4; py++) {
    for (int px = 0; px < 4; px++) {
      if (!celulaDaPeca(pecaAtual, novaRotacao, px, py)) {
        continue; // Ignore empty piece cells | Ignora células vazias da peça
      }

      int bx = novoX + px; // Board X position | Posição X no tabuleiro
      int by = novoY + py; // Board Y position | Posição Y no tabuleiro

      if (bx < 0 || bx >= COLUNAS || by >= LINHAS) {
        return true; // Collision with board limits | Colisão com os limites do tabuleiro
      }

      if (by >= 0 && tabuleiro[by][bx] != 0) {
        return true; // Collision with fixed block | Colisão com bloco fixo
      }
    }
  }

  return false; // No collision found | Nenhuma colisão encontrada
}

void fixarPeca() {
  // --- Attach current piece to the board | Fixa a peça atual no tabuleiro ---
  for (int py = 0; py < 4; py++) {
    for (int px = 0; px < 4; px++) {
      if (celulaDaPeca(pecaAtual, rotacaoAtual, px, py)) {
        int bx = pecaX + px; // Board X position | Posição X no tabuleiro
        int by = pecaY + py; // Board Y position | Posição Y no tabuleiro

        if (by >= 0 && by < LINHAS && bx >= 0 && bx < COLUNAS) {
          tabuleiro[by][bx] = pecaAtual + 1; // Save fixed block color index | Salva o índice da cor do bloco fixo
        }
      }
    }
  }
}

void limparLinhasCompletas() {
  int removidas = 0; // Removed lines counter | Contador de linhas removidas

  // --- Check board from bottom to top | Verifica o tabuleiro de baixo para cima ---
  for (int y = LINHAS - 1; y >= 0; y--) {
    bool completa = true; // Assume line is complete | Assume que a linha está completa

    for (int x = 0; x < COLUNAS; x++) {
      if (tabuleiro[y][x] == 0) {
        completa = false; // Found empty cell | Encontrou uma célula vazia
        break;            // Stop checking this line | Para de verificar esta linha
      }
    }

    if (completa) {
      removidas++; // Count removed line | Conta a linha removida

      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < COLUNAS; x++) {
          tabuleiro[yy][x] = tabuleiro[yy - 1][x]; // Move upper line down | Move a linha de cima para baixo
        }
      }

      for (int x = 0; x < COLUNAS; x++) {
        tabuleiro[0][x] = 0; // Clear top line | Limpa a linha superior
      }

      y++; // Recheck same row | Verifica novamente a mesma linha
    }
  }

  if (removidas > 0) {
    linhasFeitas += removidas;              // Update cleared lines | Atualiza linhas removidas
    pontos += removidas * removidas * 100;  // Update score | Atualiza pontuação

    nivel = 1 + linhasFeitas / 5; // Increase level every 5 lines | Aumenta o nível a cada 5 linhas

    int novoIntervalo = 550 - (nivel - 1) * 45; // Calculate new speed | Calcula a nova velocidade

    if (novoIntervalo < 120) {
      novoIntervalo = 120; // Limit maximum speed | Limita a velocidade máxima
    }

    intervaloQueda = novoIntervalo; // Apply new falling interval | Aplica novo intervalo de queda
  }
}

void novaPeca() {
  pecaAtual = proximaPeca;      // Use next piece as current | Usa a próxima peça como atual
  proximaPeca = random(0, 7);   // Randomize next piece | Sorteia a próxima peça

  rotacaoAtual = 0; // Reset rotation | Reinicia a rotação
  pecaX = 3;        // Start near center | Inicia perto do centro
  pecaY = -1;       // Start slightly above board | Inicia um pouco acima do tabuleiro

  if (colisao(pecaX, pecaY, rotacaoAtual)) {
    gameOver = true; // End game if new piece collides | Encerra o jogo se a nova peça colidir
  }
}

byte obterCelulaRenderizada(int x, int y) {
  byte valor = tabuleiro[y][x]; // Start with fixed board value | Começa com o valor fixo do tabuleiro

  if (!gameOver) {
    // --- Overlay current falling piece | Sobrepõe a peça atual em queda ---
    for (int py = 0; py < 4; py++) {
      for (int px = 0; px < 4; px++) {
        if (celulaDaPeca(pecaAtual, rotacaoAtual, px, py)) {
          int bx = pecaX + px; // Piece cell board X | X da célula da peça no tabuleiro
          int by = pecaY + py; // Piece cell board Y | Y da célula da peça no tabuleiro

          if (bx == x && by == y) {
            valor = pecaAtual + 1; // Use current piece color | Usa a cor da peça atual
          }
        }
      }
    }
  }

  return valor; // Return final cell value | Retorna o valor final da célula
}

void desenharTabuleiroSuave() {
  // --- Draw only changed board cells | Desenha apenas células alteradas do tabuleiro ---
  for (int y = 0; y < LINHAS; y++) {
    for (int x = 0; x < COLUNAS; x++) {
      byte valorAtual = obterCelulaRenderizada(x, y); // Get current cell value | Obtém o valor atual da célula

      if (valorAtual != telaAnterior[y][x]) {
        int px = TAB_X + x * TAM_BLOCO; // Pixel X position | Posição X em pixels
        int py = TAB_Y + y * TAM_BLOCO; // Pixel Y position | Posição Y em pixels

        if (valorAtual == 0) {
          display.fillRect(px, py, TAM_BLOCO, TAM_BLOCO, TFT_BLACK);          // Clear cell | Limpa a célula
          display.drawRect(px, py, TAM_BLOCO, TAM_BLOCO, TFT_DARKGREY);      // Draw grid border | Desenha a borda da grade
        } else {
          desenharBloco(px, py, CORES[valorAtual]); // Draw colored block | Desenha bloco colorido
        }

        telaAnterior[y][x] = valorAtual; // Save drawn value | Salva o valor desenhado
      }
    }
  }
}

void desenharProximaPeca() {
  display.fillRect(PAINEL_X, 58, 72, 34, TFT_BLACK);     // Clear next piece area | Limpa a área da próxima peça
  display.drawRect(PAINEL_X, 58, 72, 34, TFT_DARKGREY);  // Draw next piece box | Desenha a caixa da próxima peça

  // --- Draw next piece preview | Desenha a prévia da próxima peça ---
  for (int py = 0; py < 4; py++) {
    for (int px = 0; px < 4; px++) {
      if (celulaDaPeca(proximaPeca, 0, px, py)) {
        int x = PAINEL_X + 18 + px * 6; // Preview X position | Posição X da prévia
        int y = 63 + py * 6;            // Preview Y position | Posição Y da prévia

        display.fillRect(x, y, 6, 6, CORES[proximaPeca + 1]);      // Draw preview block | Desenha bloco da prévia
        display.drawRect(x, y, 6, 6, TFT_DARKGREY);                // Draw preview border | Desenha borda da prévia
      }
    }
  }
}

void desenharPainelSuave() {
  display.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color | Define a cor do texto
  display.setTextSize(1);                     // Set text size | Define o tamanho do texto

  if (pontosAnterior == -1) {
    display.fillRect(PAINEL_X, 0, TELA_LARGURA - PAINEL_X, TELA_ALTURA, TFT_BLACK); // Clear side panel | Limpa o painel lateral

    display.setCursor(PAINEL_X, 6);   // Set title position | Define posição do título
    display.print("TETRIS");          // Print title | Imprime o título

    display.setCursor(PAINEL_X, 22);  // Set score label position | Define posição do texto de pontos
    display.print("Pts:");            // Print score label | Imprime texto de pontos

    display.setCursor(PAINEL_X, 44);  // Set level label position | Define posição do texto de nível
    display.print("Nivel:");          // Print level label | Imprime texto de nível

    display.setCursor(PAINEL_X, 50);  // Set next label position | Define posição do texto da próxima peça
    display.print("Prox:");           // Print next label | Imprime texto da próxima peça

    display.setCursor(PAINEL_X, 100); // Set help text position | Define posição do texto de ajuda
    display.print("UP gira");         // Print rotate help | Imprime ajuda para girar

    display.setCursor(PAINEL_X, 110); // Set help text position | Define posição do texto de ajuda
    display.print("C drop");          // Print drop help | Imprime ajuda da queda rápida
  }

  if (pontos != pontosAnterior) {
    display.fillRect(PAINEL_X, 32, 72, 10, TFT_BLACK); // Clear score area | Limpa a área da pontuação
    display.setCursor(PAINEL_X, 32);                   // Set score position | Define posição da pontuação
    display.print(pontos);                             // Print score | Imprime a pontuação
    pontosAnterior = pontos;                           // Save displayed score | Salva a pontuação exibida
  }

  if (nivel != nivelAnterior) {
    display.fillRect(PAINEL_X + 36, 44, 28, 10, TFT_BLACK); // Clear level area | Limpa a área do nível
    display.setCursor(PAINEL_X + 36, 44);                   // Set level position | Define posição do nível
    display.print(nivel);                                   // Print level | Imprime o nível
    nivelAnterior = nivel;                                  // Save displayed level | Salva o nível exibido
  }

  if (proximaPeca != proximaPecaAnterior) {
    desenharProximaPeca();                 // Draw next piece preview | Desenha a prévia da próxima peça
    proximaPecaAnterior = proximaPeca;     // Save displayed next piece | Salva a próxima peça exibida
  }
}

void desenharJogo() {
  desenharTabuleiroSuave(); // Draw board softly | Desenha o tabuleiro suavemente
  desenharPainelSuave();    // Draw side panel softly | Desenha o painel lateral suavemente
}

void mostrarGameOver() {
  if (telaGameOverDesenhada) {
    return; // Avoid drawing again | Evita desenhar novamente
  }

  telaGameOverDesenhada = true; // Mark Game Over as drawn | Marca Game Over como desenhado

  display.fillRect(14, 38, 132, 52, TFT_BLACK); // Draw message background | Desenha fundo da mensagem
  display.drawRect(14, 38, 132, 52, TFT_RED);   // Draw red border | Desenha borda vermelha

  display.setTextColor(TFT_RED, TFT_BLACK); // Set red text color | Define texto vermelho
  display.setTextSize(1);                   // Set text size | Define tamanho do texto

  display.setCursor(48, 48);     // Set Game Over text position | Define posição do texto Game Over
  display.print("GAME OVER");    // Print Game Over | Imprime Game Over

  display.setTextColor(TFT_WHITE, TFT_BLACK); // Set white text color | Define texto branco

  display.setCursor(32, 64);          // Set restart text position | Define posição do texto de reinício
  display.print("Centro reinicia");   // Print restart instruction | Imprime instrução de reinício
}

void reiniciarJogo() {
  limparTabuleiro(); // Clear board matrix | Limpa a matriz do tabuleiro

  pontos = 0;             // Reset score | Reinicia pontuação
  linhasFeitas = 0;       // Reset cleared lines | Reinicia linhas removidas
  nivel = 1;              // Reset level | Reinicia nível
  intervaloQueda = 550;   // Reset falling speed | Reinicia velocidade de queda

  gameOver = false;              // Clear Game Over status | Limpa estado de Game Over
  telaGameOverDesenhada = false; // Allow Game Over screen later | Permite tela de Game Over depois

  proximaPeca = random(0, 7); // Randomize first next piece | Sorteia a primeira próxima peça
  novaPeca();                 // Create current piece | Cria a peça atual

  display.fillScreen(TFT_BLACK); // Clear full screen once | Limpa a tela inteira uma vez

  display.drawRect(
    TAB_X - 1,
    TAB_Y - 1,
    COLUNAS * TAM_BLOCO + 2,
    LINHAS * TAM_BLOCO + 2,
    TFT_WHITE
  ); // Draw board border | Desenha a borda do tabuleiro

  limparTelaAnterior(); // Reset screen buffer | Reinicia a memória da tela
  desenharJogo();       // Draw initial game screen | Desenha a tela inicial do jogo

  quedaTimer.resetMillis();   // Reset falling timer | Reinicia temporizador de queda
  entradaTimer.resetMillis(); // Reset input timer | Reinicia temporizador de entrada
}

void moverBaixo() {
  if (!colisao(pecaX, pecaY + 1, rotacaoAtual)) {
    pecaY++; // Move piece down | Move a peça para baixo
  } else {
    fixarPeca();              // Attach piece to board | Fixa a peça no tabuleiro
    limparLinhasCompletas();  // Clear completed lines | Limpa linhas completas
    novaPeca();               // Create new piece | Cria nova peça
  }
}

void quedaRapida() {
  while (!colisao(pecaX, pecaY + 1, rotacaoAtual)) {
    pecaY++; // Move down until collision | Move para baixo até colidir
  }

  fixarPeca();             // Attach piece to board | Fixa a peça no tabuleiro
  limparLinhasCompletas(); // Clear completed lines | Limpa linhas completas
  novaPeca();              // Create new piece | Cria nova peça
}

void lerControles() {
  if (!entradaTimer.intervalMillis(95)) {
    return; // Read controls every 95 ms | Lê os controles a cada 95 ms
  }

  if (gameOver) {
    if (keyboard.press(KEY_CENTER)) {
      reiniciarJogo(); // Restart game | Reinicia o jogo
    }

    return; // Stop reading movement controls | Para de ler controles de movimento
  }

  bool mudou = false; // Screen update flag | Indicador de atualização da tela

  if (keyboard.hold(KEY_LEFT)) {
    if (!colisao(pecaX - 1, pecaY, rotacaoAtual)) {
      pecaX--;      // Move left | Move para a esquerda
      mudou = true; // Mark screen change | Marca alteração na tela
    }
  }

  if (keyboard.hold(KEY_RIGHT)) {
    if (!colisao(pecaX + 1, pecaY, rotacaoAtual)) {
      pecaX++;      // Move right | Move para a direita
      mudou = true; // Mark screen change | Marca alteração na tela
    }
  }

  if (keyboard.hold(KEY_DOWN)) {
    moverBaixo();  // Speed up falling | Acelera a queda
    mudou = true;  // Mark screen change | Marca alteração na tela
  }

  if (keyboard.press(KEY_UP)) {
    int novaRotacao = (rotacaoAtual + 1) % 4; // Calculate next rotation | Calcula a próxima rotação

    if (!colisao(pecaX, pecaY, novaRotacao)) {
      rotacaoAtual = novaRotacao; // Apply rotation | Aplica rotação
      mudou = true;               // Mark screen change | Marca alteração na tela
    } else if (!colisao(pecaX - 1, pecaY, novaRotacao)) {
      pecaX--;                    // Move left to help rotation | Move à esquerda para ajudar a rotação
      rotacaoAtual = novaRotacao; // Apply rotation | Aplica rotação
      mudou = true;               // Mark screen change | Marca alteração na tela
    } else if (!colisao(pecaX + 1, pecaY, novaRotacao)) {
      pecaX++;                    // Move right to help rotation | Move à direita para ajudar a rotação
      rotacaoAtual = novaRotacao; // Apply rotation | Aplica rotação
      mudou = true;               // Mark screen change | Marca alteração na tela
    }
  }

  if (keyboard.press(KEY_CENTER)) {
    quedaRapida(); // Hard drop | Queda rápida
    mudou = true;  // Mark screen change | Marca alteração na tela
  }

  if (mudou) {
    desenharJogo(); // Redraw only if something changed | Redesenha apenas se algo mudou
  }
}

void setup() {
  Serial.begin(115200); // Start serial communication | Inicia a comunicação serial

  randomSeed(analogRead(P_POT1)); // Improve random piece generation | Melhora o sorteio das peças

  // --- Display Initialization | Inicialização do display ---
  display.init();                  // Initialize the TFT display | Inicializa o display TFT
  display.setRotation(3);          // Set display rotation | Define a rotação do display
  display.fillScreen(TFT_BLACK);   // Fill screen with black | Preenche a tela com preto

  // --- Game Initialization | Inicialização do jogo ---
  reiniciarJogo(); // Start a new game | Inicia uma nova partida
}

void loop() {
  lerControles(); // Read player controls | Lê os comandos do jogador

  if (!gameOver && quedaTimer.intervalMillis(intervaloQueda)) {
    moverBaixo();  // Move piece down automatically | Move a peça para baixo automaticamente
    desenharJogo(); // Update game screen | Atualiza a tela do jogo
  }

  if (gameOver) {
    mostrarGameOver(); // Show Game Over message | Mostra a mensagem de Game Over
  }
}