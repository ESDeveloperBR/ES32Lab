#include "ES_Camera.h"
#include "Arduino.h"

// Constructor of the class | Construtor da classe
ES_Camera::ES_Camera() {
    // Initialize the configuration structure with default values | Inicializa a estrutura de configuração com valores padrão
    _config.ledc_channel = LEDC_CHANNEL_0;
    _config.ledc_timer = LEDC_TIMER_0;
    _config.pin_d0 = Y2_GPIO_NUM;
    _config.pin_d1 = Y3_GPIO_NUM;
    _config.pin_d2 = Y4_GPIO_NUM;
    _config.pin_d3 = Y5_GPIO_NUM;
    _config.pin_d4 = Y6_GPIO_NUM;
    _config.pin_d5 = Y7_GPIO_NUM;
    _config.pin_d6 = Y8_GPIO_NUM;
    _config.pin_d7 = Y9_GPIO_NUM;
    _config.pin_xclk = XCLK_GPIO_NUM;
    _config.pin_pclk = PCLK_GPIO_NUM;
    _config.pin_vsync = VSYNC_GPIO_NUM;
    _config.pin_href = HREF_GPIO_NUM;
    _config.pin_sccb_sda = SIOD_GPIO_NUM;
    _config.pin_sccb_scl = SIOC_GPIO_NUM;
    _config.pin_pwdn = PWDN_GPIO_NUM;
    _config.pin_reset = RESET_GPIO_NUM;
}




/**
 * Initializes the camera with the specified configuration parameters. If any parameter is not provided, default values will be assigned.
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
bool ES_Camera::begin(framesize_t frameSize, uint8_t jpegQuality, framesize_t maxFrameSize, pixformat_t pixelFormat, camera_grab_mode_t grabMode, camera_fb_location_t fbLocation, int fbCount, int xclkFreqHz) {
    // Initialize the camera with the given parameters | Inicializa a câmera com os parâmetros fornecidos
    _maxFrameSize = maxFrameSize; // Set the maximum frame size | Define o tamanho máximo do quadro
    _config.xclk_freq_hz = xclkFreqHz;
    _config.pixel_format = pixelFormat;
    _config.frame_size = _maxFrameSize;
    _config.jpeg_quality = jpegQuality;
    _config.grab_mode = (camera_grab_mode_t)grabMode;
    _config.fb_location = (camera_fb_location_t)fbLocation;
    _config.fb_count = fbCount;
    
    esp_err_t err = esp_camera_init(&_config);
    if (err != ESP_OK) {
        ESP_LOGE("begin", "Initialization failed with error 0x%x", err);
        return false;
    }

    // Set the frame size | Define o tamanho do quadro
    if(frameSize <= _maxFrameSize){
        setFrameSize(frameSize); // Set default frame size | Define o tamanho do quadro padrão
    }

    return true;
}


/*
* Method to get the camera sensor name | Método para obter o nome do sensor da câmera
* @return The name of the camera sensor | O nome do sensor da câmera
*/
String ES_Camera::getSensorName() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return "Error: Sensor not found";
    }

    if (s->id.PID == OV2640_PID) {
        return "OV2640";
    } else if (s->id.PID == OV3660_PID) {
        return "OV3660";
    } else if (s->id.PID == OV7725_PID) {
        return "OV7725";
    } else if (s->id.PID == OV5640_PID) {
        return "OV5640";
    } else if (s->id.PID == OV7670_PID) {
        return "OV7670";
    } else {
        return "Unknown or unsupported sensor";
    }
}

/*
* Method to set the brightness level of the camera sensor | Método para ajustar o nível de brilho do sensor da câmera
* @param level The brightness level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de brilho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
* @return True if the brightness was set successfully, false otherwise | Verdadeiro se o brilho foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setBrightness(int8_t level) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_brightness(s, level); // Set the brightness | Ajusta o brilho
    if (err != ESP_OK) {
        ESP_LOGE("setBrightness", "Failed to set brightness with error 0x%x", err);
        return false;
    }

    return true;
}

/*
* Method to get the current brightness level of the camera sensor | Método para obter o nível de brilho atual do sensor da câmera
* @return The current brightness level | O nível de brilho atual
*/
int8_t ES_Camera::getBrightness() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.brightness; // Return the current brightness level | Retorna o nível atual de brilho
}



/*
* Method to set the contrast level of the camera sensor | Método para ajustar o nível de contraste do sensor da câmera
* @param level The contrast level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de contraste a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
* @return True if the contrast was set successfully, false otherwise | Verdadeiro se o contraste foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setContrast(int8_t level) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_contrast(s, level); // Set the contrast | Ajusta o contraste
    if (err != ESP_OK) {
        ESP_LOGE("setContrast", "Failed to set contrast with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current contrast level of the camera sensor | Método para obter o nível de contraste atual do sensor da câmera
* @return The current contrast level | O nível de contraste atual
*/
int8_t ES_Camera::getContrast() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.contrast; // Return the current contrast level | Retorna o nível atual de contraste
}


