#ifndef _ES_CAMERA_H_
#define _ES_CAMERA_H_

#include <Arduino.h>
#include "esp_camera.h"
#include "esp_http_server.h"
#include "SD.h"
#include "SPIFFS.h"
#include "ES_File/ES_File.h"

#define ES_CAMERA_VERSION "0.8.2 update 05/23/2025"  // mm/dd/yyyy

// Camera pin configuration using ES32Lab. | Configuração dos pinos da câmera utilizando a ES32Lab.
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     -1
#define SIOD_GPIO_NUM     21
#define SIOC_GPIO_NUM     22
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       16
#define Y4_GPIO_NUM       14
#define Y3_GPIO_NUM       12
#define Y2_GPIO_NUM        4
#define VSYNC_GPIO_NUM    13
#define HREF_GPIO_NUM     32
#define PCLK_GPIO_NUM     17


class ES_Camera {
    private:
        camera_config_t _config; // Camera configuration structure | Estrutura de configuração da câmera
        framesize_t _maxFrameSize; // Maximum frame size | Tamanho máximo do quadro
        const char* _streamUri; // Stores the stream URI handler | Armazena o handler do URI de stream

        uint8_t* _jpegBuf = NULL;
        size_t _jpegBufLen = 0;

    public:
        /**
         * @brief Constructor of the class | Construtor da classe
         */
        ES_Camera();

        /**
         * @brief Flag to pause the stream | Flag para pausar o stream 
         */
        bool pauseStream = false; 

        
        /**
         * @brief Initializes the camera with the specified configuration parameters. If any parameter is not provided, default values will be assigned.
         * | Inicializa a câmera com os parâmetros de configuração especificados. Caso algum parâmetro não seja fornecido, valores padrões serão atribuídos.
         * @param frameSize The frame size for the camera. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro para a câmera. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @param jpegQuality JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
         * @param maxFrameSize The maximum frame size for the camera. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho máximo do quadro para a câmera. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @param pixelFormat The pixel format for the camera. Ex.: PIXFORMAT_JPEG, PIXFORMAT_RGB565, etc. | O formato de pixel para a câmera. Ex.: PIXFORMAT_JPEG, PIXFORMAT_RGB565, etc.
         * @param grabMode The frame grab mode. | O modo de captura de quadros.
         * @param fbLocation The frame buffer location. | A localização do buffer de quadros.
         * @param fbCount The number of frame buffers to allocate. | O número de buffers de quadros a serem alocados.
         * @param xclkFreqHz The frequency of the XCLK signal in Hz. | A frequência do sinal XCLK em Hz.
         * @return True if the camera was initialized successfully, false otherwise. | Verdadeiro se a câmera foi inicializada com sucesso, falso caso contrário.
         * @note To save memory, reduce the size of maxFrameSize. | Para economizar memória, reduza o tamanho de maxFrameSize.
         */
        bool begin(framesize_t frameSize = FRAMESIZE_QQVGA, 
                   uint8_t jpegQuality = 12,
                   framesize_t maxFrameSize = FRAMESIZE_VGA, 
                   pixformat_t pixelFormat = PIXFORMAT_JPEG, 
                   camera_grab_mode_t grabMode = CAMERA_GRAB_WHEN_EMPTY, 
                   camera_fb_location_t fbLocation = CAMERA_FB_IN_DRAM, 
                   int fbCount = 1, 
                   int xclkFreqHz = 20000000);


        /**
         * @brief Method to get the camera sensor name | Método para obter o nome do sensor da câmera
         * @return The name of the camera sensor | O nome do sensor da câmera
         */
        String getSensorName();


        /**
         * @brief Method to set the brightness level of the camera sensor | Método para ajustar o nível de brilho do sensor da câmera
         * @param level The brightness level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de brilho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
         * @return True if the brightness was set successfully, false otherwise | Verdadeiro se o brilho foi ajustado com sucesso, falso caso contrário
         */
        bool setBrightness(int8_t level);
        /**
         * @brief Method to get the current brightness level of the camera sensor | Método para obter o nível de brilho atual do sensor da câmera
         * @return The current brightness level | O nível de brilho atual
         */        
        int8_t getBrightness();


