/**
 * @brief Example: Real-time camera streaming via HTTP using ES_Camera and ES32Lab
 * | Exemplo: Transmissão de vídeo em tempo real via HTTP utilizando ES_Camera e ES32Lab
 *
 * This example demonstrates how to stream real-time video from an ESP32-based camera module
 * over a local Wi-Fi network using the ES_Camera class from the ES32Lab library, taking full
 * advantage of the ES32Lab board's integrated camera connector and robust hardware resources.
 *
 * The ESP32 connects to your Wi-Fi network, initializes the camera with QQVGA resolution and
 * JPEG quality 12, and sets up an HTTP server on port 80. The video stream is made available
 * at the "/stream" endpoint, accessible from any device on the same network using a web browser
 * or compatible video viewer. The stream URL is printed to the serial monitor for quick access.
 *
 * The ES_Camera class provides a high-level interface for camera configuration and control.
 * In this example, the camera is initialized with the default pins for the ES32Lab board,
 * ensuring seamless integration and reliable operation. The HTTP server is configured using
 * the ESP-IDF httpd component, and the stream endpoint is created with createStreamEndpoint().
 * The ES_Camera class automatically manages streaming requests, enabling efficient and robust
 * video transmission.
 *
 * The ES32Lab board simplifies the connection and use of the OV2640 camera, eliminating the
 * need for complex wiring or protoboard setups. This makes it ideal for rapid prototyping,
 * educational projects, and IoT applications where real-time video is required.
 *
 * You can further customize the camera behavior using the various methods provided by the
 * ES_Camera class, such as changing resolution, adjusting JPEG quality, or enabling/disabling
 * features like brightness, contrast, saturation, white balance, exposure, sharpness, mirroring,
 * special effects, color correction, noise reduction, and lens correction. The class also
 * supports capturing frames in JPEG format, saving images to SPIFFS or SD, and advanced HTTP
 * streaming management.
 *
 * For more information about the methods used in this example and all other features of the
 * ES_Camera class, refer to the official documentation:
 * https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Camera#readme
 *
 * | Este exemplo demonstra como transmitir vídeo em tempo real de um módulo de câmera baseado
 * em ESP32 pela rede Wi-Fi local utilizando a classe ES_Camera da biblioteca ES32Lab, aproveitando
 * o conector integrado para câmera e os recursos robustos da placa ES32Lab.
 *
 * O ESP32 conecta-se à sua rede Wi-Fi, inicializa a câmera com resolução QQVGA e qualidade JPEG 12,
 * e configura um servidor HTTP na porta 80. O stream de vídeo fica disponível no endpoint "/stream",
 * podendo ser acessado de qualquer dispositivo na mesma rede usando um navegador ou visualizador
 * de vídeo compatível. A URL do stream é impressa no monitor serial para acesso rápido.
 *
 * A classe ES_Camera oferece uma interface de alto nível para configuração e controle da câmera.
 * Neste exemplo, a câmera é inicializada com os pinos padrão da placa ES32Lab, garantindo integração
 * perfeita e operação confiável. O servidor HTTP é configurado usando o componente httpd do ESP-IDF,
 * e o endpoint de stream é criado com o método createStreamEndpoint(). O gerenciamento das requisições
 * de streaming é feito automaticamente pela classe ES_Camera, permitindo transmissão de vídeo eficiente
 * e robusta.
 *
 * A placa ES32Lab simplifica a conexão e o uso da câmera OV2640, eliminando a necessidade de fiação
 * complexa ou uso de protoboard. Isso a torna ideal para prototipagem rápida, projetos educacionais e
 * aplicações IoT que exigem vídeo em tempo real.
 *
 * Você pode personalizar ainda mais o comportamento da câmera utilizando os diversos métodos da classe
 * ES_Camera, como alteração de resolução, ajuste de qualidade JPEG, brilho, contraste, saturação, balanço
 * de branco, exposição, nitidez, espelhamento, efeitos especiais, correção de cor, redução de ruído e
 * correção de lente. A classe também permite capturar frames em JPEG, salvar imagens no SPIFFS ou SD e
 * gerenciar streaming HTTP avançado.
 *
 * Para mais informações sobre os métodos utilizados neste exemplo e todos os recursos da classe ES_Camera,
 * consulte a documentação oficial:
 * https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Camera#readme
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
#include <WiFi.h>       // Wi-Fi library | Biblioteca Wi-Fi
#include <ES32Lab.h>    // Library ES32Lab | Biblioteca ES32Lab

//--- Wi-Fi Configuration | Configuração do Wi-Fi ---//
const char* ssid = "YOUR_SSID";         // Replace with your Wi-Fi network name. | Substitua pelo nome da sua rede Wi-Fi.
const char* password = "YOUR_PASSWORD"; // Replace with your Wi-Fi password. | Substitua pela senha da sua rede Wi-Fi.

ES_Camera camera;   // Camera object | Objeto da câmera

httpd_handle_t stream_httpd = NULL; // HTTP server handle for streaming | Manipulador do servidor HTTP para streaming

void setup() {
    Serial.begin(115200);   // Initialize serial communication at 115200 baud rate | Inicializa a comunicação serial a 115200 bps
    Serial.println();
    Serial.println("Initializing...");

    //--- Wi-Fi Connection | Conexão Wi-Fi ---//
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.print("Connected to WiFi: ");
    Serial.println(ssid);

    //--- Camera Initialization | Inicialização da câmera ---
    if (!camera.begin(FRAMESIZE_QQVGA, 12)) {   // Initialize the camera with QQVGA resolution and JPEG quality of 12 | Inicializa a câmera com resolução QQVGA e qualidade JPEG de 12
        Serial.println("Camera initialization failed!");
        while (true);
    }
    Serial.println("Camera initialized successfully!");

    // --- Set web server for streaming | Configura o servidor web para streaming ---
    httpd_config_t config = HTTPD_DEFAULT_CONFIG(); // Default HTTP server configuration | Configuração padrão do servidor HTTP
    config.server_port = 80;    // Set the server port to 80 | Define a porta do servidor como 80

    //--- Start the HTTP server | Inicia o servidor HTTP ---
    if (httpd_start(&stream_httpd, &config) == ESP_OK) {
        httpd_uri_t stream_uri = camera.createStreamEndpoint("/stream");    // Create the stream endpoint | Cria o endpoint de stream
        httpd_register_uri_handler(stream_httpd, &stream_uri);  // Register the stream URI handler | Registra o manipulador do URI de stream
    }

    //--- Print the stream URL | Imprime a URL do stream ---
    Serial.print("Camera Stream URL: http://");
    Serial.print(WiFi.localIP());
    Serial.println(camera.getStreamUri());
}

void loop() {

}