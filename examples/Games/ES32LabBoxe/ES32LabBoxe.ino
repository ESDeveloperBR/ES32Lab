/**
 * @file ES32LabBoxe.ino
 * @date 2026-07-17
 * @brief Example: Complete boxing game for ES32Lab using TFT, analog keyboard, buzzer and non-blocking timers
 * | Exemplo: Jogo completo de boxe para ES32Lab usando TFT, teclado analógico, buzzer e temporizadores não bloqueantes
 *
 * ES32Lab Boxe is a didactic game created to demonstrate how a larger embedded application can be organized
 * with the official classes of the ES32Lab library. The example combines a finite-state machine, animated
 * screens, double-buffered drawing, keyboard input, sound effects, collision rules and a configurable opponent AI.
 *
 * | ES32Lab Boxe é um jogo didático criado para demonstrar como uma aplicação embarcada maior pode ser organizada
 * com as classes oficiais da biblioteca ES32Lab. O exemplo combina máquina de estados, telas animadas,
 * desenho com framebuffer, leitura do teclado, efeitos sonoros, regras de colisão e uma inteligência artificial
 * configurável para os adversários.
 *
 * Learning goals | Objetivos de aprendizagem:
 *
 * - Use ES_TFT to draw a complete graphical interface on the 160 x 128 pixel display.
 *   | Usar ES_TFT para desenhar uma interface gráfica completa no display de 160 x 128 pixels.
 * - Use TFT_eSprite as an off-screen framebuffer to avoid visible screen flicker.
 *   | Usar TFT_eSprite como framebuffer fora da tela para evitar piscadas visíveis.
 * - Use ES_AnalogKeyboard to read press and hold events from the five-key analog keyboard.
 *   | Usar ES_AnalogKeyboard para ler eventos de pressionamento e tecla mantida no teclado analógico de cinco teclas.
 * - Use ES_TimeInterval instead of manual millis() control for animation and gameplay timing.
 *   | Usar ES_TimeInterval no lugar do controle manual com millis() para animações e tempos do jogo.
 * - Use ES_Buzzer and NOTE_* constants to create short game sound effects.
 *   | Usar ES_Buzzer e as constantes NOTE_* para criar efeitos sonoros curtos.
 * - Organize a project with enums, structs, helper functions and a finite-state machine.
 *   | Organizar um projeto com enums, structs, funções auxiliares e uma máquina de estados.
 * - Study basic game concepts such as health, damage, defense, dodge, special meter and opponent AI.
 *   | Estudar conceitos básicos de jogos como energia, dano, defesa, esquiva, medidor especial e IA do adversário.
 *
 * Game flow | Fluxo do jogo:
 *
 * 1. Animated opening screen | Tela de abertura animada.
 * 2. Difficulty and sound selection | Seleção de dificuldade e som.
 * 3. Animated presentation of each opponent | Apresentação animada de cada adversário.
 * 4. Boxing match | Luta de boxe.
 * 5. Victory, Game Over or final champion animation | Vitória, Game Over ou animação final de campeão.
 *
 * Menu controls | Controles do menu:
 *
 * - UP/DOWN: select EASY, MEDIUM or HARD.
 *   | CIMA/BAIXO: seleciona FÁCIL, MÉDIO ou DIFÍCIL.
 * - LEFT/RIGHT: enable or disable sound.
 *   | ESQUERDA/DIREITA: liga ou desliga o som.
 * - CENTER: start the game.
 *   | CENTRO: inicia o jogo.
 *
 * Fight controls | Controles da luta:
 *
 * - LEFT/RIGHT: move and briefly dodge.
 *   | ESQUERDA/DIREITA: movimenta e realiza uma esquiva curta.
 * - DOWN: hold the guard.
 *   | BAIXO: mantém a defesa.
 * - CENTER: normal punch.
 *   | CENTRO: soco normal.
 * - UP: hook when the special meter is full.
 *   | CIMA: gancho quando o medidor especial estiver completo.
 *
 * Opponents | Adversários:
 *
 * - Phase 1: Sovaco de Cobra.
 *   | Fase 1: Sovaco de Cobra.
 * - Phase 2: Costela de Minhoca.
 *   | Fase 2: Costela de Minhoca.
 * - Phase 3: Pouca Tripa.
 *   | Fase 3: Pouca Tripa.
 * - Phase 4: Coice de Mula.
 *   | Fase 4: Coice de Mula.
 *
 * @warning Install the ES32Lab library and the ES Developer TFT_eSPI package before compiling.
 * | Instale a biblioteca ES32Lab e o pacote TFT_eSPI da ES Developer antes de compilar.
 *
 * PlatformIO dependencies | Dependências no PlatformIO:
 *
 *     lib_deps =
 *         esdeveloper/ES32Lab
 *         esdeveloper/TFT_eSPI_ES32Lab
 *
 * @warning Keep the TFT display and analog-keyboard jumpers correctly connected on the ES32Lab.
 * | Mantenha corretamente conectados os jumpers do display TFT e do teclado analógico na ES32Lab.
 *
 * @note The example uses approximately 40 KB for a 16-bit 160 x 128 framebuffer.
 * | O exemplo utiliza aproximadamente 40 KB para um framebuffer de 160 x 128 pixels em 16 bits.
 *
 * @note The game code intentionally avoids delay() in the gameplay loop. Timing is handled by ES_TimeInterval.
 * | O código evita delay() no laço principal da luta. As temporizações são controladas por ES_TimeInterval.
 *
 * @author Ricardo Santini
 * @version 0.10
 *
 * @see ES32Lab library: https://github.com/ESDeveloperBR/ES32Lab
 * | Biblioteca ES32Lab: https://github.com/ESDeveloperBR/ES32Lab
 *
 * @see ES_TFT documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TFT#readme
 * | Documentação da ES_TFT: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TFT#readme
 *
 * @see ES_AnalogKeyboard documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_AnalogKeyboard#readme
 * | Documentação da ES_AnalogKeyboard: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_AnalogKeyboard#readme
 *
 * @see ES_TimeInterval documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TimeInterval#readme
 * | Documentação da ES_TimeInterval: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TimeInterval#readme
 *
 * @see ES_Buzzer documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
 * | Documentação da ES_Buzzer: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
 *
 * @see Official board and kits: https://www.esdeveloper.com.br
 * | Placa e kits oficiais: https://www.esdeveloper.com.br
 */

#include <Arduino.h>  // Arduino framework | Framework Arduino
#include <ES32Lab.h>  // Official ES32Lab library | Biblioteca oficial ES32Lab
#include <TFT_eSPI.h> // TFT_eSprite framebuffer from the ES Developer TFT package | Framebuffer TFT_eSprite do pacote TFT da ES Developer

// ------------------------------------------------------
// Official ES32Lab resources | Recursos oficiais da ES32Lab
// ------------------------------------------------------

ES_TFT display; // TFT display object | Objeto do display TFT
ES_AnalogKeyboard keyboard(P_KEYBOARD, 20); // Five-key analog keyboard | Teclado analógico de cinco teclas
ES_Buzzer buzzer(P_BUZZER); // Onboard buzzer object | Objeto do buzzer onboard
TFT_eSprite canvas(&display); // Off-screen framebuffer used to prevent flicker | Framebuffer fora da tela usado para evitar piscadas

// ------------------------------------------------------
// Non-blocking timers | Temporizadores não bloqueantes
// ------------------------------------------------------

/**
 * @note Each timer has one responsibility. Keeping separate timers avoids one animation or action resetting another.
 * | Cada temporizador possui uma responsabilidade. Usar temporizadores separados impede que uma animação reinicie o tempo de outra ação.
 */
ES_TimeInterval openingTimer;
ES_TimeInterval frameTimer;
ES_TimeInterval enemyDecisionTimer;
ES_TimeInterval enemyReactionTimer;
ES_TimeInterval playerImpactTimer;
ES_TimeInterval playerActionTimer;
ES_TimeInterval enemyImpactTimer;
ES_TimeInterval enemyActionTimer;
ES_TimeInterval playerDodgeTimer;
ES_TimeInterval enemyDodgeTimer;
ES_TimeInterval enemyDefenseTimer;
ES_TimeInterval inputMinimumTimer;
ES_TimeInterval inputReleaseTimer;
ES_TimeInterval portraitTimer;
ES_TimeInterval victoryTimer;
ES_TimeInterval championTimer;
ES_TimeInterval gameOverTimer;

// ------------------------------------------------------
// Display geometry and animation rates | Geometria do display e taxas de animação
// ------------------------------------------------------

constexpr int SCREEN_W = 160;
constexpr int SCREEN_H = 128;
constexpr int HUD_H = 29;
constexpr int SLOT_COUNT = 5;

const int SLOT_X[SLOT_COUNT] = {30, 55, 80, 105, 130};

constexpr unsigned long FRAME_MS = 40; // 25 gameplay frames per second | 25 quadros de jogo por segundo
constexpr unsigned long OPENING_FRAME_MS = 45; // Opening animation step | Passo da animação de abertura
constexpr unsigned long PORTRAIT_FRAME_MS = 120;
constexpr unsigned long VICTORY_FRAME_MS = 90;
constexpr unsigned long CHAMPION_FRAME_MS = 70;
constexpr unsigned long GAME_OVER_FRAME_MS = 90;
constexpr int OPENING_TOTAL_FRAMES = 100;

constexpr char GAME_VERSION[] = "v0.10";
constexpr char GAME_AUTHOR[] = "By Ricardo Santini";

bool canvasReady = false;

// ------------------------------------------------------
// Input protection between screens | Proteção de entrada entre telas
// ------------------------------------------------------

constexpr unsigned long OPENING_WAIT_MIN_MS = 350;
constexpr unsigned long MENU_MIN_MS = 500;
constexpr unsigned long INTRO_MIN_MS = 2400;
constexpr unsigned long VICTORY_MIN_MS = 3800;
constexpr unsigned long GAME_OVER_MIN_MS = 4800;
constexpr unsigned long CHAMPION_MIN_MS = 6500;
constexpr unsigned long FIGHT_LOCK_MS = 300;
constexpr unsigned long KEY_RELEASE_MS = 180;

bool inputArmed = false;
bool inputMinimumElapsed = false;
bool inputReleaseStable = false;

// ------------------------------------------------------
// Player combat constants | Constantes de combate do jogador
// ------------------------------------------------------

constexpr int PLAYER_MAX_HEALTH = 100;
constexpr int PLAYER_PUNCH_DAMAGE = 6;
constexpr int PLAYER_PUNCH_BLOCKED_DAMAGE = 2;
constexpr int PLAYER_HOOK_DAMAGE = 16;
constexpr int PLAYER_HOOK_BLOCKED_DAMAGE = 5;

constexpr unsigned long PLAYER_PUNCH_IMPACT_MS = 145;
constexpr unsigned long PLAYER_PUNCH_TOTAL_MS = 420;
constexpr unsigned long PLAYER_HOOK_IMPACT_MS = 270;
constexpr unsigned long PLAYER_HOOK_TOTAL_MS = 780;

constexpr int HOOK_READY_POINTS = 8; // Four clean punches fill the meter | Quatro socos limpos completam o medidor
constexpr int CLEAN_HIT_POINTS = 2;
constexpr int BLOCKED_HIT_POINTS = 1;

// A clean hook keeps the opponent in a special recoil pose for several
// gameplay frames. At 25 frames per second, 12 frames last about 480 ms.
// | Um gancho limpo mantém o adversário em uma pose especial de recuo por
// | vários quadros. A 25 quadros por segundo, 12 quadros duram cerca de 480 ms.
constexpr int ENEMY_HOOK_REACTION_TOTAL_FRAMES = 12;

// ------------------------------------------------------
// Opponent phase configuration | Configuração das fases e adversários
// ------------------------------------------------------

constexpr int TOTAL_PHASES = 4; // Number of opponents in the challenge | Quantidade de adversários no desafio

/**
 * @brief Selects the visual identity used to draw each opponent.
 * | Seleciona a identidade visual usada para desenhar cada adversário.
 */
enum EnemyVisualStyle {
  STYLE_MOHAWK,
  STYLE_BALD_HEADBAND,
  STYLE_HAIR_MOUSTACHE,
  STYLE_BOSS_BEARD
};

/**
 * @brief Groups balance, timing and appearance parameters for one opponent.
 * | Agrupa parâmetros de equilíbrio, tempo e aparência de um adversário.
 *
 * Keeping these values in a struct allows new phases to be created without duplicating combat logic.
 * | Manter estes valores em uma struct permite criar novas fases sem duplicar a lógica de combate.
 */
struct PhaseConfig {
  const char* name;
  const char* shortName;
  const char* description;

  uint16_t bodyColor;
  uint16_t gloveColor;
  uint16_t skinColor;

  EnemyVisualStyle visualStyle;

  int bodyWidth;
  int bodyHeight;
  int headRadius;

  int health;
  int punchDamage;
  int punchBlockedDamage;
  int hookDamage;
  int hookBlockedDamage;

  unsigned long decisionMs;
  unsigned long punchImpactMs;
  unsigned long punchTotalMs;
  unsigned long hookImpactMs;
  unsigned long hookTotalMs;
  unsigned long dodgeMs;
  unsigned long defenseMs;

  int reactionChance;
  unsigned long reactionMs;
  int approachChance;
  int attackChance;
  int defenseChance;
};

/**
 * @brief Balance table for all four opponents.
 * | Tabela de balanceamento dos quatro adversários.
 *
 * Students can safely experiment with health, damage and timing values here before changing the combat engine.
 * | Alunos podem experimentar os valores de energia, dano e tempo nesta tabela antes de alterar o motor de combate.
 */
const PhaseConfig PHASES[TOTAL_PHASES] = {
  {
    "SOVACO DE COBRA",
    "SOVACO",
    "Escorregadio e insistente",
    TFT_GREEN,
    TFT_RED,
    TFT_ORANGE,
    STYLE_MOHAWK,
    17,
    21,
    7,
    78,
    4,
    1,
    0,
    0,
    880,
    215,
    550,
    420,
    980,
    180,
    360,
    3,
    240,
    76,
    42,
    10
  },
  {
    "COSTELA DE MINHOCA",
    "COSTELA",
    "Fino, movel e traicoeiro",
    TFT_CYAN,
    TFT_MAGENTA,
    TFT_YELLOW,
    STYLE_BALD_HEADBAND,
    14,
    24,
    7,
    92,
    5,
    1,
    10,
    3,
    710,
    185,
    480,
    370,
    900,
    220,
    440,
    13,
    185,
    82,
    51,
    17
  },
  {
    "POUCA TRIPA",
    "TRIPA",
    "Rapido e muito defensivo",
    TFT_ORANGE,
    TFT_BLUE,
    TFT_ORANGE,
    STYLE_HAIR_MOUSTACHE,
    20,
    22,
    8,
    112,
    7,
    2,
    14,
    4,
    535,
    150,
    420,
    295,
    780,
    260,
    540,
    30,
    108,
    88,
    63,
    24
  },
  {
    "COICE DE MULA",
    "COICE",
    "Golpes pesados de chefao",
    TFT_RED,
    TFT_MAGENTA,
    TFT_YELLOW,
    STYLE_BOSS_BEARD,
    26,
    25,
    9,
    138,
    9,
    3,
    18,
    6,
    390,
    120,
    350,
    245,
    670,
    300,
    650,
    48,
    72,
    94,
    75,
    29
  }
};

// ------------------------------------------------------
// Difficulty profiles | Perfis de dificuldade
// ------------------------------------------------------

/**
 * @brief Available difficulty levels selected before the first fight.
 * | Níveis de dificuldade disponíveis antes da primeira luta.
 */
enum Difficulty {
  EASY,
  MEDIUM,
  HARD
};

/**
 * @brief Stores multipliers and bonuses applied on top of each phase configuration.
 * | Armazena multiplicadores e bônus aplicados sobre a configuração de cada fase.
 */
struct DifficultyConfig {
  const char* name;
  const char* description;
  uint16_t color;

  int healthPercentage;
  int damagePercentage;
  int decisionTimePercentage;
  int attackTimePercentage;

  int reactionBonus;
  int dodgeBonus;
  int defenseBonus;
  int hookBonus;
  int comboChance;

  unsigned long playerDodgeMs;
};

/**
 * @brief Multipliers that transform the same four phases into easy, medium and hard modes.
 * | Multiplicadores que transformam as mesmas quatro fases nos modos fácil, médio e difícil.
 */
const DifficultyConfig DIFFICULTIES[3] = {
  {
    "FACIL",
    "Mais tempo para aprender",
    TFT_GREEN,
    75,
    70,
    145,
    125,
    -15,
    -12,
    -10,
    -15,
    0,
    280
  },
  {
    "MEDIO",
    "A dificuldade original",
    TFT_YELLOW,
    100,
    100,
    100,
    100,
    0,
    0,
    0,
    0,
    0,
    215
  },
  {
    "DIFICIL",
    "Pressao do inicio ao fim",
    TFT_RED,
    125,
    130,
    68,
    84,
    24,
    16,
    15,
    20,
    25,
    175
  }
};

// ------------------------------------------------------
// Game states and action states | Estados do jogo e das ações
// ------------------------------------------------------

/**
 * @brief Finite-state-machine states used by loop() to select the active screen.
 * | Estados da máquina de estados usados por loop() para selecionar a tela ativa.
 */
enum GameState {
  OPENING,
  DIFFICULTY_MENU,
  PHASE_INTRO,
  PLAYING,
  PHASE_VICTORY,
  GAME_OVER,
  CHAMPION_SCREEN
};

/**
 * @brief Describes which attack animation is currently active.
 * | Descreve qual animação de ataque está ativa.
 */
enum AttackAction {
  ATTACK_NONE,
  ATTACK_PUNCH,
  ATTACK_HOOK
};

/**
 * @brief Identifies the left or right hand selected for a punch.
 * | Identifica a mão esquerda ou direita escolhida para o golpe.
 */
enum PunchHand {
  HAND_LEFT,
  HAND_RIGHT
};

/**
 * @brief Reaction that the AI may schedule after detecting a player attack.
 * | Reação que a IA pode agendar após detectar um ataque do jogador.
 */
enum EnemyReaction {
  REACTION_NONE,
  REACTION_DODGE,
  REACTION_DEFEND
};

GameState gameState = OPENING;
Difficulty selectedDifficulty = EASY;

AttackAction playerAction = ATTACK_NONE;
AttackAction enemyAction = ATTACK_NONE;

PunchHand playerHand = HAND_LEFT;
PunchHand enemyHand = HAND_RIGHT;

EnemyReaction enemyReaction = REACTION_NONE;

