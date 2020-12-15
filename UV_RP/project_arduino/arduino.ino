#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

/* Definições pinos do ML8511 */
#define PIN_GPIO34 34
#define PIN_GPIO35 35

/* Definições das mensagens possíveis de serem recebidas */
#define CMD_UV "UV"

/* Credenciais do Wi-Fi */
#define WIFI_SSID " "
#define WIFI_PASSWORD " "

/* Variáveis globais de saída para os pinos do ML8511 */
int UVOUT = analogRead(PIN_GPIO34); //Output from the sensor (GPIO34)
int REF_3V3 = analogRead(PIN_GPIO35); //3.3V power on the Arduino board (GPIO35)

/* Variáveis e objetos globais para o Wi-Fi */
WiFiClientSecure client;

/* Prototypes para Wi-Fi*/
void wifi_init(void);
void wifi_conecta(void);
void wifi_verifica_conexao(void);
/* 
 *  Implementações
 */
  
/* Função: Inicializa Wi-Fi
 * Parâmetros: Nenhum
 * Retorno: Nenhum 
 */
void wifi_init(void) {
    Serial.println("----- Wi-Fi -----");
    Serial.print("Conectando-se à rede: ");
    Serial.println(WIFI_SSID);
    Serial.println("Aguarde...");    
    wifi_conecta();
}

/* Função: Conecta-se a rede Wi-Fi
 * Parâmetros: Nenhum
 * Retorno: Nenhum 
 */
void wifi_conecta(void) {
    /* Se ja estiver conectado, nada é feito. */
    if (WiFi.status() == WL_CONNECTED)
        return;
 
    /* Refaz a conexão */
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
     
    while (WiFi.status() != WL_CONNECTED) 
    {        
        vTaskDelay(100 / portTICK_PERIOD_MS);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso a rede Wi-Fi ");
    Serial.println(WIFI_SSID);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

/* Função: Verifica se a conexao Wi-Fi está ativa 
 *         (e, em caso negativo, refaz a conexão)
 * Parâmetros: Nenhum
 * Retorno: Nenhum 
 */
void wifi_verifica_conexao(void) {
    wifi_conecta(); 
}

float read_uv_value() {
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
 
  Serial.print("Referencia: ");
  Serial.print(refLevel);
 
  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);
 
  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);
 
  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);
  
	   // Check if we are Connected.
	 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
		HTTPClient http;    //Declare object of class HTTPClient

		http.begin("http://uv.lookdb.ml/index.php");      //Specify request destination
		http.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
		int httpCode = http.POST("iuv=" + uvIntensity); //Send the request

		Serial.println(httpCode);   //Print HTTP return code
		http.writeToStream(&Serial);  // Print the response body

	}
  
  Serial.println();
  return uvIntensity;
}

void setup() {
  Serial.begin(9600);
  
  /* Inicializa a conexão Wi-Fi */
  wifi_init();
  read_uv_value();
}
 
void loop() {
    int i;
     
    /* Garante que o Wi-Fi está conectado */
    wifi_verifica_conexao();
}
 
//Recebe os valores de leitura de um determinado pin
//Retorna o valor medio
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
