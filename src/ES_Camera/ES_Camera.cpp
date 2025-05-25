#include "ES_Camera.h"
#include "Arduino.h"

// <<< Constructor of the class | Construtor da classe >>>
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



// <<< Initializes the camera with the specified configuration parameters. | Inicializa a câmera com os parâmetros de configuração especificados. >>>
bool ES_Camera::begin(framesize_t frameSize, uint8_t jpegQuality, framesize_t maxFrameSize, pixformat_t pixelFormat, camera_grab_mode_t grabMode, camera_fb_location_t fbLocation, int fbCount, int xclkFreqHz) {
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


// <<< Method to get the camera sensor name | Método para obter o nome do sensor da câmera >>>
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


// <<< Set brightness level | Ajusta o nível de brilho >>>
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
// <<< Get brightness level | Obtém o nível de brilho >>>
int8_t ES_Camera::getBrightness() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }
    return s->status.brightness; // Return the current brightness level | Retorna o nível atual de brilho
}


// <<< Set contrast level | Ajusta o nível de contraste >>>
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
// <<< Get contrast level | Obtém o nível de contraste >>>
int8_t ES_Camera::getContrast() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.contrast; // Return the current contrast level | Retorna o nível atual de contraste
}


// <<< Set saturation level | Ajusta o nível de saturação >>>
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
// <<< Get saturation level | Obtém o nível de saturação >>>
int8_t ES_Camera::getSaturation() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.saturation; // Return the current saturation level | Retorna o nível atual de saturação
}


// <<< Set Enable or disable automatic white balance. | Habilita ou desabilita o balanço de branco automático. >>>
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
// <<< Get current white balance status | Obtém o status atual do balanço de branco >>>
bool ES_Camera::getWhiteBalance() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.awb; // Return true if white balance is enabled, false otherwise | Retorna verdadeiro se o balanço de branco estiver ativado, falso caso contrário
}


// <<< Set Enable or disable automatic white balance gain. | Habilita ou desabilita o ganho automático do balanço de branco. >>>
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
// <<< Get current white balance gain status | Obtém o status atual do ganho do balanço de branco >>>
bool ES_Camera::getWhiteBalanceGain() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.awb_gain; // Return true if white balance gain is enabled, false otherwise | Retorna verdadeiro se o ganho do balanço de branco estiver ativado, falso caso contrário
}


// <<< Set Enable or disable automatic exposure control. | Habilita ou desabilita o controle automático de exposição. >>>
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
// <<< Get current exposure control status | Obtém o status atual do controle de exposição >>>
bool ES_Camera::getExposure() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }

    return s->status.aec; // Return true if exposure control is enabled, false otherwise | Retorna verdadeiro se o controle de exposição estiver ativado, falso caso contrário
}


// <<< Set Enable or disable advanced exposure control. | Habilita ou desabilita o controle avançado de exposição. >>>
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
// <<< Get current advanced exposure control status | Obtém o status atual do controle avançado de exposição >>>
bool ES_Camera::getExposureAdvanced() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.aec2; // Return true if advanced exposure control is enabled, false otherwise | Retorna verdadeiro se o controle avançado de exposição estiver ativado, falso caso contrário
}


// <<< Set Enable or disable automatic gain control. | Habilita ou desabilita o controle automático de ganho. >>>
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
// <<< Get current exposure control level | Obtém o nível atual de controle de exposição >>>
int8_t ES_Camera::getExposureLevel() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }
    return s->status.ae_level; // Return the current exposure control level | Retorna o nível atual de controle de exposição
}


// <<< Set the exposure control value | Método para ajustar o valor de controle de exposição >>>
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
// <<< Get the current exposure control value | Método para obter o valor atual de controle de exposição >>>
uint16_t ES_Camera::getExposureValue() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }
    return s->status.aec_value; // Return the current exposure control value | Retorna o valor atual de controle de exposição
}


// <<< Set the gain control value | Método para ajustar o valor de controle de ganho >>>
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
// <<< Get the current gain control value | Método para obter o valor atual de controle de ganho >>>
uint8_t ES_Camera::getExposureGain() {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("getGainControl", "Sensor not found");
        return 0; // Return an invalid value to indicate an error
    }
    return s->status.agc_gain;
}


