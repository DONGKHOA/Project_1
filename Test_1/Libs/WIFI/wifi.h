#ifndef WIFI_H_
#define WIFI_H_

#include <stdint.h>

typedef enum
{
    CONNECT_OK = 1,
    CONNECT_FAIL,
    UNEXPECTED_EVENT,
}WIFI_Status_t;

uint8_t WIFI_Station_Init(uint8_t *ssid, uint8_t *password);

#endif