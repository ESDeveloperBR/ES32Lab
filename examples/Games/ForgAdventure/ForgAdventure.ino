/**
 * @file FrogAdventure.ino
 * @date 2026-07-16
 * @brief Frog Adventure: a three-phase arcade game for the ES32Lab board.
 * | Frog Adventure: um jogo de ação em três fases para a placa ES32Lab.
 *
 * @details
 * The player controls a friendly frog on the ES32Lab TFT display. During each
 * 30-second phase, the frog must catch common and special flies while avoiding
 * animated crocodiles. The game progresses through morning, afternoon and night,
 * with increasing collision penalties. A phase is cleared only when its score is
 * greater than zero.
 *
 * | A jogadora controla um sapinho amigável no display TFT da ES32Lab. Durante
 * cada fase de 30 segundos, o sapo deve capturar moscas comuns e especiais enquanto
 * evita jacarés animados. O jogo avança pela manhã, tarde e noite, com penalidades
 * crescentes nas colisões. A fase só é concluída quando sua pontuação é maior que zero.
 *
 * Controls | Controles:
 * - LEFT / RIGHT: move the frog and selects the difficulty in the opening menu.
 *   | ESQUERDA / DIREITA: movimenta o sapo e seleciona a dificuldade no menu inicial.
 * - UP: makes the frog jump.
 *   | CIMA: faz o sapo pular.
 * - CENTER: starts the game, launches the tongue and confirms menu actions.
 *   | CENTRO: inicia o jogo, lança a língua e confirma ações dos menus.
 *
 * Scoring | Pontuação:
 * - Common fly: +1 point. | Mosca comum: +1 ponto.
 * - Special fly: +2 points. | Mosca especial: +2 pontos.
 * - Morning crocodile collision: -1 point. | Colisão pela manhã: -1 ponto.
 * - Afternoon crocodile collision: -2 points. | Colisão pela tarde: -2 pontos.
 * - Night crocodile collision: -3 points. | Colisão pela noite: -3 pontos.
 *
 * Difficulty levels | Níveis de dificuldade:
 * - EASY: higher jump and only one crocodile active at a time.
 *   | FÁCIL: pulo mais alto e apenas um jacaré ativo por vez.
 * - MEDIUM: higher jump and two active crocodiles.
 *   | MÉDIO: pulo mais alto e dois jacarés ativos.
 * - HARD: standard jump and two active crocodiles.
 *   | DIFÍCIL: pulo padrão e dois jacarés ativos.
 *
 * The example uses non-blocking timers through ES_TimeInterval. The game screen
 * restores only the previous positions of moving objects instead of repainting the
 * entire display every frame, reducing visible flicker.
 *
 * | O exemplo usa temporizadores não bloqueantes por meio de ES_TimeInterval.
 * Durante a partida, somente as posições anteriores dos objetos móveis são
 * restauradas, evitando redesenhar toda a tela a cada quadro e reduzindo piscadas.
 *
 * @author Roberta Santini
 * @version 1.0.0
 * @date 2026-07-16
 *
 * @note Game concept, visual identity and authorship credits: Roberta Santini.
 * | Conceito do jogo, identidade visual e créditos de autoria: Roberta Santini.
 *
 * @note Required ES32Lab resources: 1.8-inch TFT display, analog keyboard and
 * onboard buzzer. The recommended display rotation is 3.
 * | Recursos necessários da ES32Lab: display TFT de 1,8 polegada, teclado
 * analógico e buzzer onboard. A rotação recomendada do display é 3.
 *
 * @note For PlatformIO, include both esdeveloper/ES32Lab and
 * esdeveloper/TFT_eSPI_ES32Lab in lib_deps.
 * | No PlatformIO, inclua esdeveloper/ES32Lab e
 * esdeveloper/TFT_eSPI_ES32Lab em lib_deps.
 *
 * @warning Ensure that the ES32Lab library and the ES32Lab-adjusted TFT library
 * are installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab e a biblioteca TFT ajustada para
 * a ES32Lab estejam instaladas e configuradas corretamente.
 *
 * @see ES32Lab library: https://github.com/ESDeveloperBR/ES32Lab
 * @see ES_TFT documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_TFT/README.md
 * @see ES_AnalogKeyboard documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_AnalogKeyboard/README.md
 * @see ES_TimeInterval documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_TimeInterval/README.md
 * @see ES_Buzzer documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_Buzzer/README.md
 * @see Official ES32Lab board: https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h> // ES32Lab library | Biblioteca ES32Lab

// ======================================================
// Library objects and timers | Objetos da LIB e temporizadores
// ======================================================

ES_TFT display;                         // TFT display controller | Controlador do display TFT
ES_AnalogKeyboard keyboard(P_KEYBOARD); // Analog keyboard | Teclado analógico
ES_Buzzer buzzer(P_BUZZER);             // Onboard buzzer | Buzzer onboard

ES_TimeInterval frameTimer;             // Main animation frame interval | Intervalo principal de animação
ES_TimeInterval secondTimer;            // One-second game countdown | Contagem regressiva de um segundo
ES_TimeInterval transitionTimer;        // Phase transition duration | Duração da transição entre fases
ES_TimeInterval phaseClearedAnimTimer;  // Phase-cleared animation | Animação de fase concluída
ES_TimeInterval crocodileMouthTimer;    // Crocodile mouth animation | Animação da boca do jacaré
ES_TimeInterval confettiTimer;          // Victory confetti animation | Animação dos confetes da vitória

ES_TimeInterval gameOverBlinkStartTimer;    // Delay between blinks | Intervalo entre piscadas
ES_TimeInterval gameOverBlinkDurationTimer; // Closed-eye duration | Duração do olho fechado

bool gameOverHealthyEyeClosed = false;      // Healthy eye state | Estado do olho saudável
unsigned long gameOverNextBlinkMs = 2200;   // Next random blink delay | Próximo intervalo aleatório da piscada

// ======================================================
// Display and scene | Tela e cenário
// ======================================================

constexpr int SCREEN_W = 160;             // Logical width in rotation 3 | Largura lógica na rotação 3
constexpr int SCREEN_H = 128;             // Logical height in rotation 3 | Altura lógica na rotação 3
constexpr int HUD_H = 16;                 // Top status bar height | Altura da barra superior
constexpr int GROUND_Y = 108;             // Ground baseline | Linha de base do chão
constexpr int PHASE_SECONDS = 30;         // Duration of each phase | Duração de cada fase
constexpr int SPECIAL_FLY_CHANCE = 20;    // Percentage chance of a special fly | Chance percentual de mosca especial

// ======================================================
// Frog | Sapo
// ======================================================

constexpr int FROG_W = 16;
constexpr int FROG_H = 12;
constexpr int FROG_GROUND_Y = GROUND_Y - FROG_H;
constexpr int TONGUE_LENGTH = 60;

int frogX = 72;                           // Current horizontal position | Posição horizontal atual
int frogY = FROG_GROUND_Y;                // Current vertical position | Posição vertical atual
int jumpVelocity = 0;                     // Vertical jump velocity | Velocidade vertical do pulo
bool jumping = false;                     // True while the frog is airborne | Verdadeiro durante o pulo
int tongueFrames = 0;                     // Remaining tongue frames | Quadros restantes da língua
bool tongueWasDrawn = false;              // Helps erase the previous tongue | Ajuda a apagar a língua anterior

// ======================================================
// Flies | Moscas
// ======================================================

constexpr int FLY_COUNT = 3;

/** @brief Stores one fly state. | Armazena o estado de uma mosca. */
struct Fly {
  int x;                                  // Horizontal position | Posição horizontal
  int y;                                  // Vertical position | Posição vertical
  int speed;                              // Horizontal speed | Velocidade horizontal
  bool special;                           // True when worth two points | Verdadeiro quando vale dois pontos
};

Fly flies[FLY_COUNT];

// ======================================================
// Crocodiles | Jacarés
// ======================================================

constexpr int MAX_CROCODILES = 2;
constexpr int CROC_W = 24;
constexpr int CROC_H = 12;
constexpr int CROC_Y = GROUND_Y - CROC_H;

/** @brief Stores one crocodile state. | Armazena o estado de um jacaré. */
struct Crocodile {
  int x;                                  // Horizontal position | Posição horizontal
  int speed;                              // Horizontal speed | Velocidade horizontal
};

Crocodile crocodiles[MAX_CROCODILES];
bool crocodileMouthOpen = false;           // Shared mouth animation state | Estado compartilhado da boca

// ======================================================
// Confetti | Confetes
// ======================================================

constexpr int CONFETTI_COUNT = 18;
constexpr int CONFETTI_TOP = 39;
constexpr int CONFETTI_BOTTOM = 105;

/** @brief Stores one confetti particle. | Armazena uma partícula de confete. */
struct Confetti {
  int x;
  int y;
  int speed;
  uint16_t color;
};

Confetti confetti[CONFETTI_COUNT];
bool confettiVisible = true;

// ======================================================
// Game states and difficulty | Estados e dificuldade
// ======================================================

/** @brief Main game state machine. | Máquina de estados principal do jogo. */
enum GameState {
  DIFFICULTY_MENU,
  PLAYING,
  PHASE_CLEARED,
  GAME_OVER,
  VICTORY
};

/** @brief Available gameplay difficulty levels. | Níveis de dificuldade disponíveis. */
enum Difficulty {
  EASY,
  MEDIUM,
  HARD
};

GameState gameState = DIFFICULTY_MENU;
Difficulty selectedDifficulty = EASY;      // The opening menu always starts on EASY | O menu sempre inicia no FÁCIL

// ======================================================
// Score and phase data | Pontuação e dados da fase
// ======================================================

int currentPhase = 1;                     // 1: morning, 2: afternoon, 3: night | 1: manhã, 2: tarde, 3: noite
int phaseScore = 0;                       // Score earned in the current phase | Pontuação da fase atual
int totalScore = 0;                       // Sum of cleared phase scores | Soma das fases concluídas
int timeLeft = PHASE_SECONDS;             // Remaining seconds in the phase | Segundos restantes
bool hudDirty = true;                     // Redraw HUD only when values change | Redesenha o HUD somente quando necessário

// ======================================================
// Difficulty configuration | Configuração da dificuldade
// ======================================================

/**
 * @brief Returns the full label of the selected difficulty.
 * | Retorna o nome completo da dificuldade selecionada.
 *
 * @return Difficulty label stored in flash-compatible text.
 * | Nome da dificuldade em texto.
 */
const char* difficultyName() {
  if (selectedDifficulty == EASY) {
    return "FACIL";
  }

  if (selectedDifficulty == MEDIUM) {
    return "MEDIO";
  }

  return "DIFICIL";
}

/**
 * @brief Returns the one-letter difficulty label used by the HUD.
 * | Retorna a abreviação de uma letra usada no HUD.
 *
 * @return F, M or D.
 * | F, M ou D.
 */
const char* difficultyShortName() {
  if (selectedDifficulty == EASY) {
    return "F";
  }

  if (selectedDifficulty == MEDIUM) {
    return "M";
  }

  return "D";
}

/**
 * @brief Returns the initial vertical velocity according to the selected difficulty.
 * | Retorna a velocidade vertical inicial conforme a dificuldade selecionada.
 *
 * @return Negative vertical velocity used to start a jump.
 * | Velocidade vertical negativa usada para iniciar o pulo.
 */
int jumpStartVelocity() {
  if (selectedDifficulty == EASY) {
    return -11;
  }

  if (selectedDifficulty == MEDIUM) {
    return -10;
  }

  return -8;
}

