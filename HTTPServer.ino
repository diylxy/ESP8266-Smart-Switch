#ifdef USE_HTTP_SERVER
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <uri/UriBraces.h>
#include "A_Config.h"

ESP8266WebServer server(HTTP_SERVER_PORT);

void startServer()
{
  server.on(F("/"), []() {
    server.sendHeader("Location", "http://www.baidu.com",true);
    server.send(302, "", "");
  });

  server.on(UriBraces("/op/{}"), []() {
    String op = server.pathArg(0);
    server.send(200, "text/plain", "Arg: '" + op + "' Processed!");
    if (op == SERVER_PASSWORD_ON)
    {
      digitalWrite(RELAY, RELAY_OPEN);
    }
    else if (op == SERVER_PASSWORD_OFF)
    {
      digitalWrite(RELAY, RELAY_CLOSE);
    }
    delay(500);
  });
  server.begin();
}

void serverLoop(void) {
  server.handleClient();
}
#endif
