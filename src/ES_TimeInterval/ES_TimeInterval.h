/**
 * @file ES_TimeInterval.h
 * @author Eder João Santini
 * @date 28/12/2018
 * @brief Time interval control helper for non-blocking routines.
 * | Classe auxiliar para controle de intervalos de tempo em rotinas não bloqueantes.
 *
 * The ES_TimeInterval class provides simple methods to check elapsed time using millis()
 * and micros(), allowing periodic actions without using delay().
 *
 * | A classe ES_TimeInterval fornece métodos simples para verificar tempo decorrido usando
 * millis() e micros(), permitindo executar ações periódicas sem utilizar delay().
 *
 * @note There are 1000 microseconds in 1 millisecond and 1,000,000 microseconds in 1 second.
 * | Existem 1000 microssegundos em 1 milissegundo e 1.000.000 microssegundos em 1 segundo.
 */
#ifndef ES_TIMEINTERVAL_H
#define ES_TIMEINTERVAL_H

#include <Arduino.h>

#define ES_TIMEINTERVAL_VERSION "0.4.0 update 06/16/2026"  // mm/dd/yyyy

/**
 * @class ES_TimeInterval
 * @brief Controls elapsed time intervals using millis() and micros().
 * | Controla intervalos de tempo usando millis() e micros().
 *
 * This class is useful for tasks that must run periodically without blocking the main loop.
 * It can also be used as a simple stopwatch for measuring elapsed time.
 *
 * | Esta classe é útil para tarefas que precisam rodar periodicamente sem bloquear o loop
 * principal. Ela também pode ser usada como um cronômetro simples para medir tempo decorrido.
 */
class ES_TimeInterval{
  private:
    /**
     * @brief Internal reference time for millisecond-based operations.
     * | Tempo interno de referência para operações baseadas em milissegundos.
     */
    unsigned long _start_Millis = millis();

    /**
     * @brief Internal reference time for microsecond-based operations.
     * | Tempo interno de referência para operações baseadas em microssegundos.
     */
    unsigned long _start_Micros = micros();
     
  public:
    /**
     * @brief Checks whether the configured millisecond interval has elapsed.
     * | Verifica se o intervalo configurado em milissegundos já foi concluído.
     *
     * When the interval is reached, the internal millisecond reference is automatically
     * updated and the method returns true.
     *
     * | Quando o intervalo é alcançado, a referência interna de milissegundos é atualizada
     * automaticamente e o método retorna verdadeiro.
     *
     * @param millisTime Interval time in milliseconds. | Tempo do intervalo em milissegundos.
     * @return true if the interval has elapsed, false otherwise.
     * | Verdadeiro se o intervalo terminou, falso caso contrário.
     */
    boolean intervalMillis(unsigned long millisTime);

    /**
     * @brief Resets the internal millisecond interval reference.
     * | Reinicia a referência interna do intervalo em milissegundos.
     */
    void resetMillis();

    /**
     * @brief Checks whether the configured microsecond interval has elapsed.
     * | Verifica se o intervalo configurado em microssegundos já foi concluído.
     *
     * When the interval is reached, the internal microsecond reference is automatically
     * updated and the method returns true.
     *
     * | Quando o intervalo é alcançado, a referência interna de microssegundos é atualizada
     * automaticamente e o método retorna verdadeiro.
     *
     * @param microsTime Interval time in microseconds. | Tempo do intervalo em microssegundos.
     * @return true if the interval has elapsed, false otherwise.
     * | Verdadeiro se o intervalo terminou, falso caso contrário.
     */
    boolean intervalMicros(unsigned long microsTime);

    /**
     * @brief Resets the internal microsecond interval reference.
     * | Reinicia a referência interna do intervalo em microssegundos.
     */
    void resetMicros();

    /**
     * @brief Starts or restarts the millisecond stopwatch.
     * | Inicia ou reinicia o cronômetro em milissegundos.
     */
    void stopwatchStartMillis();

    /**
     * @brief Stops the millisecond stopwatch and returns the elapsed time.
     * | Para o cronômetro em milissegundos e retorna o tempo decorrido.
     *
     * @return Elapsed time in milliseconds. | Tempo decorrido em milissegundos.
     */
    unsigned long stopwatchStopMillis();

    /**
     * @brief Starts or restarts the microsecond stopwatch.
     * | Inicia ou reinicia o cronômetro em microssegundos.
     */
    void stopwatchStartMicros();

    /**
     * @brief Stops the microsecond stopwatch and returns the elapsed time.
     * | Para o cronômetro em microssegundos e retorna o tempo decorrido.
     *
     * @return Elapsed time in microseconds. | Tempo decorrido em microssegundos.
     */
    unsigned long stopwatchStopMicros();
};

#endif