/**
 * @brief Returns how many crocodiles are active for the selected difficulty.
 * | Retorna quantos jacarés ficam ativos na dificuldade selecionada.
 *
 * @return One crocodile in EASY and two in MEDIUM or HARD.
 * | Um jacaré no FÁCIL e dois no MÉDIO ou DIFÍCIL.
 */
int activeCrocodileCount() {
  if (selectedDifficulty == EASY) {
    return 1;
  }

  return 2;
}

// ======================================================
// Phase configuration | Configuração das fases
// ======================================================

/**
 * @brief Returns the Portuguese label of the current day period.
 * | Retorna o nome em português do período atual do dia.
 *
 * @return MANHA, TARDE or NOITE.
 * | MANHA, TARDE ou NOITE.
 */
const char* phaseName() {
  if (currentPhase == 1) {
    return "MANHA";
  }

  if (currentPhase == 2) {
    return "TARDE";
  }

  return "NOITE";
}

/**
 * @brief Returns the score penalty for a crocodile collision in the current phase.
 * | Retorna a penalidade de pontos por colisão com jacaré na fase atual.
 *
 * @return One, two or three points according to the current phase.
 * | Um, dois ou três pontos conforme a fase atual.
 */
int crocodilePenalty() {
  // Manhã: -1
  // Tarde: -2
  // Noite: -3
  return currentPhase;
}

/**
 * @brief Returns the gameplay sky color for the current phase.
 * | Retorna a cor do céu da partida para a fase atual.
 *
 * @return TFT color value.
 * | Valor de cor TFT.
 */
uint16_t skyColor() {
  if (currentPhase == 1) {
    return TFT_CYAN;
  }

  if (currentPhase == 2) {
    return TFT_ORANGE;
  }

  return TFT_NAVY;
}

/**
 * @brief Returns the gameplay ground color for the current phase.
 * | Retorna a cor do chão da partida para a fase atual.
 *
 * @return TFT color value.
 * | Valor de cor TFT.
 */
uint16_t groundColor() {
  if (currentPhase == 1) {
    return TFT_GREEN;
  }

  return TFT_DARKGREEN;
}

// ======================================================
// Partial background restoration | Restauração parcial do fundo
// Prevents full-screen erase and redraw | Evita apagar e redesenhar a tela inteira.
// ======================================================

/**
 * @brief Restores a rectangular portion of the current phase background.
 * | Restaura uma área retangular do fundo da fase atual.
 *
 * @param x Left coordinate of the area. | Coordenada esquerda da área.
 * @param y Top coordinate of the area. | Coordenada superior da área.
 * @param width Area width in pixels. | Largura da área em pixels.
 * @param height Area height in pixels. | Altura da área em pixels.
 *
 * @note This partial redraw strategy prevents full-screen flicker during gameplay. | Esta estratégia evita a piscada causada pelo redesenho completo da tela.
 */
void restoreBackgroundRect(
  int x,
  int y,
  int width,
  int height
) {
  if (width <= 0 || height <= 0) {
    return;
  }

  int x0 = max(0, x);
  int y0 = max(HUD_H, y);

  int x1 = min(SCREEN_W, x + width);
  int y1 = min(SCREEN_H, y + height);

  if (x0 >= x1 || y0 >= y1) {
    return;
  }

  int skyBottom = min(y1, GROUND_Y);

  if (y0 < skyBottom) {
    display.fillRect(
      x0,
      y0,
      x1 - x0,
      skyBottom - y0,
      skyColor()
    );
  }

  int groundTop = max(y0, GROUND_Y);

  if (groundTop < y1) {
    display.fillRect(
      x0,
      groundTop,
      x1 - x0,
      y1 - groundTop,
      groundColor()
    );
  }

  if (y0 <= GROUND_Y && y1 > GROUND_Y) {
    display.drawLine(
      x0,
      GROUND_Y,
      x1 - 1,
      GROUND_Y,
      TFT_DARKGREEN
    );
  }
}

// ======================================================
// Gameplay scene | Cenário da partida
// ======================================================

/**
 * @brief Draws the static decoration for morning, afternoon or night.
 * | Desenha a decoração fixa da manhã, tarde ou noite.
 */
void drawPhaseDecoration() {
  if (currentPhase == 1) {
    // Sol da manhã
    display.fillCircle(
      145,
      29,
      7,
      TFT_YELLOW
    );

    // Nuvem
    display.fillCircle(
      20,
      31,
      4,
      TFT_WHITE
    );

    display.fillCircle(
      26,
      29,
      6,
      TFT_WHITE
    );

    display.fillCircle(
      33,
      31,
      4,
      TFT_WHITE
    );

    return;
  }

  if (currentPhase == 2) {
    // Sol da tarde
    display.fillCircle(
      145,
      45,
      8,
      TFT_YELLOW
    );

    display.drawLine(
      0,
      88,
      SCREEN_W - 1,
      88,
      TFT_RED
    );

    return;
  }

  // Lua
  display.fillCircle(
    145,
    30,
    8,
    TFT_WHITE
  );

  display.fillCircle(
    149,
    27,
    8,
    TFT_NAVY
  );

  // Estrelas
  display.drawPixel(18, 28, TFT_WHITE);
  display.drawPixel(42, 39, TFT_WHITE);
  display.drawPixel(76, 25, TFT_WHITE);
  display.drawPixel(104, 48, TFT_WHITE);
  display.drawPixel(126, 69, TFT_WHITE);
}

/**
 * @brief Draws the phase, difficulty, score and remaining time on the HUD.
 * | Desenha fase, dificuldade, pontuação e tempo restante no HUD.
 */
void drawHUD() {
  display.fillRect(
    0,
    0,
    SCREEN_W,
    HUD_H,
    TFT_BLACK
  );

  display.drawLine(
    0,
    HUD_H - 1,
    SCREEN_W - 1,
    HUD_H - 1,
    TFT_DARKGREY
  );

  display.setTextSize(1);
  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.setCursor(2, 4);
  display.print("F");
  display.print(currentPhase);
  display.print("-");
  display.print(difficultyShortName());

  display.setCursor(37, 4);
  display.print(phaseName());

  display.setCursor(83, 4);
  display.print("P:");
  display.print(phaseScore);

  display.setCursor(126, 4);
  display.print("T:");
  display.print(timeLeft);

  hudDirty = false;
}

/**
 * @brief Draws the complete static gameplay background before a phase starts.
 * | Desenha o cenário fixo completo antes do início de uma fase.
 */
void drawStaticScene() {
  display.fillScreen(skyColor());

  display.fillRect(
    0,
    GROUND_Y,
    SCREEN_W,
    SCREEN_H - GROUND_Y,
    groundColor()
  );

  display.drawLine(
    0,
    GROUND_Y,
    SCREEN_W - 1,
    GROUND_Y,
    TFT_DARKGREEN
  );

  drawPhaseDecoration();

  hudDirty = true;
  drawHUD();
}

// ======================================================
// Frog | Sapo
// ======================================================

/**
 * @brief Draws the playable frog at its current coordinates.
 * | Desenha o sapo jogável em suas coordenadas atuais.
 */
void drawFrog() {
  // Pernas
  display.fillRect(
    frogX,
    frogY + 8,
    6,
    4,
    TFT_DARKGREEN
  );

  display.fillRect(
    frogX + 10,
    frogY + 8,
    6,
    4,
    TFT_DARKGREEN
  );

  // Corpo
  display.fillRoundRect(
    frogX + 3,
    frogY + 4,
    10,
    8,
    3,
    TFT_DARKGREEN
  );

  // Olhos
  display.fillCircle(
    frogX + 5,
    frogY + 3,
    3,
    TFT_GREEN
  );

  display.fillCircle(
    frogX + 11,
    frogY + 3,
    3,
    TFT_GREEN
  );

  display.fillCircle(
    frogX + 5,
    frogY + 3,
    1,
    TFT_BLACK
  );

  display.fillCircle(
    frogX + 11,
    frogY + 3,
    1,
    TFT_BLACK
  );

  // Boca
  display.drawLine(
    frogX + 6,
    frogY + 8,
    frogX + 10,
    frogY + 8,
    TFT_BLACK
  );
}

/**
 * @brief Draws the frog tongue using the current frog position.
 * | Desenha a língua do sapo usando a posição atual do personagem.
 */
void drawTongue() {
  int tongueX = frogX + FROG_W / 2;

  int tongueTop = max(
    HUD_H + 1,
    frogY - TONGUE_LENGTH
  );

  display.drawLine(
    tongueX,
    frogY + 5,
    tongueX,
    tongueTop,
    TFT_RED
  );

  display.drawLine(
    tongueX + 1,
    frogY + 5,
    tongueX + 1,
    tongueTop,
    TFT_RED
  );
}

// ======================================================
// Fly | Mosca
// ======================================================

/**
 * @brief Draws a common or special fly.
 * | Desenha uma mosca comum ou especial.
 *
 * @param fly Fly state to render. | Estado da mosca que será desenhada.
 */
void drawFly(const Fly& fly) {
  uint16_t wingColor =
    fly.special ? TFT_MAGENTA : TFT_WHITE;

  uint16_t bodyColor =
    fly.special ? TFT_YELLOW : TFT_BLACK;

  display.fillCircle(
    fly.x - 3,
    fly.y - 2,
    2,
    wingColor
  );

  display.fillCircle(
    fly.x + 3,
    fly.y - 2,
    2,
    wingColor
  );

  display.fillCircle(
    fly.x,
    fly.y,
    fly.special ? 3 : 2,
    bodyColor
  );

  if (fly.special) {
    display.drawPixel(
      fly.x,
      fly.y,
      TFT_RED
    );
  }
}

// ======================================================
// Crocodile with animated mouth | Jacaré com boca animada
// ======================================================

/**
 * @brief Draws a crocodile with its animated mouth state.
 * | Desenha um jacaré considerando o estado animado da boca.
 *
 * @param crocodile Crocodile state to render. | Estado do jacaré que será desenhado.
 */
void drawCrocodile(
  const Crocodile& crocodile
) {
  int x = crocodile.x;
  int y = CROC_Y;

  // Corpo
  display.fillRect(
    x + 7,
    y + 3,
    13,
    8,
    TFT_DARKGREEN
  );

  // Cauda
  display.fillTriangle(
    x + 19,
    y + 3,
    x + 24,
    y + 7,
    x + 19,
    y + 10,
    TFT_DARKGREEN
  );

  if (crocodileMouthOpen) {
    // Parte superior da boca
    display.fillRect(
      x,
      y + 3,
      9,
      3,
      TFT_DARKGREEN
    );

    // Parte inferior da boca
    display.fillRect(
      x,
      y + 9,
      9,
      2,
      TFT_DARKGREEN
    );

    // Dentes
    display.drawPixel(
      x + 2,
      y + 6,
      TFT_WHITE
    );

    display.drawPixel(
      x + 6,
      y + 6,
      TFT_WHITE
    );

    display.drawPixel(
      x + 4,
      y + 8,
      TFT_WHITE
    );
  } else {
    // Boca fechada
    display.fillRect(
      x,
      y + 5,
      9,
      5,
      TFT_DARKGREEN
    );

    display.drawLine(
      x,
      y + 8,
      x + 8,
      y + 8,
      TFT_BLACK
    );

    display.drawPixel(
      x + 2,
      y + 8,
      TFT_WHITE
    );

    display.drawPixel(
      x + 6,
      y + 8,
      TFT_WHITE
    );
  }

  // Olho
  display.fillCircle(
    x + 8,
    y + 3,
    2,
    TFT_WHITE
  );

  display.drawPixel(
    x + 8,
    y + 3,
    TFT_BLACK
  );
}

// ======================================================
// Moving-object cleanup | Limpeza dos objetos móveis
// ======================================================

/**
 * @brief Restores the previous areas occupied by moving gameplay objects.
 * | Restaura as áreas anteriormente ocupadas pelos objetos móveis.
 */
