#include "ES_TFT.h"

// <<< Compares two strings (case insensitive) | Compara duas strings (case insensitive) >>>
bool ES_TFT::_compareStr(String str1, String str2) {
    str1.toUpperCase();
    str2.toUpperCase();
    return str1 == str2;
}

// <<< Checks if a file name has a JPEG extension | Verifica se o nome do arquivo possui extensão JPEG >>>
bool ES_TFT::_isJpegFile(const String& fileName) {
    String normalizedFileName = fileName;
    normalizedFileName.toLowerCase();

    return normalizedFileName.endsWith(".jpg") || normalizedFileName.endsWith(".jpeg");
}

// <<< Normalizes a JPEG file name | Normaliza o nome de um arquivo JPEG >>>
String ES_TFT::_normalizeJpegFileName(const String& fileName) {
    if (_isJpegFile(fileName)) return fileName;
    return fileName + ".jpg";
}

// <<< Renders a decoded JPEG image | Renderiza uma imagem JPEG decodificada >>>
bool ES_TFT::_renderDecodedJPEG(int xpos, int ypos, bool fitToScreen) {
    if (!fitToScreen) return _renderDecodedJPEGOriginal(xpos, ypos);

    int availableWidth = width() - xpos;
    int availableHeight = height() - ypos;

    if (availableWidth <= 0 || availableHeight <= 0) {
        JpegDec.abort();
        return false;
    }

    if (JpegDec.width <= availableWidth && JpegDec.height <= availableHeight) {
        return _renderDecodedJPEGOriginal(xpos, ypos);
    }

    return _renderDecodedJPEGFitToScreen(xpos, ypos);
}