        /**
        * @brief Method to set the contrast level of the camera sensor | Método para ajustar o nível de contraste do sensor da câmera
         * @param level The contrast level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de contraste a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
         * @return True if the contrast was set successfully, false otherwise | Verdadeiro se o contraste foi ajustado com sucesso, falso caso contrário
         */
        bool setContrast(int8_t level);
        /**
         * @brief Method to get the current contrast level of the camera sensor | Método para obter o nível de contraste atual do sensor da câmera
         * @return The current contrast level | O nível de contraste atual
         */
        int8_t getContrast();


        /**
         * @brief Method to set the saturation level of the camera sensor | Método para ajustar o nível de saturação do sensor da câmera
         * @param level The saturation level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de saturação a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
         * @return True if the saturation was set successfully, false otherwise | Verdadeiro se a saturação foi ajustada com sucesso, falso caso contrário
         */
        bool setSaturation(int8_t level);
        /**
         * @brief Method to get the current saturation level of the camera sensor | Método para obter o nível de saturação atual do sensor da câmera
         * @return The current saturation level | O nível de saturação atual
         */
        int8_t getSaturation();


        /**
        * @brief Method to set Enable or disable automatic white balance. | Método para ativar ou desativar o balanço de branco automático.
         * @param enable True to enable automatic white balance, false to disable it | Verdadeiro para ativar o balanço de branco automático, falso para desativá-lo
         * @return True if the white balance was set successfully, false otherwise | Verdadeiro se o balanço de branco foi ajustado com sucesso, falso caso contrário
         */
        bool setWhiteBalance(bool enable);
        /**
         * @brief Method to get the current white balance status of the camera sensor | Método para obter o status atual do balanço de branco do sensor da câmera
         * @return True if the white balance is enabled, false otherwise | Verdadeiro se o balanço de branco estiver ativado, falso caso contrário
         */
        bool getWhiteBalance();


        /**
         * @brief Method to set Enable or disable automatic white balance gain. | Método para ativar ou desativar o ganho do balanço de branco automático.
         * @param enable Enable/disable additional gain for white balance. | Ativar/desativar ganho adicional para o balanço de branco.
         * @return True if the white balance gain was set successfully, false otherwise | Verdadeiro se o ganho do balanço de branco foi ajustado com sucesso, falso caso contrário
         */        
        bool setWhiteBalanceGain(bool enable);
        /**
         * @brief Method to get the current white balance gain status of the camera sensor | Método para obter o status atual do ganho do balanço de branco do sensor da câmera
         * @return True if the white balance gain is enabled, false otherwise | Verdadeiro se o ganho do balanço de branco estiver ativado, falso caso contrário
         */
        bool getWhiteBalanceGain();


        /**
         * @brief Method to set Enable or disable automatic exposure control. | Método para ativar ou desativar o controle automático de exposição.
         * @param enable True to enable automatic exposure control, false to disable it | Verdadeiro para ativar o controle automático de exposição, falso para desativá-lo
         * @return True if the exposure control was set successfully, false otherwise | Verdadeiro se o controle de exposição foi ajustado com sucesso, falso caso contrário
         */
        bool setExposure(bool enable);
        /**
         * @brief Method to get the current exposure control status of the camera sensor | Método para obter o status atual do controle de exposição do sensor da câmera
         * @return True if the exposure control is enabled, false otherwise | Verdadeiro se o controle de exposição estiver ativado, falso caso contrário
         * @note This method is used to check if the exposure control is enabled or disabled. | Este método é usado para verificar se o controle de exposição está ativado ou desativado.
         */
        bool getExposure();


