/**
 * @brief Space Invader for ES32Lab using TFT Display, Analog Keyboard and Buzzer
 * | Space Invader para ES32Lab usando Display TFT, Teclado Analógico e Buzzer
 *
 * This example creates a simple Space Invader-style game for the ES32Lab board.
 * | Este exemplo cria um jogo simples estilo Space Invader para a placa ES32Lab.
 *
 * It uses:
 * | Ele utiliza:
 *
 * - ES_TFT to draw the game on the TFT display.
 *   | ES_TFT para desenhar o jogo no display TFT.
 *
 * - ES_AnalogKeyboard to control the player spaceship.
 *   | ES_AnalogKeyboard para controlar a nave do jogador.
 *
 * - ES_TimeInterval to control timing without delay().
 *   | ES_TimeInterval para controlar o tempo sem usar delay().
 *
 * - ES_Buzzer to play short sound effects.
 *   | ES_Buzzer para tocar efeitos sonoros curtos.
 *
 * Controls:
 * | Controles:
 *
 * - LEFT: move the spaceship left.
 *   | ESQUERDA: move a nave para a esquerda.
 *
 * - RIGHT: move the spaceship right.
 *   | DIREITA: move a nave para a direita.
 *
 * - CENTER: shoot.
 *   | CENTRO: atira.
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
ES_Buzzer buzzer(P_BUZZER);             // Buzzer object | Objeto do buzzer

ES_TimeInterval inputTimer;       // Input reading timer | Temporizador da leitura dos comandos
ES_TimeInterval playerShotTimer;  // Player shot movement timer | Temporizador do tiro do jogador
ES_TimeInterval enemyMoveTimer;   // Enemy movement timer | Temporizador do movimento dos inimigos
ES_TimeInterval enemyShotTimer;   // Enemy shooting timer | Temporizador do disparo inimigo
ES_TimeInterval enemyBulletTimer; // Enemy bullet movement timer | Temporizador do tiro inimigo

const int SCREEN_W = 160; // Screen width in pixels | Largura da tela em pixels
const int SCREEN_H = 128; // Screen height in pixels | Altura da tela em pixels

const int HUD_H = 14; // Top information bar height | Altura da barra superior de informações

const int PLAYER_W = 13;  // Player spaceship width | Largura da nave do jogador
const int PLAYER_H = 8;   // Player spaceship height | Altura da nave do jogador
const int PLAYER_Y = 116; // Player spaceship Y position | Posição Y da nave do jogador

const int BULLET_W = 2; // Bullet width | Largura do tiro
const int BULLET_H = 5; // Bullet height | Altura do tiro

const int ENEMY_ROWS = 3; // Enemy rows | Linhas de inimigos
const int ENEMY_COLS = 6; // Enemy columns | Colunas de inimigos

const int ENEMY_W = 10; // Enemy width | Largura do inimigo
const int ENEMY_H = 7;  // Enemy height | Altura do inimigo

const int ENEMY_GAP_X = 22; // Horizontal distance between enemies | Distância horizontal entre inimigos
const int ENEMY_GAP_Y = 13; // Vertical distance between enemies | Distância vertical entre inimigos

bool inimigoVivo[ENEMY_ROWS][ENEMY_COLS]; // Enemy alive matrix | Matriz de inimigos vivos

int playerX = 74;    // Player spaceship X position | Posição X da nave do jogador
int oldPlayerX = 74; // Last player X position | Última posição X da nave

bool tiroJogadorAtivo = false; // Player bullet status | Estado do tiro do jogador
int tiroJogadorX = 0;          // Player bullet X position | Posição X do tiro do jogador
int tiroJogadorY = 0;          // Player bullet Y position | Posição Y do tiro do jogador
int oldTiroJogadorY = 0;       // Last player bullet Y position | Última posição Y do tiro do jogador

bool tiroInimigoAtivo = false; // Enemy bullet status | Estado do tiro inimigo
int tiroInimigoX = 0;          // Enemy bullet X position | Posição X do tiro inimigo
int tiroInimigoY = 0;          // Enemy bullet Y position | Posição Y do tiro inimigo
int oldTiroInimigoY = 0;       // Last enemy bullet Y position | Última posição Y do tiro inimigo

int inimigoX = 18;       // Enemy group X position | Posição X do grupo de inimigos
int inimigoY = 24;       // Enemy group Y position | Posição Y do grupo de inimigos
int direcaoInimigo = 2;  // Enemy horizontal step | Passo horizontal dos inimigos

int pontos = 0; // Player score | Pontuação do jogador
int vidas = 3;  // Player lives | Vidas do jogador
int nivel = 1;  // Game level | Nível do jogo

int pontosAnt = -1; // Last displayed score | Última pontuação exibida
int vidasAnt = -1;  // Last displayed lives | Últimas vidas exibidas
int nivelAnt = -1;  // Last displayed level | Último nível exibido

unsigned long intervaloInimigo = 620; // Enemy movement interval | Intervalo de movimento dos inimigos

bool gameOver = false;              // Game Over status | Estado de fim de jogo
bool telaGameOverDesenhada = false; // Game Over screen flag | Controle da tela de Game Over

// -----------------------------------------------------------------------------
// Sound effects | Efeitos sonoros
// -----------------------------------------------------------------------------

void somInicio() {
  buzzer.sound(880, 30);  // Play start tone | Toca som de início
  buzzer.end(0);          // Stop buzzer | Para o buzzer
  buzzer.sound(1175, 40); // Play start tone | Toca som de início
  buzzer.end(0);          // Stop buzzer | Para o buzzer
}

void somTiro() {
  buzzer.sound(1300, 18); // Play shooting sound | Toca som do tiro
  buzzer.end(0);          // Stop buzzer | Para o buzzer
}

void somExplosao() {
  buzzer.sound(260, 25); // Play explosion sound | Toca som de explosão
  buzzer.end(0);         // Stop buzzer | Para o buzzer
  buzzer.sound(150, 35); // Play explosion sound | Toca som de explosão
  buzzer.end(0);         // Stop buzzer | Para o buzzer
}

void somPerdeuVida() {
  buzzer.sound(420, 60); // Play hit sound | Toca som de dano
  buzzer.end(0);         // Stop buzzer | Para o buzzer
  buzzer.sound(250, 80); // Play hit sound | Toca som de dano
  buzzer.end(0);         // Stop buzzer | Para o buzzer
}

void somGameOver() {
  buzzer.sound(300, 90);  // Play Game Over sound | Toca som de Game Over
  buzzer.end(0);          // Stop buzzer | Para o buzzer
  buzzer.sound(180, 130); // Play Game Over sound | Toca som de Game Over
  buzzer.end(0);          // Stop buzzer | Para o buzzer
}

// -----------------------------------------------------------------------------
// Basic drawing functions | Funções básicas de desenho
// -----------------------------------------------------------------------------

void desenharHUD() {
  if (pontos == pontosAnt && vidas == vidasAnt && nivel == nivelAnt) {
    return; // Avoid unnecessary redraw | Evita redesenho desnecessário
  }

  display.fillRect(0, 0, SCREEN_W, HUD_H, TFT_BLACK);          // Clear HUD area | Limpa a área do HUD
  display.drawLine(0, HUD_H, SCREEN_W, HUD_H, TFT_DARKGREY);   // Draw HUD separator | Desenha separador do HUD

  display.setTextSize(1);                     // Set text size | Define o tamanho do texto
  display.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color | Define a cor do texto

  display.setCursor(2, 3); // Set score position | Define posição da pontuação
  display.print("P:");     // Print score label | Imprime texto da pontuação
  display.print(pontos);   // Print score | Imprime pontuação

  display.setCursor(62, 3); // Set lives position | Define posição das vidas
  display.print("V:");      // Print lives label | Imprime texto das vidas
  display.print(vidas);     // Print lives | Imprime vidas

  display.setCursor(112, 3); // Set level position | Define posição do nível
  display.print("N:");       // Print level label | Imprime texto do nível
  display.print(nivel);      // Print level | Imprime nível

  pontosAnt = pontos; // Save displayed score | Salva pontuação exibida
  vidasAnt = vidas;   // Save displayed lives | Salva vidas exibidas
  nivelAnt = nivel;   // Save displayed level | Salva nível exibido
}

void apagarNave(int x) {
  display.fillRect(x - 1, PLAYER_Y - 1, PLAYER_W + 2, PLAYER_H + 2, TFT_BLACK); // Clear player area | Limpa área da nave
}

void desenharNave(int x) {
  display.fillRect(x, PLAYER_Y + 3, PLAYER_W, 4, TFT_GREEN);    // Draw ship body | Desenha corpo da nave
  display.fillRect(x + 5, PLAYER_Y, 3, 4, TFT_GREEN);           // Draw ship cannon | Desenha canhão da nave
  display.drawRect(x, PLAYER_Y + 3, PLAYER_W, 4, TFT_DARKGREY); // Draw ship border | Desenha borda da nave
}

void apagarTiroJogador() {
  if (tiroJogadorAtivo || oldTiroJogadorY > 0) {
    display.fillRect(tiroJogadorX, oldTiroJogadorY, BULLET_W, BULLET_H + 2, TFT_BLACK); // Clear old shot | Limpa tiro antigo
  }
}

void desenharTiroJogador() {
  if (tiroJogadorAtivo) {
    display.fillRect(tiroJogadorX, tiroJogadorY, BULLET_W, BULLET_H, TFT_YELLOW); // Draw player shot | Desenha tiro do jogador
  }
}

void apagarTiroInimigo() {
  if (tiroInimigoAtivo || oldTiroInimigoY > 0) {
    display.fillRect(tiroInimigoX, oldTiroInimigoY, BULLET_W, BULLET_H + 2, TFT_BLACK); // Clear old enemy shot | Limpa tiro inimigo antigo
  }
}

void desenharTiroInimigo() {
  if (tiroInimigoAtivo) {
    display.fillRect(tiroInimigoX, tiroInimigoY, BULLET_W, BULLET_H, TFT_RED); // Draw enemy shot | Desenha tiro inimigo
  }
}

int posXInimigo(int coluna) {
  return inimigoX + coluna * ENEMY_GAP_X; // Calculate enemy X position | Calcula posição X do inimigo
}

int posYInimigo(int linha) {
  return inimigoY + linha * ENEMY_GAP_Y; // Calculate enemy Y position | Calcula posição Y do inimigo
}

void apagarInimigoNaPosicao(int x, int y) {
  display.fillRect(x - 1, y - 1, ENEMY_W + 2, ENEMY_H + 2, TFT_BLACK); // Clear enemy area | Limpa área do inimigo
}

void desenharInimigoNaPosicao(int x, int y, uint16_t cor) {
  display.fillRect(x + 2, y, 6, 2, cor);                 // Draw enemy head | Desenha cabeça do inimigo
  display.fillRect(x, y + 2, ENEMY_W, 3, cor);           // Draw enemy body | Desenha corpo do inimigo
  display.fillRect(x + 1, y + 5, 2, 2, cor);             // Draw enemy left leg | Desenha perna esquerda
  display.fillRect(x + 7, y + 5, 2, 2, cor);             // Draw enemy right leg | Desenha perna direita
  display.drawRect(x, y + 2, ENEMY_W, 3, TFT_DARKGREY);  // Draw enemy detail | Desenha detalhe do inimigo
}

void apagarTodosInimigos() {
  // --- Clear all currently visible enemies | Limpa todos os inimigos visíveis ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        apagarInimigoNaPosicao(posXInimigo(c), posYInimigo(l)); // Clear enemy | Limpa inimigo
      }
    }
  }
}

void desenharTodosInimigos() {
  // --- Draw all alive enemies | Desenha todos os inimigos vivos ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        uint16_t cor = TFT_CYAN; // Default enemy color | Cor padrão do inimigo

        if (l == 1) {
          cor = TFT_MAGENTA; // Middle row color | Cor da linha do meio
        }

        if (l == 2) {
          cor = TFT_ORANGE; // Bottom row color | Cor da linha inferior
        }

        desenharInimigoNaPosicao(posXInimigo(c), posYInimigo(l), cor); // Draw enemy | Desenha inimigo
      }
    }
  }
}

bool retangulosColidem(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
  return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by; // Check rectangle collision | Verifica colisão entre retângulos
}

// -----------------------------------------------------------------------------
// Game state functions | Funções de estado do jogo
// -----------------------------------------------------------------------------

void prepararInimigos() {
  // --- Mark all enemies as alive | Marca todos os inimigos como vivos ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      inimigoVivo[l][c] = true; // Enemy starts alive | Inimigo começa vivo
    }
  }

  inimigoX = 18;      // Reset enemy group X | Reinicia X do grupo inimigo
  inimigoY = 24;      // Reset enemy group Y | Reinicia Y do grupo inimigo
  direcaoInimigo = 2; // Reset enemy direction | Reinicia direção dos inimigos

  intervaloInimigo = 620 - (nivel - 1) * 55; // Increase speed by level | Aumenta velocidade por nível

  if (intervaloInimigo < 180) {
    intervaloInimigo = 180; // Limit maximum enemy speed | Limita velocidade máxima dos inimigos
  }
}

bool todosInimigosDerrotados() {
  // --- Check if all enemies are defeated | Verifica se todos os inimigos foram derrotados ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        return false; // Found alive enemy | Encontrou inimigo vivo
      }
    }
  }

  return true; // No enemies alive | Nenhum inimigo vivo
}

void limparTiros() {
  apagarTiroJogador(); // Clear player shot | Limpa tiro do jogador
  apagarTiroInimigo(); // Clear enemy shot | Limpa tiro inimigo

  tiroJogadorAtivo = false; // Disable player shot | Desativa tiro do jogador
  tiroInimigoAtivo = false; // Disable enemy shot | Desativa tiro inimigo

  oldTiroJogadorY = 0; // Reset old shot position | Reinicia posição antiga do tiro
  oldTiroInimigoY = 0; // Reset old enemy shot position | Reinicia posição antiga do tiro inimigo
}

void desenharTelaInicialDoJogo() {
  display.fillScreen(TFT_BLACK); // Clear full screen | Limpa a tela inteira

  pontosAnt = -1; // Force HUD redraw | Força redesenho do HUD
  vidasAnt = -1;  // Force HUD redraw | Força redesenho do HUD
  nivelAnt = -1;  // Force HUD redraw | Força redesenho do HUD

  desenharHUD();           // Draw top information bar | Desenha barra superior de informações
  desenharTodosInimigos(); // Draw enemies | Desenha inimigos
  desenharNave(playerX);   // Draw player spaceship | Desenha nave do jogador
}

void proximaFase() {
  apagarTodosInimigos(); // Clear current enemies | Limpa inimigos atuais
  limparTiros();         // Clear bullets | Limpa tiros

  nivel++; // Increase level | Aumenta nível

  prepararInimigos();          // Prepare new enemy wave | Prepara nova onda de inimigos
  desenharTelaInicialDoJogo(); // Redraw game screen | Redesenha tela do jogo

  somInicio(); // Play new level sound | Toca som de nova fase
}

void encerrarJogo() {
  limparTiros();                 // Clear all bullets from screen | Limpa todos os tiros da tela
  gameOver = true;               // Set Game Over | Define Game Over
  telaGameOverDesenhada = false; // Allow Game Over screen drawing | Permite desenhar tela de Game Over
  somGameOver();                 // Play Game Over sound | Toca som de Game Over
}

void perderVida() {
  vidas--; // Decrease lives | Diminui vidas

  somPerdeuVida(); // Play damage sound | Toca som de dano

  if (vidas <= 0) {
    encerrarJogo(); // End game | Encerra o jogo
    return;
  }

  limparTiros(); // Clear bullets | Limpa tiros

  apagarNave(playerX);  // Clear player ship | Limpa nave do jogador
  playerX = 74;         // Reset player position | Reinicia posição da nave
  oldPlayerX = playerX; // Save player position | Salva posição da nave
  desenharNave(playerX);// Draw player ship | Desenha nave do jogador

  pontosAnt = -1; // Force HUD redraw | Força redesenho do HUD
  desenharHUD();  // Update HUD | Atualiza HUD
}

void reiniciarJogo() {
  pontos = 0; // Reset score | Reinicia pontuação
  vidas = 3;  // Reset lives | Reinicia vidas
  nivel = 1;  // Reset level | Reinicia nível

  playerX = 74;    // Reset player X | Reinicia X da nave
  oldPlayerX = 74; // Reset old player X | Reinicia X antigo da nave

  gameOver = false;              // Clear Game Over status | Limpa estado de Game Over
  telaGameOverDesenhada = false; // Reset Game Over screen flag | Reinicia controle de Game Over

  limparTiros();      // Clear bullets | Limpa tiros
  prepararInimigos(); // Prepare enemies | Prepara inimigos

  desenharTelaInicialDoJogo(); // Draw initial game screen | Desenha tela inicial do jogo

  inputTimer.resetMillis();       // Reset input timer | Reinicia temporizador dos comandos
  playerShotTimer.resetMillis();  // Reset player shot timer | Reinicia temporizador do tiro do jogador
  enemyMoveTimer.resetMillis();   // Reset enemy movement timer | Reinicia temporizador dos inimigos
  enemyShotTimer.resetMillis();   // Reset enemy shot timer | Reinicia temporizador do disparo inimigo
  enemyBulletTimer.resetMillis(); // Reset enemy bullet timer | Reinicia temporizador do tiro inimigo

  somInicio(); // Play start sound | Toca som de início
}

// -----------------------------------------------------------------------------
// Player functions | Funções do jogador
// -----------------------------------------------------------------------------

void atirarJogador() {
  if (tiroJogadorAtivo) {
    return; // Only one player bullet at a time | Apenas um tiro do jogador por vez
  }

  tiroJogadorAtivo = true;                 // Enable player bullet | Ativa tiro do jogador
  tiroJogadorX = playerX + PLAYER_W / 2;   // Set bullet X | Define X do tiro
  tiroJogadorY = PLAYER_Y - 6;             // Set bullet Y | Define Y do tiro
  oldTiroJogadorY = tiroJogadorY;          // Save old bullet Y | Salva Y antigo do tiro

  desenharTiroJogador(); // Draw bullet | Desenha tiro
  somTiro();             // Play shooting sound | Toca som de tiro
}

void atualizarTiroJogador() {
  if (!tiroJogadorAtivo) {
    return; // No player bullet active | Nenhum tiro do jogador ativo
  }

  apagarTiroJogador(); // Clear old bullet | Limpa tiro antigo

  oldTiroJogadorY = tiroJogadorY; // Save old Y | Salva Y antigo
  tiroJogadorY -= 5;              // Move bullet up | Move tiro para cima

  if (tiroJogadorY < HUD_H + 1) {
    tiroJogadorAtivo = false; // Disable bullet out of screen | Desativa tiro fora da tela
    apagarTiroJogador();      // Clear bullet | Limpa tiro
    return;
  }

  // --- Check collision with enemies | Verifica colisão com inimigos ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        int ex = posXInimigo(c); // Enemy X position | Posição X do inimigo
        int ey = posYInimigo(l); // Enemy Y position | Posição Y do inimigo

        if (retangulosColidem(tiroJogadorX, tiroJogadorY, BULLET_W, BULLET_H, ex, ey, ENEMY_W, ENEMY_H)) {
          inimigoVivo[l][c] = false;      // Mark enemy as defeated | Marca inimigo como derrotado
          apagarInimigoNaPosicao(ex, ey); // Clear enemy from screen | Apaga inimigo da tela
          tiroJogadorAtivo = false;       // Disable player bullet | Desativa tiro do jogador
          apagarTiroJogador();            // Clear bullet | Limpa tiro

          pontos += 10 * nivel; // Add score | Soma pontos
          desenharHUD();        // Update HUD | Atualiza HUD
          somExplosao();        // Play explosion sound | Toca som de explosão

          if (todosInimigosDerrotados()) {
            proximaFase(); // Start next level | Inicia próxima fase
          }

          return;
        }
      }
    }
  }

  desenharTiroJogador(); // Draw bullet in new position | Desenha tiro na nova posição
}

// -----------------------------------------------------------------------------
// Enemy functions | Funções dos inimigos
// -----------------------------------------------------------------------------

void moverInimigos() {
  apagarTodosInimigos(); // Clear enemies before moving | Limpa inimigos antes de mover

  int menorX = SCREEN_W; // Leftmost enemy X | X do inimigo mais à esquerda
  int maiorX = 0;        // Rightmost enemy X | X do inimigo mais à direita

  // --- Find enemy group limits | Encontra limites do grupo inimigo ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        int ex = posXInimigo(c); // Enemy X position | Posição X do inimigo

        if (ex < menorX) {
          menorX = ex; // Update left limit | Atualiza limite esquerdo
        }

        if (ex + ENEMY_W > maiorX) {
          maiorX = ex + ENEMY_W; // Update right limit | Atualiza limite direito
        }
      }
    }
  }

  bool bateuNaParede = false; // Wall hit flag | Indicador de colisão com parede

  if (menorX + direcaoInimigo < 1) {
    bateuNaParede = true; // Hit left wall | Bateu na parede esquerda
  }

  if (maiorX + direcaoInimigo > SCREEN_W - 1) {
    bateuNaParede = true; // Hit right wall | Bateu na parede direita
  }

  if (bateuNaParede) {
    direcaoInimigo = -direcaoInimigo; // Invert direction | Inverte direção
    inimigoY += 6;                    // Move enemies down | Move inimigos para baixo
  } else {
    inimigoX += direcaoInimigo; // Move enemies horizontally | Move inimigos horizontalmente
  }

  desenharTodosInimigos(); // Draw enemies in new position | Desenha inimigos na nova posição

  // --- Check if enemies reached the player area | Verifica se inimigos chegaram até a nave ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        int ey = posYInimigo(l); // Enemy Y position | Posição Y do inimigo

        if (ey + ENEMY_H >= PLAYER_Y - 2) {
          encerrarJogo(); // End game | Encerra o jogo
          return;
        }
      }
    }
  }
}

void inimigoAtirar() {
  if (tiroInimigoAtivo) {
    return; // Only one enemy bullet at a time | Apenas um tiro inimigo por vez
  }

  int vivos[ENEMY_ROWS * ENEMY_COLS]; // Alive enemies list | Lista de inimigos vivos
  int total = 0;                      // Alive enemies counter | Contador de inimigos vivos

  // --- Build alive enemies list | Monta lista de inimigos vivos ---
  for (int l = 0; l < ENEMY_ROWS; l++) {
    for (int c = 0; c < ENEMY_COLS; c++) {
      if (inimigoVivo[l][c]) {
        vivos[total] = l * ENEMY_COLS + c; // Save enemy index | Salva índice do inimigo
        total++;                           // Count alive enemy | Conta inimigo vivo
      }
    }
  }

  if (total == 0) {
    return; // No enemies to shoot | Nenhum inimigo para atirar
  }

  int escolhido = vivos[random(0, total)]; // Choose random enemy | Escolhe inimigo aleatório
  int linha = escolhido / ENEMY_COLS;      // Enemy row | Linha do inimigo
  int coluna = escolhido % ENEMY_COLS;     // Enemy column | Coluna do inimigo

  tiroInimigoAtivo = true;                         // Enable enemy bullet | Ativa tiro inimigo
  tiroInimigoX = posXInimigo(coluna) + ENEMY_W / 2; // Set bullet X | Define X do tiro
  tiroInimigoY = posYInimigo(linha) + ENEMY_H + 1;  // Set bullet Y | Define Y do tiro
  oldTiroInimigoY = tiroInimigoY;                   // Save old bullet Y | Salva Y antigo do tiro

  desenharTiroInimigo(); // Draw enemy bullet | Desenha tiro inimigo
}

void atualizarTiroInimigo() {
  if (!tiroInimigoAtivo) {
    return; // No enemy bullet active | Nenhum tiro inimigo ativo
  }

  apagarTiroInimigo(); // Clear old enemy bullet | Limpa tiro inimigo antigo

  oldTiroInimigoY = tiroInimigoY; // Save old Y | Salva Y antigo
  tiroInimigoY += 4;              // Move bullet down | Move tiro para baixo

  if (tiroInimigoY > SCREEN_H) {
    tiroInimigoAtivo = false; // Disable bullet out of screen | Desativa tiro fora da tela
    apagarTiroInimigo();      // Clear bullet | Limpa tiro
    return;
  }

  if (retangulosColidem(tiroInimigoX, tiroInimigoY, BULLET_W, BULLET_H, playerX, PLAYER_Y, PLAYER_W, PLAYER_H)) {
    tiroInimigoAtivo = false; // Disable enemy bullet | Desativa tiro inimigo
    apagarTiroInimigo();      // Clear enemy bullet | Limpa tiro inimigo
    perderVida();             // Decrease player lives | Diminui vidas do jogador
    return;
  }

  desenharTiroInimigo(); // Draw enemy bullet in new position | Desenha tiro inimigo na nova posição
}

// -----------------------------------------------------------------------------
// Input and screens | Entrada e telas
// -----------------------------------------------------------------------------

void lerControles() {
  if (!inputTimer.intervalMillis(45)) {
    return; // Read controls every 45 ms | Lê comandos a cada 45 ms
  }

  if (gameOver) {
    if (keyboard.press(KEY_CENTER)) {
      reiniciarJogo(); // Restart game | Reinicia o jogo
    }

    return; // Stop movement controls | Para controles de movimento
  }

  bool moveu = false; // Movement flag | Indicador de movimento

  if (keyboard.hold(KEY_LEFT)) {
    oldPlayerX = playerX; // Save old position | Salva posição antiga
    playerX -= 4;         // Move left | Move para a esquerda

    if (playerX < 1) {
      playerX = 1; // Limit left border | Limita borda esquerda
    }

    moveu = true; // Mark movement | Marca movimento
  }

  if (keyboard.hold(KEY_RIGHT)) {
    oldPlayerX = playerX; // Save old position | Salva posição antiga
    playerX += 4;         // Move right | Move para a direita

    if (playerX > SCREEN_W - PLAYER_W - 1) {
      playerX = SCREEN_W - PLAYER_W - 1; // Limit right border | Limita borda direita
    }

    moveu = true; // Mark movement | Marca movimento
  }

  if (moveu) {
    apagarNave(oldPlayerX); // Clear old spaceship | Limpa nave antiga
    desenharNave(playerX);  // Draw new spaceship | Desenha nave nova
  }

  if (keyboard.press(KEY_CENTER)) {
    atirarJogador(); // Fire player shot | Dispara tiro do jogador
  }
}

void mostrarGameOver() {
  if (telaGameOverDesenhada) {
    return; // Avoid redrawing Game Over screen | Evita redesenhar a tela de Game Over
  }

  telaGameOverDesenhada = true; // Mark screen as drawn | Marca tela como desenhada

  display.fillRect(14, 38, 132, 56, TFT_BLACK); // Draw message background | Desenha fundo da mensagem
  display.drawRect(14, 38, 132, 56, TFT_RED);   // Draw message border | Desenha borda da mensagem

  display.setTextSize(1);                   // Set text size | Define tamanho do texto
  display.setTextColor(TFT_RED, TFT_BLACK); // Set red text | Define texto vermelho

  display.setCursor(48, 48);  // Set Game Over position | Define posição do Game Over
  display.print("GAME OVER"); // Print Game Over | Imprime Game Over

  display.setTextColor(TFT_WHITE, TFT_BLACK); // Set white text | Define texto branco

  display.setCursor(38, 64); // Set score position | Define posição da pontuação
  display.print("Pontos: "); // Print score label | Imprime texto da pontuação
  display.print(pontos);     // Print final score | Imprime pontuação final

  display.setCursor(27, 78);        // Set restart text position | Define posição do texto de reinício
  display.print("Centro reinicia"); // Print restart instruction | Imprime instrução de reinício
}

// -----------------------------------------------------------------------------
// setup() and loop() | setup() e loop()
// -----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200); // Start serial communication | Inicia comunicação serial

  randomSeed(analogRead(P_POT1)); // Improve random generation | Melhora geração aleatória

  // --- Buzzer Initialization | Inicialização do buzzer ---
  buzzer.begin();       // Initialize buzzer | Inicializa o buzzer
  buzzer.setVolume(45); // Set buzzer volume | Define volume do buzzer

  // --- Display Initialization | Inicialização do display ---
  display.init();                // Initialize the TFT display | Inicializa o display TFT
  display.setRotation(3);        // Set recommended display rotation | Define rotação recomendada do display
  display.fillScreen(TFT_BLACK); // Fill screen with black | Preenche a tela com preto

  // --- Game Initialization | Inicialização do jogo ---
  reiniciarJogo(); // Start the game | Inicia o jogo
}

void loop() {
  lerControles(); // Read player controls | Lê comandos do jogador

  if (!gameOver && playerShotTimer.intervalMillis(35)) {
    atualizarTiroJogador(); // Update player bullet | Atualiza tiro do jogador
  }

  if (!gameOver && enemyBulletTimer.intervalMillis(55)) {
    atualizarTiroInimigo(); // Update enemy bullet | Atualiza tiro inimigo
  }

  if (!gameOver && enemyMoveTimer.intervalMillis(intervaloInimigo)) {
    moverInimigos(); // Move enemies | Move inimigos
  }

  if (!gameOver && enemyShotTimer.intervalMillis(800)) {
    inimigoAtirar(); // Enemy shoots | Inimigo atira
  }

  if (gameOver) {
    mostrarGameOver(); // Show Game Over screen | Mostra tela de Game Over
  }
}