void eraseDynamicObjects() {
  if (tongueWasDrawn) {
    int tongueX = frogX + FROG_W / 2;

    restoreBackgroundRect(
      tongueX - 2,
      HUD_H,
      5,
      frogY - HUD_H + 8
    );

    tongueWasDrawn = false;
  }

  restoreBackgroundRect(
    frogX - 1,
    frogY - 1,
    FROG_W + 2,
    FROG_H + 2
  );

  for (int i = 0; i < FLY_COUNT; i++) {
    restoreBackgroundRect(
      flies[i].x - 6,
      flies[i].y - 6,
      12,
      12
    );
  }

  int crocodileCount =
    activeCrocodileCount();

  for (
    int i = 0;
    i < crocodileCount;
    i++
  ) {
    restoreBackgroundRect(
      crocodiles[i].x - 2,
      CROC_Y - 2,
      CROC_W + 5,
      CROC_H + 4
    );
  }
}

// ======================================================
// Object spawning | Surgimento dos objetos
// ======================================================

/**
 * @brief Places a fly beyond the right edge with randomized height, speed and type.
 * | Reposiciona uma mosca além da borda direita com altura, velocidade e tipo aleatórios.
 *
 * @param index Index in the flies array. | Índice no vetor de moscas.
 * @param initialPosition Adds startup spacing when true. | Adiciona espaçamento inicial quando verdadeiro.
 */
void respawnFly(
  int index,
  bool initialPosition = false
) {
  int extraDistance =
    initialPosition ? index * 48 : 0;

  flies[index].x =
    SCREEN_W +
    random(25, 120) +
    extraDistance;

  flies[index].y =
    random(34, 79);

  flies[index].speed =
    random(1, 4);

  flies[index].special =
    random(100) < SPECIAL_FLY_CHANCE;
}

/**
 * @brief Places a crocodile beyond the right edge with randomized spacing and speed.
 * | Reposiciona um jacaré além da borda direita com distância e velocidade aleatórias.
 *
 * @param index Index in the crocodiles array. | Índice no vetor de jacarés.
 * @param initialPosition Adds startup spacing when true. | Adiciona espaçamento inicial quando verdadeiro.
 */
void respawnCrocodile(
  int index,
  bool initialPosition = false
) {
  int extraDistance = 0;

  if (
    initialPosition &&
    selectedDifficulty != EASY
  ) {
    extraDistance = index * 100;
  }

  crocodiles[index].x =
    SCREEN_W +
    random(60, 155) +
    extraDistance;

  crocodiles[index].speed =
    random(2, 4);
}

/**
 * @brief Initializes all flies and crocodiles for a new phase.
 * | Inicializa todas as moscas e jacarés para uma nova fase.
 */
void prepareObjects() {
  for (int i = 0; i < FLY_COUNT; i++) {
    respawnFly(i, true);
  }

  for (
    int i = 0;
    i < MAX_CROCODILES;
    i++
  ) {
    respawnCrocodile(i, true);
  }
}

// ======================================================
// Collision helpers | Colisões
// ======================================================

/**
 * @brief Tests axis-aligned rectangle overlap.
 * | Verifica a sobreposição de dois retângulos alinhados aos eixos.
 *
 * @param ax First rectangle X coordinate. | Coordenada X do primeiro retângulo.
 * @param ay First rectangle Y coordinate. | Coordenada Y do primeiro retângulo.
 * @param aw First rectangle width. | Largura do primeiro retângulo.
 * @param ah First rectangle height. | Altura do primeiro retângulo.
 * @param bx Second rectangle X coordinate. | Coordenada X do segundo retângulo.
 * @param by Second rectangle Y coordinate. | Coordenada Y do segundo retângulo.
 * @param bw Second rectangle width. | Largura do segundo retângulo.
 * @param bh Second rectangle height. | Altura do segundo retângulo.
 *
 * @return True when the rectangles overlap.
 * | Verdadeiro quando os retângulos se sobrepõem.
 */
bool rectanglesCollide(
  int ax,
  int ay,
  int aw,
  int ah,
  int bx,
  int by,
  int bw,
  int bh
) {
  return ax < bx + bw &&
         ax + aw > bx &&
         ay < by + bh &&
         ay + ah > by;
}

/**
 * @brief Plays the short low-pitched collision effect.
 * | Reproduz o efeito sonoro grave e curto de colisão.
 */
void playCrocodileHitSound() {
  buzzer.sound(
    NOTE_G3,
    45
  );

  buzzer.end(10);

  buzzer.sound(
    NOTE_C3,
    75
  );

  buzzer.end(0);
}

/**
 * @brief Plays the ascending melody used on the victory screen.
 * | Reproduz a melodia crescente usada na tela de vitória.
 */
void playVictoryMelody() {
  const int notes[] = {
    NOTE_C5,
    NOTE_E5,
    NOTE_G5,
    NOTE_C6,
    NOTE_E6
  };

  const int durations[] = {
    80,
    80,
    90,
    110,
    190
  };

  constexpr int NOTE_COUNT =
    sizeof(notes) / sizeof(notes[0]);

  for (int i = 0; i < NOTE_COUNT; i++) {
    buzzer.sound(
      notes[i],
      durations[i]
    );

    buzzer.end(20);
  }
}

// ======================================================
// Controls | Controles
// ======================================================

/**
 * @brief Reads movement, jump and tongue actions from the analog keyboard.
 * | Lê movimento, pulo e língua pelo teclado analógico.
 */
void readControls() {
  if (keyboard.hold(KEY_LEFT)) {
    frogX -= 3;
    frogX = max(1, frogX);
  }

  if (keyboard.hold(KEY_RIGHT)) {
    frogX += 3;

    frogX = min(
      SCREEN_W - FROG_W - 1,
      frogX
    );
  }

  // Botão de cima: pular
  if (
    keyboard.press(KEY_UP) &&
    !jumping
  ) {
    jumping = true;
    jumpVelocity = jumpStartVelocity();
  }

  // Botão central: lançar língua
  if (keyboard.press(KEY_CENTER)) {
    tongueFrames = 5;
  }
}

// ======================================================
// Gameplay updates | Atualizações do jogo
// ======================================================

/**
 * @brief Applies vertical velocity and gravity to the frog jump.
 * | Aplica velocidade vertical e gravidade ao pulo do sapo.
 */
void updateJump() {
  if (!jumping) {
    return;
  }

  frogY += jumpVelocity;
  jumpVelocity++;

  if (frogY >= FROG_GROUND_Y) {
    frogY = FROG_GROUND_Y;
    jumpVelocity = 0;
    jumping = false;
  }
}

/**
 * @brief Moves flies and active crocodiles and respawns off-screen objects.
 * | Movimenta moscas e jacarés ativos e reposiciona os objetos fora da tela.
 */
void updateObjects() {
  for (int i = 0; i < FLY_COUNT; i++) {
    flies[i].x -= flies[i].speed;

    if (flies[i].x < -8) {
      respawnFly(i);
    }
  }

  int crocodileCount =
    activeCrocodileCount();

  for (
    int i = 0;
    i < crocodileCount;
    i++
  ) {
    crocodiles[i].x -=
      crocodiles[i].speed;

    if (
      crocodiles[i].x <
      -CROC_W
    ) {
      respawnCrocodile(i);
    }
  }
}

/**
 * @brief Alternates the shared open and closed crocodile mouth state.
 * | Alterna o estado compartilhado de boca aberta e fechada dos jacarés.
 */
void updateCrocodileMouth() {
  if (
    crocodileMouthTimer.intervalMillis(
      180
    )
  ) {
    crocodileMouthOpen =
      !crocodileMouthOpen;
  }
}

/**
 * @brief Checks whether the active tongue catches any fly and updates the phase score.
 * | Verifica se a língua ativa captura alguma mosca e atualiza a pontuação da fase.
 */
void checkFlies() {
  if (tongueFrames <= 0) {
    return;
  }

  int tongueX =
    frogX + FROG_W / 2;

  int tongueTop = max(
    HUD_H + 1,
    frogY - TONGUE_LENGTH
  );

  for (int i = 0; i < FLY_COUNT; i++) {
    bool alignedHorizontally =
      flies[i].x >= tongueX - 9 &&
      flies[i].x <= tongueX + 9;

    bool insideTongueHeight =
      flies[i].y >= tongueTop &&
      flies[i].y <= frogY + 5;

    if (
      alignedHorizontally &&
      insideTongueHeight
    ) {
      phaseScore +=
        flies[i].special ? 2 : 1;

      hudDirty = true;
      respawnFly(i);
    }
  }
}

/**
 * @brief Checks frog collisions with active crocodiles, applies penalties and sound.
 * | Verifica colisões com jacarés ativos, aplica penalidades e reproduz o som.
 */
void checkCrocodiles() {
  int crocodileCount =
    activeCrocodileCount();

  for (
    int i = 0;
    i < crocodileCount;
    i++
  ) {
    bool collided = rectanglesCollide(
      frogX,
      frogY,
      FROG_W,
      FROG_H,
      crocodiles[i].x,
      CROC_Y,
      CROC_W,
      CROC_H
    );

    if (!collided) {
      continue;
    }

    phaseScore -=
      crocodilePenalty();

    hudDirty = true;

    playCrocodileHitSound();
    respawnCrocodile(i);

    // Impede dois sons no mesmo quadro
    break;
  }
}

// ======================================================
// Difficulty menu | Menu de dificuldade
// ======================================================

// Temporizadores exclusivos das animações do menu.
ES_TimeInterval menuFrameTimer;
ES_TimeInterval menuBlinkStartTimer;
ES_TimeInterval menuBlinkDurationTimer;
ES_TimeInterval menuFlyStartTimer;
ES_TimeInterval menuTongueTimer;

constexpr int MENU_FLY_Y = 39;

bool menuEyeClosed = false;
bool menuFlyActive = false;
bool menuTongueActive = false;

int menuFlyX = 164;

unsigned long menuNextBlinkMs = 2200;
unsigned long menuNextFlyMs = 4500;

// ------------------------------------------------------
// Fundo decorativo do menu
// ------------------------------------------------------

/**
 * @brief Draws the opening menu landscape.
 * | Desenha o cenário da tela inicial.
 */
void drawMenuBackground() {
  // Céu
  display.fillScreen(TFT_CYAN);

  // Lago
  display.fillRect(
    0,
    70,
    SCREEN_W,
    SCREEN_H - 70,
    TFT_BLUE
  );

  // Margem de grama
  display.fillRect(
    0,
    66,
    SCREEN_W,
    9,
    TFT_GREEN
  );

  display.drawLine(
    0,
    74,
    SCREEN_W - 1,
    74,
    TFT_DARKGREEN
  );

  // Nuvem esquerda
  display.fillCircle(15, 21, 4, TFT_WHITE);
  display.fillCircle(21, 18, 6, TFT_WHITE);
  display.fillCircle(28, 21, 4, TFT_WHITE);

  // Nuvem direita
  display.fillCircle(131, 23, 4, TFT_WHITE);
  display.fillCircle(138, 19, 7, TFT_WHITE);
  display.fillCircle(146, 23, 5, TFT_WHITE);

  // Ondas
  display.drawLine(4, 89, 34, 89, TFT_CYAN);
  display.drawLine(120, 91, 153, 91, TFT_CYAN);
  display.drawLine(7, 108, 31, 108, TFT_CYAN);
  display.drawLine(126, 110, 154, 110, TFT_CYAN);

  // Vitória-régia esquerda
  display.fillCircle(
    18,
    99,
    9,
    TFT_GREEN
  );

  display.fillTriangle(
    18,
    99,
    27,
    94,
    27,
    104,
    TFT_BLUE
  );

  // Vitória-régia direita
  display.fillCircle(
    143,
    100,
    8,
    TFT_DARKGREEN
  );

  display.fillTriangle(
    143,
    100,
    151,
    96,
    151,
    104,
    TFT_BLUE
  );

  // Plantas à esquerda
  display.drawLine(4, 70, 4, 56, TFT_DARKGREEN);
  display.drawLine(8, 70, 10, 53, TFT_DARKGREEN);
  display.drawLine(12, 70, 15, 58, TFT_DARKGREEN);

  // Plantas à direita
  display.drawLine(155, 70, 155, 54, TFT_DARKGREEN);
  display.drawLine(151, 70, 148, 57, TFT_DARKGREEN);
}

