#include "ES_TFT.h"

// Compara duas strings (case insensitive)
bool ES_TFT::_compareStr(String str1, String str2) {
    str1.toUpperCase();
    str2.toUpperCase();
    return str1 == str2;
}





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


// Construtor
ES_TFT::ES_TFT(void) : TFT_eSPI() {}







// Renderiza um arquivo JPEG do FS ajustando para o tamanho do display
bool ES_TFT::renderJPEGScaled(fs::FS& fs, const String& fileName, int xpos, int ypos, int targetWidth, int targetHeight) {
    String normalizedPath = fileName;
    if (!normalizedPath.endsWith(".jpg") && !normalizedPath.endsWith(".JPG")) {
        normalizedPath += ".jpg";
    }
    if (!_arquivo.exists(fs, normalizedPath)) return false;
    if (!JpegDec.decodeFsFile(_arquivo.getFile(fs, normalizedPath))) return false;

    int jpegWidth = JpegDec.width;
    int jpegHeight = JpegDec.height;

    float scaleX = (float)targetWidth / jpegWidth;
    float scaleY = (float)targetHeight / jpegHeight;

    // Renderização simples por amostragem (nearest neighbor)
    for (int y = 0; y < targetHeight; y++) {
        int srcY = y / scaleY;
        JpegDec.read();
        uint16_t* srcLine = JpegDec.pImage + srcY * jpegWidth;
        for (int x = 0; x < targetWidth; x++) {
            int srcX = x / scaleX;
            uint16_t color = srcLine[srcX];
            drawPixel(xpos + x, ypos + y, color);
        }
    }
    return true;
}












// Renderiza um arquivo JPEG do FS
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

// Renderiza um JPEG a partir de um buffer na RAM
bool ES_TFT::renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos, int ypos) {
    if (!JpegDec.decodeArray(jpegBuf, jpegLen)) return false;
    return _renderDecodedJPEG(xpos, ypos);
}


// Renderiza um frame da câmera
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








// Navegação de arquivos JPEG
bool ES_TFT::renderFirstFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getFirstFileName(fs, directory.c_str());
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getNextFileName(fs, fileName.c_str());
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}

bool ES_TFT::renderLastFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getLastFileName(fs, directory.c_str());
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getPreviousFileName(fs, fileName.c_str());
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}

bool ES_TFT::renderNextFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getNextFileName(fs, directory);
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getNextFileName(fs, directory);
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}

bool ES_TFT::renderPreviousFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos) {
    String fileName = _arquivo.getPreviousFileName(fs, directory);
    while (!_compareStr(fileName.substring(fileName.length() - 4), ".jpg")) {
        fileName = _arquivo.getPreviousFileName(fs, directory);
        if (!_arquivo.exists(fs, fileName.c_str())) return false;
    }
    return renderJPEG(fs, fileName, xpos, ypos);
}

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