#include "A_Config.h"
#include <NTPtimeESP.h>
NTPtime NTPch(NTP_SERVER);   // Choose server pool as required

strDateTime dateTime;

extern String strTime;
void getTime () {
  byte times = 0;
  retry:
  dateTime = NTPch.getNTPtime(8.0, 0);
  if(dateTime.valid){
    char tmp[40];
    NTPch.printDateTime(dateTime);
    sprintf(tmp, "%d-%02d-%02d %02d:%02d", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second);
    strTime = String(tmp);
    return;
  }
  else
  {
    delay(10);
    if(times>= 20)
      strTime = "????-??-?? ??:??";
      return;
    goto retry;
  }
}
