#ifndef __ES_CAMERA_H__
#define __ES_CAMERA_H__

#include <Arduino.h>
#include "esp_camera.h"
#include "esp_http_server.h"
#include "SD.h"
#include "SPIFFS.h"

#define ES_CAMERA_VERSION "0.7.7 update 04/17/2025"  // mm/dd/yyyy

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
        // Constructor of the class | Construtor da classe
        ES_Camera();

        bool pauseStream = false; // Flag to pause the stream | Flag para pausar o stream

        // Function to initialize the camera | Função para inicializar a câmera
        bool begin(framesize_t frameSize = FRAMESIZE_QQVGA, 
                   uint8_t jpegQuality = 12,
                   framesize_t maxFrameSize = FRAMESIZE_VGA, 
                   pixformat_t pixelFormat = PIXFORMAT_JPEG, 
                   camera_grab_mode_t grabMode = CAMERA_GRAB_WHEN_EMPTY, 
                   camera_fb_location_t fbLocation = CAMERA_FB_IN_DRAM, 
                   int fbCount = 1, 
                   int xclkFreqHz = 20000000);

        String getSensorName(); // Method to get the camera sensor name | Método para obter o nome do sensor da câmera

        bool setBrightness(int8_t level); // Set brightness level | Ajusta o nível de brilho
        int8_t getBrightness(); // Get brightness level | Obtém o nível de brilho

        bool setContrast(int8_t level); // Set contrast level | Ajusta o nível de contraste
        int8_t getContrast(); // Get contrast level | Obtém o nível de contraste

        bool setSaturation(int8_t level); // Set saturation level | Ajusta o nível de saturação
        int8_t getSaturation(); // Get saturation level | Obtém o nível de saturação

        bool setWhiteBalance(bool enable); // Enable or disable automatic white balance. | Habilita ou desabilita o balanço de branco automático.
        bool getWhiteBalance(); // Get the current white balance status. | Obtém o status atual do balanço de branco.

        bool setWhiteBalanceGain(bool enable); // Enable or disable automatic white balance gain.
        bool getWhiteBalanceGain(); // Get the current white balance gain status.


        bool setExposure(bool enable); // Enable or disable automatic exposure control. | Habilita ou desabilita o controle automático de exposição.
        bool getExposure(); // Get the current exposure control status. | Obtém o status atual do controle de exposição.

        bool setExposureAdvanced(bool enable); // Enable or disable advanced automatic exposure control. | Habilita ou desabilita o controle avançado de exposição automática.
        bool getExposureAdvanced(); // Get the current advanced exposure control status. | Obtém o status atual do controle avançado de exposição.

        bool setExposureLevel(int8_t level); // Set the exposure control level | Ajusta o nível de controle de exposição
        int8_t getExposureLevel(); // Get the exposure control level | Obtém o nível de controle de exposição

        bool setExposureValue(uint16_t value =300);   // Control exposure value (300: default). | Valor de controle de exposição (300: padrão).
        uint16_t getExposureValue();             // Get the current exposure value | Obtém o valor de exposição atual

        bool setExposureGain(uint8_t gain = 0); // Adjusts the automatic gain control (AGC) | Ajusta o controle automático de ganho
        uint8_t getExposureGain();         // Gets the current gain control value | Obtém o valor atual do controle de ganho

        bool setSpecialEffect(uint8_t effect); // Set special effect | Ajusta o efeito especial
        uint8_t getSpecialEffect(); // Get special effect | Obtém o efeito especial

        bool setAutoGainCeiling(gainceiling_t  gainCeiling); // Set the gain ceiling value | Ajusta o valor do teto de ganho
        bool setAutoGainCeiling(uint8_t  gainCeiling); // Set the gain ceiling value | Ajusta o valor do teto de ganho
        uint8_t  getAutoGainCeiling(); // Get the current gain ceiling value | Obtém o valor atual do teto de ganho

        bool setNoiseReduction(bool enabled = true); // Enable or disable noise reduction control | Habilita ou desabilita o controle de redução de ruído
        bool getNoiseReduction(); // Get the current noise reduction control status | Obtém o status atual do controle de redução de ruído
        
        bool setPixelCorrection(bool enabled = true); // Enable or disable pixel correction control | Habilita ou desabilita o controle de correção de pixel
        bool getPixelCorrection(); // Get the current pixel correction control status | Obtém o status atual do controle de correção de pixel

        bool setColorCorrection(bool enabled = true); // Enable or disable color correction control | Habilita ou desabilita o controle de correção de cor
        bool getColorCorrection(); // Get the current color correction control status | Obtém o status atual do controle de correção de cor
        
        bool setRawColorCorrection(bool enabled = true); // Enable or disable RAW color correction control | Habilita ou desabilita o controle de correção de cor RAW
        bool getRawColorCorrection(); // Get the current RAW color correction control status | Obtém o status atual do controle de correção de cor RAW

        bool setLensCorrection(bool enabled = true); // Enable or disable lens correction control | Habilita ou desabilita o controle de correção de lente
        bool getLensCorrection(); // Get the current lens correction control status | Obtém o status atual do controle de correção de lente

        bool setSharpness(int8_t level); // Ajusta o nível de nitidez
        int8_t getSharpness();          // Obtém o nível atual de nitidez        

        bool setFrameSize(framesize_t frameSize); // Ajusta o tamanho do frame (resolução da imagem)
        framesize_t getFrameSize(); // Obtém o tamanho atual do frame (resolução da imagem)

        bool setFrameSize(int8_t frameSize); // Ajusta o tamanho do frame (resolução da imagem)

        bool setJpegCompression(int8_t jpegQuality); // Ajusta o nível de compressão JPEG
        int8_t getJpegCompression();            // Obtém o nível atual de compressão JPEG

        //--- Image Mirroring ---
        bool setHorizontalMirror(bool enabled = true); // Enable or disable horizontal mirroring | Habilita ou desabilita o espelhamento horizontal
        bool getHorizontalMirror(); // Get the current horizontal mirroring status | Obtém o status atual do espelhamento horizontal

        bool setVerticalMirror(bool enabled = true); // Enable or disable vertical mirroring | Habilita ou desabilita o espelhamento vertical
        bool getVerticalMirror(); // Get the current vertical mirroring status | Obtém o status atual do espelhamento vertical
        
        bool setColorBar(bool enabled = true); // Enable or disable color bar | Habilita ou desabilita a barra de cores
        bool getColorBar(); // Get the current color bar status | Obtém o status atual da barra de cores


        // --- Frame Buffer ---
        bool getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen); // Capture a frame in JPEG format | Captura um frame no formato JPEG
        bool getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen, framesize_t frameSize, int8_t jpegQuality = 12); // Capture a frame in JPEG format | Captura um frame no formato JPEG
        
        // --- File System ---
        bool saveFrameToJpegFile(fs::FS &fs, const char* filePath); // Save the captured frame to a JPEG file | Salva o frame capturado em um arquivo JPEG
        bool saveFrameToJpegFile(fs::FS &fs, const char* filePath, framesize_t frameSize, int8_t jpegQuality = 12); // Save the captured frame to a JPEG file with specified parameters | Salva o frame capturado em um arquivo JPEG com parâmetros especificados

        // --- Streaming ---
        esp_err_t handleStreamRequest(httpd_req_t *req); // Handle the stream request | Manipula a solicitação de stream
        httpd_uri_t createStreamEndpoint(const char* streamUri);  // Create the stream endpoint | Cria o endpoint de stream
        const char* getStreamUri();
         

};
#endif



