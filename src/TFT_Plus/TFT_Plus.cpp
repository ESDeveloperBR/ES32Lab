#include "TFT_Plus.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//********************************************** Implementação dos métodos da classe *********************************************************************
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Compara se as string são iguais >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*  Compare two strings */
boolean TFT_Plus::_compareStr(String str1, String str2){
    str1.toUpperCase();
    str2.toUpperCase();
    if(str1 == str2) return true;
    else return false;
}

// <<<<<<<<< Construtor da Classe >>>>>>>>>>>>>>>>>>>>
/* Class Constructor */
TFT_Plus::TFT_Plus(void){
    /*
    Serial.println("Construtor");
    */
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Inicializa a lib TFT_Plus >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Initialize the TFT_Plus lib */
void TFT_Plus::init(uint8_t tc){  
    tft.init(tc);
}
/* Initialize the TFT_Plus lib */
void TFT_Plus::begin(uint8_t tc){  
    tft.begin(tc);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Methods Draw >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*Method drawPixel prints a pixel
-x: Initial X coordinate;
-y: Initial Y coordinate;
-color: Pixel color;
*/
void TFT_Plus::drawPixel(int32_t x, int32_t y, uint32_t color){
    tft.drawPixel(x, y, color);
}

/*Method drawLine prints a line
-x0: Initial X coordinate;
-y0: Initial Y coordinate;
-x1: Final X coordinate;
-y1: Final Y coordinate;
-color: drawLine color;
*/
void TFT_Plus::drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color){
    tft.drawLine(x0, y0, x1, y1, color);
}

/*The drawFastVLine method prints a line vertically
-x: Initial X coordinate;
-y: Initial Y coordinate;
-h: Height;
-color: drawLine color;
*/
void TFT_Plus::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color){
    tft.drawFastVLine(x, y, h, color);
}

/*The drawFastHLine method prints a line horizontal
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-color: drawFastHLine color;
*/
void TFT_Plus::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color){
    tft.drawFastHLine(x, y, w, color);
}

/*Create a rectangle with fill
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-color: Rectangle color;
*/
void TFT_Plus::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color){
    tft.fillRect(x, y, w, h, color);
}

/* Draw Rectangle
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-color: Rectangle color;
*/
void TFT_Plus::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color){
    tft.drawRect(x, y, w, h, color);
}

/* Round corner rectangle
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-r: Radius
-color: Rectangle color;
*/
void TFT_Plus::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color){
    tft.drawRoundRect(x, y, w, h, r, color);
}

/* Create a rectangle with round corner fill
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-r: Radius
-color: Rectangle color;
*/
void TFT_Plus::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color){
    tft.fillRoundRect(x, y, w, h, r, color);
}

/* Vertical gradient rectangle fill
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-color1: Color 1 gradient;
-color2: Color 2 gradient;
*/
void TFT_Plus::fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2){
    tft.fillRectVGradient(x, y, w, h, color1, color2);
}

/* Horizontal gradient rectangle fill
-x: Initial X coordinate;
-y: Initial Y coordinate;
-w: Width;
-h: Height;
-color1: Color 1 gradient;
-color2: Color 2 gradient;
*/
void TFT_Plus::fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2){
    tft.fillRectHGradient(x, y, w, h, color1, color2);
}

/* Draw circle
-x: Initial X coordinate;
-y: Initial Y coordinate;
-r: Radius
-color: Circle color;
*/
void TFT_Plus::drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color){
    tft.drawCircle(x, y, r, color);
}

/* Draw circle helper
-x: Initial X coordinate;
-y: Initial Y coordinate;
-r: Radius
-cornername: 1, 2, 4 and 8
-color: Circle color;
*/
void TFT_Plus::drawCircleHelper( int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color){
    tft.drawCircleHelper(x, y, r, cornername, color);
}

/* Draw fill circle
-x: Initial X coordinate;
-y: Initial Y coordinate;
-r: Radius
-color: Circle color;
*/
void TFT_Plus::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color){
    tft.fillCircle(x, y, r, color);

}

/* Fill circle helper
- x: Initial X coordinate;
- y: Initial Y coordinate;
- r: Radius
- cornername: 1 or 2
- delta:
- color: Circle color;
*/
void TFT_Plus::fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color){
    tft.fillCircleHelper(x, y, r, cornername, delta, color);
}

/* Draw ellipse
- x: Initial X coordinate;
- y: Initial Y coordinate;
- rx: Radius X
- ry: Radius Y
- color: Ellipse color;
*/
void TFT_Plus::drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color){
    tft.drawEllipse(x, y, rx, ry, color);
}