// ------------------------------------------------------
// Sound option | Opção de som
// ------------------------------------------------------

bool soundEnabled = true; // Global sound preference | Preferência global de som

// ------------------------------------------------------
// Runtime game data | Dados da partida em execução
// ------------------------------------------------------

int openingFrame = 0;
int portraitFrame = 0;
int victoryFrame = 0;
int championFrame = 0;
int gameOverFrame = 0;
bool openingFinished = false;
bool openingWhooshPlayed = false;
bool openingImpactPlayed = false;
bool openingTitlePlayed = false;

int currentPhase = 1;

int playerHealth = PLAYER_MAX_HEALTH;
int enemyHealth = PHASES[0].health;
int enemyMaxHealth = PHASES[0].health;

int playerSlot = 2;
int enemySlot = 2;

int playerHookPoints = 0;
int enemyHookPoints = 0;

bool playerDefending = false;
bool enemyDefending = false;
bool playerDodging = false;
bool enemyDodging = false;
bool playerAttackResolved = false;
bool enemyAttackResolved = false;
bool playerAlternateLeft = true;
bool enemyAlternateLeft = false;
bool enemyReactionPending = false;

int playerFlashFrames = 0;
int enemyFlashFrames = 0;

// Strong-hit animation state. The direction indicates to which side the
// opponent's upper body is thrown after receiving a clean hook.
// | Estado da animação de golpe forte. A direção indica para qual lado o
// | tronco do adversário será lançado após receber um gancho limpo.
int enemyHookReactionFrames = 0;
int enemyHookReactionDirection = 1;

// A knockout caused by a hook is delayed until the recoil animation ends.
// This allows the student to see the difference even on the final hit.
// | Um nocaute causado por gancho é adiado até o fim da animação de recuo.
// | Assim, a diferença também aparece quando o gancho é o golpe final.
bool enemyKnockoutPending = false;

// ------------------------------------------------------
// Forward declarations | Protótipos de funções
// ------------------------------------------------------

void startOpening();
void showDifficultyMenu();
void preparePhase();
void beginFight();
void drawFight();
void finishEnemyKnockout();
void finishPlayerKnockout();
void startEnemyAttack(AttackAction attack);

// ======================================================
// Current phase and difficulty helpers | Auxiliares da fase e dificuldade atuais
// ======================================================

/**
 * @brief Returns the current phase as a zero-based array index.
 * | Retorna a fase atual como índice de vetor iniciado em zero.
 */
int phaseIndex() {
  return constrain(currentPhase - 1, 0, TOTAL_PHASES - 1);
}

/**
 * @brief Returns the configuration of the active opponent.
 * | Retorna a configuração do adversário ativo.
 */
const PhaseConfig& phase() {
  return PHASES[phaseIndex()];
}

/**
 * @brief Returns the currently selected difficulty profile.
 * | Retorna o perfil de dificuldade selecionado.
 */
const DifficultyConfig& difficulty() {
  return DIFFICULTIES[static_cast<int>(selectedDifficulty)];
}

/**
 * @brief Scales an integer by a percentage using rounded arithmetic.
 * | Aplica uma porcentagem a um inteiro usando arredondamento.
 */
int scaledInt(int value, int percentage) {
  return (value * percentage + 50) / 100;
}

/**
 * @brief Scales a time value by a percentage.
 * | Aplica uma porcentagem a um valor de tempo.
 */
unsigned long scaledTime(unsigned long value, int percentage) {
  return (value * static_cast<unsigned long>(percentage)) / 100UL;
}

// ======================================================
// Screen and framebuffer helpers | Auxiliares de tela e framebuffer
// ======================================================

/**
 * @brief Clears every pixel of the off-screen framebuffer.
 * | Limpa todos os pixels do framebuffer fora da tela.
 */
void clearCanvas(uint16_t color = TFT_BLACK) {
  if (!canvasReady) {
    return;
  }

  // fillSprite limpa a memoria inteira do sprite, sem depender
  // de viewport ou da area desenhada no quadro anterior.
  canvas.fillSprite(color);
}

/**
 * @brief Transfers the completed framebuffer to the physical TFT.
 * | Transfere o framebuffer concluído para o TFT físico.
 */
void presentCanvas() {
  if (!canvasReady) {
    return;
  }

  canvas.pushSprite(0, 0);
}

/**
 * @brief Clears both the physical display and the framebuffer during screen transitions.
 * | Limpa o display físico e o framebuffer durante as transições de tela.
 */
void hardClearScreen(uint16_t color = TFT_BLACK) {
  display.fillScreen(color);

  if (!canvasReady) {
    return;
  }

  canvas.fillSprite(color);
  canvas.pushSprite(0, 0);
}

/**
 * @brief Prints text approximately centered on the 160-pixel-wide screen.
 * | Imprime um texto aproximadamente centralizado na tela de 160 pixels.
 */
void centeredText(
  const String& text,
  int y,
  uint8_t size,
  uint16_t color,
  uint16_t background = TFT_BLACK
) {
  int textWidth = static_cast<int>(text.length()) * 6 * size;
  int x = (SCREEN_W - textWidth) / 2;

  if (x < 0) {
    x = 0;
  }

  canvas.setTextSize(size);
  canvas.setTextColor(color, background);
  canvas.setCursor(x, y);
  canvas.print(text);
}

// ======================================================
// Protection against accidental key presses | Proteção contra cliques acidentais
// ======================================================

/**
 * @brief Checks whether any analog-keyboard key remains held.
 * | Verifica se alguma tecla do teclado analógico continua pressionada.
 */
bool anyKeyHeld() {
  return
    keyboard.hold(KEY_CENTER) ||
    keyboard.hold(KEY_UP) ||
    keyboard.hold(KEY_RIGHT) ||
    keyboard.hold(KEY_DOWN) ||
    keyboard.hold(KEY_LEFT);
}

/**
 * @brief Detects a new press event from any keyboard key.
 * | Detecta um novo evento de pressionamento em qualquer tecla.
 */
bool anyKeyPressed() {
  return
    keyboard.press(KEY_CENTER) ||
    keyboard.press(KEY_UP) ||
    keyboard.press(KEY_RIGHT) ||
    keyboard.press(KEY_DOWN) ||
    keyboard.press(KEY_LEFT);
}

/**
 * @brief Disarms input after a screen transition to prevent accidental skipping.
 * | Desarma a entrada após uma transição para evitar avanços acidentais.
 */
void lockInput() {
  inputArmed = false;
  inputMinimumElapsed = false;
  inputReleaseStable = false;

  inputMinimumTimer.resetMillis();
  inputReleaseTimer.resetMillis();
}

/**
 * @brief Arms input only after the minimum screen time and a stable key release.
 * | Libera a entrada somente após o tempo mínimo da tela e a soltura estável das teclas.
 */
bool updateInputGate(unsigned long minimumMs) {
  if (inputArmed) {
    return false;
  }

  if (!inputMinimumElapsed) {
    if (!inputMinimumTimer.intervalMillis(minimumMs)) {
      return false;
    }

    inputMinimumElapsed = true;
  }

  if (anyKeyHeld()) {
    inputReleaseStable = false;
    inputReleaseTimer.resetMillis();
    return false;
  }

  if (!inputReleaseStable) {
    inputReleaseStable = true;
    inputReleaseTimer.resetMillis();
    return false;
  }

  if (inputReleaseTimer.intervalMillis(KEY_RELEASE_MS)) {
    inputArmed = true;
    return true;
  }

  return false;
}

// ======================================================
// Short sound effects | Efeitos sonoros curtos
// ======================================================

/**
 * @brief Checks the mute option and sets the volume before a sound effect.
 * | Verifica a opção de mudo e define o volume antes de um efeito sonoro.
 */
bool beginSound(uint8_t volume) {
  if (!soundEnabled) {
    return false;
  }

  buzzer.setVolume(volume);
  return true;
}

/**
 * @brief Plays the short sound effect for the opening start.
 * | Reproduz o efeito sonoro curto para o início da abertura.
 */
void sfxOpeningStart() {
  if (!beginSound(48)) return;
  buzzer.sound(NOTE_C4, 35);
  buzzer.sound(NOTE_G4, 45);
}

/**
 * @brief Plays the short sound effect for the opening punch movement.
 * | Reproduz o efeito sonoro curto para o movimento do soco da abertura.
 */
void sfxOpeningWhoosh() {
  if (!beginSound(40)) return;
  buzzer.sound(NOTE_G5, 24);
  buzzer.sound(NOTE_D5, 22);
}

/**
 * @brief Plays the short sound effect for the opening impact.
 * | Reproduz o efeito sonoro curto para o impacto da abertura.
 */
void sfxOpeningImpact() {
  if (!beginSound(80)) return;
  buzzer.sound(NOTE_C2, 55);
  buzzer.sound(NOTE_G2, 42);
}

/**
 * @brief Plays the short sound effect for the opening title.
 * | Reproduz o efeito sonoro curto para o título da abertura.
 */
void sfxOpeningTitle() {
  if (!beginSound(60)) return;
  buzzer.sound(NOTE_C4, 28);
  buzzer.sound(NOTE_E4, 28);
  buzzer.sound(NOTE_G4, 30);
  buzzer.sound(NOTE_C5, 55);
}

/**
 * @brief Plays the short sound effect for menu navigation.
 * | Reproduz o efeito sonoro curto para a navegação do menu.
 */
void sfxMenuMove() {
  if (!beginSound(30)) return;
  buzzer.sound(NOTE_E5, 18);
}

/**
 * @brief Plays the short sound effect for menu confirmation.
 * | Reproduz o efeito sonoro curto para a confirmação do menu.
 */
void sfxMenuConfirm() {
  if (!beginSound(52)) return;
  buzzer.sound(NOTE_C5, 24);
  buzzer.sound(NOTE_G5, 36);
}

/**
 * @brief Plays the short sound effect for the phase start.
 * | Reproduz o efeito sonoro curto para o início da fase.
 */
void sfxPhaseStart() {
  if (!beginSound(55)) return;
  buzzer.sound(NOTE_C4, 35);
  buzzer.sound(NOTE_C5, 55);
}

/**
 * @brief Plays the short sound effect for a movement step.
 * | Reproduz o efeito sonoro curto para um passo de movimento.
 */
void sfxStep() {
  if (!beginSound(20)) return;
  buzzer.sound(NOTE_G5, 18);
}

/**
 * @brief Plays the short sound effect for entering guard.
 * | Reproduz o efeito sonoro curto para a entrada em defesa.
 */
void sfxGuard() {
  if (!beginSound(35)) return;
  buzzer.sound(NOTE_E4, 28);
  buzzer.sound(NOTE_C4, 24);
}

/**
 * @brief Plays the short sound effect for a punch swing.
 * | Reproduz o efeito sonoro curto para o movimento de um soco.
 */
void sfxPunchSwing(bool enemy) {
  if (!beginSound(40)) return;

  if (enemy) {
    buzzer.sound(NOTE_D3, 30);
    buzzer.sound(NOTE_A2, 22);
  } else {
    buzzer.sound(NOTE_G4, 28);
    buzzer.sound(NOTE_D4, 20);
  }
}

/**
 * @brief Plays the short sound effect for a hook swing.
 * | Reproduz o efeito sonoro curto para o movimento de um gancho.
 */
void sfxHookSwing(bool enemy) {
  if (!beginSound(55)) return;

  if (enemy) {
    buzzer.sound(NOTE_E3, 42);
    buzzer.sound(NOTE_B2, 36);
  } else {
    buzzer.sound(NOTE_A3, 42);
    buzzer.sound(NOTE_E3, 34);
  }
}

/**
 * @brief Plays the short sound effect for a missed attack.
 * | Reproduz o efeito sonoro curto para um golpe no ar.
 */
void sfxMiss() {
  if (!beginSound(22)) return;
  buzzer.sound(NOTE_FS5, 18);
  buzzer.sound(NOTE_D5, 16);
}

/**
 * @brief Plays the short sound effect for a successful dodge.
 * | Reproduz o efeito sonoro curto para uma esquiva bem-sucedida.
 */
void sfxDodge() {
  if (!beginSound(25)) return;
  buzzer.sound(NOTE_B5, 16);
  buzzer.sound(NOTE_G5, 14);
}

/**
 * @brief Plays the short sound effect for a blocked hit.
 * | Reproduz o efeito sonoro curto para um golpe defendido.
 */
void sfxBlock() {
  if (!beginSound(55)) return;
  buzzer.sound(NOTE_FS4, 32);
  buzzer.sound(NOTE_C4, 28);
}

/**
 * @brief Plays the short sound effect for a clean hit.
 * | Reproduz o efeito sonoro curto para um golpe limpo.
 */
void sfxImpact(bool playerWasHit, bool hook) {
  if (!beginSound(hook ? 80 : 68)) return;

  if (hook) {
    buzzer.sound(playerWasHit ? NOTE_C2 : NOTE_D2, 60);
    buzzer.sound(playerWasHit ? NOTE_G2 : NOTE_A2, 48);
    return;
  }

  buzzer.sound(playerWasHit ? NOTE_A2 : NOTE_C3, 44);
  buzzer.sound(playerWasHit ? NOTE_E2 : NOTE_G2, 34);
}

/**
 * @brief Plays the short sound effect for the hook meter becoming ready.
 * | Reproduz o efeito sonoro curto para o medidor de gancho ficando pronto.
 */
void sfxHookReady() {
  if (!beginSound(60)) return;
  buzzer.sound(NOTE_C5, 28);
  buzzer.sound(NOTE_E5, 28);
  buzzer.sound(NOTE_G5, 48);
}

/**
 * @brief Plays the short sound effect for a knockout.
 * | Reproduz o efeito sonoro curto para um nocaute.
 */
void sfxKnockout() {
  if (!beginSound(80)) return;
  buzzer.sound(NOTE_G3, 55);
  buzzer.sound(NOTE_E3, 55);
  buzzer.sound(NOTE_C3, 85);
}

/**
 * @brief Plays the short sound effect for a phase victory.
 * | Reproduz o efeito sonoro curto para uma vitória de fase.
 */
void sfxVictory() {
  if (!beginSound(65)) return;
  buzzer.sound(NOTE_C4, 35);
  buzzer.sound(NOTE_E4, 35);
  buzzer.sound(NOTE_G4, 45);
  buzzer.sound(NOTE_C5, 70);
}

/**
 * @brief Plays the short sound effect for Game Over.
 * | Reproduz o efeito sonoro curto para o Game Over.
 */
void sfxGameOver() {
  if (!beginSound(65)) return;
  buzzer.sound(NOTE_E4, 55);
  buzzer.sound(NOTE_C4, 55);
  buzzer.sound(NOTE_A3, 80);
}

/**
 * @brief Plays the short sound effect for the final champion celebration.
 * | Reproduz o efeito sonoro curto para a comemoração final de campeão.
 */
void sfxChampion() {
  if (!beginSound(75)) return;
  buzzer.sound(NOTE_C4, 32);
  buzzer.sound(NOTE_E4, 32);
  buzzer.sound(NOTE_G4, 32);
  buzzer.sound(NOTE_C5, 45);
  buzzer.sound(NOTE_E5, 45);
  buzzer.sound(NOTE_G5, 80);
}

// ======================================================
// Opening animation without lateral sprite trails | Abertura sem rastros laterais dos personagens
// ======================================================

/**
 * @brief Draws one fighter used by the opening animation.
 * | Desenha um dos lutadores usados na animação de abertura.
 */
void drawOpeningFighter(
  int x,
  int baseY,
  bool facingRight,
  uint16_t bodyColor,
  uint16_t gloveColor,
  int punchExtension,
  int bodyLean
) {
  int direction = facingRight ? 1 : -1;
  int bodyX = x + direction * bodyLean;

  // Sombra.
  canvas.drawLine(
    bodyX - 14,
    baseY + 3,
    bodyX + 14,
    baseY + 3,
    TFT_DARKGREY
  );

  // Pernas curtas e verticais.
  canvas.drawLine(
    bodyX - 4,
    baseY - 4,
    bodyX - 4,
    baseY + 2,
    TFT_WHITE
  );

  canvas.drawLine(
    bodyX + 4,
    baseY - 4,
    bodyX + 4,
    baseY + 2,
    TFT_WHITE
  );

  // Tronco.
  canvas.fillRoundRect(
    bodyX - 10,
    baseY - 34,
    20,
    30,
    5,
    bodyColor
  );

  int headX = bodyX + direction * 2;
  int headY = baseY - 44;

  canvas.fillCircle(
    headX,
    headY,
    9,
    TFT_ORANGE
  );

  // Cabelo cheio.
  canvas.fillCircle(
    headX,
    headY - 5,
    6,
    TFT_BLACK
  );

  canvas.fillRect(
    headX - 6,
    headY - 6,
    12,
    5,
    TFT_BLACK
  );

  canvas.drawPixel(
    headX + direction * 6,
    headY,
    TFT_BLACK
  );

  // Luva de guarda.
  int guardGloveX = bodyX - direction * 14;

  canvas.drawLine(
    bodyX - direction * 7,
    baseY - 27,
    guardGloveX,
    baseY - 19,
    TFT_ORANGE
  );

  canvas.fillCircle(
    guardGloveX,
    baseY - 19,
    5,
    gloveColor
  );

  // Braco que golpeia. Somente o braco se move;
  // o personagem nao atravessa a tela e nao deixa rastro.
  int punchGloveX =
    bodyX +
    direction *
    (
      13 +
      punchExtension
    );

  int punchGloveY =
    baseY -
    27 -
    min(
      punchExtension / 6,
      4
    );

  canvas.drawLine(
    bodyX + direction * 7,
    baseY - 27,
    punchGloveX,
    punchGloveY,
    TFT_ORANGE
  );

  canvas.fillCircle(
    punchGloveX,
    punchGloveY,
    6,
    gloveColor
  );
}

/**
 * @brief Draws the flash shown when the opening punches meet.
 * | Desenha o clarão mostrado quando os socos da abertura se encontram.
 */
void drawImpactStar(int x, int y, int radius) {
  canvas.fillCircle(
    x,
    y,
    max(2, radius / 3),
    TFT_WHITE
  );

  canvas.drawLine(
    x - radius,
    y,
    x + radius,
    y,
    TFT_YELLOW
  );

  canvas.drawLine(
    x,
    y - radius,
    x,
    y + radius,
    TFT_YELLOW
  );

  canvas.drawLine(
    x - radius + 2,
    y - radius + 2,
    x + radius - 2,
    y + radius - 2,
    TFT_ORANGE
  );

  canvas.drawLine(
    x + radius - 2,
    y - radius + 2,
    x - radius + 2,
    y + radius - 2,
    TFT_ORANGE
  );
}

