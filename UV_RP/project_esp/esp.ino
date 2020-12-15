#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

/* Definições pinos do ML8511 */
#define PIN_GPIO34 34
#define PIN_GPIO35 35

/* Definições do Telegram */
#define TELEGRAM_TIME_CHECK_MESSAGE 250 //Em ms
#define TELEGRAM_TOKEN "1474488007:AAFMnESRAA0qbyfSKGNxJRsvpK4EqxLazkw"

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

/* Variáveis e objetos globais para o Telegram */
UniversalTelegramBot bot(TELEGRAM_TOKEN, client);
unsigned long timestamp_checagem_msg_telegram = 0;
int num_mensagens_recebidas_telegram = 0;
String resposta_msg_recebida;

/* Prototypes para Wi-Fi*/
void wifi_init(void);
void wifi_conecta(void);
void wifi_verifica_conexao(void);

/* Prototypes para o Telegram */
unsigned long diferenca_tempo(unsigned long timestamp_referencia);
String trata_mensagem_recebida(String msg_recebida);

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

/* Função: Calcula a diferença de tempo entre o timestamp
 *         de referência e o timestamp atual
 * Parâmetros: Timestamp de referência
 * Retorno: Diferença de tempo 
 */
unsigned long diferenca_tempo(unsigned long timestamp_referencia) {
    return (millis() - timestamp_referencia);
}

/* Função: trata mensagens recebidas via Telegram
 * Parametros: mensagem recebida
 * Retorno: resposta da mensagem recebida 
 */
String trata_mensagem_recebida(String msg_recebida) {
    String resposta = "";
    bool comando_valido = false;
    float uv_lido = 0.0;
 
    /* Faz tratamento da mensagem recebida */
    if (msg_recebida.equals(CMD_UV)) {
        uv_lido = read_uv_value();
        resposta = "Intensidade UV: " + String(uv_lido);
        comando_valido = true;   
    }
    if (comando_valido == false)
        resposta = "Comando invalido: "+msg_recebida;      
  
    return resposta;
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
  
  Serial.println();
  return uvIntensity;
}

void setup() {
  Serial.begin(9600);
  
  /* Inicializa a conexão Wi-Fi */
  wifi_init();
  /* Inicializa timestamp de checagem de mensagens recebidas via Telegram */
  timestamp_checagem_msg_telegram = millis();
}
 
void loop() {
    int i;
     
    /* Garante que o Wi-Fi está conectado */
    wifi_verifica_conexao();
 
    /* Verifica se é hora de checar por mensagens enviadas ao bot Telegram */
    if (diferenca_tempo(timestamp_checagem_msg_telegram) >= TELEGRAM_TIME_CHECK_MESSAGE) {
        /* Verifica se há mensagens a serem recebidas */
        num_mensagens_recebidas_telegram = bot.getUpdates(bot.last_message_received + 1);
 
        if (num_mensagens_recebidas_telegram > 0) {
            Serial.print("[BOT] Mensagens recebidas: ");
            Serial.println(num_mensagens_recebidas_telegram);
        }
         
        /* Recebe mensagem a mensagem, faz tratamento e envia resposta */
        while(num_mensagens_recebidas_telegram) {
            for (i=0; i<num_mensagens_recebidas_telegram; i++) {             
                resposta_msg_recebida = "";
                resposta_msg_recebida = trata_mensagem_recebida(bot.messages[i].text);
                bot.sendMessage(bot.messages[i].chat_id, resposta_msg_recebida, "");
            }
            num_mensagens_recebidas_telegram = bot.getUpdates(bot.last_message_received + 1);
        }
        /* Reinicializa timestamp de checagem de mensagens recebidas via Telegram */
        timestamp_checagem_msg_telegram = millis();
    }
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
