#ifndef __TIMERFUN_H__ 
#define __TIMERFUN_H__ 
#include <Arduino.h>

#ifdef ESP32
#include <ESP32Time.h>
#else
#endif
#include "ESPreset.h"
void timerSetTest();
String timerCurrent();
String timerGetEpoch();
void timerSetEpoch(unsigned long epoch);

#endif // __TIMERFUN_H__ 