/*
* Method to set the saturation level of the camera sensor | Método para ajustar o nível de saturação do sensor da câmera
* @param level The saturation level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de saturação a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
* @return True if the saturation was set successfully, false otherwise | Verdadeiro se a saturação foi ajustada com sucesso, falso caso contrário
*/
bool ES_Camera::setSaturation(int8_t level) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_saturation(s, level); // Set the saturation | Ajusta a saturação
    if (err != ESP_OK) {
        ESP_LOGE("setSaturation", "Failed to set saturation with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current saturation level of the camera sensor | Método para obter o nível de saturação atual do sensor da câmera
* @return The current saturation level | O nível de saturação atual
*/
int8_t ES_Camera::getSaturation() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.saturation; // Return the current saturation level | Retorna o nível atual de saturação
}


/*
* Method to set Enable or disable automatic white balance. | Método para ativar ou desativar o balanço de branco automático.
* @param enable True to enable automatic white balance, false to disable it | Verdadeiro para ativar o balanço de branco automático, falso para desativá-lo
* @return True if the white balance was set successfully, false otherwise | Verdadeiro se o balanço de branco foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setWhiteBalance(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_whitebal(s, (enable ? 1 : 0)); // Set the white balance | Ajusta o balanço de branco
    if (err != ESP_OK) {
        ESP_LOGE("setWhiteBalance", "Failed to set white balance with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current white balance status of the camera sensor | Método para obter o status atual do balanço de branco do sensor da câmera
* @return True if the white balance is enabled, false otherwise | Verdadeiro se o balanço de branco estiver ativado, falso caso contrário
*/
bool ES_Camera::getWhiteBalance() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.awb; // Return true if white balance is enabled, false otherwise | Retorna verdadeiro se o balanço de branco estiver ativado, falso caso contrário
}


/*
* Method to set Enable or disable automatic white balance gain. | Método para ativar ou desativar o ganho do balanço de branco automático.
* @param enable Enable/disable additional gain for white balance. | Ativar/desativar ganho adicional para o balanço de branco.
* @return True if the white balance gain was set successfully, false otherwise | Verdadeiro se o ganho do balanço de branco foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setWhiteBalanceGain(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_awb_gain(s, (enable ? 1 : 0)); // Set the white balance gain | Ajusta o ganho do balanço de branco
    if (err != ESP_OK) {
        ESP_LOGE("setWhiteBalanceGain", "Failed to set white balance gain with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current white balance gain status of the camera sensor | Método para obter o status atual do ganho do balanço de branco do sensor da câmera
* @return True if the white balance gain is enabled, false otherwise | Verdadeiro se o ganho do balanço de branco estiver ativado, falso caso contrário
*/
bool ES_Camera::getWhiteBalanceGain() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.awb_gain; // Return true if white balance gain is enabled, false otherwise | Retorna verdadeiro se o ganho do balanço de branco estiver ativado, falso caso contrário
}


/*
* Method to set Enable or disable automatic exposure control. | Método para ativar ou desativar o controle automático de exposição.
* @param enable True to enable automatic exposure control, false to disable it | Verdadeiro para ativar o controle automático de exposição, falso para desativá-lo
* @return True if the exposure control was set successfully, false otherwise | Verdadeiro se o controle de exposição foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setExposure(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_exposure_ctrl(s, (enable ? 1 : 0)); // Set the exposure control | Ajusta o controle de exposição
    if (err != ESP_OK) {
        ESP_LOGE("setExposureCtrl", "Failed to set exposure control with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current exposure control status of the camera sensor | Método para obter o status atual do controle de exposição do sensor da câmera
* @return True if the exposure control is enabled, false otherwise | Verdadeiro se o controle de exposição estiver ativado, falso caso contrário
* @note This method is used to check if the exposure control is enabled or disabled. | Este método é usado para verificar se o controle de exposição está ativado ou desativado.
*/
bool ES_Camera::getExposure() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.aec; // Return true if exposure control is enabled, false otherwise | Retorna verdadeiro se o controle de exposição estiver ativado, falso caso contrário
}


/*
* Method to set Enable or disable advanced exposure control. | Método para ativar ou desativar o controle avançado de exposição.
* @param enable True to enable advanced exposure control, false to disable it | Verdadeiro para ativar o controle avançado de exposição, falso para desativá-lo
* @return True if the advanced exposure control was set successfully, false otherwise | Verdadeiro se o controle avançado de exposição foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setExposureAdvanced(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_aec2(s, (enable ? 1 : 0)); // Set the advanced exposure control | Ajusta o controle de exposição avançado
    if (err != ESP_OK) {
        ESP_LOGE("setExposureCtrlAdvanced", "Failed to set advanced exposure control with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current advanced exposure control status of the camera sensor | Método para obter o status atual do controle avançado de exposição do sensor da câmera
* @return True if the advanced exposure control is enabled, false otherwise | Verdadeiro se o controle avançado de exposição estiver ativado, falso caso contrário
*/
bool ES_Camera::getExposureAdvanced() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.aec2; // Return true if advanced exposure control is enabled, false otherwise | Retorna verdadeiro se o controle avançado de exposição estiver ativado, falso caso contrário
}