        /**
         * @brief Method to set Enable or disable advanced exposure control. | Método para ativar ou desativar o controle avançado de exposição.
         * @param enable True to enable advanced exposure control, false to disable it | Verdadeiro para ativar o controle avançado de exposição, falso para desativá-lo
         * @return True if the advanced exposure control was set successfully, false otherwise | Verdadeiro se o controle avançado de exposição foi ajustado com sucesso, falso caso contrário
         */
        bool setExposureAdvanced(bool enable);
        /**
         * @brief Method to get the current advanced exposure control status of the camera sensor | Método para obter o status atual do controle avançado de exposição do sensor da câmera
         * @return True if the advanced exposure control is enabled, false otherwise | Verdadeiro se o controle avançado de exposição estiver ativado, falso caso contrário
         */
        bool getExposureAdvanced();


        /**
         * @brief Method to set the exposure control level | Método para ajustar o nível de controle de exposição
         * @param level The exposure control level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de controle de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
         * @return True if the exposure control level was set successfully, false otherwise | Verdadeiro se o nível de controle de exposição foi ajustado com sucesso, falso caso contrário
         */
        bool setExposureLevel(int8_t level);
        /**
         * @brief Method to get the current exposure control level of the camera sensor | Método para obter o nível de controle de exposição atual do sensor da câmera
         * @return The current exposure control level | O nível de controle de exposição atual
         */
        int8_t getExposureLevel();


        /**
         * @brief Method to set the exposure control value | Método para ajustar o valor de controle de exposição
         * @param value The exposure control value to be set. Typically, the scale accepts integer values ranging from 0 to 1000, where 300 is the default. | O valor de controle de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 1000, onde 300 é o padrão.
         * @return True if the exposure control value was set successfully, false otherwise | Verdadeiro se o valor de controle de exposição foi ajustado com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setExposureValue(uint16_t value =300);
        /**
         * @brief Method to get the current exposure control value of the camera sensor | Método para obter o valor de controle de exposição atual do sensor da câmera
         * @return The current exposure control value | O valor de controle de exposição atual
         */
        uint16_t getExposureValue();


        /**
         * @brief Set the exposure-related gain control | Método para ajustar o controle de ganho relacionado à exposição
         * @param gain The gain value to be set. Typically, the scale accepts integer values ranging from 0 to 30, where 0 is the default. | O valor de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 30, onde 0 é o padrão.
         * @return True if the gain control was set successfully, false otherwise | Verdadeiro se o controle de ganho foi ajustado com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setExposureGain(uint8_t gain = 0);
        /**
         * @brief Get the current exposure-related gain control value | Método para obter o valor atual do controle de ganho relacionado à exposição
         * @return The current gain control value | O valor atual do controle de ganho
         */
        uint8_t getExposureGain();


        /**
         * @brief Method to set the special effect of the camera sensor | Método para ajustar o efeito especial do sensor da câmera
         * @param effect The special effect to be set. Typically, the scale accepts integer values ranging from 0 to 10, where 0 is the default. | O efeito especial a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 10, onde 0 é o padrão.
         * @return True if the special effect was set successfully, false otherwise | Verdadeiro se o efeito especial foi ajustado com sucesso, falso caso contrário
         * @note 0: none, 1: Negative, 2: Black and White, 3: Blue Tones, 4: Red Tones, 5: Green Tones, 6: Sepia. | 0: nenhum, 1: negativo, 2: preto e branco, 3: tons de azul, 4: tons de vermelho, 5: tons de verde, 6: sépia.
         */
        bool setSpecialEffect(uint8_t effect);
        /**
         * @brief Method to get the current special effect of the camera sensor | Método para obter o efeito especial atual do sensor da câmera
         * @return The current special effect | O efeito especial atual
         */
        uint8_t getSpecialEffect();