/* Fill ellipse
- x: Initial X coordinate;
- y: Initial Y coordinate;
- rx: Radius X
- ry: Radius Y
- color: Ellipse color;
*/
void TFT_Plus::fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color){
    tft.fillEllipse(x, y, rx, ry, color);
}

/* Draw Triangle
- x1: Coordinate X point 1;
- y1: Coordinate Y point 1;
- x2: Coordinate X point 2;
- y2: Coordinate Y point 2;
- x3: Coordinate X point 3;
- y4: Coordinate Y point 3;
- color: Triangle color;
*/
void TFT_Plus::drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color){
    tft.drawTriangle(x1, y1, x2, y2, x3, y3, color);
}

/* Fill Triangle
- x1: Coordinate X point 1;
- y1: Coordinate Y point 1;
- x2: Coordinate X point 2;
- y2: Coordinate Y point 2;
- x3: Coordinate X point 3;
- y4: Coordinate Y point 3;
- color: Triangle color;
*/
void TFT_Plus::fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color){
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);
}

/*Return height*/
int16_t TFT_Plus::height(void){
    return tft.height();
}

/*Return width*/
int16_t TFT_Plus::width(void){
    return tft.width();
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Rotação da tela >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*Set screen rotation
-r: Rotation 1, 2, 3 or 4*/
void TFT_Plus::setRotation(uint8_t r){  
    tft.setRotation(r);
}

/*Get screen rotation */
uint8_t TFT_Plus::getRotation(void){
    return tft.getRotation();
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Cor da tela de fundo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Fill Screen */
void TFT_Plus::fillScreen(uint32_t color){  
    tft.fillScreen(color);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Carrega arquivo de font (letras) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*Load a file of type ARRAY with the font in question.
-array: Array name;

Ex.:
#include <Fonts/NotoSansBold36.h>
this.loadFont(NotoSansBold36);
*/
void TFT_Plus::loadFontArray(const uint8_t array[]){
    tft.loadFont(array);
}




// Carrega um arquivo salvo em um SD ou SPPIF do tipo fonte (.vlw)
void TFT_Plus::loadFontFile(String fontName, boolean sdCard){
    fontName.toLowerCase();

    /* Se o nome do arquivo comecar com '/' entÃƒÂ£o remova a '/' */
    if(fontName[0] == '/') fontName = fontName.substring(1, fontName.length());

    /* Se o nome do arquivo tiver extensÃƒÂ£o, remova */
    if(fontName.substring(fontName.length() - 4, fontName.length()) == ".vlw"){ 
        fontName = fontName.substring(0, fontName.length() - 4);
    }

    /* Escolhe se o arquivo esta em SD ou SPIFFS */
    _arquivo.begin(sdCard);
    if(sdCard) tft.loadFont(fontName, SD);
    else tft.loadFont(fontName, SPIFFS);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Desvincula arquivo de font >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Desvincula arquivo de font. Ex.: this.unloadFont();
void TFT_Plus::unloadFont(void){
    tft.unloadFont();
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Coordenada do cursor no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Coordenada do cursor no display
void TFT_Plus::setCursor(int16_t x, int16_t y){  
    tft.setCursor(x, y);
}
// ******************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Text >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ******************************************************************************************

/*Method drawChar prints a char
-x: Initial X coordinate;
-y: Initial Y coordinate;
-c: char;
-color: Char color;
-bg: Char background;
-size: Font size;
*/
void TFT_Plus::drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size){
    tft.drawChar(x, y, c, color, bg, size);
}

/* Draw integer or float Number
-intNumber: Intege number;
-x: Initial X coordinate;
-y: Initial Y coordinate;
-size: Font size;
*/
int16_t TFT_Plus::drawNumber(long intNumber, int32_t x, int32_t y, uint8_t font){
    return tft.drawNumber(intNumber, x, y, font);
}

/* Draw integer or float Number
-intNumber: Intege number;
-x: Initial X coordinate;
-y: Initial Y coordinate;
*/
int16_t TFT_Plus::drawNumber(long intNumber, int32_t x, int32_t y){
    return tft.drawNumber(intNumber, x, y);
}

/* Draw Float Number
-floatNumber: Float Number;
-decimal: Number of decimal places;
-x: Initial X coordinate;
-y: Initial Y coordinate;
-size: Font size;
*/
int16_t TFT_Plus::drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y, uint8_t font){
    return tft.drawFloat(floatNumber, decimal, x, y, font);
}

/* Draw Float Number
-floatNumber: Float Number;
-decimal: Number of decimal places;
-x: Initial X coordinate;
-y: Initial Y coordinate;
*/
int16_t TFT_Plus::drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y){
    return tft.drawFloat(floatNumber, decimal, x, y);
}

/* Draw string
-string: Text;
-x: Initial X coordinate;
-y: Initial Y coordinate;
-size: Font size;
*/
int16_t TFT_Plus::drawString(const char *string, int32_t x, int32_t y, uint8_t font){
    return tft.drawString(string,  x,  y,  font);
}

/* Draw string
-string: Text;
-x: Initial X coordinate;
-y: Initial Y coordinate;
*/
int16_t TFT_Plus::drawString(const char *string, int32_t x, int32_t y){
    return tft.drawString(string,  x,  y);
}

/* Draw string
-string: Text;
-x: Initial X coordinate;
-y: Initial Y coordinate;
-size: Font size;
*/
int16_t TFT_Plus::drawString(const String& string, int32_t x, int32_t y, uint8_t font){
    return tft.drawString(string, x, y, font);
}

/* Draw string
-string: Text;
-x: Initial X coordinate;
-y: Initial Y coordinate;
*/
int16_t TFT_Plus::drawString(const String& string, int32_t x, int32_t y){
    return tft.drawString(string, x, y);
}

/* Draw Centre String
- string: Text;
- x: Initial X coordinate;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font){
    return tft.drawCentreString(string, x, y, font);
}

/* Draw Centre String
- string: Text;
- x: Initial X coordinate;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawCentreString(const String& string, int32_t x, int32_t y, uint8_t font){
    return tft.drawCentreString(string, x, y, font);
}

/* Draw Centre Screen String
- string: Text;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawCentreScreenString(const char *string, int32_t y, uint8_t font){
    return tft.drawCentreString(string, width()/2, y, font);
}

/* Draw Centre Screen String
- string: Text;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawCentreScreenString(const String& string, int32_t y, uint8_t font){
    return tft.drawCentreString(string, width()/2, y, font);
}

/* Draw Right String
- string: Text;
- x: Initial X coordinate;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawRightString(const char *string, int32_t x, int32_t y, uint8_t font){
    return tft.drawRightString(string, x, y, font);
}

/* Draw Right String
- string: Text;
- x: Initial X coordinate;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawRightString(const String& string, int32_t x, int32_t y, uint8_t font){
    return tft.drawRightString(string, x, y, font);
}

/* Draw Right Screen String
- string: Text;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawRightScreenString(const char *string, int32_t y, uint8_t font){
    return tft.drawRightString(string, width(), y, font);
}

/* Draw Right Screen String
- string: Text;
- y: Initial Y coordinate;
- font: Font Size
*/
int16_t TFT_Plus::drawRightScreenString(const String& string, int32_t y, uint8_t font){
    return tft.drawRightString(string, width(), y, font);
}


/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Cor do texto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Cor do texto
void TFT_Plus::setTextColor(uint16_t fgcolor){  
    tft.setTextColor(fgcolor);
}
void TFT_Plus::setTextColor(uint16_t fgcolor, uint16_t bgcolor){  
    tft.setTextColor(fgcolor, bgcolor);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe o texto no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe o texto no display
size_t TFT_Plus::print(String label){  
    return tft.print(label);
}
size_t TFT_Plus::print(int16_t x, int16_t y, uint32_t color, String label, uint32_t bgcolor){ 
    tft.setCursor(x, y);
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.print(label);
}
size_t TFT_Plus::print(int16_t x, int16_t y, String label){ 
    tft.setCursor(x, y);
    return tft.print(label);
}
size_t TFT_Plus::print(uint32_t color, String label, uint32_t bgcolor){ 
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.print(label);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe o texto no display com quebra de linha >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe o texto no display com quebra de linha
size_t TFT_Plus::println(String label){  
    return tft.println(label);
}
size_t TFT_Plus::println(uint32_t color, String label, uint32_t bgcolor){ 
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.println(label);
}


/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna o nome do ultimo arquivo JPEG aberto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
// Retorna o nome do ultimo arquivo JPEG aberto
String TFT_Plus::getFileNameRenderJPEG(void){
    return _fileNameRenderJPEG;
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe uma imagem JPG no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a partir de um arquivo em SPIFFs ou SD
// - fileName: Nome do arquivo a ser aberto
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderJPEG(String fileName, boolean sdCard, int xpos, int ypos) {
    /* Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg", encerre.  */
    if(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        return false;
    }

    _arquivo.begin(fileName, sdCard);

    if(!_arquivo.existe()) return false;

    JpegDec.decodeFsFile(_arquivo.getFile());

    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    bool swapBytes = tft.getSwapBytes();
    tft.setSwapBytes(true);
  
    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
    uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    // save the coordinate of the right and bottom edges to assist image cropping
    // to the screen size
    max_x += xpos;
    max_y += ypos;

    // Fetch data from the file, decode and display
    while (JpegDec.read()) {    // While there is more data in the file
        pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

        // Calculate coordinates of top left corner of current MCU
        int mcu_x = JpegDec.MCUx * mcu_w + xpos;
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;

        // check if the image block size needs to be changed for the right edge
        if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
        else win_w = min_w;

        // check if the image block size needs to be changed for the bottom edge
        if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
        else win_h = min_h;

        // copy pixels into a contiguous block
        if (win_w != mcu_w){
            uint16_t *cImg;
            int p = 0;
            cImg = pImg + win_w;
            for (int h = 1; h < win_h; h++){
                p += mcu_w;
                for (int w = 0; w < win_w; w++){
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        // draw image MCU block only if it will fit on the screen
        if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
            tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
        else if ( (mcu_y + win_h) >= tft.height())
            JpegDec.abort(); // Image has run off bottom of screen so abort decoding
    }
    tft.setSwapBytes(swapBytes);
    _fileNameRenderJPEG = fileName;
    return true;
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no PRIMEIRO arquivo do diretÃƒÂ³rio >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o PRIMEIRO arquivo no diretÃƒÂ³rio. SD ou SPPIFs
// - directory: Nome do diretÃƒÂ³rio com os arquivos a serem abertos
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos){
    String fileName = _arquivo.listaPrimeiroArquivoNome(directory, sdCard);
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaProximoArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }
    if(_arquivo.existe(fileName, sdCard)) _arquivo.begin(fileName, sdCard);
    return renderJPEG(_arquivo.getNomeArquivo(), sdCard, xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no ultimo arquivo do diretÃƒÂ³rio >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o ULTIMO arquivo no diretÃƒÂ³rio. SD ou SPPIFs
// - directory: Nome do diretÃƒÂ³rio com os arquivos a serem abertos
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderLastFileJPEG(String directory, boolean sdCard, int xpos, int ypos){
    String fileName = _arquivo.listaUltimoArquivoNome(directory, sdCard);
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaAnteriorArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }
    if(_arquivo.existe(fileName, sdCard)) _arquivo.begin(fileName, sdCard);
    return renderJPEG(_arquivo.getNomeArquivo(), sdCard, xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no proximo arquivo do diretÃƒÂ³rio selecionado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o PROXIMO arquivo com base na ultima imagem aberta
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
// ATENCAO: A imagem sÃƒÂ³ serÃƒÂ¡ aberta apos a utilizaÃƒÂ§ÃƒÂ£o dos seguintes metodos, visto que ÃƒÂ© necessÃƒÂ¡rio um arquivo como referencia
//   ExecuÃƒÂ§ÃƒÂ£o obrigatÃƒÂ³ria de um dos mÃƒÂ©todos para referenciar um arquivo
//   - renderJPEG(String fileName, boolean sdCard, int xpos, int ypos)
//   - renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos)
//   - renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 )
boolean TFT_Plus::renderNextFileJPEG(int xpos, int ypos){
    String fileName = _arquivo.listaProximoArquivoNome();
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaProximoArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }

    if(_arquivo.existe(fileName)) _arquivo.setNomeArquivo(fileName);

    return renderJPEG(_arquivo.getNomeArquivo(), _arquivo.getSdCard(), xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado arquivo ANTERIOR do diretÃƒÂ³rio selecionado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o arquivo ANTERIOR com base na ultima imagem aberta
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
// ATENCAO: A imagem sÃƒÂ³ serÃƒÂ¡ aberta apos a utilizaÃƒÂ§ÃƒÂ£o dos seguintes metodos, visto que ÃƒÂ© necessÃƒÂ¡rio um arquivo como referencia
//   ExecuÃƒÂ§ÃƒÂ£o obrigatÃƒÂ³ria de um dos mÃƒÂ©todos para referenciar um arquivo
//   - renderJPEG(String fileName, boolean sdCard, int xpos, int ypos)
//   - renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos)
//   - renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 )
boolean TFT_Plus::renderBackFileJPEG(int xpos, int ypos){
    String fileName = _arquivo.listaAnteriorArquivoNome();
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaAnteriorArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }

    if(_arquivo.existe(fileName)) _arquivo.setNomeArquivo(fileName);

    return renderJPEG(_arquivo.getNomeArquivo(), _arquivo.getSdCard(), xpos, ypos);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>