/**
 * @brief Builds one complete frame of the animated opening.
 * | Monta um quadro completo da abertura animada.
 */
void drawOpening() {
  bool flash =
    openingFrame >= 52 &&
    openingFrame <= 53;

  clearCanvas(
    flash
      ? TFT_WHITE
      : TFT_NAVY
  );

  if (!flash) {
    // Fundo redesenhado integralmente em todos os quadros.
    canvas.fillRect(
      0,
      0,
      SCREEN_W,
      20,
      TFT_BLACK
    );

    canvas.fillRect(
      0,
      20,
      SCREEN_W,
      18,
      TFT_BLUE
    );

    for (int i = 0; i < 8; i++) {
      int lightX = 10 + i * 20;
      int lightY =
        27 +
        (
          (
            i +
            openingFrame / 5
          ) % 2
        ) * 5;

      canvas.fillCircle(
        lightX,
        lightY,
        2,
        i % 2
          ? TFT_CYAN
          : TFT_YELLOW
      );
    }

    canvas.fillRect(
      0,
      96,
      SCREEN_W,
      32,
      TFT_DARKGREY
    );

    canvas.drawLine(
      0,
      101,
      SCREEN_W - 1,
      101,
      TFT_WHITE
    );
  }

  int bounce =
    openingFrame < 36 &&
    (
      openingFrame / 4
    ) % 2 == 0
      ? 1
      : 0;

  int punchExtension = 0;

  if (
    openingFrame >= 36 &&
    openingFrame <= 52
  ) {
    punchExtension =
      (
        openingFrame -
        36
      ) * 2;
  } else if (
    openingFrame > 52 &&
    openingFrame <= 64
  ) {
    punchExtension =
      (
        64 -
        openingFrame
      ) * 2;
  }

  punchExtension =
    constrain(
      punchExtension,
      0,
      22
    );

  int bodyLean =
    punchExtension / 11;

  // Posicoes fixas: somente os bracos sao animados.
  drawOpeningFighter(
    48,
    111 - bounce,
    true,
    TFT_BLUE,
    TFT_RED,
    punchExtension,
    bodyLean
  );

  drawOpeningFighter(
    112,
    111 - bounce,
    false,
    TFT_RED,
    TFT_MAGENTA,
    punchExtension,
    bodyLean
  );

  if (
    openingFrame >= 48 &&
    openingFrame <= 58
  ) {
    int radius =
      constrain(
        12 -
        abs(
          53 -
          openingFrame
        ),
        5,
        12
      );

    drawImpactStar(
      80,
      80,
      radius
    );
  }

  if (openingFrame >= 68) {
    canvas.fillRoundRect(
      18,
      4,
      124,
      45,
      6,
      TFT_BLACK
    );

    canvas.drawRoundRect(
      18,
      4,
      124,
      45,
      6,
      TFT_YELLOW
    );

    centeredText(
      "ES32LAB",
      9,
      2,
      TFT_WHITE
    );

    centeredText(
      "BOXE",
      26,
      3,
      TFT_RED
    );
  }

  if (openingFrame >= 84) {
    centeredText(
      openingFinished
        ? "PRESSIONE UMA TECLA"
        : "PREPARE AS LUVAS!",
      104,
      1,
      openingFinished
        ? TFT_CYAN
        : TFT_YELLOW,
      TFT_DARKGREY
    );

    centeredText(
      GAME_AUTHOR,
      116,
      1,
      TFT_LIGHTGREY,
      TFT_DARKGREY
    );

    canvas.setTextSize(1);
    canvas.setTextColor(
      TFT_DARKGREY,
      TFT_NAVY
    );
    canvas.setCursor(132, 53);
    canvas.print(GAME_VERSION);
  }

  presentCanvas();
}

/**
 * @brief Resets and starts the opening sequence from its first frame.
 * | Reinicia e inicia a abertura a partir do primeiro quadro.
 */
void startOpening() {
  gameState = OPENING;

  currentPhase = 1;
  openingFrame = 0;
  openingFinished = false;

  openingWhooshPlayed = false;
  openingImpactPlayed = false;
  openingTitlePlayed = false;

  hardClearScreen(TFT_BLACK);
  openingTimer.resetMillis();

  drawOpening();
  sfxOpeningStart();
}

/**
 * @brief Advances the opening animation and waits for a new key after its final frame.
 * | Avança a abertura e aguarda uma nova tecla após o quadro final.
 */
void updateOpening() {
  if (!openingFinished) {
    if (
      !openingTimer.intervalMillis(
        OPENING_FRAME_MS
      )
    ) {
      return;
    }

    openingFrame++;

    if (
      openingFrame >= 36 &&
      !openingWhooshPlayed
    ) {
      openingWhooshPlayed = true;
      sfxOpeningWhoosh();
    }

    if (
      openingFrame >= 52 &&
      !openingImpactPlayed
    ) {
      openingImpactPlayed = true;
      sfxOpeningImpact();
    }

    if (
      openingFrame >= 68 &&
      !openingTitlePlayed
    ) {
      openingTitlePlayed = true;
      sfxOpeningTitle();
    }

    if (
      openingFrame >=
      OPENING_TOTAL_FRAMES
    ) {
      openingFrame =
        OPENING_TOTAL_FRAMES;

      openingFinished = true;

      // A imagem final permanece parada. O comando que
      // estava pressionado antes precisa ser solto.
      lockInput();
      drawOpening();
      return;
    }

    drawOpening();
    return;
  }

  // Depois da animacao, aguarda uma nova tecla.
  updateInputGate(
    OPENING_WAIT_MIN_MS
  );

  if (
    inputArmed &&
    anyKeyPressed()
  ) {
    sfxMenuConfirm();
    showDifficultyMenu();
  }
}

// ======================================================
// Child-friendly difficulty and sound menu | Menu simplificado de dificuldade e som
// ======================================================

/**
 * @brief Draws the speaker icon that shows whether sound is enabled.
 * | Desenha o ícone de alto-falante que indica se o som está ligado.
 */
void drawSoundIcon(int x, int y) {
  canvas.fillRect(
    x,
    y + 4,
    4,
    6,
    soundEnabled
      ? TFT_CYAN
      : TFT_ORANGE
  );

  canvas.fillTriangle(
    x + 4,
    y + 3,
    x + 9,
    y,
    x + 9,
    y + 13,
    soundEnabled
      ? TFT_CYAN
      : TFT_ORANGE
  );

  if (soundEnabled) {
    canvas.drawCircle(
      x + 10,
      y + 6,
      4,
      TFT_CYAN
    );

    canvas.drawCircle(
      x + 10,
      y + 6,
      7,
      TFT_CYAN
    );
  } else {
    canvas.drawLine(
      x + 11,
      y,
      x + 20,
      y + 13,
      TFT_RED
    );

    canvas.drawLine(
      x + 20,
      y,
      x + 11,
      y + 13,
      TFT_RED
    );
  }
}

/**
 * @brief Draws the child-friendly difficulty menu and sound option.
 * | Desenha o menu infantil de dificuldade e a opção de som.
 */
void drawDifficultyMenu() {
  clearCanvas(TFT_BLACK);

  canvas.fillRect(
    0,
    0,
    SCREEN_W,
    18,
    TFT_RED
  );

  centeredText(
    "ESCOLHA O NIVEL",
    5,
    1,
    TFT_WHITE,
    TFT_RED
  );

  const int optionY[3] = {23, 50, 77};

  for (int i = 0; i < 3; i++) {
    const DifficultyConfig& option =
      DIFFICULTIES[i];

    bool selected =
      i ==
      static_cast<int>(
        selectedDifficulty
      );

    uint16_t background =
      selected
        ? TFT_DARKGREY
        : TFT_BLACK;

    canvas.fillRoundRect(
      25,
      optionY[i],
      110,
      21,
      4,
      background
    );

    canvas.drawRoundRect(
      25,
      optionY[i],
      110,
      21,
      4,
      selected
        ? option.color
        : TFT_DARKGREY
    );

    if (selected) {
      canvas.fillTriangle(
        17,
        optionY[i] + 10,
        22,
        optionY[i] + 6,
        22,
        optionY[i] + 14,
        option.color
      );
    }

    canvas.setTextSize(1);
    canvas.setTextColor(
      selected
        ? option.color
        : TFT_LIGHTGREY,
      background
    );

    int nameX =
      (
        SCREEN_W -
        static_cast<int>(
          strlen(option.name)
        ) * 6
      ) / 2;

    canvas.setCursor(
      nameX,
      optionY[i] + 7
    );

    canvas.print(option.name);
  }

  drawSoundIcon(
    8,
    105
  );

  canvas.setTextSize(1);
  canvas.setTextColor(
    soundEnabled
      ? TFT_CYAN
      : TFT_ORANGE,
    TFT_BLACK
  );

  canvas.setCursor(
    33,
    106
  );

  canvas.print(
    soundEnabled
      ? "SOM LIGADO"
      : "SOM DESLIGADO"
  );

  centeredText(
    inputArmed
      ? "ESQ/DIR SOM  CENTRO JOGAR"
      : "AGUARDE...",
    117,
    1,
    inputArmed
      ? TFT_YELLOW
      : TFT_DARKGREY
  );

  presentCanvas();
}

/**
 * @brief Changes the game state to the difficulty menu and clears the previous screen.
 * | Muda o estado para o menu de dificuldade e limpa a tela anterior.
 */
void showDifficultyMenu() {
  gameState = DIFFICULTY_MENU;

  lockInput();
  hardClearScreen(TFT_BLACK);
  drawDifficultyMenu();
}

/**
 * @brief Moves the selected difficulty up or down with wraparound.
 * | Altera a dificuldade selecionada com retorno circular entre as opções.
 */
void changeDifficulty(int direction) {
  int value =
    static_cast<int>(
      selectedDifficulty
    ) +
    direction;

  if (value < 0) {
    value = 2;
  }

  if (value > 2) {
    value = 0;
  }

  selectedDifficulty =
    static_cast<Difficulty>(
      value
    );

  sfxMenuMove();
  drawDifficultyMenu();
}

/**
 * @brief Enables or disables every game sound effect.
 * | Liga ou desliga todos os efeitos sonoros do jogo.
 */
void toggleSound() {
  soundEnabled = !soundEnabled;

  if (soundEnabled) {
    sfxMenuConfirm();
  }

  drawDifficultyMenu();
}

/**
 * @brief Reads menu keys and starts the game after confirmation.
 * | Lê as teclas do menu e inicia o jogo após a confirmação.
 */
void updateDifficultyMenu() {
  if (
    updateInputGate(
      MENU_MIN_MS
    )
  ) {
    drawDifficultyMenu();
  }

  if (!inputArmed) {
    return;
  }

  // CIMA/BAIXO escolhem apenas a dificuldade.
  if (keyboard.press(KEY_UP)) {
    changeDifficulty(-1);
    return;
  }

  if (keyboard.press(KEY_DOWN)) {
    changeDifficulty(1);
    return;
  }

  // ESQUERDA/DIREITA somente ligam ou desligam o som.
  if (
    keyboard.press(KEY_LEFT) ||
    keyboard.press(KEY_RIGHT)
  ) {
    toggleSound();
    return;
  }

  // Um unico clique inicia o jogo.
  if (keyboard.press(KEY_CENTER)) {
    sfxMenuConfirm();

    currentPhase = 1;
    preparePhase();
  }
}

// ======================================================
// Opponent, victory, Game Over and champion screens | Telas de adversário, vitória, Game Over e campeão
// ======================================================

/**
 * @brief Draws the portrait text panel in the off-screen framebuffer.
 * | Desenha painel de texto do retrato no framebuffer fora da tela.
 */
void drawPortraitPanelText(
  const String& text,
  int y,
  uint8_t size,
  uint16_t color,
  uint16_t background = TFT_BLACK
) {
  constexpr int PANEL_X = 91;
  constexpr int PANEL_W = 65;

  int textWidth =
    static_cast<int>(text.length()) *
    6 *
    size;

  int x =
    PANEL_X +
    (
      PANEL_W -
      textWidth
    ) / 2;

  if (x < PANEL_X) {
    x = PANEL_X;
  }

  canvas.setTextSize(size);
  canvas.setTextColor(
    color,
    background
  );
  canvas.setCursor(x, y);
  canvas.print(text);
}

/**
 * @brief Draws a portrait eye in the off-screen framebuffer.
 * | Desenha olho do retrato no framebuffer fora da tela.
 */
void drawPortraitEye(
  int x,
  int y,
  bool closed,
  bool angry,
  bool lookLeft
) {
  if (closed) {
    canvas.drawLine(
      x - 3,
      y,
      x + 3,
      y,
      TFT_BLACK
    );
    return;
  }

  canvas.fillCircle(
    x,
    y,
    3,
    TFT_WHITE
  );

  canvas.fillCircle(
    x +
    (
      lookLeft
        ? -1
        : 1
    ),
    y,
    1,
    TFT_BLACK
  );

  if (angry) {
    canvas.drawLine(
      x - 4,
      y - 5,
      x + 3,
      y - 3,
      TFT_BLACK
    );
  }
}

/**
 * @brief Draws the Sovaco de Cobra portrait in the off-screen framebuffer.
 * | Desenha retrato de Sovaco de Cobra no framebuffer fora da tela.
 */
void drawSovacoPortrait(
  bool wink,
  int bob
) {
  constexpr int centerX = 46;
  int faceY = 55 + bob;

  canvas.fillCircle(
    20,
    105,
    12,
    phase().gloveColor
  );

  canvas.fillCircle(
    72,
    105,
    12,
    phase().gloveColor
  );

  canvas.fillRoundRect(
    20,
    83 + bob,
    52,
    32,
    8,
    phase().bodyColor
  );

  canvas.fillCircle(
    22,
    faceY,
    6,
    phase().skinColor
  );

  canvas.fillCircle(
    70,
    faceY,
    6,
    phase().skinColor
  );

  canvas.fillRoundRect(
    23,
    31 + bob,
    46,
    53,
    17,
    phase().skinColor
  );

  for (int i = 0; i < 6; i++) {
    int spikeX =
      31 +
      i * 6;

    int spikeHeight =
      11 +
      (
        i % 2
      ) * 4;

    canvas.fillTriangle(
      spikeX - 4,
      36 + bob,
      spikeX + 4,
      36 + bob,
      spikeX,
      36 + bob - spikeHeight,
      TFT_BLACK
    );
  }

  drawPortraitEye(
    37,
    54 + bob,
    wink,
    false,
    false
  );

  drawPortraitEye(
    55,
    54 + bob,
    false,
    false,
    true
  );

  canvas.drawLine(
    58,
    43 + bob,
    64,
    49 + bob,
    TFT_RED
  );

  canvas.drawLine(
    58,
    49 + bob,
    64,
    43 + bob,
    TFT_RED
  );

  canvas.drawLine(
    38,
    69 + bob,
    47,
    73 + bob,
    TFT_BLACK
  );

  canvas.drawLine(
    47,
    73 + bob,
    58,
    67 + bob,
    TFT_BLACK
  );

  canvas.drawLine(
    centerX - 3,
    91 + bob,
    centerX + 4,
    96 + bob,
    TFT_YELLOW
  );

  canvas.drawLine(
    centerX + 4,
    96 + bob,
    centerX - 3,
    102 + bob,
    TFT_YELLOW
  );
}

/**
 * @brief Draws the Costela de Minhoca portrait in the off-screen framebuffer.
 * | Desenha retrato de Costela de Minhoca no framebuffer fora da tela.
 */
void drawCostelaPortrait(
  bool blink,
  int bob
) {
  constexpr int centerX = 46;
  int faceY = 56 + bob;

  canvas.fillCircle(
    21,
    105,
    11,
    phase().gloveColor
  );

  canvas.fillCircle(
    71,
    105,
    11,
    phase().gloveColor
  );

  canvas.fillRoundRect(
    30,
    82 + bob,
    32,
    34,
    7,
    phase().bodyColor
  );

  canvas.fillCircle(
    28,
    faceY,
    5,
    phase().skinColor
  );

  canvas.fillCircle(
    64,
    faceY,
    5,
    phase().skinColor
  );

  canvas.fillRoundRect(
    29,
    27 + bob,
    34,
    59,
    14,
    phase().skinColor
  );

  canvas.fillRect(
    28,
    40 + bob,
    37,
    5,
    TFT_BLUE
  );

  canvas.fillTriangle(
    63,
    42 + bob,
    78,
    45 + bob,
    64,
    48 + bob,
    TFT_BLUE
  );

  canvas.fillTriangle(
    63,
    44 + bob,
    75,
    53 + bob,
    62,
    50 + bob,
    TFT_CYAN
  );

  drawPortraitEye(
    38,
    56 + bob,
    blink,
    false,
    false
  );

  drawPortraitEye(
    54,
    56 + bob,
    blink,
    false,
    true
  );

  canvas.drawLine(
    centerX,
    58 + bob,
    centerX - 2,
    67 + bob,
    TFT_ORANGE
  );

  canvas.drawLine(
    centerX - 2,
    67 + bob,
    centerX + 3,
    67 + bob,
    TFT_ORANGE
  );

  canvas.drawLine(
    39,
    75 + bob,
    54,
    75 + bob,
    TFT_BLACK
  );

  for (int i = 0; i < 3; i++) {
    canvas.drawLine(
      35,
      91 + bob + i * 6,
      57,
      91 + bob + i * 6,
      TFT_WHITE
    );
  }
}

/**
 * @brief Draws the Pouca Tripa portrait in the off-screen framebuffer.
 * | Desenha retrato de Pouca Tripa no framebuffer fora da tela.
 */
