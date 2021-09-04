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
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

DynamicJsonDocument json_response(511);

void connectCamera(const char *ssid, const char *password) {
  WiFi.begin(ssid, password);
  uiPrint("Connecting to ", ST77XX_WHITE);
  uiPrintln(getSsid(), ST77XX_WHITE);
  uiPrint("WiFi connecting", ST77XX_WHITE);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    uiPrint(".", ST77XX_WHITE);
    delay(1000);
  }
  
  uiPrintln("", ST77XX_WHITE);
  uiPrintln("connected", ST77XX_WHITE);
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  initTFT();
  connectCamera(getSsid(), getPassword());
  
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
  delay(2000);
  JsonVariant variant = json_response.as<JsonVariant>();
  JsonArray val_data = variant.getMember("result");
  String url = val_data[0];
  rpcGetLiveviewData(url);
  uiPrintln(url.c_str(), ST77XX_WHITE);
}