/*
* Method to set the exposure control level | Método para ajustar o nível de controle de exposição
* @param level The exposure control level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de controle de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
* @return True if the exposure control level was set successfully, false otherwise | Verdadeiro se o nível de controle de exposição foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setExposureLevel(int8_t level) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_ae_level(s, level); // Set the exposure control level | Ajusta o nível de controle de exposição
    if (err != ESP_OK) {
        ESP_LOGE("setExposureLevel", "Failed to set exposure control level with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current exposure control level of the camera sensor | Método para obter o nível de controle de exposição atual do sensor da câmera
* @return The current exposure control level | O nível de controle de exposição atual
*/
int8_t ES_Camera::getExposureLevel() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.ae_level; // Return the current exposure control level | Retorna o nível atual de controle de exposição
}


/*
* Method to set the exposure control value | Método para ajustar o valor de controle de exposição
* @param value The exposure control value to be set. Typically, the scale accepts integer values ranging from 0 to 1000, where 300 is the default. | O valor de controle de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 1000, onde 300 é o padrão.
* @return True if the exposure control value was set successfully, false otherwise | Verdadeiro se o valor de controle de exposição foi ajustado com sucesso, falso caso contrário
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setExposureValue(uint16_t value) {
    setExposure(false);
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_aec_value(s, value); // Set the exposure control value | Ajusta o valor de controle de exposição

    if (err != ESP_OK) {
        ESP_LOGE("setAecValue", "Failed to set exposure control value with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current exposure control value of the camera sensor | Método para obter o valor de controle de exposição atual do sensor da câmera
* @return The current exposure control value | O valor de controle de exposição atual
*/
uint16_t ES_Camera::getExposureValue() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.aec_value; // Return the current exposure control value | Retorna o valor atual de controle de exposição
}


/*
* Set the exposure-related gain control | Método para ajustar o controle de ganho relacionado à exposição
* @param gain The gain value to be set. Typically, the scale accepts integer values ranging from 0 to 30, where 0 is the default. | O valor de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 30, onde 0 é o padrão.
* @return True if the gain control was set successfully, false otherwise | Verdadeiro se o controle de ganho foi ajustado com sucesso, falso caso contrário
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setExposureGain(uint8_t gain) {
    if (gain > 30) { // Supondo que o intervalo máximo seja 30
        ESP_LOGE("setGainControl", "Invalid gain value: %d. Must be between 0 and 30.", gain);
        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("setGainControl", "Sensor not found");
        return false;
    }

    esp_err_t err = s->set_agc_gain(s, gain);
    if (err != ESP_OK) {
        ESP_LOGE("setGainControl", "Failed to set gain control with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Get the current exposure-related gain control value | Método para obter o valor atual do controle de ganho relacionado à exposição
* @return The current gain control value | O valor atual do controle de ganho
*/
uint8_t ES_Camera::getExposureGain() {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("getGainControl", "Sensor not found");
        return 0; // Return an invalid value to indicate an error
    }

    return s->status.agc_gain;
}


/*
* Method to set the special effect of the camera sensor | Método para ajustar o efeito especial do sensor da câmera
* @param effect The special effect to be set. Typically, the scale accepts integer values ranging from 0 to 10, where 0 is the default. | O efeito especial a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 10, onde 0 é o padrão.
* @return True if the special effect was set successfully, false otherwise | Verdadeiro se o efeito especial foi ajustado com sucesso, falso caso contrário
* @note 0: none, 1: Negative, 2: Black and White, 3: Blue Tones, 4: Red Tones, 5: Green Tones, 6: Sepia. | 0: nenhum, 1: negativo, 2: preto e branco, 3: tons de azul, 4: tons de vermelho, 5: tons de verde, 6: sépia.
*/
bool ES_Camera::setSpecialEffect(uint8_t effect) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_special_effect(s, effect); // Set the special effect | Ajusta o efeito especial
    if (err != ESP_OK) {
        ESP_LOGE("setSpecialEffect", "Failed to set special effect with error 0x%x", err);
        return false;
    }

    return true;
}


/*
* Method to get the current special effect of the camera sensor | Método para obter o efeito especial atual do sensor da câmera
* @return The current special effect | O efeito especial atual
*/
uint8_t ES_Camera::getSpecialEffect() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.special_effect; // Return the current special effect | Retorna o efeito especial atual
}


/*
* Method to set the maximum gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho máximo (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz.
* @param gainCeiling The gain ceiling to be set. Typically, the scale accepts integer values ranging from 0 to 7, where 0 is the default. | O teto de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 7, onde 0 é o padrão.
* @return True if the gain ceiling was set successfully, false otherwise | Verdadeiro se o teto de ganho foi ajustado com sucesso, falso caso contrário
* @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
*/
bool ES_Camera::setAutoGainCeiling(gainceiling_t  gainCeiling) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_gainceiling(s, gainCeiling); // Set the gain ceiling | Ajusta o teto de ganho
    if (err != ESP_OK) {
        ESP_LOGE("setMaxAutoGain", "Failed to set gain ceiling with error 0x%x", err);
        return false;
    }

    return true;
}