void drawPoucaTripaPortrait(
  bool blink,
  int bob
) {
  constexpr int centerX = 46;
  int faceY = 57 + bob;

  canvas.fillCircle(
    18,
    104,
    12,
    phase().gloveColor
  );

  canvas.fillCircle(
    74,
    104,
    12,
    phase().gloveColor
  );

  canvas.fillRoundRect(
    18,
    82 + bob,
    56,
    34,
    10,
    phase().bodyColor
  );

  canvas.fillCircle(
    29,
    35 + bob,
    13,
    TFT_BLACK
  );

  canvas.fillCircle(
    43,
    29 + bob,
    15,
    TFT_BLACK
  );

  canvas.fillCircle(
    59,
    34 + bob,
    13,
    TFT_BLACK
  );

  canvas.fillCircle(
    67,
    46 + bob,
    11,
    TFT_BLACK
  );

  canvas.fillCircle(
    24,
    47 + bob,
    11,
    TFT_BLACK
  );

  canvas.fillCircle(
    21,
    faceY,
    6,
    phase().skinColor
  );

  canvas.fillCircle(
    71,
    faceY,
    6,
    phase().skinColor
  );

  canvas.fillCircle(
    centerX,
    faceY,
    25,
    phase().skinColor
  );

  drawPortraitEye(
    37,
    54 + bob,
    blink,
    false,
    false
  );

  drawPortraitEye(
    55,
    54 + bob,
    blink,
    false,
    true
  );

  canvas.fillCircle(
    centerX,
    64 + bob,
    4,
    TFT_ORANGE
  );

  canvas.fillTriangle(
    45,
    69 + bob,
    28,
    74 + bob,
    44,
    78 + bob,
    TFT_BLACK
  );

  canvas.fillTriangle(
    47,
    69 + bob,
    64,
    74 + bob,
    48,
    78 + bob,
    TFT_BLACK
  );

  canvas.fillRect(
    centerX - 2,
    86 + bob,
    5,
    27,
    TFT_RED
  );
}

/**
 * @brief Draws the Coice de Mula portrait in the off-screen framebuffer.
 * | Desenha retrato de Coice de Mula no framebuffer fora da tela.
 */
void drawCoicePortrait(
  bool blink,
  int bob
) {
  constexpr int centerX = 46;
  int faceY = 55 + bob;

  canvas.fillCircle(
    15,
    103,
    15,
    phase().gloveColor
  );

  canvas.fillCircle(
    77,
    103,
    15,
    phase().gloveColor
  );

  canvas.fillRoundRect(
    13,
    79 + bob,
    66,
    37,
    8,
    phase().bodyColor
  );

  canvas.fillCircle(
    18,
    faceY,
    7,
    phase().skinColor
  );

  canvas.fillCircle(
    74,
    faceY,
    7,
    phase().skinColor
  );

  canvas.fillRoundRect(
    18,
    25 + bob,
    56,
    62,
    10,
    phase().skinColor
  );

  canvas.fillRect(
    21,
    25 + bob,
    50,
    9,
    TFT_BLACK
  );

  canvas.fillTriangle(
    21,
    31 + bob,
    30,
    31 + bob,
    25,
    38 + bob,
    TFT_BLACK
  );

  canvas.fillTriangle(
    62,
    31 + bob,
    71,
    31 + bob,
    67,
    38 + bob,
    TFT_BLACK
  );

  drawPortraitEye(
    35,
    51 + bob,
    blink,
    true,
    false
  );

  drawPortraitEye(
    57,
    51 + bob,
    blink,
    true,
    true
  );

  canvas.drawLine(
    61,
    40 + bob,
    67,
    48 + bob,
    TFT_RED
  );

  canvas.drawLine(
    61,
    48 + bob,
    67,
    40 + bob,
    TFT_RED
  );

  canvas.drawLine(
    centerX,
    54 + bob,
    centerX - 3,
    65 + bob,
    TFT_ORANGE
  );

  canvas.drawLine(
    centerX - 3,
    65 + bob,
    centerX + 4,
    65 + bob,
    TFT_ORANGE
  );

  canvas.fillTriangle(
    24,
    68 + bob,
    68,
    68 + bob,
    centerX,
    92 + bob,
    TFT_BLACK
  );

  canvas.fillRect(
    31,
    68 + bob,
    30,
    8,
    TFT_BLACK
  );

  canvas.fillRect(
    19,
    103 + bob,
    54,
    7,
    TFT_YELLOW
  );

  canvas.fillRect(
    41,
    101 + bob,
    11,
    11,
    TFT_WHITE
  );
}

/**
 * @brief Selects and draws the animated portrait for the active opponent.
 * | Seleciona e desenha o retrato animado do adversário ativo.
 */
void drawOpponentPortrait() {
  int cycle =
    portraitFrame %
    28;

  bool blink =
    cycle == 22 ||
    cycle == 23;

  bool wink =
    cycle >= 21 &&
    cycle <= 23;

  int bob =
    (
      portraitFrame /
      6
    ) % 2;

  canvas.fillRoundRect(
    5,
    21,
    82,
    94,
    7,
    TFT_DARKGREY
  );

  canvas.drawRoundRect(
    5,
    21,
    82,
    94,
    7,
    phase().bodyColor
  );

  canvas.fillCircle(
    46,
    66,
    38,
    TFT_NAVY
  );

  switch (phase().visualStyle) {
    case STYLE_MOHAWK:
      drawSovacoPortrait(
        wink,
        bob
      );
      break;

    case STYLE_BALD_HEADBAND:
      drawCostelaPortrait(
        blink,
        bob
      );
      break;

    case STYLE_HAIR_MOUSTACHE:
      drawPoucaTripaPortrait(
        blink,
        bob
      );
      break;

    case STYLE_BOSS_BEARD:
      drawCoicePortrait(
        blink,
        bob
      );
      break;
  }
}

/**
 * @brief Draws the portrait name and information in the off-screen framebuffer.
 * | Desenha nome e informações do retrato no framebuffer fora da tela.
 */
void drawPortraitNameAndInfo() {
  switch (currentPhase) {
    case 1:
      drawPortraitPanelText(
        "SOVACO DE",
        28,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "COBRA",
        40,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "ESCORREGA",
        57,
        1,
        TFT_WHITE
      );

      drawPortraitPanelText(
        "E INSISTE",
        68,
        1,
        TFT_WHITE
      );
      break;

    case 2:
      drawPortraitPanelText(
        "COSTELA DE",
        28,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "MINHOCA",
        40,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "FINO E",
        57,
        1,
        TFT_WHITE
      );

      drawPortraitPanelText(
        "TRAICOEIRO",
        68,
        1,
        TFT_WHITE
      );
      break;

    case 3:
      drawPortraitPanelText(
        "POUCA",
        28,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "TRIPA",
        40,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "RAPIDO E",
        57,
        1,
        TFT_WHITE
      );

      drawPortraitPanelText(
        "DEFENSIVO",
        68,
        1,
        TFT_WHITE
      );
      break;

    default:
      drawPortraitPanelText(
        "COICE DE",
        28,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "MULA",
        40,
        1,
        phase().bodyColor
      );

      drawPortraitPanelText(
        "FORTE E",
        57,
        1,
        TFT_WHITE
      );

      drawPortraitPanelText(
        "AGRESSIVO",
        68,
        1,
        TFT_WHITE
      );
      break;
  }

  drawPortraitPanelText(
    difficulty().name,
    84,
    1,
    difficulty().color
  );

  drawPortraitPanelText(
    inputArmed
      ? "CENTRO"
      : "PREPARE",
    98,
    1,
    inputArmed
      ? TFT_CYAN
      : TFT_LIGHTGREY
  );

  drawPortraitPanelText(
    inputArmed
      ? "LUTAR"
      : "SE...",
    108,
    1,
    inputArmed
      ? TFT_YELLOW
      : TFT_LIGHTGREY
  );
}

/**
 * @brief Draws the animated opponent presentation shown before each fight.
 * | Desenha a apresentação animada do adversário antes de cada luta.
 */
void drawPhaseIntroScreen() {
  clearCanvas(TFT_BLACK);

  canvas.fillRect(
    0,
    0,
    SCREEN_W,
    18,
    TFT_BLACK
  );

  canvas.drawLine(
    0,
    18,
    SCREEN_W - 1,
    18,
    phase().bodyColor
  );

  String title =
    "DESAFIANTE ";

  title += currentPhase;
  title += "/";
  title += TOTAL_PHASES;

  centeredText(
    title,
    5,
    1,
    TFT_YELLOW
  );

  drawOpponentPortrait();

  canvas.fillRoundRect(
    90,
    21,
    67,
    94,
    7,
    TFT_BLACK
  );

  canvas.drawRoundRect(
    90,
    21,
    67,
    94,
    7,
    difficulty().color
  );

  drawPortraitNameAndInfo();

  presentCanvas();
}

/**
 * @brief Draws celebration confetti in the off-screen framebuffer.
 * | Desenha confetes da comemoração no framebuffer fora da tela.
 */
void drawCelebrationConfetti(
  int animationFrame,
  int topY,
  int bottomY,
  int amount
) {
  const uint16_t colors[6] = {
    TFT_YELLOW,
    TFT_CYAN,
    TFT_MAGENTA,
    TFT_GREEN,
    TFT_RED,
    TFT_WHITE
  };

  int height =
    max(
      1,
      bottomY - topY
    );

  for (int i = 0; i < amount; i++) {
    int x =
      (
        i * 37 +
        animationFrame *
        (
          1 +
          i % 3
        )
      ) % SCREEN_W;

    int y =
      topY +
      (
        i * 23 +
        animationFrame *
        (
          2 +
          i % 2
        )
      ) % height;

    uint16_t color =
      colors[
        (
          i +
          animationFrame / 4
        ) % 6
      ];

    if (i % 3 == 0) {
      canvas.drawLine(
        x,
        y,
        x + 2,
        y + 3,
        color
      );
    } else if (i % 3 == 1) {
      canvas.fillRect(
        x,
        y,
        2,
        3,
        color
      );
    } else {
      canvas.fillCircle(
        x,
        y,
        1,
        color
      );
    }
  }
}

/**
 * @brief Draws the celebrating player in the off-screen framebuffer.
 * | Desenha jogador comemorando no framebuffer fora da tela.
 */
void drawCelebratingPlayer(
  int centerX,
  int bodyY,
  int animationFrame,
  bool championStyle
) {
  int armCycle =
    (
      animationFrame /
      2
    ) % 4;

  int bob =
    (
      animationFrame /
      3
    ) % 2;

  int x = centerX;
  int y = bodyY - bob;

  uint16_t shirtColor =
    championStyle
      ? TFT_BLUE
      : TFT_NAVY;

  uint16_t gloveColor =
    championStyle
      ? TFT_YELLOW
      : TFT_RED;

  // Sombra.
  canvas.fillRoundRect(
    x - 18,
    y + 33,
    36,
    5,
    2,
    TFT_DARKGREY
  );

  // Pernas e tenis.
  canvas.drawLine(
    x - 5,
    y + 19,
    x - 5,
    y + 31,
    TFT_ORANGE
  );

  canvas.drawLine(
    x + 5,
    y + 19,
    x + 5,
    y + 31,
    TFT_ORANGE
  );

  canvas.fillRect(
    x - 10,
    y + 29,
    8,
    4,
    TFT_WHITE
  );

  canvas.fillRect(
    x + 2,
    y + 29,
    8,
    4,
    TFT_WHITE
  );

  // Calcao e tronco.
  canvas.fillRoundRect(
    x - 13,
    y - 5,
    26,
    27,
    5,
    shirtColor
  );

  canvas.fillRect(
    x - 11,
    y + 14,
    22,
    8,
    TFT_BLACK
  );

  // Faixa de campeao.
  if (championStyle) {
    canvas.fillRect(
      x - 12,
      y + 10,
      24,
      7,
      TFT_YELLOW
    );

    canvas.fillRoundRect(
      x - 4,
      y + 8,
      8,
      11,
      2,
      TFT_ORANGE
    );

    canvas.drawRect(
      x - 3,
      y + 9,
      6,
      9,
      TFT_WHITE
    );
  }

  // Cabeca vista de frente.
  canvas.fillCircle(
    x,
    y - 16,
    10,
    TFT_ORANGE
  );

  // Cabelo cheio.
  canvas.fillCircle(
    x,
    y - 22,
    8,
    TFT_BLACK
  );

  canvas.fillRect(
    x - 8,
    y - 23,
    16,
    5,
    TFT_BLACK
  );

  // Olhos.
  canvas.drawPixel(
    x - 3,
    y - 16,
    TFT_BLACK
  );

  canvas.drawPixel(
    x + 3,
    y - 16,
    TFT_BLACK
  );

  // Sorriso.
  canvas.drawLine(
    x - 3,
    y - 11,
    x,
    y - 9,
    TFT_BLACK
  );

  canvas.drawLine(
    x,
    y - 9,
    x + 3,
    y - 11,
    TFT_BLACK
  );

  int leftGloveX;
  int leftGloveY;
  int rightGloveX;
  int rightGloveY;

  if (armCycle == 0) {
    leftGloveX = x - 23;
    leftGloveY = y - 28;
    rightGloveX = x + 21;
    rightGloveY = y - 20;
  } else if (armCycle == 1) {
    leftGloveX = x - 20;
    leftGloveY = y - 20;
    rightGloveX = x + 24;
    rightGloveY = y - 30;
  } else if (armCycle == 2) {
    leftGloveX = x - 25;
    leftGloveY = y - 31;
    rightGloveX = x + 19;
    rightGloveY = y - 18;
  } else {
    leftGloveX = x - 19;
    leftGloveY = y - 18;
    rightGloveX = x + 25;
    rightGloveY = y - 31;
  }

  // Braco esquerdo chacoalhando.
  canvas.drawLine(
    x - 10,
    y,
    x - 17,
    y - 10,
    TFT_ORANGE
  );

  canvas.drawLine(
    x - 17,
    y - 10,
    leftGloveX,
    leftGloveY,
    TFT_ORANGE
  );

  canvas.fillCircle(
    leftGloveX,
    leftGloveY,
    championStyle
      ? 6
      : 5,
    gloveColor
  );

  // Braco direito chacoalhando.
  canvas.drawLine(
    x + 10,
    y,
    x + 17,
    y - 10,
    TFT_ORANGE
  );

  canvas.drawLine(
    x + 17,
    y - 10,
    rightGloveX,
    rightGloveY,
    TFT_ORANGE
  );

  canvas.fillCircle(
    rightGloveX,
    rightGloveY,
    championStyle
      ? 6
      : 5,
    gloveColor
  );
}

/**
 * @brief Draws victory rays in the off-screen framebuffer.
 * | Desenha raios de vitória no framebuffer fora da tela.
 */
void drawVictoryRays(
  int centerX,
  int centerY,
  int animationFrame
) {
  const int8_t directionX[12] = {
    10, 9, 5, 0, -5, -9,
    -10, -9, -5, 0, 5, 9
  };

  const int8_t directionY[12] = {
    0, 5, 9, 10, 9, 5,
    0, -5, -9, -10, -9, -5
  };

  const uint16_t rayColors[4] = {
    TFT_GREEN,
    TFT_YELLOW,
    TFT_CYAN,
    TFT_WHITE
  };

  int rotationOffset =
    (
      animationFrame / 2
    ) % 12;

  for (int i = 0; i < 12; i++) {
    int directionIndex =
      (
        i +
        rotationOffset
      ) % 12;

    int innerRadius = 3;
    int outerRadius =
      4 +
      (
        i +
        animationFrame / 3
      ) % 2;

    int x1 =
      centerX +
      directionX[directionIndex] *
      innerRadius;

    int y1 =
      centerY +
      directionY[directionIndex] *
      innerRadius;

    int x2 =
      centerX +
      directionX[directionIndex] *
      outerRadius;

    int y2 =
      centerY +
      directionY[directionIndex] *
      outerRadius;

    canvas.drawLine(
      x1,
      y1,
      x2,
      y2,
      rayColors[
        (
          i +
          animationFrame / 2
        ) % 4
      ]
    );
  }
}

/**
 * @brief Draws one frame of the player victory celebration.
 * | Desenha um quadro da comemoração de vitória do jogador.
 */
void drawPhaseVictoryScreen() {
  clearCanvas(TFT_BLACK);

  uint16_t borderColor =
    (
      victoryFrame / 3
    ) % 2 == 0
      ? TFT_GREEN
      : TFT_YELLOW;

  canvas.fillRoundRect(
    3,
    3,
    154,
    122,
    8,
    TFT_DARKGREY
  );

  canvas.drawRoundRect(
    3,
    3,
    154,
    122,
    8,
    borderColor
  );

  canvas.drawRoundRect(
    5,
    5,
    150,
    118,
    7,
    TFT_WHITE
  );

  centeredText(
    "VITORIA!",
    7,
    2,
    TFT_GREEN,
    TFT_DARKGREY
  );

  drawVictoryRays(
    80,
    67,
    victoryFrame
  );

  drawCelebrationConfetti(
    victoryFrame,
    24,
    100,
    12
  );

  drawCelebratingPlayer(
    80,
    72,
    victoryFrame,
    false
  );

  String defeated =
    phase().shortName;

  defeated += " FOI AO CHAO";

  centeredText(
    defeated,
    99,
    1,
    TFT_WHITE,
    TFT_DARKGREY
  );

  centeredText(
    inputArmed
      ? "CENTRO: PROXIMA FASE"
      : "COMEMORE!",
    113,
    1,
    inputArmed
      ? TFT_YELLOW
      : TFT_CYAN,
    TFT_DARKGREY
  );

  presentCanvas();
}

/**
 * @brief Draws Game Over stars in the off-screen framebuffer.
 * | Desenha estrelas do Game Over no framebuffer fora da tela.
 */
void drawGameOverStars(
  int centerX,
  int centerY,
  int animationFrame
) {
  const int8_t orbitX[12] = {
    0, 5, 9, 11, 9, 5,
    0, -5, -9, -11, -9, -5
  };

  const int8_t orbitY[12] = {
    -7, -6, -3, 1, 5, 7,
    8, 7, 5, 1, -3, -6
  };

  const uint16_t colors[3] = {
    TFT_YELLOW,
    TFT_WHITE,
    TFT_CYAN
  };

  int base =
    (
      animationFrame / 2
    ) % 12;

  for (int i = 0; i < 3; i++) {
    int index =
      (
        base +
        i * 4
      ) % 12;

    int x =
      centerX +
      orbitX[index] * 2;

    int y =
      centerY +
      orbitY[index];

    uint16_t color =
      colors[i];

    canvas.drawLine(
      x - 2,
      y,
      x + 2,
      y,
      color
    );

    canvas.drawLine(
      x,
      y - 2,
      x,
      y + 2,
      color
    );

    canvas.drawPixel(
      x - 1,
      y - 1,
      color
    );

    canvas.drawPixel(
      x + 1,
      y + 1,
      color
    );
  }
}

/**
 * @brief Draws the defeated player in the off-screen framebuffer.
 * | Desenha jogador derrotado no framebuffer fora da tela.
 */
