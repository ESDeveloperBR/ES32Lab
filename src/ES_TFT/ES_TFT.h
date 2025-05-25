#ifndef ES_TFT_h
#define ES_TFT_h

#include <TFT_eSPI.h>
#include "JPEGDecoder/src/JPEGDecoder.h"
#include "ES_File/ES_File.h"
#include "ES_Camera/ES_Camera.h"

#define ES_TFT_VERSION "0.11.1 update 23/05/2024"

class ES_TFT : public TFT_eSPI {
private:
    #define minimum(a,b)     (((a) < (b)) ? (a) : (b))
    bool _trabalharComArquivos = false;
    ES_File _arquivo;
    bool _compareStr(String str1, String str2);
    bool _renderDecodedJPEG(int xpos, int ypos);

public:
    ES_TFT(void);

    // Renderização de JPEG
    bool renderJPEGScaled(fs::FS& fs, const String& fileName, int xpos, int ypos, int targetWidth, int targetHeight);
    
    bool renderJPEG(fs::FS& fs, const String& fileName, int xpos = 0, int ypos = 0);
    bool renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos = 0, int ypos = 0);
    bool renderCameraFrame(ES_Camera& camera, int xpos = 0, int ypos = 0);

    // Navegação de arquivos JPEG
    bool renderFirstFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0);
    bool renderLastFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0);
    bool renderNextFileJPEG(fs::FS& fs, const String& directory = "", int xpos = 0, int ypos = 0);
    bool renderPreviousFileJPEG(fs::FS& fs, const String& directory = "", int xpos = 0, int ypos = 0);


    void loadFontFile(fs::FS& fs, const String& fontName);
    
    // Os métodos da TFT_eSPI já estão herdados!
};

#endif