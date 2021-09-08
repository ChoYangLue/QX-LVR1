int rpcPostJson(char *buffer, DynamicJsonDocument *result) {
  if (buffer == NULL || result == NULL) return -1;
  HTTPClient http;
  http.begin("http://10.0.0.1:10000/sony/camera");
  http.addHeader("Content-Type", "application/json");
  int status_code = http.POST((uint8_t*)buffer, strlen(buffer));

  if (status_code != HTTP_CODE_OK) {  
    Serial.printf("status_code=%d\r\n", status_code);
    return status_code;
  }
  Stream* resp = http.getStreamPtr();
  deserializeJson(*result, *resp);
  http.end();
  return status_code;
}

int rpcGetLiveviewData(String host) {
  if (host == NULL) return -1;
  HTTPClient http;
  http.begin(host.c_str());
  int status_code = http.GET();

  if (status_code != HTTP_CODE_OK) {  
    Serial.printf("status_code=%d\r\n", status_code);
    return status_code;
  }
  String body = http.getString();
  readHeader(&body);
  http.end();
  return status_code;
}

int rpcStartRecModeSync(DynamicJsonDocument *json_response) {
  StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_request;
  StaticJsonDocument<JSON_ARRAY_SIZE(1)> json_array;
  json_request["method"] = "startRecMode";
  json_request["params"] = json_array.to<JsonArray>();
  json_request["id"] = 1;
  json_request["version"] = "1.0";

  serializeJson(json_request, Serial);
  Serial.println("");
  char buffer[127];
  serializeJson(json_request, buffer, sizeof(buffer));
  
  return rpcPostJson(buffer, json_response);
}

int rpcStartLiveviewSync(DynamicJsonDocument *json_response) {
  StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_request;
  StaticJsonDocument<JSON_ARRAY_SIZE(1)> json_array;
  json_request["method"] = "startLiveview";
  json_request["params"] = json_array.to<JsonArray>();
  json_request["id"] = 1;
  json_request["version"] = "1.0";

  serializeJson(json_request, Serial);
  Serial.println("");
  char buffer[127];
  serializeJson(json_request, buffer, sizeof(buffer));

  return rpcPostJson(buffer, json_response);
}

int rpcGetApplicationInfoSync(DynamicJsonDocument *json_response) {
  StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_request;
  StaticJsonDocument<JSON_ARRAY_SIZE(1)> json_array;
  json_request["method"] = "getApplicationInfo";
  json_request["params"] = json_array.to<JsonArray>();
  //json_request["params"].add("");
  json_request["id"] = 1;
  json_request["version"] = "1.0";

  serializeJson(json_request, Serial);
  Serial.println("");
  char buffer[127];
  serializeJson(json_request, buffer, sizeof(buffer));

  return rpcPostJson(buffer, json_response);
}

int rpcGetAvailableApiListSync(DynamicJsonDocument *json_response) {
  StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_request;
  StaticJsonDocument<JSON_ARRAY_SIZE(1)> json_array;
  json_request["method"] = "getAvailableApiList";
  json_request["params"] = json_array.to<JsonArray>();
  //json_request["params"].add("");
  json_request["id"] = 1;
  json_request["version"] = "1.0";

  serializeJson(json_request, Serial);
  Serial.println("");
  char buffer[127];
  serializeJson(json_request, buffer, sizeof(buffer));

  return rpcPostJson(buffer, json_response);
}

int rpcGetMethodTypesSync(DynamicJsonDocument *json_response) {
  StaticJsonDocument<JSON_OBJECT_SIZE(4)> json_request;
  StaticJsonDocument<JSON_ARRAY_SIZE(1)> json_array;
  json_request["method"] = "getMethodTypes";
  json_request["params"] = json_array.to<JsonArray>();
  json_request["params"].add("1.0");
  json_request["id"] = 1;
  json_request["version"] = "1.0";

  serializeJson(json_request, Serial);
  Serial.println("");
  char buffer[127];
  serializeJson(json_request, buffer, sizeof(buffer));

  return rpcPostJson(buffer, json_response);
}
