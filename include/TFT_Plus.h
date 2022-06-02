/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação.: 05/29/2020 (Derivada da LIB TFT_Pus v.0.2.0)
*/

#ifndef TFT_Plus_h
#define TFT_Plus_h

#include <Arduino.h>      //Biblioteca Arduino
#include <TFT_eSPI.h>     // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <JPEGDecoder.h>
#include "include/FileManager.h"

#define TFT_PLUS_VERSION "0.8.1 update 06/02/2022"

// Classe TFT_Plus 
class TFT_Plus{
    private:
        #define minimum(a,b)     (((a) < (b)) ? (a) : (b))
        boolean _trabalharComArquivos = false;
        FileManager _arquivo;
        boolean _compareStr(String str1, String str2);
        String  _fileNameRenderJPEG;
    
    public: 

        TFT_eSPI tft; // = TFT_eSPI(128, 460);  // Invoke library, pins defined in User_Setup.h

        TFT_Plus(void);                           /* Construtor */
        void    init(uint8_t tc = TAB_COLOUR), begin(uint8_t tc = TAB_COLOUR);   /* Inicializa a lib */

        // These are virtual so the TFT_eSprite class can override them with sprite specific functions
        virtual void drawPixel(int32_t x, int32_t y, uint32_t color),
                     drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size),
                     drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color),
                     drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color),
                     drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color),
                     fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

        virtual int16_t /*drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font),
                        drawChar(uint16_t uniCode, int32_t x, int32_t y),*/
                        height(void),
                        width(void);

        void    setRotation(uint8_t r);           /* Rotação da tela */
        uint8_t getRotation(void);


        /*
        void     invertDisplay(bool i);  // Tell TFT to invert all displayed colours


        // The TFT_eSprite class inherits the following functions (not all are useful to Sprite class
        void    setAddrWindow(int32_t xs, int32_t ys, int32_t w, int32_t h), // Note: start coordinates + width and height
                setWindow(int32_t xs, int32_t ys, int32_t xe, int32_t ye);   // Note: start + end coordinates
        */

        /*
        // Viewport commands, see "Viewport_Demo" sketch
        void     setViewport(int32_t x, int32_t y, int32_t w, int32_t h, bool vpDatum = true);
        bool     checkViewport(int32_t x, int32_t y, int32_t w, int32_t h);
        int32_t  getViewportX(void);
        int32_t  getViewportY(void);
        int32_t  getViewportWidth(void);
        int32_t  getViewportHeight(void);
        bool     getViewportDatum(void);
        void     frameViewport(uint16_t color, int32_t w);
        void     resetViewport(void);

        // Push (aka write pixel) colours to the TFT (use setAddrWindow() first)
        void     pushColor(uint16_t color),
               pushColor(uint16_t color, uint32_t len),  // Deprecated, use pushBlock()
               pushColors(uint16_t  *data, uint32_t len, bool swap = true), // With byte swap option
               pushColors(uint8_t  *data, uint32_t len); // Deprecated, use pushPixels()

        // Write a solid block of a single colour
        void     pushBlock(uint16_t color, uint32_t len);

        // Write a set of pixels stored in memory, use setSwapBytes(true/false) function to correct endianess
        void     pushPixels(const void * data_in, uint32_t len);

        // Read the colour of a pixel at x,y and return value in 565 format 
        uint16_t readPixel(int32_t x, int32_t y);

           // Support for half duplex (bi-directional SDA) SPI bus where MOSI must be switched to input
           #ifdef TFT_SDA_READ
             #if defined (TFT_eSPI_ENABLE_8_BIT_READ)
        uint8_t  tft_Read_8(void);     // Read 8 bit value from TFT command register
             #endif
        void     begin_SDA_Read(void); // Begin a read on a half duplex (bi-directional SDA) SPI bus - sets MOSI to input
        void     end_SDA_Read(void);   // Restore MOSI to output
           #endif
        */


        void    fillScreen(uint32_t color);       /* Cor da tela de fundo */

        void    drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color),
                drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color),
                fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color);

        void    fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2);
        void    fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2);

        void    drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color),
                drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color),
                fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color),
                fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color);

        void    drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color),
                fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color);

                //                 Corner 1               Corner 2               Corner 3
        void    drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color),
                fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);

