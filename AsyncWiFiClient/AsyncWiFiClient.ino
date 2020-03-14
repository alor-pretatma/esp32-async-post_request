
#include <WiFi.h>

const char* ssid = "Wifi SSID";
const char* pass = "wifipassword";
const char* host = "192.168.0.1";//Your server ip

void sendData(void* params){
  WiFiClient client;
  if(!client.connect(host, 80/*port*/)){
    Serial.println("Not connected!");
    return;
  }
  
  client.print("GET /api/get.php?key1=value1 HTTP/1.1\r\nHost: "+String(host)+"\r\nConnection: close\r\n\r\n");
  int i=0;
  while((!client.available()) && (i<1000)){//waiting for server response
      delay(10);
      i++;
  }
  /*while(client.available()){
    String line=client.readStringUntil('\r');
    Serial.println(line);
  }*/
  client.stop();
  Serial.println("A task ended!");
  vTaskDelete(NULL);
}


void setup(){
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Wifi ok!");
}
void loop(){
  xTaskCreate(sendData, "sendData", (1024 * 32), NULL, 5, NULL);
  delay(1000);
}