void drawDefeatedPlayer(
  int centerX,
  int baseY,
  int animationFrame
) {
  int bob =
    (
      animationFrame / 7
    ) % 2;

  int headX =
    centerX + 4;

  int headY =
    baseY - 52 + bob;

  // Sombra no piso.
  canvas.fillRoundRect(
    centerX - 27,
    baseY - 4,
    54,
    8,
    4,
    TFT_BLACK
  );

  // Pernas dobradas de quem caiu sentado.
  canvas.drawLine(
    centerX - 7,
    baseY - 16,
    centerX - 18,
    baseY - 5,
    TFT_ORANGE
  );

  canvas.drawLine(
    centerX + 6,
    baseY - 16,
    centerX + 19,
    baseY - 5,
    TFT_ORANGE
  );

  canvas.fillRect(
    centerX - 23,
    baseY - 6,
    10,
    4,
    TFT_BLACK
  );

  canvas.fillRect(
    centerX + 14,
    baseY - 6,
    10,
    4,
    TFT_BLACK
  );

  // Calçao e tronco inclinado.
  canvas.fillRoundRect(
    centerX - 12,
    baseY - 25,
    24,
    12,
    4,
    TFT_NAVY
  );

  canvas.fillRoundRect(
    centerX - 13,
    baseY - 48,
    25,
    28,
    6,
    TFT_BLUE
  );

  // Bracos caidos e luvas apoiadas.
  canvas.drawLine(
    centerX - 10,
    baseY - 39,
    centerX - 24,
    baseY - 18,
    TFT_ORANGE
  );

  canvas.drawLine(
    centerX + 10,
    baseY - 38,
    centerX + 24,
    baseY - 18,
    TFT_ORANGE
  );

  canvas.fillCircle(
    centerX - 25,
    baseY - 16,
    6,
    TFT_RED
  );

  canvas.fillCircle(
    centerX + 25,
    baseY - 16,
    6,
    TFT_RED
  );

  // Cabeca baixa, agora vista de frente.
  canvas.fillCircle(
    headX,
    headY,
    13,
    TFT_ORANGE
  );

  // Cabelo desalinhado.
  canvas.fillCircle(
    headX - 4,
    headY - 10,
    7,
    TFT_BLACK
  );

  canvas.fillCircle(
    headX + 4,
    headY - 10,
    7,
    TFT_BLACK
  );

  canvas.fillTriangle(
    headX - 10,
    headY - 7,
    headX - 3,
    headY - 15,
    headX - 1,
    headY - 7,
    TFT_BLACK
  );

  canvas.fillTriangle(
    headX + 1,
    headY - 7,
    headX + 6,
    headY - 15,
    headX + 10,
    headY - 7,
    TFT_BLACK
  );

  // Um olho fechado e outro machucado.
  canvas.drawLine(
    headX - 8,
    headY - 1,
    headX - 3,
    headY + 1,
    TFT_BLACK
  );

  canvas.fillCircle(
    headX + 5,
    headY,
    5,
    TFT_MAGENTA
  );

  canvas.fillCircle(
    headX + 5,
    headY,
    2,
    TFT_BLACK
  );

  // Boca abatida.
  canvas.drawLine(
    headX - 5,
    headY + 8,
    headX,
    headY + 6,
    TFT_BLACK
  );

  canvas.drawLine(
    headX,
    headY + 6,
    headX + 5,
    headY + 8,
    TFT_BLACK
  );

  // Gota de suor animada.
  if (
    (
      animationFrame / 5
    ) % 2 == 0
  ) {
    canvas.fillTriangle(
      headX + 15,
      headY - 5,
      headX + 12,
      headY + 2,
      headX + 18,
      headY + 2,
      TFT_CYAN
    );

    canvas.fillCircle(
      headX + 15,
      headY + 2,
      3,
      TFT_CYAN
    );
  }

  drawGameOverStars(
    headX,
    headY - 13,
    animationFrame
  );
}

/**
 * @brief Draws one frame of the animated Game Over scene.
 * | Desenha um quadro da cena animada de Game Over.
 */
void drawGameOverScreen() {
  clearCanvas(TFT_BLACK);

  // Fundo escuro de arena.
  canvas.fillRect(
    0,
    0,
    SCREEN_W,
    SCREEN_H,
    TFT_NAVY
  );

  for (int y = 24; y < SCREEN_H; y += 8) {
    canvas.drawLine(
      0,
      y,
      SCREEN_W - 1,
      y,
      (
        y / 8
      ) % 2 == 0
        ? TFT_BLACK
        : TFT_DARKGREY
    );
  }

  // Luz fraca sobre o guerreiro derrotado.
  uint16_t spotlightColor =
    (
      gameOverFrame / 5
    ) % 2 == 0
      ? TFT_DARKGREY
      : TFT_BLUE;

  canvas.fillTriangle(
    60,
    24,
    100,
    24,
    124,
    115,
    spotlightColor
  );

  canvas.fillTriangle(
    60,
    24,
    100,
    24,
    36,
    115,
    spotlightColor
  );

  uint16_t borderColor =
    (
      gameOverFrame / 4
    ) % 2 == 0
      ? TFT_RED
      : TFT_ORANGE;

  canvas.drawRoundRect(
    3,
    3,
    154,
    122,
    8,
    borderColor
  );

  canvas.drawRoundRect(
    5,
    5,
    150,
    118,
    7,
    TFT_DARKGREY
  );

  canvas.fillRoundRect(
    16,
    7,
    128,
    22,
    6,
    TFT_BLACK
  );

  canvas.drawRoundRect(
    16,
    7,
    128,
    22,
    6,
    TFT_RED
  );

  centeredText(
    "GAME OVER",
    12,
    2,
    TFT_RED,
    TFT_BLACK
  );

  drawDefeatedPlayer(
    80,
    107,
    gameOverFrame
  );

  canvas.fillRoundRect(
    21,
    96,
    118,
    13,
    4,
    TFT_BLACK
  );

  centeredText(
    "NAO DESISTA, GUERREIRO!",
    99,
    1,
    TFT_YELLOW,
    TFT_BLACK
  );

  canvas.fillRoundRect(
    17,
    111,
    126,
    14,
    4,
    TFT_BLACK
  );

  canvas.drawRoundRect(
    17,
    111,
    126,
    14,
    4,
    TFT_RED
  );

  centeredText(
    inputArmed
      ? "CENTRO: RECOMECAR"
      : "RECUPERANDO...",
    115,
    1,
    inputArmed
      ? TFT_CYAN
      : TFT_LIGHTGREY,
    TFT_BLACK
  );

  presentCanvas();
}

/**
 * @brief Draws champion spotlights in the off-screen framebuffer.
 * | Desenha holofotes da tela de campeão no framebuffer fora da tela.
 */
void drawChampionSpotlights(
  int animationFrame
) {
  uint16_t leftColor =
    (
      animationFrame / 4
    ) % 2 == 0
      ? TFT_CYAN
      : TFT_BLUE;

  uint16_t rightColor =
    (
      animationFrame / 4
    ) % 2 == 0
      ? TFT_MAGENTA
      : TFT_RED;

  int leftTarget =
    48 +
    (
      animationFrame % 24
    );

  int rightTarget =
    112 -
    (
      animationFrame % 24
    );

  canvas.fillTriangle(
    8,
    15,
    24,
    15,
    leftTarget,
    108,
    leftColor
  );

  canvas.fillTriangle(
    136,
    15,
    152,
    15,
    rightTarget,
    108,
    rightColor
  );

  canvas.fillTriangle(
    69,
    12,
    79,
    12,
    88,
    108,
    TFT_DARKGREY
  );

  canvas.fillTriangle(
    81,
    12,
    91,
    12,
    72,
    108,
    TFT_DARKGREY
  );
}

/**
 * @brief Draws the champion marquee in the off-screen framebuffer.
 * | Desenha letreiro da tela de campeão no framebuffer fora da tela.
 */
void drawChampionMarquee(
  int animationFrame
) {
  canvas.fillRoundRect(
    3,
    2,
    154,
    24,
    7,
    TFT_BLACK
  );

  canvas.drawRoundRect(
    3,
    2,
    154,
    24,
    7,
    TFT_YELLOW
  );

  for (int i = 0; i < 14; i++) {
    uint16_t color =
      (
        i +
        animationFrame / 2
      ) % 3 == 0
        ? TFT_WHITE
        : (
          (
            i +
            animationFrame / 2
          ) % 3 == 1
            ? TFT_YELLOW
            : TFT_RED
        );

    canvas.fillCircle(
      11 + i * 11,
      6,
      2,
      color
    );

    canvas.fillCircle(
      11 + i * 11,
      22,
      2,
      color
    );
  }

  centeredText(
    "GRANDE CAMPEAO!",
    9,
    1,
    TFT_YELLOW,
    TFT_BLACK
  );
}

/**
 * @brief Draws a firework in the off-screen framebuffer.
 * | Desenha fogo de artifício no framebuffer fora da tela.
 */
void drawFirework(
  int centerX,
  int centerY,
  int animationFrame,
  int phaseOffset,
  uint16_t color
) {
  const int8_t directionX[8] = {
    10, 7, 0, -7,
    -10, -7, 0, 7
  };

  const int8_t directionY[8] = {
    0, 7, 10, 7,
    0, -7, -10, -7
  };

  int cycle =
    (
      animationFrame +
      phaseOffset
    ) % 28;

  if (
    cycle < 3 ||
    cycle > 20
  ) {
    return;
  }

  int radius =
    2 +
    (
      cycle - 3
    ) / 3;

  for (int i = 0; i < 8; i++) {
    int innerRadius =
      max(
        1,
        radius - 1
      );

    int x1 =
      centerX +
      directionX[i] *
      innerRadius /
      5;

    int y1 =
      centerY +
      directionY[i] *
      innerRadius /
      5;

    int x2 =
      centerX +
      directionX[i] *
      radius /
      5;

    int y2 =
      centerY +
      directionY[i] *
      radius /
      5;

    canvas.drawLine(
      x1,
      y1,
      x2,
      y2,
      color
    );

    if (cycle > 13) {
      canvas.drawPixel(
        x2,
        y2 + 2,
        TFT_WHITE
      );
    }
  }

  canvas.fillCircle(
    centerX,
    centerY,
    2,
    TFT_WHITE
  );
}

/**
 * @brief Draws the champion podium in the off-screen framebuffer.
 * | Desenha pódio de campeão no framebuffer fora da tela.
 */
void drawChampionPodium() {
  canvas.fillRect(
    48,
    103,
    64,
    20,
    TFT_LIGHTGREY
  );

  canvas.fillRect(
    55,
    96,
    50,
    27,
    TFT_WHITE
  );

  canvas.fillRect(
    62,
    91,
    36,
    32,
    TFT_YELLOW
  );

  canvas.drawRect(
    62,
    91,
    36,
    32,
    TFT_ORANGE
  );

  centeredText(
    "1",
    99,
    2,
    TFT_RED,
    TFT_YELLOW
  );
}

/**
 * @brief Draws the champion crown in the off-screen framebuffer.
 * | Desenha coroa de campeão no framebuffer fora da tela.
 */
void drawChampionCrown(
  int x,
  int y,
  int animationFrame
) {
  int bob =
    (
      animationFrame /
      3
    ) % 2;

  y -= bob;

  canvas.fillTriangle(
    x - 12,
    y + 8,
    x - 9,
    y - 4,
    x - 3,
    y + 8,
    TFT_YELLOW
  );

  canvas.fillTriangle(
    x - 5,
    y + 8,
    x,
    y - 7,
    x + 5,
    y + 8,
    TFT_YELLOW
  );

  canvas.fillTriangle(
    x + 3,
    y + 8,
    x + 9,
    y - 4,
    x + 12,
    y + 8,
    TFT_YELLOW
  );

  canvas.fillRect(
    x - 12,
    y + 6,
    24,
    5,
    TFT_ORANGE
  );

  canvas.fillCircle(
    x,
    y + 7,
    2,
    TFT_RED
  );
}

/**
 * @brief Draws one frame of the final champion celebration.
 * | Desenha um quadro da comemoração final de campeão.
 */
void drawChampionScreen() {
  clearCanvas(TFT_BLACK);

  // Fundo de arena.
  canvas.fillRect(
    0,
    0,
    SCREEN_W,
    SCREEN_H,
    TFT_NAVY
  );

  for (int y = 28; y < SCREEN_H; y += 10) {
    canvas.drawLine(
      0,
      y,
      SCREEN_W - 1,
      y,
      y % 20 == 0
        ? TFT_BLUE
        : TFT_BLACK
    );
  }

  drawChampionSpotlights(
    championFrame
  );

  drawFirework(
    24,
    46,
    championFrame,
    0,
    TFT_CYAN
  );

  drawFirework(
    136,
    46,
    championFrame,
    9,
    TFT_MAGENTA
  );

  drawFirework(
    43,
    67,
    championFrame,
    17,
    TFT_YELLOW
  );

  drawFirework(
    119,
    67,
    championFrame,
    23,
    TFT_GREEN
  );

  drawCelebrationConfetti(
    championFrame,
    25,
    112,
    26
  );

  drawChampionPodium();

  drawCelebratingPlayer(
    80,
    72,
    championFrame,
    true
  );

  drawChampionCrown(
    80,
    25,
    championFrame
  );

  drawChampionMarquee(
    championFrame
  );

  canvas.fillRoundRect(
    27,
    111,
    106,
    14,
    4,
    TFT_BLACK
  );

  canvas.drawRoundRect(
    27,
    111,
    106,
    14,
    4,
    TFT_YELLOW
  );

  centeredText(
    inputArmed
      ? "CENTRO: ABERTURA"
      : "VOCE VENCEU O JOGO!",
    115,
    1,
    inputArmed
      ? TFT_CYAN
      : TFT_WHITE,
    TFT_BLACK
  );

  presentCanvas();
}

// ======================================================
// Fight initialization and reset | Inicialização e reinício da luta
// ======================================================

/**
 * @brief Resets every timer that belongs to an active fight.
 * | Reinicia todos os temporizadores usados durante a luta.
 */
void resetCombatTimers() {
  frameTimer.resetMillis();
  enemyDecisionTimer.resetMillis();
  enemyReactionTimer.resetMillis();
  playerImpactTimer.resetMillis();
  playerActionTimer.resetMillis();
  enemyImpactTimer.resetMillis();
  enemyActionTimer.resetMillis();
  playerDodgeTimer.resetMillis();
  enemyDodgeTimer.resetMillis();
  enemyDefenseTimer.resetMillis();
}

/**
 * @brief Restores health, positions, meters and action flags before a new phase.
 * | Restaura energia, posições, medidores e ações antes de uma nova fase.
 */
void resetCombat() {
  playerHealth = PLAYER_MAX_HEALTH;

  enemyMaxHealth =
    scaledInt(
      phase().health,
      difficulty().healthPercentage
    );

  enemyHealth = enemyMaxHealth;

  playerSlot = 2;
  enemySlot = 2;

  playerHookPoints = 0;
  enemyHookPoints = 0;

  playerAction = ATTACK_NONE;
  enemyAction = ATTACK_NONE;

  playerDefending = false;
  enemyDefending = false;
  playerDodging = false;
  enemyDodging = false;
  playerAttackResolved = false;
  enemyAttackResolved = false;
  playerAlternateLeft = true;
  enemyAlternateLeft = false;
  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;

  playerFlashFrames = 0;
  enemyFlashFrames = 0;

  enemyHookReactionFrames = 0;
  enemyHookReactionDirection = 1;
  enemyKnockoutPending = false;

  resetCombatTimers();
}

/**
 * @brief Prepares the active opponent and opens the presentation screen.
 * | Prepara o adversário ativo e abre a tela de apresentação.
 */
void preparePhase() {
  resetCombat();

  gameState = PHASE_INTRO;
  portraitFrame = 0;
  portraitTimer.resetMillis();

  lockInput();

  hardClearScreen(TFT_BLACK);
  drawPhaseIntroScreen();

  sfxPhaseStart();
}

/**
 * @brief Starts gameplay after the opponent presentation.
 * | Inicia a luta após a apresentação do adversário.
 */
void beginFight() {
  resetCombatTimers();

  gameState = PLAYING;
  lockInput();

  hardClearScreen(TFT_BLACK);
  drawFight();
}

// ======================================================
// Heads-up display: health and hook meters | HUD: energia e medidores de gancho
// ======================================================

/**
 * @brief Draws a labeled health bar with color thresholds.
 * | Desenha uma barra de energia com rótulo e faixas de cor.
 */
void drawHealthBar(
  int x,
  int y,
  int width,
  int height,
  int health,
  int maximum,
  const char* label
) {
  canvas.setTextSize(1);
  canvas.setTextColor(TFT_WHITE, TFT_BLACK);
  canvas.setCursor(x, y);
  canvas.print(label);

  int barY = y + 9;

  canvas.drawRect(
    x,
    barY,
    width,
    height,
    TFT_WHITE
  );

  canvas.fillRect(
    x + 1,
    barY + 1,
    width - 2,
    height - 2,
    TFT_BLACK
  );

  int safeHealth =
    constrain(
      health,
      0,
      maximum
    );

  int fillWidth =
    safeHealth *
    (
      width - 2
    ) /
    maximum;

  uint16_t color =
    safeHealth <= maximum / 4
      ? TFT_RED
      : safeHealth <= maximum / 2
        ? TFT_YELLOW
        : TFT_GREEN;

  if (fillWidth > 0) {
    canvas.fillRect(
      x + 1,
      barY + 1,
      fillWidth,
      height - 2,
      color
    );
  }
}

/**
 * @brief Draws the four-segment hook meter.
 * | Desenha o medidor de gancho dividido em quatro segmentos.
 */
void drawHookMeter(
  int x,
  int y,
  int points,
  bool rightAligned
) {
  constexpr int SEGMENT_WIDTH = 9;
  constexpr int SEGMENT_HEIGHT = 4;
  constexpr int GAP = 2;

  int totalWidth =
    4 * SEGMENT_WIDTH +
    3 * GAP;

  int startX =
    rightAligned
      ? x - totalWidth
      : x;

  for (int i = 0; i < 4; i++) {
    int segmentPoints =
      points -
      i * 2;

    uint16_t color =
      segmentPoints >= 2
        ? TFT_YELLOW
        : segmentPoints == 1
          ? TFT_ORANGE
          : TFT_DARKGREY;

    int segmentX =
      startX +
      i *
      (
        SEGMENT_WIDTH +
        GAP
      );

    canvas.fillRect(
      segmentX,
      y,
      SEGMENT_WIDTH,
      SEGMENT_HEIGHT,
      color
    );

    canvas.drawRect(
      segmentX,
      y,
      SEGMENT_WIDTH,
      SEGMENT_HEIGHT,
      TFT_WHITE
    );
  }
}

/**
 * @brief Draws health, phase, difficulty and hook information.
 * | Desenha energia, fase, dificuldade e informações do gancho.
 */
