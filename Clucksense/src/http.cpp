#include <HTTPClient.h>

const char* url = "http://example.com/";

void getHelloWorld() {

  HTTPClient http;
  http.begin(url);  // Adjust your hostname here

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    // Get the response body as a raw string
    String payload = http.getString();

    Serial.println("Raw response:");
    Serial.println(payload);  // This is the raw string response
  } else {
    Serial.printf("HTTP GET failed, code: %d\n", httpCode);
  }

  http.end();
}
