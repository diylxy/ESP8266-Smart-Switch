#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "A_Config.h"

DynamicJsonDocument doc(4096);

extern String confirmed;
extern unsigned long fans;
String HTTPGET(char *url)
{
  WiFiClient client;
  HTTPClient http;

  String payload = "{\"data\":[]}";

  if (http.begin(client, url)) {
    if (http.GET() == HTTP_CODE_OK) {
      payload = http.getString();
    }
    http.end();
  }
  return payload;
}

void getConfirmed()
{
  WiFiClient client;
  HTTPClient http;
  uint8_t buff[1280] = { 0 };
  http.begin(client, "http://cdn.mdeer.com/data/yqstaticdata.js");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    int len = http.getSize();
    WiFiClient * stream = &client;
    stream->readBytes(buff, std::min((size_t)len, (size_t)1280));
  }
  buff[1023] = 0;
  String body = String(((const char *)buff));
  if (body == "" || http.getSize() < 1280)
  {
    confirmed="N/A";
    http.end();
    return;
  }
  unsigned long confirmPos = body.indexOf("\"totalConfirmed\"");
  confirmPos += 17;
  unsigned long lastMark = body.indexOf(",", confirmPos + 1);
  confirmed = body.substring(confirmPos, lastMark);
  http.end();
}

char * PROGMEM FansURL = "http://api.bilibili.com/x/relation/stat?vmid=" UID;
void getFans()
{
  String input = HTTPGET(FansURL);
  if (input == "{\"data\":[]}")
  {
    fans=0;
    return;
  }
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  fans = obj["data"]["follower"];
}
