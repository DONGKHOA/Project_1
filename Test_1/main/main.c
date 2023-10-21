#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "dht.h"
#include "wifi.h"
#include "mqtt_client_tcp.h"

#define DHT11_PIN   GPIO_NUM_5

static uint8_t 			ssid[32] = "Khoa";
static uint8_t 			pass[32] = "17042021";
static char			url_mqtt[30] = "mqtt://172.20.10.5:1883";

// static uint8_t 			ssid[32] = "TP-Link";
// static uint8_t 			pass[32] = "khoaanbk21";

static float temperature = 0, humidity = 0;
DHT11_Data_t dht11_0;
MQTT_Client_Data_t mqtt_client_0;

static TaskHandle_t DHT11_task;

void DHT11(void *arg)
{
	while (1)
	{
		DHT11_Get_Data(&dht11_0);
		temperature = dht11_0.temperature;
		humidity = dht11_0.humidity;
		char str[5];
		sprintf(str, "%.1f", temperature);
		esp_mqtt_client_publish(mqtt_client_0.client, "dht11_tem", str, 0, 1, 0);
		sprintf(str, "%.1f", humidity);
		esp_mqtt_client_publish(mqtt_client_0.client, "dht11_hum", str, 0, 1, 0);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
    WIFI_Station_Init(ssid, pass);
    mqtt_app_start(&mqtt_client_0, url_mqtt);
    DHT11_Init(&dht11_0, DHT11_PIN);
    xTaskCreate(DHT11, "DHT11", 1024 * 2, NULL, 10, &DHT11_task);
}