// ------------------------------------------------------
// Olhos do sapo do menu
// ------------------------------------------------------

/**
 * @brief Draws the opening frog eyes in open or winking state.
 * | Desenha os olhos do sapo da abertura abertos ou piscando.
 *
 * @param closed Closes the animated eye when true. | Fecha o olho animado quando verdadeiro.
 */
void drawMenuFrogEyes(bool closed) {
  const int x = 58;
  const int y = 31;

  // Refaz as bases verdes dos olhos.
  display.fillCircle(
    x + 13,
    y + 12,
    10,
    TFT_GREEN
  );

  display.fillCircle(
    x + 35,
    y + 12,
    10,
    TFT_GREEN
  );

  if (closed) {
    // Olho esquerdo fechado
    display.drawLine(
      x + 8,
      y + 12,
      x + 18,
      y + 12,
      TFT_BLACK
    );

    display.drawLine(
      x + 9,
      y + 13,
      x + 17,
      y + 13,
      TFT_BLACK
    );

    // Olho direito permanece aberto
    display.fillCircle(
      x + 35,
      y + 11,
      6,
      TFT_WHITE
    );

    display.fillCircle(
      x + 34,
      y + 12,
      2,
      TFT_BLACK
    );

    return;
  }

  // Dois olhos abertos
  display.fillCircle(
    x + 13,
    y + 11,
    6,
    TFT_WHITE
  );

  display.fillCircle(
    x + 35,
    y + 11,
    6,
    TFT_WHITE
  );

  display.fillCircle(
    x + 14,
    y + 12,
    2,
    TFT_BLACK
  );

  display.fillCircle(
    x + 34,
    y + 12,
    2,
    TFT_BLACK
  );
}

// ------------------------------------------------------
// Sapinho simpático do menu
// ------------------------------------------------------

/**
 * @brief Draws the friendly frog used on the opening menu.
 * | Desenha o sapinho amigável usado no menu inicial.
 */
void drawFriendlyMenuFrog() {
  const int x = 58;
  const int y = 31;

  // Sombra sobre a água
  display.fillRoundRect(
    x - 4,
    y + 38,
    52,
    7,
    4,
    TFT_DARKGREEN
  );

  // Pernas
  display.fillRoundRect(
    x - 5,
    y + 29,
    18,
    10,
    4,
    TFT_DARKGREEN
  );

  display.fillRoundRect(
    x + 35,
    y + 29,
    18,
    10,
    4,
    TFT_DARKGREEN
  );

  // Corpo
  display.fillRoundRect(
    x + 5,
    y + 14,
    38,
    29,
    10,
    TFT_GREEN
  );

  // Barriga
  display.fillRoundRect(
    x + 13,
    y + 24,
    22,
    16,
    7,
    TFT_YELLOW
  );

  drawMenuFrogEyes(false);

  // Nariz
  display.drawPixel(
    x + 21,
    y + 22,
    TFT_DARKGREEN
  );

  display.drawPixel(
    x + 27,
    y + 22,
    TFT_DARKGREEN
  );

  // Sorriso
  display.drawLine(
    x + 17,
    y + 28,
    x + 21,
    y + 31,
    TFT_BLACK
  );

  display.drawLine(
    x + 21,
    y + 31,
    x + 27,
    y + 31,
    TFT_BLACK
  );

  display.drawLine(
    x + 27,
    y + 31,
    x + 31,
    y + 27,
    TFT_BLACK
  );

  // Bochechas
  display.fillCircle(
    x + 12,
    y + 26,
    2,
    TFT_YELLOW
  );

  display.fillCircle(
    x + 37,
    y + 26,
    2,
    TFT_YELLOW
  );
}

// ------------------------------------------------------
// Mosquinha da animação inicial
// ------------------------------------------------------

/**
 * @brief Draws the small fly used by the opening animation.
 * | Desenha a pequena mosca usada na animação da abertura.
 *
 * @param x Horizontal coordinate. | Coordenada horizontal.
 * @param y Vertical coordinate. | Coordenada vertical.
 */
void drawMenuFly(int x, int y) {
  // Asas
  display.fillCircle(
    x - 3,
    y - 2,
    2,
    TFT_WHITE
  );

  display.fillCircle(
    x + 3,
    y - 2,
    2,
    TFT_WHITE
  );

  // Corpo
  display.fillCircle(
    x,
    y,
    2,
    TFT_BLACK
  );

  // Olhinhos
  display.drawPixel(
    x - 1,
    y - 1,
    TFT_RED
  );

  display.drawPixel(
    x + 1,
    y - 1,
    TFT_RED
  );
}

/**
 * @brief Erases the previous opening-animation fly position.
 * | Apaga a posição anterior da mosca da animação de abertura.
 *
 * @param x Previous horizontal coordinate. | Coordenada horizontal anterior.
 * @param y Previous vertical coordinate. | Coordenada vertical anterior.
 */
void eraseMenuFly(int x, int y) {
  display.fillRect(
    x - 6,
    y - 5,
    12,
    10,
    TFT_CYAN
  );
}

// ------------------------------------------------------
// Língua da animação inicial
// ------------------------------------------------------

/**
 * @brief Draws the opening frog tongue toward a target.
 * | Desenha a língua do sapo da abertura em direção ao alvo.
 *
 * @param targetX Target horizontal coordinate. | Coordenada horizontal do alvo.
 * @param targetY Target vertical coordinate. | Coordenada vertical do alvo.
 */
void drawMenuTongue(int targetX, int targetY) {
  constexpr int frogMouthX = 82;
  constexpr int frogMouthY = 60;

  display.drawLine(
    frogMouthX,
    frogMouthY,
    targetX,
    targetY,
    TFT_RED
  );

  display.drawLine(
    frogMouthX + 1,
    frogMouthY,
    targetX + 1,
    targetY,
    TFT_RED
  );
}

/**
 * @brief Erases the opening tongue and restores the frog face.
 * | Apaga a língua da abertura e restaura o rosto do sapo.
 *
 * @param targetX Previous target horizontal coordinate. | Coordenada horizontal anterior do alvo.
 * @param targetY Previous target vertical coordinate. | Coordenada vertical anterior do alvo.
 */
void eraseMenuTongue(int targetX, int targetY) {
  constexpr int frogMouthX = 82;
  constexpr int frogMouthY = 60;

  // O caminho da língua está na área azul-clara do céu.
  display.drawLine(
    frogMouthX,
    frogMouthY,
    targetX,
    targetY,
    TFT_CYAN
  );

  display.drawLine(
    frogMouthX + 1,
    frogMouthY,
    targetX + 1,
    targetY,
    TFT_CYAN
  );

  // Refaz o sapo para restaurar a boca e o rosto.
  drawFriendlyMenuFrog();

  // Preserva o estado da piscada caso ela esteja ocorrendo.
  if (menuEyeClosed) {
    drawMenuFrogEyes(true);
  }
}

// ------------------------------------------------------
// Reinicia as animações do menu
// ------------------------------------------------------

/**
 * @brief Resets blink, fly and tongue animation state when the menu opens.
 * | Reinicia os estados de piscada, mosca e língua quando o menu é aberto.
 */
void resetMenuAnimations() {
  menuEyeClosed = false;
  menuFlyActive = false;
  menuTongueActive = false;

  menuFlyX = SCREEN_W + 4;

  menuNextBlinkMs = random(1800, 3400);
  menuNextFlyMs = random(3500, 6500);

  menuFrameTimer.resetMillis();
  menuBlinkStartTimer.resetMillis();
  menuBlinkDurationTimer.resetMillis();
  menuFlyStartTimer.resetMillis();
  menuTongueTimer.resetMillis();
}

// ------------------------------------------------------
// Atualiza a piscada do sapo
// ------------------------------------------------------

/**
 * @brief Updates the randomized wink animation on the opening frog.
 * | Atualiza a piscada aleatória do sapo na abertura.
 */
void updateMenuBlink() {
  if (!menuEyeClosed) {
    if (
      menuBlinkStartTimer.intervalMillis(
        menuNextBlinkMs
      )
    ) {
      menuEyeClosed = true;

      drawMenuFrogEyes(true);
      menuBlinkDurationTimer.resetMillis();
    }

    return;
  }

  if (
    menuBlinkDurationTimer.intervalMillis(150)
  ) {
    menuEyeClosed = false;

    drawMenuFrogEyes(false);

    menuNextBlinkMs = random(1800, 3400);
    menuBlinkStartTimer.resetMillis();
  }
}

// ------------------------------------------------------
// Atualiza a mosquinha e a língua
// ------------------------------------------------------

/**
 * @brief Moves the opening fly and triggers the automatic tongue capture.
 * | Movimenta a mosca da abertura e aciona automaticamente a captura com a língua.
 */
void updateMenuFlyAnimation() {
  // Aguarda alguns segundos antes de soltar outra mosca.
  if (
    !menuFlyActive &&
    !menuTongueActive
  ) {
    if (
      menuFlyStartTimer.intervalMillis(
        menuNextFlyMs
      )
    ) {
      menuFlyActive = true;
      menuFlyX = SCREEN_W + 4;

      menuFrameTimer.resetMillis();
    }
  }

  // Fly | Mosca voando da direita em direção ao sapo.
  if (
    menuFlyActive &&
    menuFrameTimer.intervalMillis(70)
  ) {
    eraseMenuFly(
      menuFlyX,
      MENU_FLY_Y
    );

    menuFlyX -= 4;

    // Quando chega perto do sapo, ele lança a língua.
    if (menuFlyX <= 106) {
      menuFlyActive = false;
      menuTongueActive = true;

      drawMenuFly(
        menuFlyX,
        MENU_FLY_Y
      );

      drawMenuTongue(
        menuFlyX,
        MENU_FLY_Y
      );

      menuTongueTimer.resetMillis();

      return;
    }

    drawMenuFly(
      menuFlyX,
      MENU_FLY_Y
    );
  }

  // Mantém a língua visível por um pequeno período.
  if (
    menuTongueActive &&
    menuTongueTimer.intervalMillis(230)
  ) {
    eraseMenuFly(
      menuFlyX,
      MENU_FLY_Y
    );

    eraseMenuTongue(
      menuFlyX,
      MENU_FLY_Y
    );

    menuTongueActive = false;

    menuNextFlyMs = random(3500, 6500);
    menuFlyStartTimer.resetMillis();
  }
}

/**
 * @brief Updates all non-blocking opening-menu animations.
 * | Atualiza todas as animações não bloqueantes do menu inicial.
 */
void updateMenuAnimations() {
  updateMenuBlink();
  updateMenuFlyAnimation();
}

// ------------------------------------------------------
// Cartão de cada dificuldade
// ------------------------------------------------------

/**
 * @brief Draws one difficulty selection card.
 * | Desenha um cartão de seleção de dificuldade.
 *
 * @param x Left coordinate. | Coordenada esquerda.
 * @param y Top coordinate. | Coordenada superior.
 * @param width Card width. | Largura do cartão.
 * @param label Text shown on the card. | Texto exibido no cartão.
 * @param option Difficulty represented by the card. | Dificuldade representada pelo cartão.
 */
