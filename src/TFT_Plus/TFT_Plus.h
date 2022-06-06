/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação.: 05/29/2020 (Derivada da LIB TFT_Pus v.0.2.0)
*/
#ifndef TFT_PLUS_h
#define TFT_PLUS_h

#include <TFT_eSPI.h>     // Graphics and font library for ST7735 driver chip
#include "JPEGDecoder/src/JPEGDecoder.h"
#include "FileManager/FileManager.h"

#define TFT_PLUS_VERSION "0.8.2 update 06/05/2022"  // mm/dd/yyyy

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
#endif