/*
Métodos a serem implementados:
 x   s->set_agc_gain(s, 0);            // Controle de ganho automático (0: desativado).

 x   s->set_special_effect(s, 0);      // Efeito especial (0: nenhum, 1: Negativo, 2: Preto e Branco, 3: Tons de Azul, 4: Tons de Vermelho, 5: Tons de Verde, 6: Sépia, 7: Retro, 8: Solarizado, 9: Cores Frias, 10: Cores Quentes).


 x   s->set_gainceiling(s, GAINCEILING_2X); // Útil para ajustar a captura em condições de baixa luz. Dedfault: GAINCEILING_2X (2x). Outros valores: GAINCEILING_4X, GAINCEILING_8X, GAINCEILING_16X, GAINCEILING_32X, GAINCEILING_64X, GAINCEILING_128X.
 x   s->set_dcw(s, 1);                 // Controle de redução de ruído (1: ativado).
 x   s->set_bpc(s, 1);                 // Controle de correção de pixel (1: ativado).
 x   s->set_wpc(s, 1);                 // Controle de correção de cor (1: ativado).
    s->set_raw_gma(s, 1);             // Controle de correção de cor RAW (1: ativado).
    s->set_lenc(s, 1);                // Controle de correção de lente (1: ativado).
    s->set_hmirror(s, 0);             // Espelhamento horizontal (0: desativado).
    s->set_vflip(s, 0);               // Espelhamento vertical (0: desativado).
    s->set_colorbar(s, 0);            // Barra de cores (0: desativado).    

*/