void drawDifficultyOption(
  int x,
  int y,
  int width,
  const char* label,
  Difficulty option
) {
  bool selected =
    selectedDifficulty == option;

  uint16_t borderColor =
    selected ? TFT_YELLOW : TFT_WHITE;

  uint16_t backgroundColor =
    selected ? TFT_DARKGREEN : TFT_BLUE;

  uint16_t textColor =
    selected ? TFT_YELLOW : TFT_WHITE;

  // Sombra
  display.fillRoundRect(
    x + 2,
    y + 2,
    width,
    20,
    4,
    TFT_BLACK
  );

  // Fundo
  display.fillRoundRect(
    x,
    y,
    width,
    20,
    4,
    backgroundColor
  );

  // Contorno
  display.drawRoundRect(
    x,
    y,
    width,
    20,
    4,
    borderColor
  );

  // Indicador da opção selecionada
  if (selected) {
    display.fillTriangle(
      x + width / 2 - 4,
      y - 6,
      x + width / 2 + 4,
      y - 6,
      x + width / 2,
      y - 1,
      TFT_YELLOW
    );
  }

  display.setTextSize(1);

  display.setTextColor(
    textColor,
    backgroundColor
  );

  int textWidth =
    strlen(label) * 6;

  display.setCursor(
    x + (width - textWidth) / 2,
    y + 7
  );

  display.print(label);
}

// ------------------------------------------------------
// Desenha a tela principal
// ------------------------------------------------------

/**
 * @brief Draws the complete animated opening and difficulty-selection screen.
 * | Desenha a tela completa de abertura e seleção de dificuldade.
 *
 * @note This function preserves the current selection. Use openDifficultyMenu() when the menu must restart on EASY. | Esta função preserva a seleção atual. Use openDifficultyMenu() para reabrir o menu no FÁCIL.
 */
void showDifficultyMenu() {
  gameState = DIFFICULTY_MENU;

  drawMenuBackground();

  // Painel do título
  display.fillRoundRect(
    41,
    2,
    78,
    27,
    6,
    TFT_DARKGREEN
  );

  display.drawRoundRect(
    41,
    2,
    78,
    27,
    6,
    TFT_YELLOW
  );

  display.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    "FROG",
    3,
    2
  );

  display.setTextColor(
    TFT_WHITE,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    "ADVENTURE",
    19,
    1
  );

  // Sapinho central
  drawFriendlyMenuFrog();

  // Opções de dificuldade
  drawDifficultyOption(
    3,
    81,
    48,
    "FACIL",
    EASY
  );

  drawDifficultyOption(
    56,
    81,
    48,
    "MEDIO",
    MEDIUM
  );

  drawDifficultyOption(
    109,
    81,
    48,
    "DIFICIL",
    HARD
  );

  // Instrução
  display.fillRoundRect(
    2,
    104,
    156,
    13,
    4,
    TFT_BLACK
  );

  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    "< > ESCOLHE  CENTRO INICIA",
    107,
    1
  );

  // Assinatura
  display.fillRect(
    0,
    119,
    SCREEN_W,
    9,
    TFT_BLACK
  );

  display.setTextColor(
    TFT_DARKGREY,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    "By Roberta Santini",
    120,
    1
  );

  resetMenuAnimations();
}

// ------------------------------------------------------
// Abre o menu sempre no nível fácil
// ------------------------------------------------------

/**
 * @brief Selects EASY and opens the difficulty menu.
 * | Seleciona FÁCIL e abre o menu de dificuldade.
 */
void openDifficultyMenu() {
  selectedDifficulty = EASY;
  showDifficultyMenu();
}

// ------------------------------------------------------
// Controle do menu
// ------------------------------------------------------

/**
 * @brief Handles difficulty selection and updates opening animations.
 * | Controla a seleção de dificuldade e atualiza as animações da abertura.
 */
void updateDifficultyMenu() {
  bool changed = false;

  if (keyboard.press(KEY_LEFT)) {
    int value =
      static_cast<int>(
        selectedDifficulty
      );

    value--;

    if (value < 0) {
      value = 2;
    }

    selectedDifficulty =
      static_cast<Difficulty>(value);

    changed = true;
  }

  if (keyboard.press(KEY_RIGHT)) {
    int value =
      static_cast<int>(
        selectedDifficulty
      );

    value++;

    if (value > 2) {
      value = 0;
    }

    selectedDifficulty =
      static_cast<Difficulty>(value);

    changed = true;
  }

  if (changed) {
    showDifficultyMenu();
    return;
  }

  updateMenuAnimations();
}

// ======================================================
// Telas intermediárias
// ======================================================

// Estado da animação da passagem de fase.
bool phaseClearedFrogWinking = false;
bool phaseClearedSparklesBright = true;

int phaseClearedBlinkTicks = 0;
int phaseClearedNextBlinkTicks = 7;

// ------------------------------------------------------
// Informações da próxima fase
// ------------------------------------------------------

/**
 * @brief Returns the label of the phase that follows the current one.
 * | Retorna o nome da fase seguinte à fase atual.
 *
 * @return TARDE after morning and NOITE after afternoon.
 * | TARDE depois da manhã e NOITE depois da tarde.
 */
const char* nextPhaseName() {
  if (currentPhase == 1) {
    return "TARDE";
  }

  return "NOITE";
}

/**
 * @brief Returns the sky color used to preview the next phase.
 * | Retorna a cor do céu usada para antecipar a próxima fase.
 *
 * @return TFT color value.
 * | Valor de cor TFT.
 */
uint16_t nextPhaseSkyColor() {
  if (currentPhase == 1) {
    return TFT_ORANGE;
  }

  return TFT_NAVY;
}

// ------------------------------------------------------
// Fundo da passagem de fase
// ------------------------------------------------------

/**
 * @brief Draws the restrained celebratory background between phases.
 * | Desenha o fundo comemorativo e discreto da passagem de fase.
 */
void drawPhaseClearedBackground() {
  uint16_t backgroundColor =
    nextPhaseSkyColor();

  display.fillScreen(backgroundColor);

  // Lago
  display.fillRect(
    0,
    73,
    SCREEN_W,
    SCREEN_H - 73,
    TFT_BLUE
  );

  // Margem de grama
  display.fillRect(
    0,
    68,
    SCREEN_W,
    9,
    TFT_GREEN
  );

  display.drawLine(
    0,
    76,
    SCREEN_W - 1,
    76,
    TFT_DARKGREEN
  );

  // Prévia visual da próxima fase.
  if (currentPhase == 1) {
    // Sol da tarde
    display.fillCircle(
      146,
      30,
      8,
      TFT_YELLOW
    );

    display.drawLine(
      132,
      30,
      126,
      30,
      TFT_YELLOW
    );

    display.drawLine(
      146,
      16,
      146,
      11,
      TFT_YELLOW
    );
  } else {
    // Lua da noite
    display.fillCircle(
      146,
      29,
      8,
      TFT_WHITE
    );

    display.fillCircle(
      150,
      26,
      8,
      TFT_NAVY
    );

    display.drawPixel(126, 31, TFT_WHITE);
    display.drawPixel(137, 17, TFT_WHITE);
    display.drawPixel(155, 43, TFT_WHITE);
  }

  // Ondas discretas
  display.drawLine(4, 88, 32, 88, TFT_CYAN);
  display.drawLine(126, 91, 154, 91, TFT_CYAN);
  display.drawLine(7, 106, 30, 106, TFT_CYAN);
  display.drawLine(130, 108, 154, 108, TFT_CYAN);
}

// ------------------------------------------------------
// Olhos do sapinho da passagem de fase
// ------------------------------------------------------

/**
 * @brief Draws the phase-cleared frog eyes in open or winking state.
 * | Desenha os olhos do sapo da passagem de fase abertos ou piscando.
 *
 * @param winking Draws the wink when true. | Desenha a piscada quando verdadeiro.
 */
void drawPhaseClearedFrogEyes(bool winking) {
  const int x = 12;
  const int y = 31;

  // Bases verdes
  display.fillCircle(
    x + 13,
    y + 12,
    9,
    TFT_GREEN
  );

  display.fillCircle(
    x + 32,
    y + 12,
    9,
    TFT_GREEN
  );

  if (winking) {
    // Olho esquerdo piscando
    display.drawLine(
      x + 8,
      y + 12,
      x + 18,
      y + 12,
      TFT_BLACK
    );

    display.drawLine(
      x + 9,
      y + 13,
      x + 17,
      y + 13,
      TFT_BLACK
    );
  } else {
    display.fillCircle(
      x + 13,
      y + 11,
      5,
      TFT_WHITE
    );

    display.fillCircle(
      x + 14,
      y + 12,
      2,
      TFT_BLACK
    );
  }

  // Olho direito aberto
  display.fillCircle(
    x + 32,
    y + 11,
    5,
    TFT_WHITE
  );

  display.fillCircle(
    x + 31,
    y + 12,
    2,
    TFT_BLACK
  );
}

// ------------------------------------------------------
// Sapinho feliz da passagem de fase
// ------------------------------------------------------

/**
 * @brief Draws the happy waving frog used between phases.
 * | Desenha o sapo alegre e acenando usado entre as fases.
 */
void drawPhaseClearedFrog() {
  const int x = 12;
  const int y = 31;

  // Vitória-régia
  display.fillCircle(
    x + 24,
    y + 43,
    22,
    TFT_DARKGREEN
  );

  display.fillTriangle(
    x + 24,
    y + 43,
    x + 46,
    y + 35,
    x + 46,
    y + 51,
    TFT_BLUE
  );

  // Pernas
  display.fillRoundRect(
    x - 1,
    y + 31,
    17,
    9,
    4,
    TFT_DARKGREEN
  );

  display.fillRoundRect(
    x + 30,
    y + 31,
    17,
    9,
    4,
    TFT_DARKGREEN
  );

  // Braço levantado acenando
  display.fillRoundRect(
    x + 37,
    y + 17,
    7,
    17,
    3,
    TFT_GREEN
  );

  display.fillCircle(
    x + 42,
    y + 15,
    4,
    TFT_GREEN
  );

  // Corpo
  display.fillRoundRect(
    x + 5,
    y + 15,
    35,
    29,
    10,
    TFT_GREEN
  );

  // Barriga
  display.fillRoundRect(
    x + 12,
    y + 25,
    21,
    16,
    7,
    TFT_YELLOW
  );

  drawPhaseClearedFrogEyes(false);

  // Nariz
  display.drawPixel(
    x + 20,
    y + 23,
    TFT_DARKGREEN
  );

  display.drawPixel(
    x + 26,
    y + 23,
    TFT_DARKGREEN
  );

  // Sorriso
  display.drawLine(
    x + 16,
    y + 29,
    x + 20,
    y + 33,
    TFT_BLACK
  );

  display.drawLine(
    x + 20,
    y + 33,
    x + 27,
    y + 33,
    TFT_BLACK
  );

  display.drawLine(
    x + 27,
    y + 33,
    x + 31,
    y + 29,
    TFT_BLACK
  );

  // Bochechas
  display.fillCircle(
    x + 11,
    y + 27,
    2,
    TFT_YELLOW
  );

  display.fillCircle(
    x + 35,
    y + 27,
    2,
    TFT_YELLOW
  );
}

// ------------------------------------------------------
// Placa indicando a próxima fase
// ------------------------------------------------------

/**
 * @brief Draws the sign that announces the next phase.
 * | Desenha a placa que anuncia a próxima fase.
 *
 * @param brightArrow Highlights the arrow when true. | Destaca a seta quando verdadeiro.
 */
