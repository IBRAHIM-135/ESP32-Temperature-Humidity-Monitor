#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "xxx" 
#define BLYNK_TEMPLATE_NAME "ESP32 Weather Station"
#define BLYNK_AUTH_TOKEN "xxx"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "xxx";     
char pass[] = "xxx"; 

#define DHTPIN 4 
#define DHTTYPE DHT22

DHT e(DHTPIN, DHTTYPE); 
BlynkTimer timer;

void sendSensorData() {
  float T = e.readTemperature(); 
  float H = e.readHumidity();

  if (isnan(T) || isnan(H)) { 
    Serial.println("ERROR: Failed to read from DHT sensor!"); 
    return;
  }

 
  Serial.print(T);
  Serial.print(",");
  Serial.println(H);


  Blynk.virtualWrite(V1, T);
  Blynk.virtualWrite(V2, H);
}

void setup() {
  Serial.begin(115200);
  

  while (!Serial) {
    ; 
  }
  
  e.begin();


  Blynk.begin(auth, ssid, pass);


  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}