// <<< Set the special effect | Método para ajustar o efeito especial >>>
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
// <<< Get the current special effect | Método para obter o efeito especial atual >>>
uint8_t ES_Camera::getSpecialEffect() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }

    return s->status.special_effect; // Return the current special effect | Retorna o efeito especial atual
}


// <<< Set the gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz. >>>
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
// <<< Set the gain ceiling (gain ceiling) in automatic mode on the camera sensor, used to control amplification in low light conditions. | Método para ajustar o teto de ganho (teto de ganho) no modo automático do sensor da câmera, usado para controlar a amplificação em condições de pouca luz. >>>
bool ES_Camera::setAutoGainCeiling(uint8_t  gainCeiling) {
    return setAutoGainCeiling(static_cast<gainceiling_t>(gainCeiling)); // Call the overloaded method with the appropriate type | Chama o método sobrecarregado com o tipo apropriado
}
// <<< Get the current gain ceiling value | Obtém o valor atual do teto de ganho >>>
uint8_t  ES_Camera::getAutoGainCeiling() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return 0; // Return an invalid value to indicate an error | Retorna um valor inválido para indicar erro
    }
    return s->status.gainceiling; // Return the current gain ceiling | Retorna o teto de ganho atual
}


// <<< Set the frame size | Método para ajustar o tamanho do quadro >>>
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
// <<< Get the current noise reduction status | Método para obter o status atual da redução de ruído >>>
bool ES_Camera::getNoiseReduction() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.denoise; // Return true if noise reduction is enabled, false otherwise | Retorna verdadeiro se a redução de ruído estiver ativada, falso caso contrário
}


// <<< Set Enable or disable pixel correction. | Habilita ou desabilita a correção de pixel. >>>
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
// <<< Get the current pixel correction status | Método para obter o status atual da correção de pixel >>>
bool ES_Camera::getPixelCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.bpc; // Return true if pixel correction is enabled, false otherwise | Retorna verdadeiro se a correção de pixel estiver ativada, falso caso contrário
}


// <<< Set Enable or disable color correction. | Habilita ou desabilita a correção de cor. >>>
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
// <<< Get the current color correction status | Método para obter o status atual da correção de cor >>>
bool ES_Camera::getColorCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.wpc; // Return true if color correction is enabled, false otherwise | Retorna verdadeiro se a correção de cor estiver ativada, falso caso contrário
}


// <<< Set Enable or disable raw color correction. | Habilita ou desabilita a correção de cor RAW. >>>
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
// <<< Get the current raw color correction status | Método para obter o status atual da correção de cor RAW >>>
bool ES_Camera::getRawColorCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.raw_gma; // Return true if raw color correction is enabled, false otherwise | Retorna verdadeiro se a correção de cor RAW estiver ativada, falso caso contrário
}


// <<< Set Enable or disable lens correction. | Habilita ou desabilita a correção de lente. >>>
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
// <<< Get the current lens correction status | Método para obter o status atual da correção de lente >>>
bool ES_Camera::getLensCorrection() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.lenc; // Return true if lens correction is enabled, false otherwise | Retorna verdadeiro se a correção de lente estiver ativada, falso caso contrário
}


// <<< Set the sharpness level | Método para ajustar o nível de nitidez >>>
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
// <<< Get the current sharpness level | Método para obter o nível atual de nitidez >>>
int8_t ES_Camera::getSharpness() {
    sensor_t *s = esp_camera_sensor_get();
    if (s == NULL) {
        ESP_LOGE("getSharpness", "Sensor not found");
        return 0;
    }
    return s->status.sharpness;
}


// <<< Set the frame size | Método para ajustar o tamanho do quadro >>>
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
// <<< Set the frame size | Método para ajustar o tamanho do quadro >>>
bool ES_Camera::setFrameSize(int8_t frameSize) {
    return setFrameSize(static_cast<framesize_t>(frameSize)); // Chama o método sobrecarregado com o tipo apropriado
} 
// <<< Get the current frame size | Método para obter o tamanho atual do quadro >>>
framesize_t ES_Camera::getFrameSize() {
    sensor_t *s = esp_camera_sensor_get(); // Obtém o sensor da câmera
    if (s == NULL) {
        ESP_LOGE("getFrameSize", "Sensor not found");
        return FRAMESIZE_INVALID; // Retorna um valor inválido para indicar erro
    }
    return s->status.framesize; // Retorna o tamanho atual do quadro
}