void drawNextPhaseSign(bool brightArrow) {
  // Poste
  display.fillRect(
    109,
    66,
    5,
    15,
    TFT_DARKGREY
  );

  // Placa
  display.fillRoundRect(
    68,
    30,
    87,
    42,
    6,
    TFT_BLACK
  );

  display.drawRoundRect(
    68,
    30,
    87,
    42,
    6,
    TFT_WHITE
  );

  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.setTextSize(1);
  display.setCursor(91, 36);
  display.print("PROXIMA");

  display.setTextColor(
    TFT_YELLOW,
    TFT_BLACK
  );

  display.setTextSize(2);
  display.setCursor(82, 49);
  display.print(nextPhaseName());

  // Seta pequena e pulsante
  uint16_t arrowColor =
    brightArrow ? TFT_YELLOW : TFT_WHITE;

  display.drawLine(
    61,
    49,
    67,
    49,
    arrowColor
  );

  display.fillTriangle(
    67,
    45,
    67,
    53,
    72,
    49,
    arrowColor
  );
}

// ------------------------------------------------------
// Indicador de progresso pelas três fases
// ------------------------------------------------------

/**
 * @brief Draws the three-step phase progress indicator.
 * | Desenha o indicador de progresso das três fases.
 */
void drawPhaseProgress() {
  const int padY = 115;
  const int padX[3] = {
    34,
    80,
    126
  };

  // Caminho entre as vitórias-régias
  display.drawLine(
    padX[0] + 10,
    padY,
    padX[1] - 10,
    padY,
    TFT_WHITE
  );

  display.drawLine(
    padX[1] + 10,
    padY,
    padX[2] - 10,
    padY,
    TFT_WHITE
  );

  for (int i = 0; i < 3; i++) {
    int phaseNumber = i + 1;

    uint16_t padColor =
      TFT_DARKGREEN;

    uint16_t numberColor =
      TFT_WHITE;

    if (phaseNumber <= currentPhase) {
      padColor = TFT_GREEN;
      numberColor = TFT_BLACK;
    } else if (
      phaseNumber == currentPhase + 1
    ) {
      padColor = TFT_YELLOW;
      numberColor = TFT_BLACK;
    }

    display.fillCircle(
      padX[i],
      padY,
      10,
      padColor
    );

    display.fillTriangle(
      padX[i],
      padY,
      padX[i] + 10,
      padY - 5,
      padX[i] + 10,
      padY + 5,
      TFT_BLUE
    );

    display.setTextSize(1);
    display.setTextColor(
      numberColor,
      padColor
    );

    display.setCursor(
      padX[i] - 3,
      padY - 3
    );

    display.print(phaseNumber);
  }
}

// ------------------------------------------------------
// Pequenos brilhos discretos
// ------------------------------------------------------

/**
 * @brief Draws subtle animated sparkles on the phase-cleared screen.
 * | Desenha brilhos animados discretos na tela de passagem de fase.
 *
 * @param bright Uses the bright sparkle state when true. | Usa o estado brilhante quando verdadeiro.
 */
void drawPhaseClearedSparkles(bool bright) {
  uint16_t sparkleColor =
    bright
      ? TFT_YELLOW
      : nextPhaseSkyColor();

  // Brilho próximo ao sapinho
  display.drawLine(
    61,
    27,
    67,
    27,
    sparkleColor
  );

  display.drawLine(
    64,
    24,
    64,
    30,
    sparkleColor
  );

  // Brilho próximo à placa
  display.drawLine(
    151,
    78,
    157,
    78,
    sparkleColor
  );

  display.drawLine(
    154,
    75,
    154,
    81,
    sparkleColor
  );
}

// ------------------------------------------------------
// Tela completa de passagem de fase
// ------------------------------------------------------

/**
 * @brief Draws and initializes the phase-cleared transition screen.
 * | Desenha e inicializa a tela de transição de fase concluída.
 */
void showPhaseClearedScreen() {
  drawPhaseClearedBackground();

  // Título
  display.fillRoundRect(
    8,
    2,
    144,
    22,
    7,
    TFT_DARKGREEN
  );

  display.drawRoundRect(
    8,
    2,
    144,
    22,
    7,
    TFT_WHITE
  );

  String title = "FASE ";
  title += currentPhase;
  title += " CONCLUIDA!";

  display.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    title,
    8,
    1
  );

  drawPhaseClearedFrog();
  drawNextPhaseSign(true);

  // Painel de pontuação
  display.fillRoundRect(
    5,
    82,
    150,
    20,
    6,
    TFT_BLACK
  );

  display.drawRoundRect(
    5,
    82,
    150,
    20,
    6,
    TFT_WHITE
  );

  String scoreLine = "Fase: +";
  scoreLine += phaseScore;
  scoreLine += "   Total: ";
  scoreLine += totalScore;

  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    scoreLine,
    88,
    1
  );

  drawPhaseProgress();
  drawPhaseClearedSparkles(true);

  phaseClearedFrogWinking = false;
  phaseClearedSparklesBright = true;

  phaseClearedBlinkTicks = 0;
  phaseClearedNextBlinkTicks =
    random(6, 10);

  transitionTimer.resetMillis();
  phaseClearedAnimTimer.resetMillis();
}

// ------------------------------------------------------
// Animação discreta da passagem de fase
// ------------------------------------------------------

/**
 * @brief Updates the wink, arrow and sparkle animations between phases.
 * | Atualiza as animações de piscada, seta e brilhos entre as fases.
 */
void updatePhaseClearedAnimation() {
  if (
    !phaseClearedAnimTimer.intervalMillis(
      160
    )
  ) {
    return;
  }

  phaseClearedSparklesBright =
    !phaseClearedSparklesBright;

  drawPhaseClearedSparkles(
    phaseClearedSparklesBright
  );

  drawNextPhaseSign(
    phaseClearedSparklesBright
  );

  phaseClearedBlinkTicks++;

  if (!phaseClearedFrogWinking) {
    if (
      phaseClearedBlinkTicks >=
      phaseClearedNextBlinkTicks
    ) {
      phaseClearedFrogWinking = true;
      phaseClearedBlinkTicks = 0;

      drawPhaseClearedFrogEyes(true);
    }

    return;
  }

  // Aproximadamente 160 ms com o olho fechado.
  if (phaseClearedBlinkTicks >= 1) {
    phaseClearedFrogWinking = false;
    phaseClearedBlinkTicks = 0;

    drawPhaseClearedFrogEyes(false);

    phaseClearedNextBlinkTicks =
      random(6, 10);
  }
}

// ======================================================
// Fundo da tela de Game Over
// ======================================================

/**
 * @brief Draws the child-friendly Game Over landscape.
 * | Desenha o cenário infantil da tela de Game Over.
 */
void drawGameOverBackground() {
  // Céu mais escuro, mantendo o estilo da abertura.
  display.fillScreen(TFT_NAVY);

  // Nuvens discretas
  display.fillCircle(
    15,
    27,
    4,
    TFT_DARKGREY
  );

  display.fillCircle(
    21,
    24,
    6,
    TFT_DARKGREY
  );

  display.fillCircle(
    28,
    27,
    4,
    TFT_DARKGREY
  );

  display.fillCircle(
    133,
    30,
    4,
    TFT_DARKGREY
  );

  display.fillCircle(
    140,
    27,
    6,
    TFT_DARKGREY
  );

  display.fillCircle(
    147,
    30,
    4,
    TFT_DARKGREY
  );

  // Lago
  display.fillRect(
    0,
    72,
    SCREEN_W,
    SCREEN_H - 72,
    TFT_BLUE
  );

  // Margem de grama
  display.fillRect(
    0,
    68,
    SCREEN_W,
    8,
    TFT_DARKGREEN
  );

  display.drawLine(
    0,
    75,
    SCREEN_W - 1,
    75,
    TFT_GREEN
  );

  // Ondas
  display.drawLine(
    4,
    88,
    34,
    88,
    TFT_CYAN
  );

  display.drawLine(
    125,
    91,
    154,
    91,
    TFT_CYAN
  );

  display.drawLine(
    8,
    105,
    31,
    105,
    TFT_CYAN
  );

  display.drawLine(
    127,
    108,
    153,
    108,
    TFT_CYAN
  );

  // Vitória-régia esquerda
  display.fillCircle(
    18,
    97,
    9,
    TFT_DARKGREEN
  );

  display.fillTriangle(
    18,
    97,
    27,
    92,
    27,
    102,
    TFT_BLUE
  );

  // Vitória-régia direita
  display.fillCircle(
    143,
    99,
    8,
    TFT_DARKGREEN
  );

  display.fillTriangle(
    143,
    99,
    151,
    95,
    151,
    103,
    TFT_BLUE
  );
}

// ======================================================
// Olho saudável do sapo na tela de Game Over
// ======================================================

/**
 * @brief Draws the healthy Game Over frog eye and preserves its tear.
 * | Desenha o olho saudável do sapo no Game Over e preserva a lágrima.
 *
 * @param closed Closes the healthy eye when true. | Fecha o olho saudável quando verdadeiro.
 */
void drawGameOverHealthyEye(bool closed) {
  const int x = 58;
  const int y = 29;

  // Refaz a base verde do olho direito.
  display.fillCircle(
    x + 35,
    y + 12,
    10,
    TFT_GREEN
  );

  if (closed) {
    // Olho piscando.
    display.drawLine(
      x + 30,
      y + 12,
      x + 40,
      y + 12,
      TFT_BLACK
    );

    display.drawLine(
      x + 31,
      y + 13,
      x + 39,
      y + 13,
      TFT_BLACK
    );
  } else {
    // Olho aberto.
    display.fillCircle(
      x + 35,
      y + 12,
      6,
      TFT_WHITE
    );

    display.fillCircle(
      x + 34,
      y + 14,
      2,
      TFT_BLACK
    );
  }

  // Redesenha a lágrima, pois ela fica parcialmente
  // dentro da área do olho que foi restaurada.
  display.drawPixel(
    x + 39,
    y + 18,
    TFT_CYAN
  );

  display.drawLine(
    x + 40,
    y + 19,
    x + 40,
    y + 21,
    TFT_CYAN
  );

  display.drawPixel(
    x + 39,
    y + 22,
    TFT_CYAN
  );
}

// ======================================================
// Controle da piscada no Game Over
// ======================================================

/**
 * @brief Resets the randomized healthy-eye blink animation.
 * | Reinicia a animação aleatória de piscada do olho saudável.
 */
void resetGameOverBlink() {
  gameOverHealthyEyeClosed = false;

  gameOverNextBlinkMs =
    random(1800, 3400);

  gameOverBlinkStartTimer.resetMillis();
  gameOverBlinkDurationTimer.resetMillis();

  drawGameOverHealthyEye(false);
}


/**
 * @brief Updates the non-blocking healthy-eye blink on the Game Over screen.
 * | Atualiza a piscada não bloqueante do olho saudável no Game Over.
 */
void updateGameOverBlink() {
  if (!gameOverHealthyEyeClosed) {
    if (
      gameOverBlinkStartTimer.intervalMillis(
        gameOverNextBlinkMs
      )
    ) {
      gameOverHealthyEyeClosed = true;

      drawGameOverHealthyEye(true);

      gameOverBlinkDurationTimer.resetMillis();
    }

    return;
  }

  // Mantém o olho fechado por 150 ms.
  if (
    gameOverBlinkDurationTimer.intervalMillis(150)
  ) {
    gameOverHealthyEyeClosed = false;

    drawGameOverHealthyEye(false);

    gameOverNextBlinkMs =
      random(1800, 3400);

    gameOverBlinkStartTimer.resetMillis();
  }
}

// ======================================================
// Sapinho derrotado, mas com aparência infantil
// ======================================================

