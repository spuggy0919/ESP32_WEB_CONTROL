#ifndef __ESPRESET__H__
#define __ESPRESET__H__
#include <Arduino.h>
#include <esp_task_wdt.h> 

void ESPHW_config_wdt();
void ESP_force_wdt(int minisec);
bool ESPHW_powerloss();

#endif  //__ESPRESET__H__