// <<<  Method to get the current frame width | Método para obter a largura do quadro atual >>>
int ES_Camera::getFrameWidth() {
    framesize_t size = getFrameSize();
    switch (size) {
        case FRAMESIZE_96X96:    return 96;
        case FRAMESIZE_QQVGA:    return 160;
        case FRAMESIZE_QCIF:     return 176;
        case FRAMESIZE_HQVGA:    return 240;
        case FRAMESIZE_240X240:  return 240;
        case FRAMESIZE_QVGA:     return 320;
        case FRAMESIZE_CIF:      return 352;
        case FRAMESIZE_HVGA:     return 480;
        case FRAMESIZE_VGA:      return 640;
        case FRAMESIZE_SVGA:     return 800;
        case FRAMESIZE_XGA:      return 1024;
        case FRAMESIZE_HD:       return 1280;
        case FRAMESIZE_SXGA:     return 1280;
        case FRAMESIZE_UXGA:     return 1600;
        case FRAMESIZE_FHD:      return 1920;
        case FRAMESIZE_P_HD:     return 720;
        case FRAMESIZE_P_3MP:    return 864;
        case FRAMESIZE_QXGA:     return 2048;
        case FRAMESIZE_QHD:      return 2560;
        case FRAMESIZE_WQXGA:    return 2560;
        case FRAMESIZE_P_FHD:    return 1080;
        case FRAMESIZE_QSXGA:    return 2560;
        default:                 return 0;
    }
}
// <<< Method to get the current frame height | Método para obter a altura do quadro atual >>>
int ES_Camera::getFrameHeight() {
    framesize_t size = getFrameSize();
    switch (size) {
        case FRAMESIZE_96X96:    return 96;
        case FRAMESIZE_QQVGA:    return 120;
        case FRAMESIZE_QCIF:     return 144;
        case FRAMESIZE_HQVGA:    return 160;
        case FRAMESIZE_240X240:  return 240;
        case FRAMESIZE_QVGA:     return 240;
        case FRAMESIZE_CIF:      return 288;
        case FRAMESIZE_HVGA:     return 320;
        case FRAMESIZE_VGA:      return 480;
        case FRAMESIZE_SVGA:     return 600;
        case FRAMESIZE_XGA:      return 768;
        case FRAMESIZE_HD:       return 720;
        case FRAMESIZE_SXGA:     return 1024;
        case FRAMESIZE_UXGA:     return 1200;
        case FRAMESIZE_FHD:      return 1080;
        case FRAMESIZE_P_HD:     return 1280;
        case FRAMESIZE_P_3MP:    return 1536;
        case FRAMESIZE_QXGA:     return 1536;
        case FRAMESIZE_QHD:      return 1440;
        case FRAMESIZE_WQXGA:    return 1600;
        case FRAMESIZE_P_FHD:    return 1920;
        case FRAMESIZE_QSXGA:    return 1920;
        default:                 return 0;
    }
}


// <<< Set the JPEG compression quality | Método para ajustar a qualidade de compressão JPEG >>>
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
// <<< Get the current JPEG compression quality | Método para obter a qualidade de compressão JPEG atual >>>
int8_t ES_Camera::getJpegCompression() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.quality; // Return the current JPEG compression quality | Retorna a qualidade atual de compressão JPEG
}


// <<< Set the horizontal mirror | Método para ajustar o espelhamento horizontal >>>
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
// <<< Get the current horizontal mirror status | Método para obter o status atual do espelhamento horizontal >>>
bool ES_Camera::getHorizontalMirror() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.hmirror; // Return true if horizontal mirror is enabled, false otherwise | Retorna verdadeiro se o espelhamento horizontal estiver ativado, falso caso contrário
}


// <<< Set the vertical mirror | Método para ajustar o espelhamento vertical >>>
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
// <<< Get the current vertical mirror status | Método para obter o status atual do espelhamento vertical >>>
bool ES_Camera::getVerticalMirror() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.vflip; // Return true if vertical flip is enabled, false otherwise | Retorna verdadeiro se o espelhamento vertical estiver ativado, falso caso contrário
}


