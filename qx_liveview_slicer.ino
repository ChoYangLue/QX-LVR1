const int COMMON_HEADER_SIZE = 8;
const int PAYLOAD_HEADER_SIZE = 128;

int readHeader(String *inputStream) {
  byte CommonHeaderBuf[COMMON_HEADER_SIZE];
  inputStream->getBytes(CommonHeaderBuf, COMMON_HEADER_SIZE);
  if (CommonHeaderBuf[0] != (byte)0xFF) return 0;
  //Serial.print(inputStream[0], HEX);

  //*inputStream = inputStream->substring(COMMON_HEADER_SIZE+PAYLOAD_HEADER_SIZE);
  
  for(int i=0;i<inputStream->length();i++) {
    //inputStream.charAt(i);
    Serial.print(" 0x");
    Serial.print(inputStream->charAt(i), HEX);
    if (i%100 == 0) Serial.println("");
  }
  Serial.println("");

  //byte bytebuf[1024];
  //inputStream.getBytes(bytebuf, 1024);
  //String body = http.getString();
  //Serial.println(body);
  
  return 0;
}