/**
 * @brief Draws the cute defeated frog with a bandage, tear and dizzy stars.
 * | Desenha o sapinho derrotado de forma infantil, com curativo, lágrima e estrelas.
 */
void drawDefeatedGameOverFrog() {
  const int x = 58;
  const int y = 29;

  // Sombra sobre a água
  display.fillRoundRect(
    x - 5,
    y + 41,
    54,
    7,
    4,
    TFT_DARKGREEN
  );

  // Pernas caídas
  display.fillRoundRect(
    x - 6,
    y + 31,
    19,
    9,
    4,
    TFT_DARKGREEN
  );

  display.fillRoundRect(
    x + 35,
    y + 31,
    19,
    9,
    4,
    TFT_DARKGREEN
  );

  // Corpo
  display.fillRoundRect(
    x + 5,
    y + 15,
    38,
    29,
    10,
    TFT_GREEN
  );

  // Barriga
  display.fillRoundRect(
    x + 13,
    y + 25,
    22,
    16,
    7,
    TFT_YELLOW
  );

  // Bases verdes dos olhos
  display.fillCircle(
    x + 13,
    y + 12,
    10,
    TFT_GREEN
  );

  display.fillCircle(
    x + 35,
    y + 12,
    10,
    TFT_GREEN
  );

  // Olho esquerdo semicerrado
  display.drawLine(
    x + 8,
    y + 12,
    x + 18,
    y + 12,
    TFT_BLACK
  );

  display.drawLine(
    x + 9,
    y + 13,
    x + 17,
    y + 13,
    TFT_BLACK
  );

  // Olho direito saudável, aberto inicialmente.
  drawGameOverHealthyEye(false);

  // Nariz
  display.drawPixel(
    x + 21,
    y + 23,
    TFT_DARKGREEN
  );

  display.drawPixel(
    x + 27,
    y + 23,
    TFT_DARKGREEN
  );

  // Boca triste
  display.drawLine(
    x + 17,
    y + 33,
    x + 21,
    y + 29,
    TFT_BLACK
  );

  display.drawLine(
    x + 21,
    y + 29,
    x + 27,
    y + 29,
    TFT_BLACK
  );

  display.drawLine(
    x + 27,
    y + 29,
    x + 31,
    y + 33,
    TFT_BLACK
  );

  // Bochechas discretas
  display.fillCircle(
    x + 12,
    y + 27,
    2,
    TFT_YELLOW
  );

  display.fillCircle(
    x + 37,
    y + 27,
    2,
    TFT_YELLOW
  );

  // Curativo infantil na testa
  display.fillRoundRect(
    x + 18,
    y + 7,
    13,
    6,
    2,
    TFT_WHITE
  );

  display.drawRoundRect(
    x + 18,
    y + 7,
    13,
    6,
    2,
    TFT_DARKGREY
  );

  // Detalhe central do curativo
  display.fillRect(
    x + 23,
    y + 8,
    3,
    4,
    TFT_YELLOW
  );

  // Pequenas estrelinhas de tontura
  display.drawLine(
    x - 8,
    y + 8,
    x - 2,
    y + 8,
    TFT_YELLOW
  );

  display.drawLine(
    x - 5,
    y + 5,
    x - 5,
    y + 11,
    TFT_YELLOW
  );

  display.drawLine(
    x + 48,
    y + 5,
    x + 54,
    y + 5,
    TFT_YELLOW
  );

  display.drawLine(
    x + 51,
    y + 2,
    x + 51,
    y + 8,
    TFT_YELLOW
  );
}


// ======================================================
// Complete Game Over screen | Tela completa de Game Over
// ======================================================

/**
 * @brief Draws the complete Game Over screen and initializes its blink animation.
 * | Desenha a tela completa de Game Over e inicializa sua animação de piscada.
 */
void showGameOverScreen() {
  drawGameOverBackground();

  // Painel do título
  display.fillRoundRect(
    31,
    2,
    98,
    23,
    7,
    TFT_BLACK
  );

  display.drawRoundRect(
    31,
    2,
    98,
    23,
    7,
    TFT_RED
  );

  display.setTextColor(
    TFT_RED,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    "GAME OVER",
    6,
    2
  );

  // Sapinho derrotado
  drawDefeatedGameOverFrog();

  // Painel das informações
  display.fillRoundRect(
    4,
    77,
    152,
    32,
    6,
    TFT_BLACK
  );

  display.drawRoundRect(
    4,
    77,
    152,
    32,
    6,
    TFT_WHITE
  );

  String gameOverLine1 = "Fase: ";
  gameOverLine1 += currentPhase;
  gameOverLine1 += "  Nivel: ";
  gameOverLine1 += difficultyName();

  String gameOverLine2 = "Pontos: ";
  gameOverLine2 += phaseScore;
  gameOverLine2 += "  Total: ";
  gameOverLine2 += totalScore;

  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    gameOverLine1,
    82,
    1
  );

  display.drawCentreScreenString(
    gameOverLine2,
    95,
    1
  );

  // Mensagem positiva para o público infantil
  display.fillRoundRect(
    37,
    111,
    86,
    15,
    5,
    TFT_DARKGREEN
  );

  display.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    "CENTRO: TENTAR DE NOVO",
    115,
    1
  );
  resetGameOverBlink();
}

// ======================================================
// Victory screen | Tela de vitória
// ======================================================

// Estado das animações da tela de vitória.
bool victoryFrogWinking = false;
bool victorySparklesBright = true;

int victoryBlinkTicks = 0;
int victoryNextBlinkTicks = 20;

// ------------------------------------------------------
// Fundo comemorativo
// ------------------------------------------------------

/**
 * @brief Draws the bright celebratory victory landscape.
 * | Desenha o cenário claro e comemorativo da vitória.
 */
void drawVictoryBackground() {
  // Céu claro
  display.fillScreen(TFT_CYAN);

  // Lago
  display.fillRect(
    0,
    72,
    SCREEN_W,
    SCREEN_H - 72,
    TFT_BLUE
  );

  // Margem de grama
  display.fillRect(
    0,
    68,
    SCREEN_W,
    9,
    TFT_GREEN
  );

  display.drawLine(
    0,
    76,
    SCREEN_W - 1,
    76,
    TFT_DARKGREEN
  );

  // Ondas
  display.drawLine(5, 89, 34, 89, TFT_WHITE);
  display.drawLine(125, 91, 154, 91, TFT_WHITE);
  display.drawLine(8, 105, 34, 105, TFT_CYAN);
  display.drawLine(126, 107, 153, 107, TFT_CYAN);

  // Vitórias-régias
  display.fillCircle(
    18,
    98,
    9,
    TFT_GREEN
  );

  display.fillTriangle(
    18,
    98,
    27,
    93,
    27,
    103,
    TFT_BLUE
  );

  display.fillCircle(
    143,
    99,
    8,
    TFT_DARKGREEN
  );

  display.fillTriangle(
    143,
    99,
    151,
    95,
    151,
    103,
    TFT_BLUE
  );
}

// ------------------------------------------------------
// Olhos do sapo vencedor
// ------------------------------------------------------

/**
 * @brief Draws the winner frog eyes in open or winking state.
 * | Desenha os olhos do sapo vencedor abertos ou piscando.
 *
 * @param winking Draws the wink when true. | Desenha a piscada quando verdadeiro.
 */
void drawVictoryFrogEyes(bool winking) {
  const int x = 58;
  const int y = 30;

  // Bases verdes
  display.fillCircle(
    x + 13,
    y + 13,
    10,
    TFT_GREEN
  );

  display.fillCircle(
    x + 35,
    y + 13,
    10,
    TFT_GREEN
  );

  if (winking) {
    // Olho esquerdo piscando
    display.drawLine(
      x + 8,
      y + 13,
      x + 18,
      y + 13,
      TFT_BLACK
    );

    display.drawLine(
      x + 9,
      y + 14,
      x + 17,
      y + 14,
      TFT_BLACK
    );
  } else {
    // Olho esquerdo aberto
    display.fillCircle(
      x + 13,
      y + 12,
      6,
      TFT_WHITE
    );

    display.fillCircle(
      x + 14,
      y + 13,
      2,
      TFT_BLACK
    );
  }

  // Olho direito sempre aberto
  display.fillCircle(
    x + 35,
    y + 12,
    6,
    TFT_WHITE
  );

  display.fillCircle(
    x + 34,
    y + 13,
    2,
    TFT_BLACK
  );
}

// ------------------------------------------------------
// Sapinho vencedor
// ------------------------------------------------------

/**
 * @brief Draws the crowned winner frog with raised arms and medal.
 * | Desenha o sapo vencedor com coroa, braços levantados e medalha.
 */
void drawVictoryFrog() {
  const int x = 58;
  const int y = 30;

  // Sombra sobre a água
  display.fillRoundRect(
    x - 6,
    y + 42,
    56,
    7,
    4,
    TFT_DARKGREEN
  );

  // Pernas
  display.fillRoundRect(
    x - 6,
    y + 32,
    19,
    10,
    4,
    TFT_DARKGREEN
  );

  display.fillRoundRect(
    x + 35,
    y + 32,
    19,
    10,
    4,
    TFT_DARKGREEN
  );

  // Braços levantados
  display.fillRoundRect(
    x + 1,
    y + 18,
    7,
    18,
    3,
    TFT_GREEN
  );

  display.fillRoundRect(
    x + 40,
    y + 18,
    7,
    18,
    3,
    TFT_GREEN
  );

  // Corpo
  display.fillRoundRect(
    x + 5,
    y + 15,
    38,
    30,
    10,
    TFT_GREEN
  );

  // Barriga
  display.fillRoundRect(
    x + 13,
    y + 25,
    22,
    17,
    7,
    TFT_YELLOW
  );

  drawVictoryFrogEyes(false);

  // Nariz
  display.drawPixel(
    x + 21,
    y + 23,
    TFT_DARKGREEN
  );

  display.drawPixel(
    x + 27,
    y + 23,
    TFT_DARKGREEN
  );

  // Sorriso aberto
  display.drawLine(
    x + 17,
    y + 29,
    x + 21,
    y + 33,
    TFT_BLACK
  );

  display.drawLine(
    x + 21,
    y + 33,
    x + 27,
    y + 33,
    TFT_BLACK
  );

  display.drawLine(
    x + 27,
    y + 33,
    x + 31,
    y + 29,
    TFT_BLACK
  );

  display.fillRect(
    x + 22,
    y + 33,
    5,
    2,
    TFT_RED
  );

  // Bochechas
  display.fillCircle(
    x + 12,
    y + 27,
    2,
    TFT_YELLOW
  );

  display.fillCircle(
    x + 37,
    y + 27,
    2,
    TFT_YELLOW
  );

  // Coroa
  display.fillRect(
    x + 16,
    y + 4,
    17,
    6,
    TFT_YELLOW
  );

  display.fillTriangle(
    x + 16,
    y + 4,
    x + 20,
    y - 2,
    x + 23,
    y + 4,
    TFT_YELLOW
  );

  display.fillTriangle(
    x + 21,
    y + 4,
    x + 25,
    y - 4,
    x + 28,
    y + 4,
    TFT_YELLOW
  );

  display.fillTriangle(
    x + 27,
    y + 4,
    x + 31,
    y - 2,
    x + 33,
    y + 4,
    TFT_YELLOW
  );

  display.drawLine(
    x + 16,
    y + 9,
    x + 32,
    y + 9,
    TFT_ORANGE
  );

  // Medalha na barriga
  display.fillCircle(
    x + 24,
    y + 33,
    4,
    TFT_ORANGE
  );

  display.drawPixel(
    x + 24,
    y + 33,
    TFT_WHITE
  );
}

// ------------------------------------------------------
// Estrelinhas ao redor do sapo
// ------------------------------------------------------