/*
* Method to set the maximum gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho máximo (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz.
* @param gainCeiling The gain ceiling to be set. Typically, the scale accepts integer values ranging from 0 to 7, where 0 is the default. | O teto de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de 0 a 7, onde 0 é o padrão.
* @return True if the gain ceiling was set successfully, false otherwise | Verdadeiro se o teto de ganho foi ajustado com sucesso, falso caso contrário
* @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
*/
bool ES_Camera::setAutoGainCeiling(uint8_t  gainCeiling) {
    return setAutoGainCeiling(static_cast<gainceiling_t>(gainCeiling)); // Call the overloaded method with the appropriate type | Chama o método sobrecarregado com o tipo apropriado
}

/*
* Method to get the current gain ceiling (gain ceiling) in automatic mode on the camera sensor | Método para obter o teto de ganho atual (teto de ganho) no modo automático do sensor da câmera
* @return The current gain ceiling | O teto de ganho atual
* @note 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X. | 0: GAINCEILING_2X, 1: GAINCEILING_4X, 2: GAINCEILING_8X, 3: GAINCEILING_16X, 4: GAINCEILING_32X, 5: GAINCEILING_64X, 6: GAINCEILING_128X.
*/
uint8_t  ES_Camera::getAutoGainCeiling() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.gainceiling; // Return the current gain ceiling | Retorna o teto de ganho atual
}


/*
* Method to set Enable or disable noise reduction control. | Método para ativar ou desativar o controle de redução de ruído.
* @param enable True to enable noise reduction, false to disable it | Verdadeiro para ativar a redução de ruído, falso para desativá-la
* @return True if the noise reduction was set successfully, false otherwise | Verdadeiro se a redução de ruído foi ajustada com sucesso, falso caso contrário
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setNoiseReduction(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_denoise(s, (enable ? 1 : 0)); // Set the noise reduction | Ajusta a redução de ruído
    if (err != ESP_OK) {
        ESP_LOGE("setNoiseReduction", "Failed to set noise reduction with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current noise reduction status of the camera sensor | Método para obter o status atual da redução de ruído do sensor da câmera
* @return True if the noise reduction is enabled, false otherwise | Verdadeiro se a redução de ruído estiver ativada, falso caso contrário
*/
bool ES_Camera::getNoiseReduction() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.denoise; // Return true if noise reduction is enabled, false otherwise | Retorna verdadeiro se a redução de ruído estiver ativada, falso caso contrário
}


/*
* Method to set Enable or disable pixel correction. | Método para ativar ou desativar a correção de pixel.
* @param enable True to enable pixel correction, false to disable it | Verdadeiro para ativar a correção de pixel, falso para desativá-la
* @return True if the pixel correction was set successfully, false otherwise | Verdadeiro se a correção de pixel foi ajustada com sucesso, falso caso contrário
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setPixelCorrection(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_bpc(s, (enable ? 1 : 0)); // Set the pixel correction | Ajusta a correção de pixel
    if (err != ESP_OK) {
        ESP_LOGE("setPixelCorrection", "Failed to set pixel correction with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current pixel correction status of the camera sensor | Método para obter o status atual da correção de pixel do sensor da câmera
* @return True if the pixel correction is enabled, false otherwise | Verdadeiro se a correção de pixel estiver ativada, falso caso contrário
* @note This method is used to check if the pixel correction is enabled or disabled. | Este método é usado para verificar se a correção de pixel está ativada ou desativada.
*/
bool ES_Camera::getPixelCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.bpc; // Return true if pixel correction is enabled, false otherwise | Retorna verdadeiro se a correção de pixel estiver ativada, falso caso contrário
}