// <<< Renders a decoded JPEG image in original size | Renderiza uma imagem JPEG decodificada no tamanho original >>>
bool ES_TFT::_renderDecodedJPEGOriginal(int xpos, int ypos) {
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

// <<< Renders a decoded JPEG image fitted to the display area | Renderiza uma imagem JPEG decodificada ajustada à área do display >>>
bool ES_TFT::_renderDecodedJPEGFitToScreen(int xpos, int ypos) {
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t sourceWidth = JpegDec.width;
    uint32_t sourceHeight = JpegDec.height;
    uint16_t availableWidth = width() - xpos;
    uint16_t availableHeight = height() - ypos;

    float scaleX = (float)availableWidth / sourceWidth;
    float scaleY = (float)availableHeight / sourceHeight;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    if (scale <= 0.0f) {
        JpegDec.abort();
        return false;
    }

    uint16_t targetWidth = (uint16_t)(sourceWidth * scale);
    uint16_t targetHeight = (uint16_t)(sourceHeight * scale);

    if (targetWidth == 0) targetWidth = 1;
    if (targetHeight == 0) targetHeight = 1;
    if (targetWidth > availableWidth) targetWidth = availableWidth;
    if (targetHeight > availableHeight) targetHeight = availableHeight;

    uint32_t *xMap = new uint32_t[targetWidth];
    uint32_t *yMap = new uint32_t[targetHeight];
    uint32_t scaledBlockCapacity = (uint32_t)(mcu_w + 2) * (uint32_t)(mcu_h + 2);
    uint16_t *scaledBlock = new uint16_t[scaledBlockCapacity];

    if (!xMap || !yMap || !scaledBlock) {
        delete[] xMap;
        delete[] yMap;
        delete[] scaledBlock;
        JpegDec.abort();
        return false;
    }

    for (uint16_t x = 0; x < targetWidth; x++) {
        xMap[x] = ((uint32_t)x * sourceWidth) / targetWidth;
        if (xMap[x] >= sourceWidth) xMap[x] = sourceWidth - 1;
    }

    for (uint16_t y = 0; y < targetHeight; y++) {
        yMap[y] = ((uint32_t)y * sourceHeight) / targetHeight;
        if (yMap[y] >= sourceHeight) yMap[y] = sourceHeight - 1;
    }

    bool swapBytes = getSwapBytes();
    setSwapBytes(true);

    while (JpegDec.read()) {
        pImg = JpegDec.pImage;

        uint32_t sourceX = JpegDec.MCUx * mcu_w;
        uint32_t sourceY = JpegDec.MCUy * mcu_h;
        uint32_t sourceBlockWidth = ((sourceX + mcu_w) <= sourceWidth) ? mcu_w : (sourceWidth - sourceX);
        uint32_t sourceBlockHeight = ((sourceY + mcu_h) <= sourceHeight) ? mcu_h : (sourceHeight - sourceY);

        int32_t targetX0 = xpos + ((sourceX * targetWidth) / sourceWidth);
        int32_t targetY0 = ypos + ((sourceY * targetHeight) / sourceHeight);
        int32_t targetX1 = xpos + (((sourceX + sourceBlockWidth) * targetWidth + sourceWidth - 1) / sourceWidth);
        int32_t targetY1 = ypos + (((sourceY + sourceBlockHeight) * targetHeight + sourceHeight - 1) / sourceHeight);

        int32_t blockWidth = targetX1 - targetX0;
        int32_t blockHeight = targetY1 - targetY0;

        if (blockWidth <= 0 || blockHeight <= 0) continue;
        if (targetX0 >= width() || targetY0 >= height()) continue;

        if (targetX0 < 0 || targetY0 < 0 || (targetX0 + blockWidth) > width() || (targetY0 + blockHeight) > height()) {
            JpegDec.abort();
            setSwapBytes(swapBytes);
            delete[] xMap;
            delete[] yMap;
            delete[] scaledBlock;
            return false;
        }

        if ((uint32_t)(blockWidth * blockHeight) > scaledBlockCapacity) {
            JpegDec.abort();
            setSwapBytes(swapBytes);
            delete[] xMap;
            delete[] yMap;
            delete[] scaledBlock;
            return false;
        }

        for (int32_t y = 0; y < blockHeight; y++) {
            uint32_t targetRelativeY = targetY0 + y - ypos;
            if (targetRelativeY >= targetHeight) targetRelativeY = targetHeight - 1;
            uint32_t mappedSourceY = yMap[targetRelativeY];

            if (mappedSourceY < sourceY) mappedSourceY = sourceY;
            if (mappedSourceY >= sourceY + sourceBlockHeight) mappedSourceY = sourceY + sourceBlockHeight - 1;

            uint32_t sourceOffsetY = mappedSourceY - sourceY;

            for (int32_t x = 0; x < blockWidth; x++) {
                uint32_t targetRelativeX = targetX0 + x - xpos;
                if (targetRelativeX >= targetWidth) targetRelativeX = targetWidth - 1;
                uint32_t mappedSourceX = xMap[targetRelativeX];

                if (mappedSourceX < sourceX) mappedSourceX = sourceX;
                if (mappedSourceX >= sourceX + sourceBlockWidth) mappedSourceX = sourceX + sourceBlockWidth - 1;

                uint32_t sourceOffsetX = mappedSourceX - sourceX;
                scaledBlock[(y * blockWidth) + x] = pImg[(sourceOffsetY * mcu_w) + sourceOffsetX];
            }
        }

        pushImage(targetX0, targetY0, blockWidth, blockHeight, scaledBlock);
    }

    setSwapBytes(swapBytes);
    delete[] xMap;
    delete[] yMap;
    delete[] scaledBlock;
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
bool ES_TFT::renderJPEG(fs::FS& fs, const String& fileName, int xpos, int ypos, bool fitToScreen) {
    String normalizedPath = _normalizeJpegFileName(fileName);

    if (!_arquivo.exists(fs, normalizedPath)) return false;

    File jpegFile = _arquivo.getFile(fs, normalizedPath);
    if (!jpegFile) return false;

    if (!JpegDec.decodeFsFile(jpegFile)) return false;
    bool result = _renderDecodedJPEG(xpos, ypos, fitToScreen);
    return result;
}


// <<< Renders a JPEG image from a buffer | Renderiza uma imagem JPEG de um buffer >>>
bool ES_TFT::renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos, int ypos) {
    if (!JpegDec.decodeArray(jpegBuf, jpegLen)) return false;
    return _renderDecodedJPEG(xpos, ypos, false);
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
bool ES_TFT::renderFirstFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos, bool fitToScreen) {
    String fileName = _arquivo.getFirstFileName(fs, directory.c_str());
    String startFileName = fileName;

    while (fileName.length() > 0 && !_isJpegFile(fileName)) {
        String nextFileName = _arquivo.getNextFileName(fs, fileName.c_str());
        if (nextFileName.length() == 0 || nextFileName == fileName || nextFileName == startFileName) return false;
        fileName = nextFileName;
    }

    if (!_isJpegFile(fileName)) return false;

    return renderJPEG(fs, fileName, xpos, ypos, fitToScreen);
}


// <<< Renders the last JPEG file in a directory | Renderiza o último arquivo JPEG em um diretório >>>
bool ES_TFT::renderLastFileJPEG(fs::FS& fs, const String& directory, int xpos, int ypos, bool fitToScreen) {
    String fileName = _arquivo.getLastFileName(fs, directory.c_str());
    String startFileName = fileName;

    while (fileName.length() > 0 && !_isJpegFile(fileName)) {
        String previousFileName = _arquivo.getPreviousFileName(fs, fileName.c_str());
        if (previousFileName.length() == 0 || previousFileName == fileName || previousFileName == startFileName) return false;
        fileName = previousFileName;
    }

    if (!_isJpegFile(fileName)) return false;

    return renderJPEG(fs, fileName, xpos, ypos, fitToScreen);
}


// <<< Renders the next JPEG file in a directory | Renderiza o próximo arquivo JPEG em um diretório >>>
bool ES_TFT::renderNextFileJPEG(fs::FS& fs, const String& path, int xpos, int ypos, bool fitToScreen) {
    String fileName = _arquivo.getNextFileName(fs, path);
    String startFileName = fileName;

    while (fileName.length() > 0 && !_isJpegFile(fileName)) {
        String nextFileName = _arquivo.getNextFileName(fs, fileName.c_str());
        if (nextFileName.length() == 0 || nextFileName == fileName || nextFileName == startFileName) return false;
        fileName = nextFileName;
    }

    if (!_isJpegFile(fileName)) return false;

    return renderJPEG(fs, fileName, xpos, ypos, fitToScreen);
}


// <<< Renders the previous JPEG file in a directory | Renderiza o arquivo JPEG anterior em um diretório >>>
bool ES_TFT::renderPreviousFileJPEG(fs::FS& fs, const String& path, int xpos, int ypos, bool fitToScreen) {
    String fileName = _arquivo.getPreviousFileName(fs, path);
    String startFileName = fileName;

    while (fileName.length() > 0 && !_isJpegFile(fileName)) {
        String previousFileName = _arquivo.getPreviousFileName(fs, fileName.c_str());
        if (previousFileName.length() == 0 || previousFileName == fileName || previousFileName == startFileName) return false;
        fileName = previousFileName;
    }

    if (!_isJpegFile(fileName)) return false;

    return renderJPEG(fs, fileName, xpos, ypos, fitToScreen);
}


// <<< Loads a font file from the file system | Carrega um arquivo de fonte do sistema de arquivos >>>
void ES_TFT::loadFontFile(fs::FS& fs, const String& fontName) {
    String fontNameNormalized = fontName;
    fontNameNormalized.toLowerCase();
    if (fontNameNormalized[0] == '/') fontNameNormalized = fontNameNormalized.substring(1);
    if (fontNameNormalized.endsWith(".vlw")) {
        fontNameNormalized = fontNameNormalized.substring(0, fontNameNormalized.length() - 4);
    }
    _arquivo.begin(fs);
    TFT_eSPI::loadFont(fontNameNormalized, fs);
}