/**
 * @brief Draws the animated stars around the winner frog.
 * | Desenha as estrelas animadas ao redor do sapo vencedor.
 *
 * @param bright Uses the bright star state when true. | Usa o estado brilhante quando verdadeiro.
 */
void drawVictorySparkles(bool bright) {
  uint16_t color =
    bright ? TFT_YELLOW : TFT_CYAN;

  // Esquerda
  display.drawLine(45, 39, 51, 39, color);
  display.drawLine(48, 36, 48, 42, color);

  display.drawLine(39, 57, 45, 57, color);
  display.drawLine(42, 54, 42, 60, color);

  // Direita
  display.drawLine(109, 40, 115, 40, color);
  display.drawLine(112, 37, 112, 43, color);

  display.drawLine(116, 58, 122, 58, color);
  display.drawLine(119, 55, 119, 61, color);
}

// ------------------------------------------------------
// Painéis e textos da vitória
// ------------------------------------------------------

/**
 * @brief Draws protected title, score and menu labels on the victory screen.
 * | Desenha título, pontuação e instrução protegidos na tela de vitória.
 *
 * @note The labels are redrawn after confetti updates so particles never erase the text. | As legendas são redesenhadas após os confetes para que as partículas não apaguem o texto.
 */
void drawVictoryLabels() {
  // Painel do título
  display.fillRoundRect(
    15,
    2,
    130,
    24,
    7,
    TFT_DARKGREEN
  );

  display.drawRoundRect(
    15,
    2,
    130,
    24,
    7,
    TFT_YELLOW
  );

  display.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    "VOCE VENCEU!",
    6,
    2
  );

  // Painel das informações
  display.fillRoundRect(
    4,
    79,
    152,
    30,
    6,
    TFT_BLACK
  );

  display.drawRoundRect(
    4,
    79,
    152,
    30,
    6,
    TFT_WHITE
  );

  String victoryLine1 = "Nivel: ";
  victoryLine1 += difficultyName();

  String victoryLine2 = "Pontuacao total: ";
  victoryLine2 += totalScore;

  display.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  display.drawCentreScreenString(
    victoryLine1,
    84,
    1
  );

  display.drawCentreScreenString(
    victoryLine2,
    97,
    1
  );

  // Botão de retorno
  display.fillRoundRect(
    2,
    111,
    156,
    15,
    5,
    TFT_DARKGREEN
  );

  display.drawRoundRect(
    2,
    111,
    156,
    15,
    5,
    TFT_YELLOW
  );

  display.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREEN
  );

  display.drawCentreScreenString(
    "CENTRO: VOLTAR AO MENU",
    115,
    1
  );
}

// ------------------------------------------------------
// Confetes laterais
// ------------------------------------------------------

/**
 * @brief Creates randomized confetti particles restricted to the side areas.
 * | Cria partículas aleatórias de confete limitadas às áreas laterais.
 */
void generateConfetti() {
  const uint16_t colors[] = {
    TFT_RED,
    TFT_YELLOW,
    TFT_MAGENTA,
    TFT_GREEN,
    TFT_WHITE,
    TFT_ORANGE
  };

  for (int i = 0; i < CONFETTI_COUNT; i++) {
    bool leftSide =
      random(2) == 0;

    if (leftSide) {
      confetti[i].x =
        random(3, 40);
    } else {
      confetti[i].x =
        random(120, 157);
    }

    // Os confetes ficam somente na área do céu.
    // Assim, nunca passam sobre títulos ou informações.
    confetti[i].y =
      random(29, 68);

    confetti[i].speed =
      random(2, 5);

    confetti[i].color =
      colors[random(0, 6)];
  }
}

/**
 * @brief Erases the current confetti particles before moving them.
 * | Apaga as partículas atuais de confete antes de movimentá-las.
 */
void eraseConfetti() {
  for (int i = 0; i < CONFETTI_COUNT; i++) {
    display.fillRect(
      confetti[i].x,
      confetti[i].y,
      2,
      3,
      TFT_CYAN
    );
  }
}

/**
 * @brief Draws all current victory confetti particles.
 * | Desenha todas as partículas atuais de confete da vitória.
 */
void drawConfetti() {
  for (int i = 0; i < CONFETTI_COUNT; i++) {
    display.fillRect(
      confetti[i].x,
      confetti[i].y,
      2,
      3,
      confetti[i].color
    );
  }
}

/**
 * @brief Moves confetti downward and recycles particles at the top.
 * | Move os confetes para baixo e reaproveita as partículas no topo.
 */
void moveConfetti() {
  for (int i = 0; i < CONFETTI_COUNT; i++) {
    confetti[i].y +=
      confetti[i].speed;

    if (confetti[i].y > 68) {
      confetti[i].y = 29;

      bool leftSide =
        random(2) == 0;

      if (leftSide) {
        confetti[i].x =
          random(3, 40);
      } else {
        confetti[i].x =
          random(120, 157);
      }
    }
  }
}

// ------------------------------------------------------
// Abre a tela de vitória
// ------------------------------------------------------

/**
 * @brief Draws the final celebration, initializes animation state and plays the melody.
 * | Desenha a comemoração final, inicializa as animações e reproduz a melodia.
 */
void showVictoryScreen() {
  drawVictoryBackground();
  drawVictoryFrog();
  drawVictorySparkles(true);
  drawVictoryLabels();

  generateConfetti();
  drawConfetti();

  victoryFrogWinking = false;
  victorySparklesBright = true;

  victoryBlinkTicks = 0;
  victoryNextBlinkTicks =
    random(16, 29);

  confettiVisible = true;

  // A tela aparece antes da melodia.
  playVictoryMelody();

  confettiTimer.resetMillis();
}

// ------------------------------------------------------
// Atualiza confetes, estrelinhas e piscada
// ------------------------------------------------------

/**
 * @brief Updates confetti, sparkles and the winner frog wink.
 * | Atualiza confetes, brilhos e a piscada do sapo vencedor.
 */
void updateVictoryConfetti() {
  if (
    !confettiTimer.intervalMillis(120)
  ) {
    return;
  }

  eraseConfetti();
  moveConfetti();
  drawConfetti();

  // Faz as estrelinhas brilharem.
  victorySparklesBright =
    !victorySparklesBright;

  drawVictorySparkles(
    victorySparklesBright
  );

  // Controla a piscada do sapinho vencedor.
  victoryBlinkTicks++;

  if (!victoryFrogWinking) {
    if (
      victoryBlinkTicks >=
      victoryNextBlinkTicks
    ) {
      victoryFrogWinking = true;
      victoryBlinkTicks = 0;

      drawVictoryFrogEyes(true);
    }

    return;
  }

  // Aproximadamente 240 ms com o olho fechado.
  if (victoryBlinkTicks >= 2) {
    victoryFrogWinking = false;
    victoryBlinkTicks = 0;

    drawVictoryFrogEyes(false);

    victoryNextBlinkTicks =
      random(16, 29);
  }
}

// ======================================================
// Dynamic-object rendering | Desenho dos objetos móveis
// ======================================================

/**
 * @brief Draws all moving gameplay objects and updates the HUD when required.
 * | Desenha todos os objetos móveis e atualiza o HUD quando necessário.
 */
void drawAllDynamicObjects() {
  // Repara decorações que possam ter sido
  // atravessadas pelos objetos móveis.
  drawPhaseDecoration();

  for (int i = 0; i < FLY_COUNT; i++) {
    drawFly(flies[i]);
  }

  int crocodileCount =
    activeCrocodileCount();

  for (
    int i = 0;
    i < crocodileCount;
    i++
  ) {
    drawCrocodile(crocodiles[i]);
  }

  drawFrog();

  if (tongueFrames > 0) {
    drawTongue();

    tongueWasDrawn = true;
    tongueFrames--;
  }

  if (hudDirty) {
    drawHUD();
  }
}

// ======================================================
// Phase flow control | Controle das fases
// ======================================================

/**
 * @brief Resets phase state, prepares objects and starts gameplay.
 * | Reinicia o estado da fase, prepara os objetos e inicia a partida.
 */
void startPhase() {
  phaseScore = 0;
  timeLeft = PHASE_SECONDS;

  frogX = 72;
  frogY = FROG_GROUND_Y;

  jumpVelocity = 0;
  jumping = false;

  tongueFrames = 0;
  tongueWasDrawn = false;

  crocodileMouthOpen = false;

  prepareObjects();

  frameTimer.resetMillis();
  secondTimer.resetMillis();
  crocodileMouthTimer.resetMillis();

  gameState = PLAYING;

  drawStaticScene();
  drawAllDynamicObjects();
}

/**
 * @brief Resets the campaign to phase one and starts a new game.
 * | Reinicia a campanha na primeira fase e começa um novo jogo.
 */
void startNewGame() {
  currentPhase = 1;
  totalScore = 0;

  startPhase();
}

/**
 * @brief Evaluates the phase score and routes to Game Over, transition or victory.
 * | Avalia a pontuação da fase e direciona para Game Over, transição ou vitória.
 */
void finishPhase() {
  if (phaseScore <= 0) {
    gameState = GAME_OVER;
    showGameOverScreen();

    return;
  }

  totalScore += phaseScore;

  if (currentPhase >= 3) {
    gameState = VICTORY;
    showVictoryScreen();

    return;
  }

  gameState = PHASE_CLEARED;
  showPhaseClearedScreen();
}

/**
 * @brief Performs one complete non-blocking gameplay frame.
 * | Executa um quadro completo e não bloqueante da partida.
 */
void updatePlayingFrame() {
  // Apaga somente os objetos antigos.
  eraseDynamicObjects();

  readControls();
  updateJump();
  updateObjects();
  updateCrocodileMouth();

  checkFlies();
  checkCrocodiles();

  drawAllDynamicObjects();
}

// ======================================================
// Arduino setup | Configuração inicial
// ======================================================

/**
 * @brief Initializes Serial, random seed, buzzer, display and opening menu.
 * | Inicializa Serial, semente aleatória, buzzer, display e menu inicial.
 */
void setup() {
  Serial.begin(115200);

  Serial.print("ES32Lab LIB: ");
  Serial.println(ES32LAB_VERSION);

  randomSeed(
    analogRead(P_POT1)
  );

  buzzer.begin();
  buzzer.setVolume(55);

  display.init();
  display.setRotation(3);
  display.fillScreen(TFT_BLACK);

  openDifficultyMenu();
}

// ======================================================
// Arduino loop | Laço principal
// ======================================================

/**
 * @brief Runs the main game state machine.
 * | Executa a máquina de estados principal do jogo.
 */
void loop() {
  if (gameState == DIFFICULTY_MENU) {
    updateDifficultyMenu();

    if (keyboard.press(KEY_CENTER)) {
      startNewGame();
    }

    return;
  }

  if (gameState == GAME_OVER) {
    updateGameOverBlink();

    if (keyboard.press(KEY_CENTER)) {
      openDifficultyMenu();
    }

    return;
  }

  if (gameState == PHASE_CLEARED) {
    updatePhaseClearedAnimation();

    if (
      transitionTimer.intervalMillis(
        2600
      )
    ) {
      currentPhase++;
      startPhase();
    }

    return;
  }

  if (gameState == VICTORY) {
    updateVictoryConfetti();

    if (keyboard.press(KEY_CENTER)) {
          openDifficultyMenu();
    }

    return;
  }

  if (
    secondTimer.intervalMillis(1000)
  ) {
    timeLeft--;
    hudDirty = true;

    if (timeLeft <= 0) {
      timeLeft = 0;

      drawHUD();
      finishPhase();

      return;
    }
  }

  if (
    frameTimer.intervalMillis(50)
  ) {
    updatePlayingFrame();
  }
}