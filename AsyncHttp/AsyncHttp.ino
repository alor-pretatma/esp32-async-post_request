#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "yourSSID";
const char* pass = "YourPassword";
const char* url = "http://192.168.0.120/";

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
void sendData(void* params){
  HTTPClient http;
  Serial.println("Sending data..");
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 

  int httpCode=http.POST("id="+String(id)+"&key="+String(key)+"&temp=100&heart=3.1416&spo2=122&ecg=66");
  if (httpCode > 0) { //Check for the returning code
    Serial.println(http.getString());
  }else {
    Serial.printf("\nError: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  Serial.println("A task ended!");
  vTaskDelete(NULL);
}
void loop(){
  xTaskCreate(sendData, "sendData", 3000, NULL, 1, NULL);
  delay(2000);
}