        /**
         * @brief Method to set the maximum gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho máximo (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz.
         * @param gainCeiling The gain ceiling to be set. Typically, the scale accepts integer values ranging from 0 to 7, where 0 is the default. | O teto de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 7, onde 0 é o padrão.
         * @return True if the gain ceiling was set successfully, false otherwise | Verdadeiro se o teto de ganho foi ajustado com sucesso, falso caso contrário
         * @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
         */
        bool setAutoGainCeiling(gainceiling_t  gainCeiling);
        /**
         * @brief Method to set the maximum gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho máximo (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz.
         * @param gainCeiling The gain ceiling to be set. Typically, the scale accepts integer values ranging from 0 to 7, where 0 is the default. | O teto de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 7, onde 0 é o padrão.
         * @return True if the gain ceiling was set successfully, false otherwise | Verdadeiro se o teto de ganho foi ajustado com sucesso, falso caso contrário
         * @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
         */
        bool setAutoGainCeiling(uint8_t  gainCeiling);
        /**
         * @brief Method to get the current gain ceiling (gain ceiling) in automatic mode on the camera sensor | Método para obter o teto de ganho atual (teto de ganho) no modo automático do sensor da câmera
         * @return The current gain ceiling | O teto de ganho atual
         * @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
         */
        uint8_t  getAutoGainCeiling();


        /**
         * @brief Method to set Enable or disable noise reduction control. | Método para ativar ou desativar o controle de redução de ruído.
         * @param enable True to enable noise reduction, false to disable it | Verdadeiro para ativar a redução de ruído, falso para desativá-la
         * @return True if the noise reduction was set successfully, false otherwise | Verdadeiro se a redução de ruído foi ajustada com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setNoiseReduction(bool enabled = true);
        /**
         * @brief Method to get the current noise reduction status of the camera sensor | Método para obter o status atual da redução de ruído do sensor da câmera
         * @return True if the noise reduction is enabled, false otherwise | Verdadeiro se a redução de ruído estiver ativada, falso caso contrário
         */
        bool getNoiseReduction();
        

        /**
         * @brief Method to set Enable or disable pixel correction. | Método para ativar ou desativar a correção de pixel.
         * @param enable True to enable pixel correction, false to disable it | Verdadeiro para ativar a correção de pixel, falso para desativá-la
         * @return True if the pixel correction was set successfully, false otherwise | Verdadeiro se a correção de pixel foi ajustada com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setPixelCorrection(bool enabled = true);
        /**
         * @brief Method to get the current pixel correction status of the camera sensor | Método para obter o status atual da correção de pixel do sensor da câmera
         * @return True if the pixel correction is enabled, false otherwise | Verdadeiro se a correção de pixel estiver ativada, falso caso contrário
         * @note This method is used to check if the pixel correction is enabled or disabled. | Este método é usado para verificar se a correção de pixel está ativada ou desativada.
         */
        bool getPixelCorrection();


        /**
         * @brief Method to set Enable or disable color correction. | Método para ativar ou desativar a correção de cor.
         * @param enable True to enable color correction, false to disable it | Verdadeiro para ativar a correção de cor, falso para desativá-la
         * @return True if the color correction was set successfully, false otherwise | Verdadeiro se a correção de cor foi ajustada com sucesso, falso caso contrário
         */
        bool setColorCorrection(bool enabled = true);
        /**
         * @brief Method to get the current color correction status of the camera sensor | Método para obter o status atual da correção de cor do sensor da câmera
         * @return True if the color correction is enabled, false otherwise | Verdadeiro se a correção de cor estiver ativada, falso caso contrário
         */
        bool getColorCorrection(); // Get the current color correction control status | Obtém o status atual do controle de correção de cor


        /**
         * @brief Method to set Enable or disable raw color correction. | Método para ativar ou desativar a correção de cor RAW.
         * @param enable True to enable raw color correction, false to disable it | Verdadeiro para ativar a correção de cor RAW, falso para desativá-la
         * @return True if the raw color correction was set successfully, false otherwise | Verdadeiro se a correção de cor RAW foi ajustada com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setRawColorCorrection(bool enabled = true);
        /**
         * @brief Method to get the current raw color correction status of the camera sensor | Método para obter o status atual da correção de cor RAW do sensor da câmera
         * @return True if the raw color correction is enabled, false otherwise | Verdadeiro se a correção de cor RAW estiver ativada, falso caso contrário
         */
        bool getRawColorCorrection(); // Get the current RAW color correction control status | Obtém o status atual do controle de correção de cor RAW