/*
* Method to set Enable or disable color correction. | Método para ativar ou desativar a correção de cor.
* @param enable True to enable color correction, false to disable it | Verdadeiro para ativar a correção de cor, falso para desativá-la
* @return True if the color correction was set successfully, false otherwise | Verdadeiro se a correção de cor foi ajustada com sucesso, falso caso contrário
*/
bool ES_Camera::setColorCorrection(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_wpc(s, (enable ? 1 : 0)); // Set the color correction | Ajusta a correção de cor
    if (err != ESP_OK) {
        ESP_LOGE("setColorCorrection", "Failed to set color correction with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current color correction status of the camera sensor | Método para obter o status atual da correção de cor do sensor da câmera
* @return True if the color correction is enabled, false otherwise | Verdadeiro se a correção de cor estiver ativada, falso caso contrário
*/
bool ES_Camera::getColorCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.wpc; // Return true if color correction is enabled, false otherwise | Retorna verdadeiro se a correção de cor estiver ativada, falso caso contrário
}


/*
* Method to set Enable or disable raw color correction. | Método para ativar ou desativar a correção de cor RAW.
* @param enable True to enable raw color correction, false to disable it | Verdadeiro para ativar a correção de cor RAW, falso para desativá-la
* @return True if the raw color correction was set successfully, false otherwise | Verdadeiro se a correção de cor RAW foi ajustada com sucesso, falso caso contrário
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setRawColorCorrection(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_raw_gma(s, (enable ? 1 : 0)); // Set the raw color correction | Ajusta a correção de cor RAW
    if (err != ESP_OK) {
        ESP_LOGE("setRawColorCorrection", "Failed to set raw color correction with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current raw color correction status of the camera sensor | Método para obter o status atual da correção de cor RAW do sensor da câmera
* @return True if the raw color correction is enabled, false otherwise | Verdadeiro se a correção de cor RAW estiver ativada, falso caso contrário
*/
bool ES_Camera::getRawColorCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.raw_gma; // Return true if raw color correction is enabled, false otherwise | Retorna verdadeiro se a correção de cor RAW estiver ativada, falso caso contrário
}









        //s->set_lenc(s, 1);                // Controle de correção de lente (1: ativado).
bool ES_Camera::setLensCorrection(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_lenc(s, (enable ? 1 : 0)); // Set the lens correction | Ajusta a correção de lente
    if (err != ESP_OK) {
        ESP_LOGE("setLensCorrection", "Failed to set lens correction with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

bool ES_Camera::getLensCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.lenc; // Return true if lens correction is enabled, false otherwise | Retorna verdadeiro se a correção de lente estiver ativada, falso caso contrário
}


/*
* Method to set the sharpness level of the camera sensor | Método para ajustar o nível de nitidez do sensor da câmera
* @param level The sharpness level to be set. Typically, the scale accepts integer values ranging from -2 to 2, where 0 is the default. | O nível de nitidez a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de -2 a 2, onde 0 é o padrão.
* @return True if the sharpness level was set successfully, false otherwise | Verdadeiro se o nível de nitidez foi ajustado com sucesso, falso caso contrário
* @note -2: Minimum sharpness, 0: Default sharpness, 2: Maximum sharpness. | -2: nitidez mínima, 0: nitidez padrão, 2: nitidez máxima.
* @note Not all sensors support this feature. | Nem todos os sensores suportam esse recurso.
*/
bool ES_Camera::setSharpness(int8_t level) {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("setSharpness", "Sensor not found");
        return false;
    }

    esp_err_t err = s->set_sharpness(s, level); // Set the sharpness | Ajusta a nitidez
    if (err != ESP_OK) {
        ESP_LOGE("setSharpness", "Failed to set sharpness with error 0x%x. The sensor may not support this feature or the driver may not implement it.", err);
        return false;
    }

    return true;
}

/*
* Method to get the current sharpness level of the camera sensor | Método para obter o nível atual de nitidez do sensor da câmera
* @return The current sharpness level | O nível atual de nitidez
*/
int8_t ES_Camera::getSharpness() {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("getSharpness", "Sensor not found");
        return 0;
    }

    return s->status.sharpness;
}


/*
* Method to set the frame size of the camera sensor at runtime | Método para ajustar o tamanho do quadro do sensor da câmera em tempo de execução
* @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
* @return True if the frame size was set successfully, false otherwise | Verdadeiro se o tamanho do quadro foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setFrameSize(framesize_t frameSize) {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("setFrameSize", "Sensor not found");
        return false;
    }

    if(frameSize < 0){
        frameSize = FRAMESIZE_96X96; 
    }else if(frameSize > _maxFrameSize){
        frameSize = _maxFrameSize;
    }

    esp_err_t err = s->set_framesize(s, frameSize); // Ajusta o tamanho do quadro
    if (err != ESP_OK) {
        ESP_LOGE("setFrameSize", "Failed to set frame size with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }

    ESP_LOGI("setFrameSize", "Frame size set to %d successfully", frameSize);
    return true;
}
/*
* Method to set the frame size of the camera sensor at runtime | Método para ajustar o tamanho do quadro do sensor da câmera em tempo de execução
* @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
* @return True if the frame size was set successfully, false otherwise | Verdadeiro se o tamanho do quadro foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setFrameSize(int8_t frameSize) {
    return setFrameSize(static_cast<framesize_t>(frameSize)); // Chama o método sobrecarregado com o tipo apropriado
} 

/*
* Method to get the current frame size of the camera sensor | Método para obter o tamanho atual do quadro do sensor da câmera
* @return The current frame size | O tamanho atual do quadro
*/
framesize_t ES_Camera::getFrameSize() {
    sensor_t *s = esp_camera_sensor_get(); // Obtém o sensor da câmera
    if (s == NULL) {
        ESP_LOGE("getFrameSize", "Sensor not found");
        return FRAMESIZE_INVALID; // Retorna um valor inválido para indicar erro
    }

    return s->status.framesize; // Retorna o tamanho atual do quadro
}





/*
* Method to set the JPEG compression quality | Método para ajustar a qualidade de compressão JPEG
* @param quality The JPEG compression quality to be set. Typically, the scale accepts integer values ranging from 0 to 100, where 10 is the default. | A qualidade de compressão JPEG a ser ajustada. Geralmente, a escala aceita valores inteiros que variam de 0 a 100, onde 10 é o padrão.
* @return True if the JPEG compression quality was set successfully, false otherwise | Verdadeiro se a qualidade de compressão JPEG foi ajustada com sucesso, falso caso contrário
* @note JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
*/
bool ES_Camera::setJpegCompression(int8_t jpegQuality) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_quality(s, jpegQuality); // Set the JPEG compression quality | Ajusta a qualidade de compressão JPEG
    if (err != ESP_OK) {
        ESP_LOGE("setJpegCompression", "Failed to set JPEG compression with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current JPEG compression quality of the camera sensor | Método para obter a qualidade de compressão JPEG atual do sensor da câmera
* @return The current JPEG compression quality | A qualidade de compressão JPEG atual
*/
int8_t ES_Camera::getJpegCompression() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.quality; // Return the current JPEG compression quality | Retorna a qualidade atual de compressão JPEG
}


/*
* Method to set Enable or disable horizontal mirror. | Método para ativar ou desativar o espelhamento horizontal.
* @param enable True to enable horizontal mirror, false to disable it | Verdadeiro para ativar o espelhamento horizontal, falso para desativá-lo
* @return True if the horizontal mirror was set successfully, false otherwise | Verdadeiro se o espelhamento horizontal foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setHorizontalMirror(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_hmirror(s, (enable ? 1 : 0)); // Set the horizontal mirror | Ajusta o espelhamento horizontal
    if (err != ESP_OK) {
        ESP_LOGE("setHMirror", "Failed to set horizontal mirror with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current horizontal mirror status of the camera sensor | Método para obter o status atual do espelhamento horizontal do sensor da câmera
* @return True if the horizontal mirror is enabled, false otherwise | Verdadeiro se o espelhamento horizontal estiver ativado, falso caso contrário
* @note This method is used to check if the horizontal mirror is enabled or disabled. | Este método é usado para verificar se o espelhamento horizontal está ativado ou desativado.
*/
bool ES_Camera::getHorizontalMirror() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.hmirror; // Return true if horizontal mirror is enabled, false otherwise | Retorna verdadeiro se o espelhamento horizontal estiver ativado, falso caso contrário
}


/*
* Method to set Enable or disable vertical mirror. | Método para ativar ou desativar o espelhamento vertical.
* @param enable True to enable vertical mirror, false to disable it | Verdadeiro para ativar o espelhamento vertical, falso para desativá-lo
* @return True if the vertical mirror was set successfully, false otherwise | Verdadeiro se o espelhamento vertical foi ajustado com sucesso, falso caso contrário
*/
bool ES_Camera::setVerticalMirror(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_vflip(s, (enable ? 1 : 0)); // Set the vertical flip | Ajusta o espelhamento vertical
    if (err != ESP_OK) {
        ESP_LOGE("setVFlip", "Failed to set vertical flip with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current vertical mirror status of the camera sensor | Método para obter o status atual do espelhamento vertical do sensor da câmera
* @return True if the vertical mirror is enabled, false otherwise | Verdadeiro se o espelhamento vertical estiver ativado, falso caso contrário
*/
bool ES_Camera::getVerticalMirror() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.vflip; // Return true if vertical flip is enabled, false otherwise | Retorna verdadeiro se o espelhamento vertical estiver ativado, falso caso contrário
}


/*
* Method to set Enable or disable color bar. | Método para ativar ou desativar a barra de cores.
* @param enable True to enable color bar, false to disable it | Verdadeiro para ativar a barra de cores, falso para desativá-la
*/
bool ES_Camera::setColorBar(bool enable) {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    esp_err_t err = s->set_colorbar(s, (enable ? 1 : 0)); // Set the color bar | Ajusta a barra de cores
    if (err != ESP_OK) {
        ESP_LOGE("setColorBar", "Failed to set color bar with error 0x%x. The sensor may not support this feature.", err);
        return false;
    }
    return true;
}

/*
* Method to get the current color bar status of the camera sensor | Método para obter o status atual da barra de cores do sensor da câmera
* @return True if the color bar is enabled, false otherwise | Verdadeiro se a barra de cores estiver ativada, falso caso contrário
*/
bool ES_Camera::getColorBar() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.colorbar; // Return true if color bar is enabled, false otherwise | Retorna verdadeiro se a barra de cores estiver ativada, falso caso contrário
}


/*
* Method to capture a frame in JPEG format | Método para capturar um frame no formato JPEG
* @param jpegBuf Pointer to the buffer where the JPEG data will be stored | Ponteiro para o buffer onde os dados JPEG serão armazenados
* @param jpegBufLen Pointer to the variable where the length of the JPEG data will be stored | Ponteiro para a variável onde o comprimento dos dados JPEG será armazenado
* @return True if the frame was captured successfully, false otherwise | Verdadeiro se o frame foi capturado com sucesso, falso caso contrário
*/
bool ES_Camera::getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen ) {

    camera_fb_t *fb = esp_camera_fb_get(); // Captures a frame from the camera | Captura um frame da câmera
    // Check if the frame was captured successfully | Verifica se o frame foi capturado com sucesso
    if (!fb) {
        ESP_LOGE("getFrameJpegBuffer", "Failed to capture frame from the camera");
        return false;
    }
    // Check if the frame is in JPEG format | Verifica se o frame está no formato JPEG
    if (fb->format != PIXFORMAT_JPEG) {
        bool jpeg_converted = frame2jpg(fb, 80, jpegBuf, jpegBufLen);   // Converts the frame to JPEG format | Converte o frame para o formato JPEG
        esp_camera_fb_return(fb);   // Release the frame from the buffer | Libera o frame do buffer
        if (!jpeg_converted) {
            ESP_LOGE("getFrameJpegBuffer", "Failed to convert frame to JPEG");
            return false;
        }
    } else {
        // If the frame is already in JPEG format, just return the buffer and length | Se o frame já estiver no formato JPEG, apenas retorna o buffer e o comprimento
        *jpegBufLen = fb->len;
        *jpegBuf = fb->buf;
        esp_camera_fb_return(fb); // Release frame from buffer | Libera o frame do buffer
    }

    return true;
}
/*
* Method to capture a frame in JPEG format with specified frame size and JPEG quality | Método para capturar um frame no formato JPEG com tamanho de quadro e qualidade JPEG especificados
* @param jpegBuf Pointer to the buffer where the JPEG data will be stored | Ponteiro para o buffer onde os dados JPEG serão armazenados
* @param jpegBufLen Pointer to the variable where the length of the JPEG data will be stored | Ponteiro para a variável onde o comprimento dos dados JPEG será armazenado
* @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
* @param jpegQuality JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
* @return True if the frame was captured successfully, false otherwise | Verdadeiro se o frame foi capturado com sucesso, falso caso contrário
* @note This method sets the frame size and JPEG quality before capturing the frame. | Este método ajusta o tamanho do quadro e a qualidade JPEG antes de capturar o frame.
*/
bool ES_Camera::getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen, framesize_t frameSize, int8_t jpegQuality) {
    if (!setFrameSize(frameSize)) { // Adjust the frame size | Ajusta o tamanho do quadro
        ESP_LOGE("getFrameJpegBuffer", "Failed to set frame size");
        return false;
    }
    if (!setJpegCompression(jpegQuality)) { // Adjust the JPEG compression quality | Ajusta a qualidade de compressão JPEG
        ESP_LOGE("getFrameJpegBuffer", "Failed to set JPEG compression quality");
        return false;
    }

    return getFrameJpegBuffer(jpegBuf, jpegBufLen); // Call the method to capture the frame | Chama o método para capturar o frame
}


