/*
const char *SSID = "DIRECT-hogehoge";
const char *PASSWORD = "fugafuga";

char *getSsid(){
  return SSID;
}

char *getPassword(){
  return PASSWORD;
}
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

DynamicJsonDocument json_response(511);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  WiFi.begin(getSsid(), getPassword());
  Serial.print("Connecting to ");
  Serial.println(getSsid());
  Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  
  rpcGetAvailableApiListSync(&json_response);
  serializeJson(json_response, Serial);
  Serial.println("");

  rpcStartRecModeSync(&json_response);
  serializeJson(json_response, Serial);
  Serial.println("");
  
  rpcStartLiveviewSync(&json_response);
  serializeJson(json_response, Serial);
  Serial.println("");
  
}

void loop() {
  delay(1000);
  JsonVariant variant = json_response.as<JsonVariant>();
  JsonArray val_data = variant.getMember("result");
  String url = val_data[0];
  rpcGetLiveviewData(url);
}