void drawHUD() {
  canvas.fillRect(
    0,
    0,
    SCREEN_W,
    HUD_H,
    TFT_BLACK
  );

  drawHealthBar(
    3,
    1,
    68,
    8,
    playerHealth,
    PLAYER_MAX_HEALTH,
    "VOCE"
  );

  drawHealthBar(
    89,
    1,
    68,
    8,
    enemyHealth,
    enemyMaxHealth,
    phase().shortName
  );

  drawHookMeter(
    3,
    22,
    playerHookPoints,
    false
  );

  drawHookMeter(
    157,
    22,
    enemyHookPoints,
    true
  );

  canvas.setTextSize(1);
  canvas.setTextColor(
    difficulty().color,
    TFT_BLACK
  );

  canvas.setCursor(73, 2);
  canvas.print(difficulty().name[0]);

  canvas.setCursor(73, 12);
  canvas.print("F");
  canvas.print(currentPhase);

  if (
    playerHookPoints >=
    HOOK_READY_POINTS
  ) {
    canvas.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    canvas.setCursor(53, 21);
    canvas.print("GANCHO");
  }
}

// ======================================================
// Boxing ring background | Cenário do ringue
// ======================================================

/**
 * @brief Draws the boxing-ring background in perspective.
 * | Desenha o cenário do ringue em perspectiva.
 */
void drawRing() {
  canvas.fillRect(
    0,
    HUD_H,
    SCREEN_W,
    SCREEN_H - HUD_H,
    TFT_DARKGREY
  );

  canvas.fillRect(
    0,
    HUD_H,
    SCREEN_W,
    24,
    TFT_BLUE
  );

  canvas.drawLine(
    0,
    HUD_H + 5,
    SCREEN_W - 1,
    HUD_H + 5,
    TFT_RED
  );

  canvas.drawLine(
    0,
    HUD_H + 12,
    SCREEN_W - 1,
    HUD_H + 12,
    TFT_WHITE
  );

  canvas.drawLine(
    0,
    HUD_H + 19,
    SCREEN_W - 1,
    HUD_H + 19,
    TFT_RED
  );

  canvas.fillRect(
    2,
    HUD_H + 1,
    4,
    63,
    TFT_WHITE
  );

  canvas.fillRect(
    SCREEN_W - 6,
    HUD_H + 1,
    4,
    63,
    TFT_WHITE
  );

  canvas.fillRect(
    7,
    HUD_H + 25,
    SCREEN_W - 14,
    SCREEN_H - HUD_H - 25,
    TFT_LIGHTGREY
  );

  canvas.drawLine(
    7,
    SCREEN_H - 1,
    53,
    HUD_H + 25,
    TFT_WHITE
  );

  canvas.drawLine(
    SCREEN_W - 8,
    SCREEN_H - 1,
    107,
    HUD_H + 25,
    TFT_WHITE
  );

  canvas.drawLine(
    80,
    SCREEN_H - 1,
    80,
    HUD_H + 25,
    TFT_DARKGREY
  );
}

// ======================================================
// Player drawing and animation | Desenho e animação do jogador
// ======================================================

/**
 * @brief Draws the player hair in the off-screen framebuffer.
 * | Desenha cabelo do jogador no framebuffer fora da tela.
 */
void drawPlayerHair(int x, int headY) {
  canvas.fillCircle(
    x,
    headY - 4,
    7,
    TFT_BLACK
  );

  canvas.fillRect(
    x - 7,
    headY - 6,
    14,
    6,
    TFT_BLACK
  );

  canvas.fillCircle(
    x - 6,
    headY - 1,
    2,
    TFT_BLACK
  );

  canvas.fillCircle(
    x + 6,
    headY - 1,
    2,
    TFT_BLACK
  );
}

/**
 * @brief Draws the player lower body in the off-screen framebuffer.
 * | Desenha parte inferior do corpo do jogador no framebuffer fora da tela.
 */
void drawPlayerLowerBody(int x, int bodyY) {
  // Calcao.
  canvas.fillRect(
    x - 8,
    bodyY + 9,
    16,
    8,
    TFT_NAVY
  );

  // Pernas proximas e verticais.
  canvas.drawLine(
    x - 4,
    bodyY + 16,
    x - 4,
    bodyY + 25,
    TFT_ORANGE
  );

  canvas.drawLine(
    x + 4,
    bodyY + 16,
    x + 4,
    bodyY + 25,
    TFT_ORANGE
  );

  // Pes apoiados no piso.
  canvas.fillRect(
    x - 8,
    bodyY + 24,
    7,
    3,
    TFT_BLACK
  );

  canvas.fillRect(
    x + 2,
    bodyY + 24,
    7,
    3,
    TFT_BLACK
  );

  // Sombra.
  canvas.drawLine(
    x - 11,
    bodyY + 27,
    x + 11,
    bodyY + 27,
    TFT_DARKGREY
  );
}

/**
 * @brief Draws the player according to defense and attack states.
 * | Desenha o jogador conforme os estados de defesa e ataque.
 */
void drawPlayer() {
  int x = SLOT_X[playerSlot];
  int bodyY = 98;
  int headY = bodyY - 17;

  uint16_t bodyColor =
    playerFlashFrames > 0
      ? TFT_WHITE
      : TFT_BLUE;

  drawPlayerLowerBody(
    x,
    bodyY
  );

  canvas.fillRoundRect(
    x - 11,
    bodyY - 8,
    22,
    25,
    5,
    bodyColor
  );

  canvas.fillCircle(
    x,
    headY,
    8,
    TFT_ORANGE
  );

  drawPlayerHair(
    x,
    headY
  );

  if (playerDefending) {
    canvas.drawLine(
      x - 8,
      bodyY - 3,
      x - 5,
      bodyY - 16,
      TFT_ORANGE
    );

    canvas.drawLine(
      x + 8,
      bodyY - 3,
      x + 5,
      bodyY - 16,
      TFT_ORANGE
    );

    canvas.fillCircle(
      x - 5,
      bodyY - 17,
      5,
      TFT_RED
    );

    canvas.fillCircle(
      x + 5,
      bodyY - 17,
      5,
      TFT_RED
    );

    return;
  }

  if (
    playerAction ==
    ATTACK_PUNCH
  ) {
    int gloveX =
      playerHand == HAND_LEFT
        ? x - 7
        : x + 7;

    int armX =
      playerHand == HAND_LEFT
        ? x - 8
        : x + 8;

    int restingGloveX =
      playerHand == HAND_LEFT
        ? x + 12
        : x - 12;

    canvas.drawLine(
      armX,
      bodyY - 2,
      gloveX,
      bodyY - 27,
      TFT_ORANGE
    );

    canvas.fillCircle(
      gloveX,
      bodyY - 29,
      5,
      TFT_RED
    );

    canvas.fillCircle(
      restingGloveX,
      bodyY - 5,
      5,
      TFT_RED
    );

    return;
  }

  if (
    playerAction ==
    ATTACK_HOOK
  ) {
    int direction =
      playerHand == HAND_LEFT
        ? -1
        : 1;

    canvas.drawLine(
      x + direction * 8,
      bodyY - 2,
      x + direction * 17,
      bodyY - 15,
      TFT_ORANGE
    );

    canvas.drawLine(
      x + direction * 17,
      bodyY - 15,
      x + direction * 8,
      bodyY - 25,
      TFT_ORANGE
    );

    canvas.fillCircle(
      x + direction * 7,
      bodyY - 27,
      6,
      TFT_MAGENTA
    );

    canvas.fillCircle(
      x - direction * 12,
      bodyY - 5,
      5,
      TFT_RED
    );

    return;
  }

  canvas.drawLine(
    x - 8,
    bodyY - 2,
    x - 12,
    bodyY - 7,
    TFT_ORANGE
  );

  canvas.drawLine(
    x + 8,
    bodyY - 2,
    x + 12,
    bodyY - 7,
    TFT_ORANGE
  );

  canvas.fillCircle(
    x - 13,
    bodyY - 8,
    5,
    TFT_RED
  );

  canvas.fillCircle(
    x + 13,
    bodyY - 8,
    5,
    TFT_RED
  );
}

// ======================================================
// Distinct opponent appearance | Aparência exclusiva dos adversários
// ======================================================

/**
 * @brief Draws the mohawk in the off-screen framebuffer.
 * | Desenha moicano no framebuffer fora da tela.
 */
void drawMohawk(int x, int headY) {
  for (int i = -2; i <= 2; i++) {
    int spikeX =
      x +
      i * 2;

    canvas.fillTriangle(
      spikeX - 2,
      headY - 5,
      spikeX + 2,
      headY - 5,
      spikeX,
      headY - 12 -
      (
        2 -
        abs(i)
      ),
      TFT_BLACK
    );
  }
}

/**
 * @brief Draws the bald opponent headband in the off-screen framebuffer.
 * | Desenha faixa do adversário careca no framebuffer fora da tela.
 */
void drawBaldHeadband(
  int x,
  int headY,
  int radius
) {
  canvas.drawLine(
    x - radius,
    headY - 2,
    x + radius,
    headY - 2,
    TFT_BLUE
  );

  canvas.drawLine(
    x - radius,
    headY - 1,
    x + radius,
    headY - 1,
    TFT_BLUE
  );

  canvas.fillTriangle(
    x + radius - 1,
    headY - 1,
    x + radius + 5,
    headY + 1,
    x + radius,
    headY + 3,
    TFT_BLUE
  );
}

/**
 * @brief Draws hair and moustache in the off-screen framebuffer.
 * | Desenha cabelo e bigode no framebuffer fora da tela.
 */
void drawHairAndMoustache(
  int x,
  int headY,
  int radius
) {
  canvas.fillCircle(
    x,
    headY - radius + 2,
    radius - 1,
    TFT_BLACK
  );

  canvas.fillCircle(
    x - 5,
    headY - radius + 3,
    4,
    TFT_BLACK
  );

  canvas.fillCircle(
    x + 5,
    headY - radius + 3,
    4,
    TFT_BLACK
  );

  canvas.drawLine(
    x - 4,
    headY + 3,
    x - 1,
    headY + 4,
    TFT_BLACK
  );

  canvas.drawLine(
    x + 1,
    headY + 4,
    x + 4,
    headY + 3,
    TFT_BLACK
  );
}

/**
 * @brief Draws the boss head in the off-screen framebuffer.
 * | Desenha cabeça do chefão no framebuffer fora da tela.
 */
void drawBossHead(
  int x,
  int headY,
  int radius
) {
  canvas.fillRect(
    x - radius + 1,
    headY - radius,
    radius * 2 - 2,
    4,
    TFT_BLACK
  );

  canvas.drawLine(
    x - 6,
    headY - 2,
    x - 2,
    headY - 1,
    TFT_BLACK
  );

  canvas.drawLine(
    x + 2,
    headY - 1,
    x + 6,
    headY - 2,
    TFT_BLACK
  );

  canvas.fillTriangle(
    x - 6,
    headY + 3,
    x + 6,
    headY + 3,
    x,
    headY + 11,
    TFT_BLACK
  );
}

/**
 * @brief Draws the opponent face style in the off-screen framebuffer.
 * | Desenha estilo do rosto do adversário no framebuffer fora da tela.
 */
void drawEnemyFaceStyle(
  int x,
  int headY,
  int radius
) {
  switch (phase().visualStyle) {
    case STYLE_MOHAWK:
      drawMohawk(
        x,
        headY
      );
      break;

    case STYLE_BALD_HEADBAND:
      drawBaldHeadband(
        x,
        headY,
        radius
      );
      break;

    case STYLE_HAIR_MOUSTACHE:
      drawHairAndMoustache(
        x,
        headY,
        radius
      );
      break;

    case STYLE_BOSS_BEARD:
      drawBossHead(
        x,
        headY,
        radius
      );
      break;
  }
}

/**
 * @brief Draws opponent body details in the off-screen framebuffer.
 * | Desenha detalhes do corpo do adversário no framebuffer fora da tela.
 */
void drawEnemyBodyDetails(
  int x,
  int torsoTop,
  int torsoWidth,
  int torsoHeight
) {
  switch (phase().visualStyle) {
    case STYLE_MOHAWK:
      canvas.drawLine(
        x - 2,
        torsoTop + 6,
        x + 2,
        torsoTop + 9,
        TFT_YELLOW
      );

      canvas.drawLine(
        x + 2,
        torsoTop + 9,
        x - 2,
        torsoTop + 12,
        TFT_YELLOW
      );
      break;

    case STYLE_BALD_HEADBAND:
      for (int i = 0; i < 3; i++) {
        canvas.drawLine(
          x - torsoWidth / 2 + 2,
          torsoTop + 7 + i * 4,
          x + torsoWidth / 2 - 2,
          torsoTop + 7 + i * 4,
          TFT_WHITE
        );
      }
      break;

    case STYLE_HAIR_MOUSTACHE:
      canvas.fillRect(
        x - 1,
        torsoTop + 3,
        3,
        torsoHeight - 6,
        TFT_RED
      );
      break;

    case STYLE_BOSS_BEARD:
      canvas.fillRect(
        x - torsoWidth / 2 + 1,
        torsoTop + torsoHeight - 7,
        torsoWidth - 2,
        5,
        TFT_YELLOW
      );

      canvas.fillRect(
        x - 3,
        torsoTop + torsoHeight - 8,
        6,
        7,
        TFT_WHITE
      );
      break;
  }
}


/**
 * @brief Draws the special backward recoil caused by a clean hook.
 * | Desenha o recuo especial para trás causado por um gancho limpo.
 *
 * The legs remain fixed on the ring while the torso and head are displaced.
 * Two triangles form a slanted torso, making the impact visibly stronger than
 * a normal punch. The pose expands and then returns to the neutral position.
 *
 * | As pernas permanecem firmes no ringue enquanto o tronco e a cabeça são
 * | deslocados. Dois triângulos formam um tronco inclinado, deixando o impacto
 * | visivelmente mais forte que um soco normal. A pose aumenta e depois retorna
 * | gradualmente à posição neutra.
 */
void drawEnemyHookReaction() {
  int baseX = SLOT_X[enemySlot];
  int torsoTop = 54;
  int torsoWidth = phase().bodyWidth;
  int torsoHeight = phase().bodyHeight;
  int torsoBottom = torsoTop + torsoHeight;
  int headRadius = phase().headRadius;

  // Convert the remaining-frame counter into a triangular 0..6..0 motion.
  // | Converte a contagem restante em um movimento triangular 0..6..0.
  int elapsed =
    ENEMY_HOOK_REACTION_TOTAL_FRAMES -
    enemyHookReactionFrames +
    1;

  int half =
    ENEMY_HOOK_REACTION_TOTAL_FRAMES / 2;

  int strength =
    elapsed <= half
      ? elapsed
      : ENEMY_HOOK_REACTION_TOTAL_FRAMES - elapsed;

  strength =
    constrain(
      strength,
      0,
      half
    );

  int leanX =
    enemyHookReactionDirection *
    strength;

  int leanY =
    -strength / 2;

  int topCenterX =
    baseX + leanX;

  int headX =
    baseX + leanX * 2;

  int headY =
    torsoTop -
    9 +
    leanY -
    strength / 2;

  uint16_t bodyColor =
    enemyFlashFrames > 0
      ? TFT_WHITE
      : phase().bodyColor;

  // Feet remain planted to make the backward inclination easy to read.
  // | Os pés ficam plantados para tornar a inclinação fácil de perceber.
  canvas.drawLine(
    baseX - 4,
    torsoBottom - 1,
    baseX - 4,
    torsoBottom + 10,
    TFT_BLACK
  );

  canvas.drawLine(
    baseX + 4,
    torsoBottom - 1,
    baseX + 4,
    torsoBottom + 10,
    TFT_BLACK
  );

  canvas.fillRect(
    baseX - 7,
    torsoBottom + 9,
    6,
    2,
    TFT_BLACK
  );

  canvas.fillRect(
    baseX + 2,
    torsoBottom + 9,
    6,
    2,
    TFT_BLACK
  );

  // Slanted quadrilateral made from two triangles.
  // | Quadrilátero inclinado formado por dois triângulos.
  int bottomLeftX =
    baseX -
    torsoWidth / 2;

  int bottomRightX =
    baseX +
    torsoWidth / 2;

  int topLeftX =
    topCenterX -
    torsoWidth / 2;

  int topRightX =
    topCenterX +
    torsoWidth / 2;

  int shiftedTop =
    torsoTop +
    leanY;

  canvas.fillTriangle(
    topLeftX,
    shiftedTop,
    topRightX,
    shiftedTop,
    bottomLeftX,
    torsoBottom,
    bodyColor
  );

  canvas.fillTriangle(
    topRightX,
    shiftedTop,
    bottomRightX,
    torsoBottom,
    bottomLeftX,
    torsoBottom,
    bodyColor
  );

  // Reuse the opponent's exclusive clothing details on the displaced torso.
  // | Reaproveita os detalhes exclusivos da roupa no tronco deslocado.
  drawEnemyBodyDetails(
    topCenterX,
    shiftedTop,
    torsoWidth,
    torsoHeight
  );

  // Head and facial identity also follow the backward motion.
  // | A cabeça e a identidade facial acompanham o movimento para trás.
  canvas.fillCircle(
    headX,
    headY,
    headRadius,
    phase().skinColor
  );

  drawEnemyFaceStyle(
    headX,
    headY,
    headRadius
  );

  // Closed eyes and open mouth emphasize the heavy impact.
  // | Olhos fechados e boca aberta reforçam o impacto pesado.
  canvas.drawLine(
    headX - 5,
    headY - 1,
    headX - 1,
    headY + 1,
    TFT_BLACK
  );

  canvas.drawLine(
    headX + 1,
    headY + 1,
    headX + 5,
    headY - 1,
    TFT_BLACK
  );

  canvas.drawCircle(
    headX,
    headY + 5,
    2,
    TFT_BLACK
  );

  // Arms are thrown away from the guard during the recoil.
  // | Os braços são lançados para fora da guarda durante o recuo.
  canvas.drawLine(
    topLeftX,
    shiftedTop + 6,
    topLeftX - 8,
    shiftedTop + 1,
    phase().skinColor
  );

  canvas.drawLine(
    topRightX,
    shiftedTop + 6,
    topRightX + 8,
    shiftedTop + 1,
    phase().skinColor
  );

  canvas.fillCircle(
    topLeftX - 9,
    shiftedTop,
    4,
    phase().gloveColor
  );

  canvas.fillCircle(
    topRightX + 9,
    shiftedTop,
    4,
    phase().gloveColor
  );

  // Impact rays are visible only during the strongest part of the motion.
  // | Os raios aparecem somente na parte mais forte do movimento.
  if (strength >= half - 2) {
    int impactX =
      headX -
      enemyHookReactionDirection *
      (
        headRadius +
        5
      );

    int impactY =
      headY + 1;

    canvas.drawLine(
      impactX - 4,
      impactY,
      impactX + 4,
      impactY,
      TFT_YELLOW
    );

    canvas.drawLine(
      impactX,
      impactY - 4,
      impactX,
      impactY + 4,
      TFT_WHITE
    );

    canvas.drawLine(
      impactX - 3,
      impactY - 3,
      impactX + 3,
      impactY + 3,
      TFT_ORANGE
    );

    canvas.drawLine(
      impactX + 3,
      impactY - 3,
      impactX - 3,
      impactY + 3,
      TFT_ORANGE
    );
  }
}