/*
* Method to save the captured frame to a JPEG file | Método para salvar o frame capturado em um arquivo JPEG
* @param fs The file system to use (e.g., SPIFFS or SD) | O sistema de arquivos a ser usado (ex.: SPIFFS ou SD)
* @param filePath The path where the JPEG file will be saved | O caminho onde o arquivo JPEG será salvo
*/
bool ES_Camera::saveFrameToJpegFile(fs::FS &fs, const char* filePath) {
    pauseStream = true; // Pausa o stream

    // Captures the frame from the camera and converts it to JPEG | Captura o frame da câmera e converte para JPEG
    if (!getFrameJpegBuffer(&_jpegBuf, &_jpegBufLen)) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to capture frame");
        return false;
    }

    // Check if the JPEG buffer is valid | Verifica se o buffer JPEG é válido
    if (fs.exists(filePath)) {
        if (!fs.remove(filePath)) {
            ESP_LOGE("saveFrameToJpegFile", "Failed to remove existing file: %s", filePath);
            free(_jpegBuf); // Libera o buffer JPEG
            return false;
        }
    }

    // Open the file for writing | Abre o arquivo para escrita
    File file = fs.open(filePath, FILE_WRITE);
    if (!file) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to open file: %s", filePath);
        free(_jpegBuf); // Libera o buffer JPEG
        return false;
    }

    // Write the JPEG data to the file | Escreve os dados JPEG no arquivo
    if (file.write(_jpegBuf, _jpegBufLen) != _jpegBufLen) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to write data to file: %s", filePath);
        file.close();
        free(_jpegBuf); // Libera o buffer JPEG
        return false;
    }
    
    file.close(); // Fecha o arquivo

    pauseStream = false; // Returns the stream to normal operation | Retorna o stream para operação normal

    return true;
}

