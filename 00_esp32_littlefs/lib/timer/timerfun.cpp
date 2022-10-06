#include "timerfun.h"


ESP32Time rtc(3600*8); // UTC+8
void timerSetTest(){
    rtc.setTime(16, 13, 15, 4, 10, 2022);  // 4th Oct 2022 13:13:30
}
String timerCurrent(){
    return rtc.getTime();          //  (String) 15:24:38
}
String timerGetEpoch(){
    return String(rtc.getEpoch());          //  (String) 15:24:38
}
void timerSetEpoch(unsigned long epoch){
    if (ESPHW_powerloss()){
        rtc.setTime(epoch);
        Serial.println("ESP timer Set");
    }
}
