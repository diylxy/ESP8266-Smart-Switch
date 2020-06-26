#ifndef __A_CONFIG_H__
#define __A_CONFIG_H__

#define RELAY 14
#define RELAY_OPEN HIGH
#define RELAY_CLOSE LOW

#define KEY 0

#define WIFI_SSID "WIFI-SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"
#define OTA_NAME "LED"
#define U8G2_DISPLAY U8G2_ST7565_JLX12864_1_4W_SW_SPI u8g2(U8G2_MIRROR, /* clock=*/4, /* data=*/ 2, /* cs=*/ 13, /* dc=*/ 5, /* reset=*/ 12);
#define REFRESH_DELAY 5000

#define USE_HTTP_SERVER
#define HTTP_SERVER_PORT 80
#define SERVER_PASSWORD_ON "on"
#define SERVER_PASSWORD_OFF "off"

#define UID "213123506"

#define NTP_SERVER "ntp.ntsc.ac.cn"

#endif
