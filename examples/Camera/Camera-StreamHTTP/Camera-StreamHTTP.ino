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