/*
* Method to save the captured frame to a JPEG file with specified frame size and JPEG quality | Método para salvar o frame capturado em um arquivo JPEG com tamanho de quadro e qualidade JPEG especificados
* @param fs The file system to use (e.g., SPIFFS or SD) | O sistema de arquivos a ser usado (ex.: SPIFFS ou SD)
* @param filePath The path where the JPEG file will be saved | O caminho onde o arquivo JPEG será salvo
* @param frameSize The frame size to be set. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc. | O tamanho do quadro a ser ajustado. Ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA, etc.
* @param jpegQuality JPEG quality (0-10 High quality, 11-20 medium quality, 21-63 low quality). | Qualidade JPEG (0-10 Alta qualidade, 11-20 qualidade média, 21-63 baixa qualidade).
* @return True if the frame was saved successfully, false otherwise | Verdadeiro se o frame foi salvo com sucesso, falso caso contrário
*/
bool ES_Camera::saveFrameToJpegFile(fs::FS &fs, const char* filePath, framesize_t frameSize, int8_t jpegQuality) {
    framesize_t originalFrameSize = getFrameSize(); // Salva o tamanho do quadro original
    int8_t originalJpegQuality = getJpegCompression(); // Salva a qualidade JPEG original
    pauseStream = true; // Pauses the stream | Pausa o stream

    if (!setFrameSize(frameSize)) { // Adjust the frame size | Ajusta o tamanho do quadro
        ESP_LOGE("saveFrameToJpegFile", "Failed to set frame size");
        pauseStream = false; // Resume the stream | Retoma o stream
        return false;
    }
    if (!setJpegCompression(jpegQuality)) { // Adjust the JPEG compression quality | Ajusta a qualidade de compressão JPEG
        ESP_LOGE("saveFrameToJpegFile", "Failed to set JPEG compression quality");
        setFrameSize(originalFrameSize); // Restore the original frame size | Restaura o tamanho do quadro original
        pauseStream = false; // Resume the stream | Retoma o stream
        return false;
    }

    bool result = saveFrameToJpegFile(fs, filePath); // Call the method to save the frame | Chama o método para salvar o frame

    // Restore the original frame size and JPEG quality | Restaura o tamanho do quadro original e a qualidade JPEG
    if (!setFrameSize(originalFrameSize)) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to restore original frame size to %d", originalFrameSize);
        result = false;
    }
    // Restore the original JPEG quality | Restaura a qualidade JPEG original
    if (!setJpegCompression(originalJpegQuality)) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to restore original JPEG quality to %d", originalJpegQuality);
        result = false;
    }

    // Atualmente não é necessário, pois o stream já foi despausado na função saveFrameToJpegFile, porém isso não interfere em um frame de tamanho errado no stream. Mesmo que a pause do stream seja controlada aqui por esse método o frame de tamnho errado preciste.
    pauseStream = false; // Returns the stream to normal operation | Retorna o stream para operação normal

    return result;
}


