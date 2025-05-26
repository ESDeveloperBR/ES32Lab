#include "ES_TFT.h"

// <<< Compares two strings (case insensitive) | Compara duas strings (case insensitive) >>>
bool ES_TFT::_compareStr(String str1, String str2) {
    str1.toUpperCase();
    str2.toUpperCase();
    return str1 == str2;
}

// <<< Renders a decoded JPEG image | Renderiza uma imagem JPEG decodificada >>>
bool ES_TFT::_renderDecodedJPEG(int xpos, int ypos) {
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    bool swapBytes = getSwapBytes();
    setSwapBytes(true);

    uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
    uint32_t min_h = minimum(mcu_h, max_y % mcu_h);
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    max_x += xpos;
    max_y += ypos;

    while (JpegDec.read()) {
        pImg = JpegDec.pImage;
        int mcu_x = JpegDec.MCUx * mcu_w + xpos;
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;

        win_w = (mcu_x + mcu_w <= max_x) ? mcu_w : min_w;
        win_h = (mcu_y + mcu_h <= max_y) ? mcu_h : min_h;

        if (win_w != mcu_w) {
            uint16_t *cImg = pImg + win_w;
            int p = 0;
            for (int h = 1; h < win_h; h++) {
                p += mcu_w;
                for (int w = 0; w < win_w; w++) {
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        if ((mcu_x + win_w) <= width() && (mcu_y + win_h) <= height())
            pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
        else if ((mcu_y + win_h) >= height())
            JpegDec.abort();
    }
    setSwapBytes(swapBytes);
    return true;
}


// <<< Constructor of the class | Construtor da classe >>>
ES_TFT::ES_TFT(void) : TFT_eSPI() {}


// <<< Draws a centered string on the screen | Desenha uma string centralizada na tela >>>
int16_t ES_TFT::drawCentreScreenString(const char *string, int32_t y, uint8_t font){
    return drawCentreString(string, width()/2, y, font);
}
// <<< Draws a centered string on the screen | Desenha uma string centralizada na tela >>>
int16_t ES_TFT::drawCentreScreenString(const String& string, int32_t y, uint8_t font){
    return drawCentreString(string, width()/2, y, font);
}


// <<< Draws a right-aligned string on the screen | Desenha uma string alinhada à direita na tela >>>
int16_t ES_TFT::drawRightScreenString(const char *string, int32_t y, uint8_t font){
    return drawRightString(string, width(), y, font);
}
// <<< Draws a right-aligned string on the screen | Desenha uma string alinhada à direita na tela >>>
int16_t ES_TFT::drawRightScreenString(const String& string, int32_t y, uint8_t font){
//    return TFT_eSPI::drawRightString(string, width(), y, font);
    return drawRightString(string, width(), y, font);
}


// <<< Renders a JPEG image from the file system | Renderiza uma imagem JPEG do sistema de arquivos >>>
bool ES_TFT::renderJPEG(fs::FS& fs, const String& fileName, int xpos, int ypos) {
    String normalizedPath = fileName;
    if (!normalizedPath.endsWith(".jpg") && !normalizedPath.endsWith(".JPG")) {
        normalizedPath += ".jpg";
    }

    //if (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) return false;
    if (!_arquivo.exists(fs, normalizedPath)) return false;

    if (!JpegDec.decodeFsFile(_arquivo.getFile(fs, normalizedPath))) return false;
    bool result = _renderDecodedJPEG(xpos, ypos);
    return result;
}


// <<< Renders a JPEG image from a buffer | Renderiza uma imagem JPEG de um buffer >>>
bool ES_TFT::renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos, int ypos) {
    if (!JpegDec.decodeArray(jpegBuf, jpegLen)) return false;
    return _renderDecodedJPEG(xpos, ypos);
}


// <<< Renders a camera frame | Renderiza um quadro da câmera >>>
bool ES_TFT::renderCameraFrame(ES_Camera& camera, int xpos, int ypos) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) return false;

    bool result = false;
    if (fb->format == PIXFORMAT_JPEG) {
        result = renderJpegBuffer(fb->buf, fb->len, xpos, ypos);
    } else if (fb->format == PIXFORMAT_RGB565) {
        int width = camera.getFrameWidth();
        int height = camera.getFrameHeight();
        pushImage(xpos, ypos, width, height, (uint16_t*)fb->buf);
        result = true;
    }
    esp_camera_fb_return(fb);
    return result;
}


// <<< Renders the first JPEG file in a directory | Renderiza o primeiro arquivo JPEG em um diretório >>>
bool ES_TFT::renderFirstFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getFirstFileName(fs, directory.c_str());
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getNextFileName(fs, fileName.c_str());
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}


// <<< Renders the last JPEG file in a directory | Renderiza o último arquivo JPEG em um diretório >>>
bool ES_TFT::renderLastFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getLastFileName(fs, directory.c_str());
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getPreviousFileName(fs, fileName.c_str());
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}


// <<< Renders the next JPEG file in a directory | Renderiza o próximo arquivo JPEG em um diretório >>>
bool ES_TFT::renderNextFileJPEG(fs::FS& fs, const String& path, int xpos, int ypos) {
    String fileName = _arquivo.getNextFileName(fs, path);
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getNextFileName(fs, path);
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}


// <<< Renders the previous JPEG file in a directory | Renderiza o arquivo JPEG anterior em um diretório >>>
bool ES_TFT::renderPreviousFileJPEG(fs::FS& fs, const String& path, int xpos, int ypos) {
    String fileName = _arquivo.getPreviousFileName(fs, path);
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getPreviousFileName(fs, path);
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}


// <<< Loads a font file from the file system | Carrega um arquivo de fonte do sistema de arquivos >>>
void ES_TFT::loadFontFile(fs::FS& fs, const String& fontName) {
    Serial.println(fontName);

    String fontNameNormalized = fontName;
    fontNameNormalized.toLowerCase();
    if (fontNameNormalized[0] == '/') fontNameNormalized = fontNameNormalized.substring(1);
    if (fontNameNormalized.endsWith(".vlw")) {
        fontNameNormalized = fontNameNormalized.substring(0, fontNameNormalized.length() - 4);
    }
    _arquivo.begin(fs);
    Serial.println("fontNameNormalized: " + fontNameNormalized);
    TFT_eSPI::loadFont(fontNameNormalized, fs);
}