/**
 * @brief Example: Displaying JPEG images from SD card using ES32Lab and ES_TFT
 * | Exemplo: Exibição de imagens JPEG do cartão SD utilizando ES32Lab e ES_TFT
 *
 * This example demonstrates how to use the ES32Lab library to display JPEG images stored on an SD card,
 * SPIFFS, or LittleFS directly on the TFT display of the ES32Lab board. The ES_TFT class is used for display
 * control, while the ES_AnalogKeyboard class allows navigation between images using the onboard keyboard.
 *
 * On startup, the display is initialized and set to the desired rotation. The first JPEG image found in
 * the root directory of the selected file system (SD, SPIFFS, or LittleFS) is rendered automatically.
 * In the main loop, the user can navigate through the images using the left and right keys on the analog
 * keyboard: pressing the left key displays the previous image, and pressing the right key displays the next image.
 *
 * The renderFirstFileJPEG(), renderPreviousFileJPEG(), and renderNextFileJPEG() methods accept an optional
 * parameter to specify the file system (FS) to be used. By default, SD is used, but you can pass SPIFFS or
 * LittleFS as needed, allowing flexibility in where your images are stored.
 *
 * @warning The images to be displayed must be in the correct resolution for the display in use.
 * This example does not automatically resize images to fit the display; ensure your JPEG files match the
 * display's native resolution for best results.
 *
 * The ES32Lab board makes this process simple by integrating the SD card slot, TFT display, and keyboard,
 * providing a complete platform for image viewing, educational demonstrations, and multimedia projects.
 *
 * | Este exemplo demonstra como utilizar a biblioteca ES32Lab para exibir imagens JPEG armazenadas no cartão SD,
 * SPIFFS ou LittleFS diretamente no display TFT da placa ES32Lab. A classe ES_TFT é utilizada para o controle
 * do display, enquanto a classe ES_AnalogKeyboard permite a navegação entre as imagens usando o teclado analógico onboard.
 *
 * Ao iniciar, o display é inicializado e a rotação é definida. A primeira imagem JPEG encontrada no diretório
 * raiz do sistema de arquivos selecionado (SD, SPIFFS ou LittleFS) é exibida automaticamente. No loop principal,
 * o usuário pode navegar pelas imagens usando as teclas esquerda e direita do teclado analógico: pressionando
 * a tecla esquerda exibe a imagem anterior e pressionando a tecla direita exibe a próxima imagem.
 *
 * Os métodos renderFirstFileJPEG(), renderPreviousFileJPEG() e renderNextFileJPEG() aceitam um parâmetro opcional
 * para especificar o sistema de arquivos (FS) a ser utilizado. Por padrão, é usado o SD, mas você pode passar
 * SPIFFS ou LittleFS se necessário, permitindo flexibilidade no armazenamento das imagens.
 *
 * @warning As imagens a serem exibidas devem estar na resolução adequada para o display utilizado.
 * Este exemplo não redimensiona automaticamente as imagens para a resolução do display; certifique-se de que
 * seus arquivos JPEG estejam na resolução nativa do display para melhores resultados.
 *
 * A placa ES32Lab facilita esse processo ao integrar slot para cartão SD, display TFT e teclado, proporcionando
 * uma plataforma completa para visualização de imagens, demonstrações educacionais e projetos multimídia.
 *
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
 *
 * @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TFT#readme
 * | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TFT#readme
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>    
#include <ES32Lab.h>    // Library ES32Lab | Biblioteca ES32Lab

ES_TFT display; // TFT display object | Objeto do display TFT
ES_AnalogKeyboard keyboard(P_KEYBOARD); // Keyboard object | Objeto do teclado

void setup() {
    display.begin(); // Initialize the TFT display | Inicializa o display TFT
    display.setRotation(3); // Set the display rotation | Define a rotação do display
    display.renderFirstFileJPEG(SD, "/"); // Render the first JPEG file from the SD card | Renderiza o primeiro arquivo JPEG do cartão SD
}

void loop() {
    if(keyboard.press(KEY_LEFT)) {
        display.renderPreviousFileJPEG(SD); // Render the previous JPEG file from the SD card | Renderiza o arquivo JPEG anterior do cartão SD
    }
    if(keyboard.press(KEY_RIGHT)) {
        display.renderNextFileJPEG(SD); // Render the next JPEG file from the SD card | Renderiza o próximo arquivo JPEG do cartão SD
    }
}