/*
* Method to handle the stream request | Método para manipular a solicitação de stream
* @param req The HTTP request | A solicitação HTTP
* @return ESP_OK if the request was handled successfully, otherwise an error code | ESP_OK se a solicitação foi manipulada com sucesso, caso contrário, um código de erro
* @note This method is used to handle the stream request from the client. | Este método é usado para manipular a solicitação de stream do cliente.
*/
esp_err_t ES_Camera::handleStreamRequest(httpd_req_t *req) {
    esp_err_t res = ESP_OK;

    // Set the HTTP response type | Configura o tipo de resposta HTTP
    res = httpd_resp_set_type(req, "multipart/x-mixed-replace;boundary=frame");
    if (res != ESP_OK) return res;

    while (true) {
        // Pausa the stream if needed | Pausa o stream se necessário
        if (!pauseStream) {
            // Capture a frame from the camera | Captura um frame da câmera
            if (!getFrameJpegBuffer(&_jpegBuf, &_jpegBufLen)) {
                ESP_LOGE("handleStreamRequest", "Failed to capture frame");
                res = ESP_FAIL;
                break;
            }

            // Send the frame as part of the stream | Envia o frame como parte do stream
            char part_buf[64];
            size_t hlen = snprintf((char *)part_buf, 64, "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n", _jpegBufLen);
            res = httpd_resp_send_chunk(req, part_buf, hlen);
            if (res == ESP_OK) {
                res = httpd_resp_send_chunk(req, (const char *)_jpegBuf, _jpegBufLen);
            }

            if (res != ESP_OK) break;

        }else{
            // If the stream is paused, wait for a short period before checking again | Se o stream estiver pausado, aguarde um curto período antes de verificar novamente
            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for a short period before checking again | Aguarda um curto período antes de verificar novamente
        }
    }
    return res;
}


/*
* Method to create the stream endpoint | Método para criar o endpoint de stream
* @param uri The URI for the stream endpoint | O URI para o endpoint de stream
* @return The HTTP URI structure for the stream endpoint | A estrutura HTTP URI para o endpoint de stream
* @note This method is used to create the stream endpoint for the camera. | Este método é usado para criar o endpoint de stream para a câmera.
*/
httpd_uri_t ES_Camera::createStreamEndpoint(const char* streamUri) {
    _streamUri = streamUri; // Store the stream URI | Armazena o URI de stream
    return {
        .uri = _streamUri,
        .method = HTTP_GET,
        .handler = [](httpd_req_t *req) -> esp_err_t {
            ES_Camera* camera = (ES_Camera*)req->user_ctx;
            return camera->handleStreamRequest(req);
        },
        .user_ctx = this,
        .is_websocket = true,
        .handle_ws_control_frames = false,
        .supported_subprotocol = NULL
    };
}

/*
* Method to get the stream URI | Método para obter o URI de stream
* @return The stream URI | O URI de stream
* @note This method is used to retrieve the stream URI for the camera. | Este método é usado para recuperar o URI de stream para a câmera.
*/
const char* ES_Camera::getStreamUri() {
    return _streamUri; // Return the stored stream URI handler | Retorna o handler do URI de stream armazenado
}