// <<< Enable or disable color bar | Habilita ou desabilita a barra de cores >>>
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
// <<< Get the current color bar status | Obtém o status atual da barra de cores >>>
bool ES_Camera::getColorBar() {
    sensor_t *s = esp_camera_sensor_get(); // Get the camera sensor | Obtém o sensor da câmera
    if (s == NULL) {
        return false;
    }
    return s->status.colorbar; // Return true if color bar is enabled, false otherwise | Retorna verdadeiro se a barra de cores estiver ativada, falso caso contrário
}


// <<< Method to capture a frame from the camera | Método para capturar um frame da câmera >>>
bool ES_Camera::getFrameBuffer(uint8_t** buf, size_t* bufLen) {
    camera_fb_t *fb = esp_camera_fb_get(); // Captura um frame da câmera
    if (!fb) {
        ESP_LOGE("getFrameBuffer", "Failed to capture frame from the camera");
        return false;
    }
    *buf = fb->buf;
    *bufLen = fb->len;
    esp_camera_fb_return(fb); // Libera o frame do buffer
    return true;
}
















// <<< Method to capture a frame in JPEG format | Método para capturar um frame no formato JPEG >>>
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
            ESP_LOGE("getFrameJpegBuffer", "Failed to convert frame to JPEG. Try initializing the camera with PIXFORMAT_JPEG in begin() to avoid memory issues.");
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
// <<< Method to capture a frame in JPEG format with specified frame size and JPEG quality | Método para capturar um frame no formato JPEG com tamanho de quadro e qualidade JPEG especificados >>>
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


// <<<< Method to save the captured frame to a JPEG file | Método para salvar o frame capturado em um arquivo JPEG >>>
bool ES_Camera::saveFrameToJpegFile(fs::FS &fs, const String& fileName) {
    pauseStream = true; // Pausa o stream
    // Captures the frame from the camera and converts it to JPEG | Captura o frame da câmera e converte para JPEG
    if (!getFrameJpegBuffer(&_jpegBuf, &_jpegBufLen)) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to capture frame");
        return false;
    }

    // Ensures the file name ends with ".jpg" | Garante que o nome do arquivo termine com ".jpg"
    String normalizedPath = fileName;
    if (!normalizedPath.endsWith(".jpg") && !normalizedPath.endsWith(".JPG")) {
        normalizedPath += ".jpg";
    }

    ES_File fileManager;
    fileManager.remove(fs, normalizedPath, false);

    File file = fileManager.getFile(fs, String(normalizedPath), true);

    if (!file) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to open file: %s", normalizedPath);
        free(_jpegBuf); // Libera o buffer JPEG
        return false;
    }

    // Write the JPEG data to the file | Escreve os dados JPEG no arquivo
    if (file.write(_jpegBuf, _jpegBufLen) != _jpegBufLen) {
        ESP_LOGE("saveFrameToJpegFile", "Failed to write data to file: %s", normalizedPath);
        file.close();
        free(_jpegBuf); // Libera o buffer JPEG
        return false;
    }
    
    file.close(); // Fecha o arquivo
    pauseStream = false; // Returns the stream to normal operation | Retorna o stream para operação normal
    return true;
}
// <<< Method to save the captured frame to a JPEG file with specified frame size and JPEG quality | Método para salvar o frame capturado em um arquivo JPEG com tamanho de quadro e qualidade JPEG especificados >>>
bool ES_Camera::saveFrameToJpegFile(fs::FS &fs, const String& fileName, framesize_t frameSize, int8_t jpegQuality) {
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

    bool result = saveFrameToJpegFile(fs, fileName); // Call the method to save the frame | Chama o método para salvar o frame

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


// <<< Method to handle the stream request | Método para lidar com a solicitação de stream >>>
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


// <<< Method to create the stream endpoint | Método para criar o endpoint de stream >>>
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

// <<< Method to get the stream URI | Método para obter o URI de stream >>>
const char* ES_Camera::getStreamUri() {
    return _streamUri; // Return the stored stream URI handler | Retorna o handler do URI de stream armazenado
}