/**
 * @brief Draws the active opponent using its exclusive visual style.
 * | Desenha o adversário ativo usando seu estilo visual exclusivo.
 */
void drawEnemy() {
  // A strong hook temporarily replaces the normal opponent pose.
  // | Um gancho forte substitui temporariamente a pose normal do adversário.
  if (enemyHookReactionFrames > 0) {
    drawEnemyHookReaction();
    return;
  }

  int x = SLOT_X[enemySlot];
  int torsoTop = 54;
  int torsoWidth = phase().bodyWidth;
  int torsoHeight = phase().bodyHeight;
  int torsoBottom = torsoTop + torsoHeight;
  int headY = torsoTop - 9;
  int headRadius = phase().headRadius;

  uint16_t bodyColor =
    enemyFlashFrames > 0
      ? TFT_WHITE
      : phase().bodyColor;

  canvas.drawLine(
    x - 4,
    torsoBottom - 1,
    x - 4,
    torsoBottom + 10,
    TFT_BLACK
  );

  canvas.drawLine(
    x + 4,
    torsoBottom - 1,
    x + 4,
    torsoBottom + 10,
    TFT_BLACK
  );

  canvas.fillRect(
    x - 7,
    torsoBottom + 9,
    6,
    2,
    TFT_BLACK
  );

  canvas.fillRect(
    x + 2,
    torsoBottom + 9,
    6,
    2,
    TFT_BLACK
  );

  if (
    phase().visualStyle ==
    STYLE_BOSS_BEARD
  ) {
    canvas.fillCircle(
      x - torsoWidth / 2,
      torsoTop + 5,
      5,
      bodyColor
    );

    canvas.fillCircle(
      x + torsoWidth / 2,
      torsoTop + 5,
      5,
      bodyColor
    );
  }

  canvas.fillRoundRect(
    x - torsoWidth / 2,
    torsoTop,
    torsoWidth,
    torsoHeight,
    4,
    bodyColor
  );

  drawEnemyBodyDetails(
    x,
    torsoTop,
    torsoWidth,
    torsoHeight
  );

  canvas.fillCircle(
    x,
    headY,
    headRadius,
    phase().skinColor
  );

  drawEnemyFaceStyle(
    x,
    headY,
    headRadius
  );

  canvas.drawPixel(
    x - 2,
    headY,
    TFT_BLACK
  );

  canvas.drawPixel(
    x + 2,
    headY,
    TFT_BLACK
  );

  if (enemyDefending) {
    canvas.drawLine(
      x - torsoWidth / 2,
      torsoTop + 5,
      x - 5,
      headY,
      phase().skinColor
    );

    canvas.drawLine(
      x + torsoWidth / 2,
      torsoTop + 5,
      x + 5,
      headY,
      phase().skinColor
    );

    canvas.fillCircle(
      x - 5,
      headY,
      4,
      phase().gloveColor
    );

    canvas.fillCircle(
      x + 5,
      headY,
      4,
      phase().gloveColor
    );

    return;
  }

  if (
    enemyAction ==
    ATTACK_PUNCH
  ) {
    int gloveX =
      enemyHand == HAND_LEFT
        ? x - 6
        : x + 6;

    int armX =
      enemyHand == HAND_LEFT
        ? x - torsoWidth / 2
        : x + torsoWidth / 2;

    int restingGloveX =
      enemyHand == HAND_LEFT
        ? x + torsoWidth / 2 + 3
        : x - torsoWidth / 2 - 3;

    canvas.drawLine(
      armX,
      torsoTop + 6,
      gloveX,
      torsoBottom + 8,
      phase().skinColor
    );

    canvas.fillCircle(
      gloveX,
      torsoBottom + 10,
      5,
      phase().gloveColor
    );

    canvas.fillCircle(
      restingGloveX,
      torsoTop + 8,
      4,
      phase().gloveColor
    );

    return;
  }

  if (
    enemyAction ==
    ATTACK_HOOK
  ) {
    int direction =
      enemyHand == HAND_LEFT
        ? -1
        : 1;

    canvas.drawLine(
      x + direction *
      (
        torsoWidth / 2
      ),
      torsoTop + 5,
      x + direction * 16,
      torsoTop + 13,
      phase().skinColor
    );

    canvas.drawLine(
      x + direction * 16,
      torsoTop + 13,
      x + direction * 7,
      torsoBottom + 8,
      phase().skinColor
    );

    canvas.fillCircle(
      x + direction * 6,
      torsoBottom + 10,
      6,
      phase().gloveColor
    );

    canvas.fillCircle(
      x - direction *
      (
        torsoWidth / 2 + 3
      ),
      torsoTop + 8,
      4,
      phase().gloveColor
    );

    return;
  }

  canvas.drawLine(
    x - torsoWidth / 2,
    torsoTop + 6,
    x - torsoWidth / 2 - 4,
    torsoTop + 11,
    phase().skinColor
  );

  canvas.drawLine(
    x + torsoWidth / 2,
    torsoTop + 6,
    x + torsoWidth / 2 + 4,
    torsoTop + 11,
    phase().skinColor
  );

  canvas.fillCircle(
    x - torsoWidth / 2 - 5,
    torsoTop + 12,
    4,
    phase().gloveColor
  );

  canvas.fillCircle(
    x + torsoWidth / 2 + 5,
    torsoTop + 12,
    4,
    phase().gloveColor
  );
}

// ======================================================
// Complete fight frame rendering | Renderização completa do quadro da luta
// ======================================================

/**
 * @brief Builds and presents one complete gameplay frame.
 * | Monta e apresenta um quadro completo da luta.
 */
void drawFight() {
  clearCanvas(TFT_BLACK);

  drawRing();
  drawEnemy();
  drawPlayer();
  drawHUD();

  presentCanvas();

  if (playerFlashFrames > 0) {
    playerFlashFrames--;
  }

  if (enemyFlashFrames > 0) {
    enemyFlashFrames--;
  }

  // The hook reaction advances one step only after the completed frame has
  // been shown. This keeps the animation synchronized with the display.
  // | A reação ao gancho avança somente depois que o quadro pronto foi
  // | mostrado. Assim, a animação permanece sincronizada com o display.
  if (enemyHookReactionFrames > 0) {
    enemyHookReactionFrames--;
  }
}

// ======================================================
// Movement, range and automatic hand selection | Movimento, alcance e seleção automática da mão
// ======================================================

/**
 * @brief Chooses the hand closest to the target, alternating when aligned.
 * | Escolhe a mão mais próxima do alvo, alternando quando estão alinhados.
 */
PunchHand selectAttackHand(
  int attackerSlot,
  int targetSlot,
  bool& alternateLeft
) {
  if (targetSlot < attackerSlot) {
    return HAND_LEFT;
  }

  if (targetSlot > attackerSlot) {
    return HAND_RIGHT;
  }

  PunchHand selected =
    alternateLeft
      ? HAND_LEFT
      : HAND_RIGHT;

  alternateLeft = !alternateLeft;

  return selected;
}

/**
 * @brief Checks whether the lateral positions permit a hit.
 * | Verifica se as posições laterais permitem que o golpe acerte.
 */
bool fightersInRange() {
  return
    abs(
      playerSlot -
      enemySlot
    ) <= 1;
}

/**
 * @brief Moves the player one slot and opens a short dodge window.
 * | Move o jogador uma posição e abre uma pequena janela de esquiva.
 */
void movePlayer(int direction) {
  int nextSlot =
    constrain(
      playerSlot +
      direction,
      0,
      SLOT_COUNT - 1
    );

  if (nextSlot == playerSlot) {
    return;
  }

  playerSlot = nextSlot;
  playerDodging = true;

  playerDodgeTimer.resetMillis();
  sfxStep();
}

/**
 * @brief Moves the opponent one slot toward the player.
 * | Move o adversário uma posição em direção ao jogador.
 */
void moveEnemyTowardPlayer() {
  if (enemySlot < playerSlot) {
    enemySlot++;
  } else if (enemySlot > playerSlot) {
    enemySlot--;
  }

  enemySlot =
    constrain(
      enemySlot,
      0,
      SLOT_COUNT - 1
    );

  enemyDodging = true;
  enemyDodgeTimer.resetMillis();
}

/**
 * @brief Moves the opponent one slot away from the player.
 * | Move o adversário uma posição para longe do jogador.
 */
void moveEnemyAwayFromPlayer() {
  int direction;

  if (enemySlot < playerSlot) {
    direction = -1;
  } else if (enemySlot > playerSlot) {
    direction = 1;
  } else {
    direction =
      random(0, 2)
        ? 1
        : -1;
  }

  int nextSlot =
    constrain(
      enemySlot +
      direction,
      0,
      SLOT_COUNT - 1
    );

  if (nextSlot == enemySlot) {
    nextSlot =
      constrain(
        enemySlot -
        direction,
        0,
        SLOT_COUNT - 1
      );
  }

  enemySlot = nextSlot;
  enemyDodging = true;

  enemyDodgeTimer.resetMillis();
}

/**
 * @brief Moves the opponent to a randomly chosen neighboring slot.
 * | Move o adversário para uma posição vizinha escolhida aleatoriamente.
 */
void moveEnemyRandomly() {
  int direction =
    random(0, 2)
      ? 1
      : -1;

  int nextSlot =
    constrain(
      enemySlot +
      direction,
      0,
      SLOT_COUNT - 1
    );

  if (nextSlot == enemySlot) {
    nextSlot =
      constrain(
        enemySlot -
        direction,
        0,
        SLOT_COUNT - 1
      );
  }

  enemySlot = nextSlot;
  enemyDodging = true;

  enemyDodgeTimer.resetMillis();
}

// ======================================================
// Special hook meters | Medidores especiais de gancho
// ======================================================

/**
 * @brief Adds points to the player hook meter and signals when it becomes ready.
 * | Adiciona pontos ao medidor do jogador e avisa quando o gancho fica pronto.
 */
void addPlayerHookPoints(int points) {
  int previous =
    playerHookPoints;

  playerHookPoints =
    constrain(
      playerHookPoints +
      points,
      0,
      HOOK_READY_POINTS
    );

  if (
    previous <
      HOOK_READY_POINTS &&
    playerHookPoints >=
      HOOK_READY_POINTS
  ) {
    sfxHookReady();
  }
}

/**
 * @brief Adds points to the opponent hook meter.
 * | Adiciona pontos ao medidor de gancho do adversário.
 */
void addEnemyHookPoints(int points) {
  enemyHookPoints =
    constrain(
      enemyHookPoints +
      points,
      0,
      HOOK_READY_POINTS
    );
}

// ======================================================
// Opponent reactions | Reações do adversário
// ======================================================

/**
 * @brief Decides whether the AI will dodge or defend against the new player attack.
 * | Decide se a IA irá esquivar ou defender o novo ataque do jogador.
 */
void scheduleEnemyReaction(
  AttackAction playerAttack
) {
  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;

  if (
    enemyAction != ATTACK_NONE ||
    enemyDefending
  ) {
    return;
  }

  int reactionChance =
    phase().reactionChance +
    difficulty().reactionBonus;

  if (
    playerAttack ==
    ATTACK_HOOK
  ) {
    reactionChance += 15;
  }

  reactionChance =
    constrain(
      reactionChance,
      0,
      88
    );

  if (
    random(0, 100) >=
    reactionChance
  ) {
    return;
  }

  int baseDodgeChance =
    30 +
    phaseIndex() * 10;

  int dodgeChance =
    constrain(
      baseDodgeChance +
      difficulty().dodgeBonus,
      5,
      85
    );

  enemyReaction =
    random(0, 100) <
      dodgeChance
      ? REACTION_DODGE
      : REACTION_DEFEND;

  enemyReactionPending = true;
  enemyReactionTimer.resetMillis();
}

/**
 * @brief Executes a previously scheduled AI reaction after its reaction delay.
 * | Executa uma reação agendada da IA após o tempo de reação.
 */
void updateEnemyReaction() {
  if (
    enemyHookReactionFrames > 0 ||
    enemyKnockoutPending
  ) {
    enemyReactionPending = false;
    enemyReaction = REACTION_NONE;
    return;
  }

  if (!enemyReactionPending) {
    return;
  }

  if (
    playerAction == ATTACK_NONE ||
    enemyAction != ATTACK_NONE ||
    enemyDefending
  ) {
    enemyReactionPending = false;
    enemyReaction = REACTION_NONE;
    return;
  }

  unsigned long reactionTime =
    scaledTime(
      phase().reactionMs,
      difficulty().
        attackTimePercentage
    );

  if (
    playerAction ==
    ATTACK_HOOK
  ) {
    reactionTime += 25;
  }

  if (
    !enemyReactionTimer.
      intervalMillis(
        reactionTime
      )
  ) {
    return;
  }

  enemyReactionPending = false;

  if (
    enemyReaction ==
    REACTION_DODGE
  ) {
    moveEnemyAwayFromPlayer();
    sfxDodge();
  } else if (
    enemyReaction ==
    REACTION_DEFEND
  ) {
    enemyDefending = true;
    enemyDefenseTimer.resetMillis();
    sfxGuard();
  }

  enemyReaction = REACTION_NONE;
}

// ======================================================
// Attack initialization | Inicialização dos ataques
// ======================================================

/**
 * @brief Starts a player punch or hook and selects the correct hand.
 * | Inicia um soco ou gancho do jogador e seleciona a mão correta.
 */
void startPlayerAttack(AttackAction attack) {
  if (
    playerAction !=
    ATTACK_NONE
  ) {
    return;
  }

  playerDefending = false;
  playerAction = attack;
  playerAttackResolved = false;

  playerHand =
    selectAttackHand(
      playerSlot,
      enemySlot,
      playerAlternateLeft
    );

  if (
    attack ==
    ATTACK_HOOK
  ) {
    playerHookPoints = 0;
    sfxHookSwing(false);
  } else {
    sfxPunchSwing(false);
  }

  playerImpactTimer.resetMillis();
  playerActionTimer.resetMillis();

  scheduleEnemyReaction(attack);
}

/**
 * @brief Starts an opponent punch or hook.
 * | Inicia um soco ou gancho do adversário.
 */
void startEnemyAttack(AttackAction attack) {
  if (
    enemyAction !=
    ATTACK_NONE
  ) {
    return;
  }

  enemyDefending = false;
  enemyAction = attack;
  enemyAttackResolved = false;

  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;

  enemyHand =
    selectAttackHand(
      enemySlot,
      playerSlot,
      enemyAlternateLeft
    );

  if (
    attack ==
    ATTACK_HOOK
  ) {
    enemyHookPoints = 0;
    sfxHookSwing(true);
  } else {
    sfxPunchSwing(true);
  }

  enemyImpactTimer.resetMillis();
  enemyActionTimer.resetMillis();
}

/**
 * @brief Places the opponent in guard for a limited time.
 * | Coloca o adversário em defesa por um tempo limitado.
 */
void startEnemyDefense() {
  if (
    enemyAction !=
    ATTACK_NONE
  ) {
    return;
  }

  enemyDefending = true;
  enemyDefenseTimer.resetMillis();
  sfxGuard();
}

// ======================================================
// Player input handling | Leitura dos controles do jogador
// ======================================================

/**
 * @brief Reads movement, defense, punch and hook commands during gameplay.
 * | Lê os comandos de movimento, defesa, soco e gancho durante a luta.
 */
void readPlayerControls() {
  if (!inputArmed) {
    return;
  }

  bool wantsDefense =
    playerAction ==
      ATTACK_NONE &&
    keyboard.hold(
      KEY_DOWN
    );

  if (
    wantsDefense &&
    !playerDefending
  ) {
    sfxGuard();
  }

  playerDefending =
    wantsDefense;

  if (
    playerAction != ATTACK_NONE ||
    playerDefending
  ) {
    return;
  }

  if (
    keyboard.press(
      KEY_LEFT
    )
  ) {
    movePlayer(-1);
    return;
  }

  if (
    keyboard.press(
      KEY_RIGHT
    )
  ) {
    movePlayer(1);
    return;
  }

  if (
    keyboard.press(
      KEY_UP
    ) &&
    playerHookPoints >=
      HOOK_READY_POINTS
  ) {
    startPlayerAttack(
      ATTACK_HOOK
    );

    return;
  }

  if (
    keyboard.press(
      KEY_CENTER
    )
  ) {
    startPlayerAttack(
      ATTACK_PUNCH
    );
  }
}

// ======================================================
// Opponent artificial intelligence | Inteligência artificial dos adversários
// ======================================================

/**
 * @brief Chooses the opponent next action from distance, meters and difficulty.
 * | Escolhe a próxima ação do adversário usando distância, medidores e dificuldade.
 */
void updateEnemyAI() {
  unsigned long decisionInterval =
    scaledTime(
      phase().decisionMs,
      difficulty().
        decisionTimePercentage
    );

  if (
    !enemyDecisionTimer.
      intervalMillis(
        decisionInterval
      )
  ) {
    return;
  }

  if (
    enemyAction != ATTACK_NONE ||
    enemyDefending ||
    enemyReactionPending ||
    enemyHookReactionFrames > 0 ||
    enemyKnockoutPending
  ) {
    return;
  }

  int distance =
    abs(
      playerSlot -
      enemySlot
    );

  if (distance > 1) {
    int approachChance =
      phase().approachChance;

    if (
      selectedDifficulty ==
      HARD
    ) {
      approachChance += 4;
    }

    approachChance =
      constrain(
        approachChance,
        0,
        98
      );

    if (
      random(0, 100) <
      approachChance
    ) {
      moveEnemyTowardPlayer();
    } else {
      moveEnemyRandomly();
    }

    return;
  }

  if (
    currentPhase >= 2 &&
    enemyHookPoints >=
      HOOK_READY_POINTS
  ) {
    int hookChance =
      30 +
      phaseIndex() * 12 +
      difficulty().hookBonus;

    if (playerDefending) {
      hookChance += 10;
    }

    hookChance =
      constrain(
        hookChance,
        5,
        92
      );

    if (
      random(0, 100) <
      hookChance
    ) {
      startEnemyAttack(
        ATTACK_HOOK
      );

      return;
    }
  }

  int attackChance =
    phase().attackChance;

  int defenseChance =
    phase().defenseChance +
    difficulty().defenseBonus;

  if (
    playerDefending &&
    currentPhase ==
      TOTAL_PHASES
  ) {
    attackChance += 8;
  }

  attackChance =
    constrain(
      attackChance,
      10,
      92
    );

  defenseChance =
    constrain(
      defenseChance,
      2,
      45
    );

  int decision =
    random(0, 100);

  if (
    decision <
    attackChance
  ) {
    startEnemyAttack(
      ATTACK_PUNCH
    );
    return;
  }

  if (
    decision <
    attackChance +
    defenseChance
  ) {
    startEnemyDefense();
    return;
  }

  if (
    selectedDifficulty ==
    HARD
  ) {
    moveEnemyTowardPlayer();
  } else if (
    random(0, 100) < 55
  ) {
    moveEnemyAwayFromPlayer();
  } else {
    moveEnemyRandomly();
  }
}