        /**
         * @brief Enable or disable lens correction on the camera sensor.
         * | Habilita ou desabilita a correção de lente no sensor da câmera.
         * @param enabled Set to true to enable lens correction, false to disable. | Defina como true para habilitar a correção de lente, false para desabilitar.
         * @return true if the operation was successful, false otherwise. | true se a operação foi bem-sucedida, false caso contrário.
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setLensCorrection(bool enabled = true);
        /**
         * @brief Get the current lens correction status of the camera sensor.
         * | Obtém o status atual da correção de lente do sensor da câmera.
         * @return true if lens correction is enabled, false otherwise. | true se a correção de lente estiver ativada, false caso contrário.
         * @note This method is used to check if lens correction is enabled or disabled. | Este método é usado para verificar se a correção de lente está ativada ou desativada.
         */
        bool getLensCorrection(); // Get the current lens correction control status | Obtém o status atual do controle de correção de lente


        /**
         * @brief Method to set the sharpness level of the camera sensor | Método para ajustar o nível de nitidez do sensor da câmera
         * @param level The sharpness level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de nitidez a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
         * @return True if the sharpness was set successfully, false otherwise | Verdadeiro se a nitidez foi ajustada com sucesso, falso caso contrário
         * @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
         */
        bool setSharpness(int8_t level);
        /**
         * @brief Method to get the current sharpness level of the camera sensor | Método para obter o nível de nitidez atual do sensor da câmera
         * @return The current sharpness level | O nível de nitidez atual
         */
        int8_t getSharpness();


        /**
         * @brief Method to set the frame size of the camera sensor | Método para ajustar o tamanho do quadro do sensor da câmera
         * @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @return True if the frame size was set successfully, false otherwise | Verdadeiro se o tamanho do quadro foi ajustado com sucesso, falso caso contrário
         * @note The frame size determines the resolution of the image captured by the camera. | O tamanho do quadro determina a resolução da imagem capturada pela câmera.
         */
        bool setFrameSize(framesize_t frameSize);
        /**
         * @brief Method to set the frame size of the camera sensor | Método para ajustar o tamanho do quadro do sensor da câmera
         * @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @return True if the frame size was set successfully, false otherwise | Verdadeiro se o tamanho do quadro foi ajustado com sucesso, falso caso contrário
         * @note The frame size determines the resolution of the image captured by the camera. | O tamanho do quadro determina a resolução da imagem capturada pela câmera.
         */
        bool setFrameSize(int8_t frameSize);
        /**
         * @brief Method to get the current frame size of the camera sensor | Método para obter o tamanho do quadro atual do sensor da câmera
         * @return The current frame size | O tamanho do quadro atual
         */
        framesize_t getFrameSize();


        /**
         * @brief Method to get the current frame width | Método para obter a largura do quadro atual
         * @return The width of the current frame in pixels | A largura do quadro atual em pixels
         */
        int getFrameWidth();
        /**
         * @brief Method to get the current frame height | Método para obter a altura do quadro atual
         * @return The height of the current frame in pixels | A altura do quadro atual em pixels
         */
        int getFrameHeight();


