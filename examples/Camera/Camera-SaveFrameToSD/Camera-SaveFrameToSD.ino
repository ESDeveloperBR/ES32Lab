/**
 * @brief Example: Save camera frame as JPEG file on SD using ES_Camera and ES32Lab
 * | Exemplo: Salve um frame da câmera como arquivo JPEG no SD usando ES_Camera e ES32Lab
 *
 * This example demonstrates how to capture a frame from the camera and save it as a JPEG file on the SD card
 * using the ES_Camera class from the ES32Lab library. The main command is:
 *     boolean saveSuccess = camera.saveFrameToJpegFile(SD, fileName);
 * This line captures the current frame and saves it as a JPEG image in the SD card using the specified file name.
 * To use another file system, simply replace SD with SPIFFS or LittleFS.
 *
 * | Este exemplo demonstra como capturar um frame da câmera e salvar como arquivo JPEG no cartão SD
 * usando a classe ES_Camera da biblioteca ES32Lab. O comando principal é:
 *     boolean saveSuccess = camera.saveFrameToJpegFile(SD, fileName);
 * Esta linha captura o quadro atual e salva a imagem JPEG no cartão SD com o nome de arquivo especificado.
 * Para usar outro sistema de arquivos, basta trocar SD por SPIFFS ou LittleFS.
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
ES_AnalogKeyboard keyboard(P_KEYBOARD); // Keyboard object | Objeto do teclado
int cont = 0;       // Counter for image files | Contador para os arquivos de imagem

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
    display.println("Initialized successfully!"); // Print success message on display | Imprime mensagem de sucesso no display
    display.println("  Press the CENTER key!  "); // Print instruction message on display | Imprime mensagem de instrução no display
    delay(8000); // Delay for 8 seconds | Atraso de 8 segundos
}

void loop() {
    if (keyboard.press(KEY_CENTER)) {                   // Key Center Pressed | Tecla central pressionada
        String fileName = "/img/image" + String(cont) + ".jpg"; // Create file name | Cria o nome do arquivo
        boolean saveSuccess = camera.saveFrameToJpegFile(SD, fileName); // Save the image to SD card | Salva a imagem no cartão SD

        display.renderJPEG(SD, fileName);               // Render the saved image on the display | Renderiza a imagem salva no display
        display.setCursor(0, 0);                        // Set cursor position | Define a posição do cursor
        if(saveSuccess){
            display.println("Image saved in SD card!"); // Print message on display | Imprime mensagem no display
            display.println(fileName);                  // Print file name on display | Imprime o nome do arquivo no display
            cont++;                                     // Increment the image counter | Incrementa o contador de imagens
        }else{
            display.fillScreen(TFT_RED);                // Fill the screen with red color | Preenche a tela com a cor vermelha
            display.println("Failed to save image!");   // Print error message on display | Imprime mensagem de erro no display
            display.println("Check SD card!");          // Print instruction message on display | Imprime mensagem de instrução no display
        }
        delay(5000);                                    // Delay for 5 seconds | Atraso de 5 segundos
    }

    display.renderCameraFrame(camera);                  // Render the camera frame on the display | Renderiza o quadro da câmera no display
}