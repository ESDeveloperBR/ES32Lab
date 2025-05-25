/**
 * @brief Example: Display camera frame on TFT using ES_Camera and ES32Lab
 * | Exemplo: Exiba o frame da câmera no display TFT usando ES_Camera e ES32Lab
 *
 * This example demonstrates how easy it is to initialize the camera and display its image on a TFT using the ES32Lab board and its library.
 * The main command is:
 *     display.renderCameraFrame(camera);
 * With just this line, the current camera frame is rendered directly on the display.
 *
 * The ES32Lab board and ES32Lab library make camera integration simple and reliable, eliminating complex wiring and configuration.
 * To initialize the camera, use:
 *     camera.begin(frameSize, jpegQuality, maxFrameSize, pixelFormat, grabMode, fbLocation, fbCount, xclkFreqHz);
 * - frameSize: Image resolution (e.g., FRAMESIZE_QVGA, FRAMESIZE_VGA)
 * - jpegQuality: JPEG quality (0-10 high, 11-20 medium, 21-63 low)
 * - maxFrameSize: Maximum allowed frame size
 * - pixelFormat: Image format (e.g., PIXFORMAT_JPEG, PIXFORMAT_RGB565)
 * - grabMode: Frame grab mode (e.g., CAMERA_GRAB_WHEN_EMPTY)
 * - fbLocation: Frame buffer location (e.g., CAMERA_FB_IN_DRAM or CAMERA_FB_IN_PSRAM)
 * - fbCount: Number of frame buffers (1 for static images, 2+ for streaming)
 * - xclkFreqHz: XCLK frequency in Hz (e.g., 20000000)
 *
 * | Este exemplo demonstra como é fácil inicializar a câmera e exibir sua imagem em um display TFT usando a placa ES32Lab e sua biblioteca.
 * O comando principal é:
 *     display.renderCameraFrame(camera);
 * Com apenas essa linha, o frame atual da câmera é exibido diretamente no display.
 *
 * A placa ES32Lab e a biblioteca ES32Lab tornam a integração da câmera simples e confiável, eliminando a necessidade de fiação e configuração complexas.
 * Para inicializar a câmera, utilize:
 *     camera.begin(frameSize, jpegQuality, maxFrameSize, pixelFormat, grabMode, fbLocation, fbCount, xclkFreqHz);
 * - frameSize: Resolução da imagem (ex.: FRAMESIZE_QVGA, FRAMESIZE_VGA)
 * - jpegQuality: Qualidade JPEG (0-10 alta, 11-20 média, 21-63 baixa)
 * - maxFrameSize: Tamanho máximo permitido do quadro
 * - pixelFormat: Formato da imagem (ex.: PIXFORMAT_JPEG, PIXFORMAT_RGB565)
 * - grabMode: Modo de captura de quadros (ex.: CAMERA_GRAB_WHEN_EMPTY)
 * - fbLocation: Local do buffer de quadros (ex.: CAMERA_FB_IN_DRAM ou CAMERA_FB_IN_PSRAM)
 * - fbCount: Número de buffers de quadros (1 para imagens estáticas, 2+ para streaming)
 * - xclkFreqHz: Frequência do XCLK em Hz (ex.: 20000000)
 *
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
 *
 * @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Camera#readme
 * | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Camera#readme
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>    
#include <ES32Lab.h> // Library ES32Lab | Biblioteca ES32Lab

ES_Camera camera;   // Camera object | Objeto da câmera
ES_TFT display;     // TFT object | Objeto TFT

void setup() {
    // --- Display Initialization | Inicialização do display ---
    display.begin();               // Initialize the TFT display | Inicializa o display TFT
    display.setRotation(3);        // Set the display rotation | Define a rotação do display
    display.fillScreen(TFT_BLACK); // Fill the screen with black color | Preenche a tela com a cor preta
    display.setCursor(0, 0);       // Set cursor position | Define a posição do cursor

    //--- Camera Initialization | Inicialização da câmera ---
    if (!camera.begin()){
        display.fillScreen(TFT_RED);       // Fill the screen with red color | Preenche a tela com a cor vermelha
        display.println("Camera failed!"); // Print error message on display | Imprime mensagem de erro no display
        while (true);
    }
}

void loop() {
    display.renderCameraFrame(camera);  // Render the camera frame on the display | Renderiza o quadro da câmera no display
}