        /**
         * @brief Method to set the JPEG compression quality | Método para ajustar a qualidade de compressão JPEG
         * @param quality The JPEG compression quality to be set. Typically, the scale accepts integer values ranging from 0 to 100, where 10 is the default. | A qualidade de compressão JPEG a ser ajustada. Geralmente, a escala aceita valores inteiros que variam de 0 a 100, onde 10 é o padrão.
         * @return True if the JPEG compression quality was set successfully, false otherwise | Verdadeiro se a qualidade de compressão JPEG foi ajustada com sucesso, falso caso contrário
         * @note JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
         */
        bool setJpegCompression(int8_t jpegQuality);
        /**
         * @brief Method to get the current JPEG compression quality of the camera sensor | Método para obter a qualidade de compressão JPEG atual do sensor da câmera
         * @return The current JPEG compression quality | A qualidade de compressão JPEG atual
         */
        int8_t getJpegCompression();

        
        /**
         * @brief Method to set Enable or disable horizontal mirror. | Método para ativar ou desativar o espelhamento horizontal.
         * @param enable True to enable horizontal mirror, false to disable it | Verdadeiro para ativar o espelhamento horizontal, falso para desativá-lo
         * @return True if the horizontal mirror was set successfully, false otherwise | Verdadeiro se o espelhamento horizontal foi ajustado com sucesso, falso caso contrário
         */
        bool setHorizontalMirror(bool enabled = true);
        /**
         * @brief to get the current horizontal mirror status of the camera sensor | Método para obter o status atual do espelhamento horizontal do sensor da câmera
         * @return True if the horizontal mirror is enabled, false otherwise | Verdadeiro se o espelhamento horizontal estiver ativado, falso caso contrário
         * @note This method is used to check if the horizontal mirror is enabled or disabled. | Este método é usado para verificar se o espelhamento horizontal está ativado ou desativado.
         */
        bool getHorizontalMirror();


        /**
         * Method to set Enable or disable vertical mirror. | Método para ativar ou desativar o espelhamento vertical.
         * @param enable True to enable vertical mirror, false to disable it | Verdadeiro para ativar o espelhamento vertical, falso para desativá-lo
         * @return True if the vertical mirror was set successfully, false otherwise | Verdadeiro se o espelhamento vertical foi ajustado com sucesso, falso caso contrário
         */
        bool setVerticalMirror(bool enabled = true);
        /**
         * Method to get the current vertical mirror status of the camera sensor | Método para obter o status atual do espelhamento vertical do sensor da câmera
         * @return True if the vertical mirror is enabled, false otherwise | Verdadeiro se o espelhamento vertical estiver ativado, falso caso contrário
         */
        bool getVerticalMirror(); // Get the current vertical mirroring status | Obtém o status atual do espelhamento vertical
        

        /**
         * Method to set Enable or disable color bar. | Método para ativar ou desativar a barra de cores.
         * @param enable True to enable color bar, false to disable it | Verdadeiro para ativar a barra de cores, falso para desativá-la
         */
        bool setColorBar(bool enabled = true);
        /**
         * @brief Method to get the current color bar status of the camera sensor | Método para obter o status atual da barra de cores do sensor da câmera
         * @return True if the color bar is enabled, false otherwise | Verdadeiro se a barra de cores estiver ativada, falso caso contrário
         * @note This method is used to check if the color bar is enabled or disabled. | Este método é usado para verificar se a barra de cores está ativada ou desativada.
         */
        bool getColorBar(); 


