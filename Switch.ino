
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include "A_Config.h"

U8G2_DISPLAY;
bool relayStatus = true;
unsigned long fans;
String confirmed;
String strTime;
void setup(void) {
  pinMode(0, INPUT_PULLUP);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  u8g2.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname(OTA_NAME);

  ArduinoOTA.begin();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_mf);
    u8g2.setCursor(0,34);
    u8g2.println("Press to continue");
  } while ( u8g2.nextPage() );
  
  while (digitalRead(0) == 1)
  {
    ArduinoOTA.handle();
    delay(1);
  }
  #ifdef USE_HTTP_SERVER
  startServer();
  #endif
  u8g2.clear();
}

void Display()
{
  uint8_t w;
  char fansArr[10];
  ltoa(fans, fansArr, 10);
  getFans();
  getConfirmed();
  getTime();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_mf);
    w = u8g2.getStrWidth(strTime.c_str());
    u8g2.drawStr((127-w)/2,11,strTime.c_str());
    u8g2.drawLine(0, 12, 128, 12);
    
    u8g2.setFont(u8g2_font_inr19_mr);
    w = u8g2.getStrWidth(confirmed.c_str());

    u8g2.setCursor((127-w)/2, 36);
    u8g2.print(confirmed);
    
    u8g2.setFont(u8g2_font_inr16_mn);
    w = u8g2.getStrWidth(fansArr);
    u8g2.setCursor((63-w)/2, 62);
    u8g2.print(fansArr);
    
    u8g2.drawLine(63, 38, 63, 64);
    u8g2.drawLine(0, 38, 128, 38);
  } while ( u8g2.nextPage() );
  return;
}

unsigned long millisOld = 0;
void loop(void) {
  ArduinoOTA.handle();
  if (digitalRead(0) == 0)
  {
    delay(10);
    digitalWrite(RELAY, relayStatus);
    relayStatus = !relayStatus;
    while (digitalRead(KEY) == 0);
  }
  #ifdef USE_HTTP_SERVER
  serverLoop();
  #endif
  if (millis() - millisOld >= REFRESH_DELAY)
  {
    millisOld = millis();
    Display();
  }
}