// ======================================================
// Temporary dodge and defense states | Estados temporários de esquiva e defesa
// ======================================================

/**
 * @brief Ends dodge and defense states when their timers expire.
 * | Encerra os estados de esquiva e defesa quando seus tempos terminam.
 */
void updateTemporaryStates() {
  if (
    playerDodging &&
    playerDodgeTimer.
      intervalMillis(
        difficulty().
          playerDodgeMs
      )
  ) {
    playerDodging = false;
  }

  if (
    enemyDodging &&
    enemyDodgeTimer.
      intervalMillis(
        phase().dodgeMs
      )
  ) {
    enemyDodging = false;
  }

  long defenseDuration =
    static_cast<long>(
      phase().defenseMs
    ) +
    static_cast<long>(
      difficulty().
        defenseBonus
    ) * 8L;

  if (defenseDuration < 240) {
    defenseDuration = 240;
  }

  if (
    enemyDefending &&
    enemyDefenseTimer.
      intervalMillis(
        static_cast<unsigned long>(
          defenseDuration
        )
      )
  ) {
    enemyDefending = false;
  }
}

// ======================================================
// Collision, defense and damage resolution | Resolução de colisão, defesa e dano
// ======================================================

/**
 * @brief Checks range, dodge and guard, then applies player damage.
 * | Verifica alcance, esquiva e defesa e então aplica o dano do jogador.
 */
void resolvePlayerAttack() {
  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;

  if (enemyDodging) {
    sfxDodge();
    return;
  }

  if (!fightersInRange()) {
    sfxMiss();
    return;
  }

  bool blocked =
    enemyDefending;

  bool cleanHookHit =
    playerAction == ATTACK_HOOK &&
    !blocked;

  int damage = 0;
  int meterGain = 0;

  if (
    playerAction ==
    ATTACK_PUNCH
  ) {
    damage =
      blocked
        ? PLAYER_PUNCH_BLOCKED_DAMAGE
        : PLAYER_PUNCH_DAMAGE;

    meterGain =
      blocked
        ? BLOCKED_HIT_POINTS
        : CLEAN_HIT_POINTS;
  } else {
    damage =
      blocked
        ? PLAYER_HOOK_BLOCKED_DAMAGE
        : PLAYER_HOOK_DAMAGE;

    if (!blocked) {
      // A clean hook interrupts any action the opponent was performing.
      // | Um gancho limpo interrompe qualquer ação do adversário.
      enemyAction = ATTACK_NONE;
      enemyAttackResolved = false;
      enemyDodging = false;
      enemyDefending = false;
    }
  }

  enemyHealth =
    max(
      0,
      enemyHealth -
      damage
    );

  enemyFlashFrames =
    blocked
      ? 2
      : 4;

  if (cleanHookHit) {
    // The upper body is thrown to the opposite side of the glove used.
    // | O tronco é lançado para o lado oposto ao da luva utilizada.
    enemyHookReactionDirection =
      playerHand == HAND_LEFT
        ? 1
        : -1;

    enemyHookReactionFrames =
      ENEMY_HOOK_REACTION_TOTAL_FRAMES;
  }

  if (blocked) {
    sfxBlock();
  } else {
    sfxImpact(
      false,
      playerAction ==
        ATTACK_HOOK
    );
  }

  if (
    playerAction ==
      ATTACK_PUNCH &&
    enemyHealth > 0
  ) {
    addPlayerHookPoints(
      meterGain
    );
  }

  if (enemyHealth <= 0) {
    if (cleanHookHit) {
      // Keep gameplay active only long enough to show the strong-hit pose.
      // | Mantém a luta ativa apenas pelo tempo necessário para mostrar o recuo.
      enemyKnockoutPending = true;
      return;
    }

    finishEnemyKnockout();
  }
}

/**
 * @brief Checks range, dodge and guard, then applies opponent damage.
 * | Verifica alcance, esquiva e defesa e então aplica o dano do adversário.
 */
void resolveEnemyAttack() {
  if (playerDodging) {
    sfxDodge();
    return;
  }

  if (!fightersInRange()) {
    sfxMiss();
    return;
  }

  bool blocked =
    playerDefending;

  int baseDamage;
  int meterGain = 0;

  if (
    enemyAction ==
    ATTACK_PUNCH
  ) {
    baseDamage =
      blocked
        ? phase().
          punchBlockedDamage
        : phase().
          punchDamage;

    meterGain =
      blocked
        ? BLOCKED_HIT_POINTS
        : CLEAN_HIT_POINTS;
  } else {
    baseDamage =
      blocked
        ? phase().
          hookBlockedDamage
        : phase().
          hookDamage;

    if (!blocked) {
      playerAction = ATTACK_NONE;
      playerAttackResolved = false;
      enemyReactionPending = false;
      enemyReaction = REACTION_NONE;
    }
  }

  int damage =
    scaledInt(
      baseDamage,
      difficulty().
        damagePercentage
    );

  damage =
    max(
      1,
      damage
    );

  playerHealth =
    max(
      0,
      playerHealth -
      damage
    );

  playerFlashFrames =
    blocked
      ? 2
      : 4;

  if (blocked) {
    sfxBlock();
  } else {
    sfxImpact(
      true,
      enemyAction ==
        ATTACK_HOOK
    );
  }

  if (
    enemyAction ==
      ATTACK_PUNCH &&
    playerHealth > 0
  ) {
    addEnemyHookPoints(
      meterGain
    );
  }

  if (playerHealth <= 0) {
    finishPlayerKnockout();
  }
}

// ======================================================
// Attack timing and combo updates | Atualização dos tempos de ataque e combinações
// ======================================================

/**
 * @brief Advances the impact and recovery timing of the player attack.
 * | Avança os tempos de impacto e recuperação do ataque do jogador.
 */
void updatePlayerAttack() {
  if (
    playerAction ==
    ATTACK_NONE
  ) {
    return;
  }

  unsigned long impactTime =
    playerAction ==
      ATTACK_HOOK
      ? PLAYER_HOOK_IMPACT_MS
      : PLAYER_PUNCH_IMPACT_MS;

  unsigned long totalTime =
    playerAction ==
      ATTACK_HOOK
      ? PLAYER_HOOK_TOTAL_MS
      : PLAYER_PUNCH_TOTAL_MS;

  if (
    !playerAttackResolved &&
    playerImpactTimer.
      intervalMillis(
        impactTime
      )
  ) {
    playerAttackResolved = true;
    resolvePlayerAttack();
  }

  if (
    playerActionTimer.
      intervalMillis(
        totalTime
      )
  ) {
    playerAction = ATTACK_NONE;
    playerAttackResolved = false;
    enemyReactionPending = false;
    enemyReaction = REACTION_NONE;
  }
}

/**
 * @brief Advances the opponent attack and may start a difficulty-based combo.
 * | Avança o ataque adversário e pode iniciar uma combinação conforme a dificuldade.
 */
void updateEnemyAttack() {
  if (
    enemyAction ==
    ATTACK_NONE
  ) {
    return;
  }

  unsigned long impactTime =
    enemyAction ==
      ATTACK_HOOK
      ? phase().
        hookImpactMs
      : phase().
        punchImpactMs;

  unsigned long totalTime =
    enemyAction ==
      ATTACK_HOOK
      ? phase().
        hookTotalMs
      : phase().
        punchTotalMs;

  impactTime =
    scaledTime(
      impactTime,
      difficulty().
        attackTimePercentage
    );

  totalTime =
    scaledTime(
      totalTime,
      difficulty().
        attackTimePercentage
    );

  if (
    !enemyAttackResolved &&
    enemyImpactTimer.
      intervalMillis(
        impactTime
      )
  ) {
    enemyAttackResolved = true;
    resolveEnemyAttack();
  }

  if (
    enemyActionTimer.
      intervalMillis(
        totalTime
      )
  ) {
    AttackAction completedAction =
      enemyAction;

    enemyAction = ATTACK_NONE;
    enemyAttackResolved = false;

    bool canUseCombination =
      completedAction ==
        ATTACK_PUNCH &&
      gameState ==
        PLAYING &&
      fightersInRange() &&
      !playerDodging;

    if (
      canUseCombination &&
      random(0, 100) <
        difficulty().
          comboChance
    ) {
      startEnemyAttack(
        ATTACK_PUNCH
      );
    }
  }
}

/**
 * @brief Updates both active attack state machines.
 * | Atualiza as máquinas de estado dos ataques ativos.
 */
void updateCombat() {
  updatePlayerAttack();

  if (
    gameState ==
    PLAYING
  ) {
    updateEnemyAttack();
  }
}

// ======================================================
// Knockout and screen transitions | Nocautes e transições de tela
// ======================================================

/**
 * @brief Ends the phase and opens victory or champion celebration.
 * | Encerra a fase e abre a comemoração de vitória ou de campeão.
 */
void finishEnemyKnockout() {
  playerAction = ATTACK_NONE;
  enemyAction = ATTACK_NONE;
  playerDefending = false;
  enemyDefending = false;
  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;
  enemyHookReactionFrames = 0;
  enemyKnockoutPending = false;

  drawFight();
  sfxKnockout();

  if (
    currentPhase >=
    TOTAL_PHASES
  ) {
    gameState =
      CHAMPION_SCREEN;

    championFrame = 0;
    championTimer.resetMillis();

    lockInput();
    hardClearScreen(TFT_BLACK);
    drawChampionScreen();
    sfxChampion();

    return;
  }

  gameState =
    PHASE_VICTORY;

  victoryFrame = 0;
  victoryTimer.resetMillis();

  lockInput();
  hardClearScreen(TFT_BLACK);
  drawPhaseVictoryScreen();
  sfxVictory();
}

/**
 * @brief Ends gameplay and opens the animated Game Over screen.
 * | Encerra a luta e abre a tela animada de Game Over.
 */
void finishPlayerKnockout() {
  playerAction = ATTACK_NONE;
  enemyAction = ATTACK_NONE;
  playerDefending = false;
  enemyDefending = false;
  enemyReactionPending = false;
  enemyReaction = REACTION_NONE;
  enemyHookReactionFrames = 0;
  enemyKnockoutPending = false;

  drawFight();
  sfxKnockout();

  gameState =
    GAME_OVER;

  gameOverFrame = 0;
  gameOverTimer.resetMillis();

  lockInput();
  hardClearScreen(TFT_BLACK);
  drawGameOverScreen();
  sfxGameOver();
}

// ======================================================
// Finite-state-machine updates | Atualização da máquina de estados
// ======================================================

/**
 * @brief Runs one complete gameplay update before drawing the next frame.
 * | Executa uma atualização completa da luta antes de desenhar o próximo quadro.
 */
void updatePlaying() {
  updateInputGate(
    FIGHT_LOCK_MS
  );

  // When the final hit is a hook, freeze combat decisions and show the full
  // recoil before opening the victory screen.
  // | Quando o golpe final é um gancho, congela as decisões da luta e mostra
  // | todo o recuo antes de abrir a tela de vitória.
  if (enemyKnockoutPending) {
    if (enemyHookReactionFrames > 0) {
      drawFight();
      return;
    }

    finishEnemyKnockout();
    return;
  }

  readPlayerControls();
  updateEnemyReaction();
  updateEnemyAI();
  updateTemporaryStates();
  updateCombat();

  if (
    gameState ==
    PLAYING
  ) {
    drawFight();
  }
}

/**
 * @brief Animates the opponent portrait and waits for the fight command.
 * | Anima o retrato do adversário e aguarda o comando para lutar.
 */
void updatePhaseIntro() {
  bool redraw =
    updateInputGate(
      INTRO_MIN_MS
    );

  if (
    portraitTimer.intervalMillis(
      PORTRAIT_FRAME_MS
    )
  ) {
    portraitFrame++;
    redraw = true;
  }

  if (redraw) {
    drawPhaseIntroScreen();
  }

  if (
    inputArmed &&
    keyboard.press(
      KEY_CENTER
    )
  ) {
    beginFight();
  }
}

/**
 * @brief Animates the victory scene and waits before allowing the next phase.
 * | Anima a vitória e aguarda antes de liberar a próxima fase.
 */
void updatePhaseVictory() {
  bool redraw =
    updateInputGate(
      VICTORY_MIN_MS
    );

  if (
    victoryTimer.intervalMillis(
      VICTORY_FRAME_MS
    )
  ) {
    victoryFrame++;
    redraw = true;
  }

  if (redraw) {
    drawPhaseVictoryScreen();
  }

  if (
    inputArmed &&
    keyboard.press(
      KEY_CENTER
    )
  ) {
    currentPhase++;
    preparePhase();
  }
}

/**
 * @brief Animates Game Over and restarts through the opening when confirmed.
 * | Anima o Game Over e reinicia pela abertura após a confirmação.
 */
void updateGameOver() {
  bool redraw =
    updateInputGate(
      GAME_OVER_MIN_MS
    );

  if (
    gameOverTimer.intervalMillis(
      GAME_OVER_FRAME_MS
    )
  ) {
    gameOverFrame++;
    redraw = true;
  }

  if (redraw) {
    drawGameOverScreen();
  }

  if (
    inputArmed &&
    keyboard.press(
      KEY_CENTER
    )
  ) {
    startOpening();
  }
}

/**
 * @brief Animates the final celebration and restarts through the opening.
 * | Anima a comemoração final e reinicia pela abertura.
 */
void updateChampionScreen() {
  bool redraw =
    updateInputGate(
      CHAMPION_MIN_MS
    );

  if (
    championTimer.intervalMillis(
      CHAMPION_FRAME_MS
    )
  ) {
    championFrame++;
    redraw = true;
  }

  if (redraw) {
    drawChampionScreen();
  }

  if (
    inputArmed &&
    keyboard.press(
      KEY_CENTER
    )
  ) {
    startOpening();
  }
}

// ======================================================
// Hardware and game initialization | Inicialização do hardware e do jogo
// ======================================================

/**
 * @brief Initializes Serial, TFT, buzzer, framebuffer and the opening state.
 * | Inicializa Serial, TFT, buzzer, framebuffer e a tela de abertura.
 */
void setup() {
  Serial.begin(115200); // Start the diagnostic serial port | Inicia a porta serial de diagnóstico

  Serial.print("ES32Lab LIB: "); // Print the installed library version | Imprime a versão instalada da biblioteca
  Serial.println(ES32LAB_VERSION);

  randomSeed(
    analogRead(
      P_POT1 // Use analog noise to vary AI decisions between matches | Usa ruído analógico para variar as decisões da IA
    )
  );

  display.init();               // Initialize the ES32Lab TFT | Inicializa o TFT da ES32Lab
  display.setRotation(3);       // Recommended landscape rotation | Rotação horizontal recomendada
  display.fillScreen(TFT_BLACK); // Clear the physical display | Limpa o display físico

  buzzer.begin();        // Initialize the onboard buzzer | Inicializa o buzzer onboard
  buzzer.setSpeed(220);  // Keep game effects short | Mantém os efeitos do jogo curtos
  buzzer.setPitch(100);  // Default pitch correction | Correção padrão de tom
  buzzer.setVolume(55);  // Initial volume; menu can mute all effects | Volume inicial; o menu pode silenciar os efeitos

  canvas.setColorDepth(16); // Use 16-bit colors in the framebuffer | Usa cores de 16 bits no framebuffer

  canvasReady =
    canvas.createSprite(
      SCREEN_W,
      SCREEN_H
    ) != nullptr; // Allocate the complete off-screen frame | Aloca o quadro completo fora da tela

  if (!canvasReady) {
    display.fillScreen(TFT_RED);
    display.setTextColor(
      TFT_WHITE,
      TFT_RED
    );
    display.setTextSize(1);
    display.setCursor(8, 45);
    display.print("ERRO: SEM MEMORIA");
    display.setCursor(8, 60);
    display.print("PARA O FRAMEBUFFER");

    Serial.println(
      "Nao foi possivel criar o framebuffer."
    );

    return;
  }

  canvas.setTextWrap(false);      // Prevent automatic text wrapping | Evita quebra automática de texto
  canvas.fillSprite(TFT_BLACK);     // Start with a clean framebuffer | Inicia com o framebuffer limpo

  startOpening(); // Enter the first state of the game | Entra no primeiro estado do jogo
}

// ======================================================
// Main finite-state-machine loop | Laço principal da máquina de estados
// ======================================================

/**
 * @brief Runs the finite-state machine without blocking the active animations.
 * | Executa a máquina de estados sem bloquear as animações ativas.
 */
void loop() {
  if (!canvasReady) {
    return;
  }

  switch (gameState) {
    case OPENING: // Animated title screen | Tela de título animada
      updateOpening();
      break;

    case DIFFICULTY_MENU: // Difficulty and sound selection | Seleção de dificuldade e som
      updateDifficultyMenu();
      break;

    case PHASE_INTRO: // Animated opponent presentation | Apresentação animada do adversário
      updatePhaseIntro();
      break;

    case PLAYING: // Active boxing match | Luta de boxe em andamento
      if (
        frameTimer.intervalMillis(
          FRAME_MS
        )
      ) {
        updatePlaying();
      }
      break;

    case PHASE_VICTORY: // Player celebration between phases | Comemoração entre as fases
      updatePhaseVictory();
      break;

    case GAME_OVER: // Animated defeat screen | Tela animada de derrota
      updateGameOver();
      break;

    case CHAMPION_SCREEN: // Final celebration after all four opponents | Comemoração após os quatro adversários
      updateChampionScreen();
      break;
  }
}