        /**
         * @brief Method to get the frame buffer according to the camera format | Método para obter o buffer do frame de acordo com o formato da câmera
         * @param buf Pointer to the buffer where the frame data will be stored | Ponteiro para o buffer onde os dados do frame serão armazenados
         * @param bufLen Pointer to the variable where the length of the frame data will be stored | Ponteiro para a variável onde o comprimento dos dados do frame será armazenado
         * @return True if the frame buffer was obtained successfully, false otherwise | Verdadeiro se o buffer do frame foi obtido com sucesso, falso caso contrário
         */
        bool getFrameBuffer(uint8_t** buf, size_t* bufLen);

        
        /**
         * @brief to capture a frame in JPEG format | Método para capturar um frame no formato JPEG
         * @param jpegBuf Pointer to the buffer where the JPEG data will be stored | Ponteiro para o buffer onde os dados JPEG serão armazenados
         * @param jpegBufLen Pointer to the variable where the length of the JPEG data will be stored | Ponteiro para a variável onde o comprimento dos dados JPEG será armazenado
         * @return True if the frame was captured successfully, false otherwise | Verdadeiro se o frame foi capturado com sucesso, falso caso contrário
         */
        bool getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen); // Capture a frame in JPEG format | Captura um frame no formato JPEG
        /**
         * Method to capture a frame in JPEG format with specified frame size and JPEG quality | Método para capturar um frame no formato JPEG com tamanho de quadro e qualidade JPEG especificados
         * @param jpegBuf Pointer to the buffer where the JPEG data will be stored | Ponteiro para o buffer onde os dados JPEG serão armazenados
         * @param jpegBufLen Pointer to the variable where the length of the JPEG data will be stored | Ponteiro para a variável onde o comprimento dos dados JPEG será armazenado
         * @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @param jpegQuality JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
         * @return True if the frame was captured successfully, false otherwise | Verdadeiro se o frame foi capturado com sucesso, falso caso contrário
         * @note This method sets the frame size and JPEG quality before capturing the frame. | Este método ajusta o tamanho do quadro e a qualidade JPEG antes de capturar o frame.
         */
        bool getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen, framesize_t frameSize, int8_t jpegQuality = 12); // Capture a frame in JPEG format | Captura um frame no formato JPEG
        
        /**
         * @brief Method to save the captured frame to a JPEG file | Método para salvar o frame capturado em um arquivo JPEG
         * @param fs The file system to use (e.g., SPIFFS, LittleFS or SD) | O sistema de arquivos a ser usado (ex.: SPIFFS, LittleFS ou SD)
         * @param fileName The path where the JPEG file will be saved | O caminho onde o arquivo JPEG será salvo
         */
        bool saveFrameToJpegFile(fs::FS &fs, const String& fileName);
        /**
         * @brief Method to save the captured frame to a JPEG file with specified frame size and JPEG quality | Método para salvar o frame capturado em um arquivo JPEG com tamanho de quadro e qualidade JPEG especificados
         * @param fs The file system to use (e.g., SPIFFS, LittleFS or SD) | O sistema de arquivos a ser usado (ex.: SPIFFS, LittleFS ou SD)
         * @param filePath The path where the JPEG file will be saved | O caminho onde o arquivo JPEG será salvo
         * @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
         * @param jpegQuality JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
         * @return True if the frame was saved successfully, false otherwise | Verdadeiro se o frame foi salvo com sucesso, falso caso contrário
         */
        bool saveFrameToJpegFile(fs::FS &fs, const String& fileName, framesize_t frameSize, int8_t jpegQuality = 12);

        /**
         * @brief Method to handle the stream request | Método para manipular a solicitação de stream
         * @param req The HTTP request | A solicitação HTTP
         * @return ESP_OK if the request was handled successfully, otherwise an error code | ESP_OK se a solicitação foi manipulada com sucesso, caso contrário, um código de erro
         * @note This method is used to handle the stream request from the client. | Este método é usado para manipular a solicitação de stream do cliente.
         */
        esp_err_t handleStreamRequest(httpd_req_t *req);
        /**
         * @brief Method to create the stream endpoint | Método para criar o endpoint de stream
         * @param uri The URI for the stream endpoint | O URI para o endpoint de stream
         * @return The HTTP URI structure for the stream endpoint | A estrutura HTTP URI para o endpoint de stream
         * @note This method is used to create the stream endpoint for the camera. | Este método é usado para criar o endpoint de stream para a câmera.
         */
        httpd_uri_t createStreamEndpoint(const char* streamUri);
        /**
         * @brief to get the stream URI | Método para obter o URI de stream
         * @return The stream URI | O URI de stream
         * @note This method is used to retrieve the stream URI for the camera. | Este método é usado para recuperar o URI de stream para a câmera.
         */
        const char* getStreamUri();

};
#endif