/*
  // Image rendering
           // Swap the byte order for pushImage() and pushPixels() - corrects endianness
  void     setSwapBytes(bool swap);
  bool     getSwapBytes(void);

           // Draw bitmap
  void     drawBitmap( int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor),
           drawBitmap( int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor, uint16_t bgcolor),
           drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor),
           drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor, uint16_t bgcolor),
           setBitmapColor(uint16_t fgcolor, uint16_t bgcolor); // Define the 2 colours for 1bpp sprites

           // Set TFT pivot point (use when rendering rotated sprites)
  void     setPivot(int16_t x, int16_t y);
  int16_t  getPivotX(void), // Get pivot x
           getPivotY(void); // Get pivot y

           // The next functions can be used as a pair to copy screen blocks (or horizontal/vertical lines) to another location
           // Read a block of pixels to a data buffer, buffer is 16 bit and the size must be at least w * h
  void     readRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data);
           // Write a block of pixels to the screen which have been read by readRect()
  void     pushRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data);

           // These are used to render images or sprites stored in RAM arrays (used by Sprite class for 16bpp Sprites)
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data);
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint16_t transparent);

           // These are used to render images stored in FLASH (PROGMEM)
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data, uint16_t transparent);
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data);

           // These are used by Sprite class pushSprite() member function for 1, 4 and 8 bits per pixel (bpp) colours
           // They are not intended to be used with user sketches (but could be)
           // Set bpp8 true for 8bpp sprites, false otherwise. The cmap pointer must be specified for 4bpp
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t  *data, bool bpp8 = true, uint16_t *cmap = nullptr);
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t  *data, uint8_t  transparent, bool bpp8 = true, uint16_t *cmap = nullptr);
           // FLASH version
  void     pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *data, bool bpp8,  uint16_t *cmap = nullptr);
           // This next function has been used successfully to dump the TFT screen to a PC for documentation purposes
           // It reads a screen area and returns the 3 RGB 8 bit colour values of each pixel in the buffer
           // Set w and h to 1 to read 1 pixel's colour. The data buffer must be at least w * h * 3 bytes
  void     readRectRGB(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t *data);
  */

        // Text rendering - value returned is the pixel width of the rendered text
        int16_t drawNumber(long intNumber, int32_t x, int32_t y, uint8_t font), // Draw integer using specified font number
                drawNumber(long intNumber, int32_t x, int32_t y),               // Draw integer using current font

                drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y, uint8_t font), // Draw float using specified font number
                drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y),               // Draw float using current font

                // Handle char arrays
                // Use with setTextDatum() to position string on TFT, and setTextPadding() to blank old displayed strings
                drawString(const char *string, int32_t x, int32_t y, uint8_t font),  // Draw string using specified font number
                drawString(const char *string, int32_t x, int32_t y),                // Draw string using current font
                drawString(const String& string, int32_t x, int32_t y, uint8_t font),// Draw string using specified font number
                drawString(const String& string, int32_t x, int32_t y);              // Draw string using current font

        int16_t drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font),  // Deprecated, use setTextDatum() and drawString()
                drawRightString(const char *string, int32_t x, int32_t y, uint8_t font),   // Deprecated, use setTextDatum() and drawString()
                drawCentreString(const String& string, int32_t x, int32_t y, uint8_t font),// Deprecated, use setTextDatum() and drawString()
                drawRightString(const String& string, int32_t x, int32_t y, uint8_t font), // Deprecated, use setTextDatum() and drawString()

                drawCentreScreenString(const char *string, int32_t y, uint8_t font),
                drawCentreScreenString(const String& string, int32_t y, uint8_t font),

                drawRightScreenString(const char *string, int32_t y, uint8_t font),   
                drawRightScreenString(const String& string, int32_t y, uint8_t font); 




    /*
  // Text rendering and font handling support funtions
  void     setCursor(int16_t x, int16_t y),                 // Set cursor for tft.print()
           setCursor(int16_t x, int16_t y, uint8_t font);   // Set cursor and font number for tft.print()

  int16_t  getCursorX(void),                                // Read current cursor x position (moves with tft.print())
           getCursorY(void);                                // Read current cursor y position
           
  void     setTextColor(uint16_t color),                    // Set character (glyph) color only (background not over-written)
           setTextColor(uint16_t fgcolor, uint16_t bgcolor),// Set character (glyph) foreground and backgorund colour
           setTextSize(uint8_t size);                       // Set character size multiplier (this increases pixel size)

  void     setTextWrap(bool wrapX, bool wrapY = false);     // Turn on/off wrapping of text in TFT width and/or height

  void     setTextDatum(uint8_t datum);                     // Set text datum position (default is top left), see Section 6 above 
  uint8_t  getTextDatum(void);

  void     setTextPadding(uint16_t x_width);                // Set text padding (background blanking/over-write) width in pixels
  uint16_t getTextPadding(void);                            // Get text padding

#ifdef LOAD_GFXFF
  void     setFreeFont(const GFXfont *f = NULL),            // Select the GFX Free Font
           setTextFont(uint8_t font);                       // Set the font number to use in future
#else
  void     setFreeFont(uint8_t font),                       // Not used, historical fix to prevent an error
           setTextFont(uint8_t font);                       // Set the font number to use in future
#endif

  int16_t  textWidth(const char *string, uint8_t font),     // Returns pixel width of string in specified font
           textWidth(const char *string),                   // Returns pixel width of string in current font
           textWidth(const String& string, uint8_t font),   // As above for String types
           textWidth(const String& string),
           fontHeight(int16_t font),                        // Returns pixel height of string in specified font
           fontHeight(void);                                // Returns pixel width of string in current font

           // Used by library and Smooth font class to extract Unicode point codes from a UTF8 encoded string
  uint16_t decodeUTF8(uint8_t *buf, uint16_t *index, uint16_t remaining),
           decodeUTF8(uint8_t c);

           // Support function to UTF8 decode and draw characters piped through print stream
  size_t   write(uint8_t);
  
           // Used by Smooth font class to fetch a pixel colour for the anti-aliasing
  void     setCallback(getColorCallback getCol);

  uint16_t fontsLoaded(void); // Each bit in returned value represents a font type that is loaded - used for debug/error handling only

  // Low level read/write
  void     spiwrite(uint8_t);        // legacy support only

  void     writecommand(uint8_t c),  // Send a command, function resets DC/RS high ready for data
           writedata(uint8_t d);     // Send data with DC/RS set high

  void     commandList(const uint8_t *addr); // Send a initialisation sequence to TFT stored in FLASH

  uint8_t  readcommand8( uint8_t cmd_function, uint8_t index = 0); // read 8 bits from TFT
  uint16_t readcommand16(uint8_t cmd_function, uint8_t index = 0); // read 16 bits from TFT
  uint32_t readcommand32(uint8_t cmd_function, uint8_t index = 0); // read 32 bits from TFT


  // Colour conversion
           // Convert 8 bit red, green and blue to 16 bits
  uint16_t color565(uint8_t red, uint8_t green, uint8_t blue);

           // Convert 8 bit colour to 16 bits
  uint16_t color8to16(uint8_t color332);
           // Convert 16 bit colour to 8 bits
  uint8_t  color16to8(uint16_t color565);

           // Convert 16 bit colour to/from 24 bit, R+G+B concatenated into LS 24 bits
  uint32_t color16to24(uint16_t color565);
  uint32_t color24to16(uint32_t color888);

           // Alpha blend 2 colours, see generic "alphaBlend_Test" example
           // alpha =   0 = 100% background colour
           // alpha = 255 = 100% foreground colour
  uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc);
           // 16 bit colour alphaBlend with alpha dither (dither reduces colour banding)
  uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc, uint8_t dither);
           // 24 bit colour alphaBlend with optional alpha dither
  uint32_t alphaBlend24(uint8_t alpha, uint32_t fgc, uint32_t bgc, uint8_t dither = 0);


  // DMA support functions - these are currently just for SPI writes when using the ESP32 or STM32 processors
           // Bear in mind DMA will only be of benefit in particular circumstances and can be tricky
           // to manage by noobs. The functions have however been designed to be noob friendly and
           // avoid a few DMA behaviour "gotchas".
           //
           // At best you will get a 2x TFT rendering performance improvement when using DMA because
           // this library handles the SPI bus so efficiently during normal (non DMA) transfers. The best
           // performance improvement scenario is the DMA transfer time is exactly the same as the time it
           // takes for the processor to prepare the next image buffer and initiate another DMA transfer.
           //
           // DMA transfer to the TFT is done while the processor moves on to handle other tasks. Bear
           // this in mind and watch out for "gotchas" like the image buffer going out of scope as the
           // processor leaves a function or its content being changed while the DMA engine is reading it.
           //
           // The compiler MAY change the implied scope of a buffer which has been set aside by creating
           // an array. For example a buffer defined before a "for-next" loop may get de-allocated when
           // the loop ends. To avoid this use, for example, malloc() and free() to take control of when
           // the buffer space is available and ensure it is not released until DMA is complete.
           //
           // Clearly you should not modify a buffer that is being DMA'ed to the TFT until the DMA is over.
           // Use the dmaBusy() function to check this.  Use tft.startWrite() before invoking DMA so the
           // TFT chip select stays low. If you use tft.endWrite() before DMA is complete then the endWrite
           // function will wait for the DMA to complete, so this may defeat any DMA performance benefit.
           //

  bool     initDMA(bool ctrl_cs = false);  // Initialise the DMA engine and attach to SPI bus - typically used in setup()
                                           // Parameter "true" enables DMA engine control of TFT chip select (ESP32 only)
                                           // For ESP32 only, TFT reads will not work if parameter is true
  void     deInitDMA(void);   // De-initialise the DMA engine and detach from SPI bus - typically not used
  
           // Push an image to the TFT using DMA, buffer is optional and grabs (double buffers) a copy of the image
           // Use the buffer if the image data will get over-written or destroyed while DMA is in progress
           // If swapping colour bytes is defined, and the double buffer option is NOT used, then the bytes
           // in the original data image will be swapped by the function before DMA is initiated.
           // The function will wait for the last DMA to complete if it is called while a previous DMA is still
           // in progress, this simplifies the sketch and helps avoid "gotchas".
  void     pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t* data, uint16_t* buffer = nullptr);

#if defined (ESP32) // ESP32 only at the moment
           // For case where pointer is a const and the image data must not be modified (clipped or byte swapped)
  void     pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t const* data);
#endif
           // Push a block of pixels into a window set up using setAddrWindow()
  void     pushPixelsDMA(uint16_t* image, uint32_t len);

           // Check if the DMA is complete - use while(tft.dmaBusy); for a blocking wait
  bool     dmaBusy(void); // returns true if DMA is still in progress
  void     dmaWait(void); // wait until DMA is complete

  bool     DMA_Enabled = false;   // Flag for DMA enabled state
  uint8_t  spiBusyCheck = 0;      // Number of ESP32 transfer buffers to check

  // Bare metal functions
  void     startWrite(void);                         // Begin SPI transaction
  void     writeColor(uint16_t color, uint32_t len); // Deprecated, use pushBlock()
  void     endWrite(void);                           // End SPI transaction

  // Set/get an arbitrary library configuration attribute or option
  //       Use to switch ON/OFF capabilities such as UTF8 decoding - each attribute has a unique ID
  //       id = 0: reserved - may be used in future to reset all attributes to a default state
  //       id = 1: Turn on (a=true) or off (a=false) GLCD cp437 font character error correction
  //       id = 2: Turn on (a=true) or off (a=false) UTF8 decoding
  //       id = 3: Enable or disable use of ESP32 PSRAM (if available)
           #define CP437_SWITCH 1
           #define UTF8_SWITCH  2
           #define PSRAM_ENABLE 3
  void     setAttribute(uint8_t id = 0, uint8_t a = 0); // Set attribute value
  uint8_t  getAttribute(uint8_t id = 0);                // Get attribute value

           // Used for diagnostic sketch to see library setup adopted by compiler, see Section 7 above
  void     getSetup(setup_t& tft_settings); // Sketch provides the instance to populate

  // Global variables
  static   SPIClass& getSPIinstance(void); // Get SPI class handle

  uint32_t textcolor, textbgcolor;         // Text foreground and background colours

  uint32_t bitmap_fg, bitmap_bg;           // Bitmap foreground (bit=1) and background (bit=0) colours

  uint8_t  textfont,  // Current selected font number
           textsize,  // Current font size multiplier
           textdatum, // Text reference datum
           rotation;  // Display rotation (0-3)


*/



        void    loadFontArray(const uint8_t array[]);
        void    loadFontFile(String fontName, boolean sdCard);

        void    unloadFont(void);                     /* Desvincula arquivo de font*/

        void    setCursor(int16_t x, int16_t y);      /* Coordenada do cursor no display */
        void    setTextColor(uint16_t fgcolor);         /* Cor do texto */
        void    setTextColor(uint16_t fgcolor, uint16_t bgcolor);

      size_t  print(String label);                  /* Exibe o texto no display */
      size_t  print(int16_t x, int16_t y, uint32_t color, String label, uint32_t bgcolor = 0);        /* Exibe o texto no display */
      size_t  print(int16_t x, int16_t y, String label);        /* Exibe o texto no display */
      size_t  print(uint32_t color, String label, uint32_t bgcolor = 0);        /* Exibe o texto no display */
      size_t  println(String label);                /* Exibe o texto no display com quebra de linha*/
      size_t  println(uint32_t color, String label, uint32_t bgcolor = 0);/* Exibe o texto no display */

      String  getFileNameRenderJPEG(void);
      boolean renderJPEG(String fileName, boolean sdCard, int xpos = 0, int ypos = 0);
      boolean renderFirstFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 );
      boolean renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 );
      boolean renderNextFileJPEG(int xpos = 0, int ypos = 0 );
      boolean renderBackFileJPEG(int xpos = 0, int ypos = 0 );
      
  };
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
#endif