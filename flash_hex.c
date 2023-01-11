#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "driver/gpio.h"

#define HEX_FILE "BOOTLOADER.HEX"
#define GPIO_MOSI 23
#define GPIO_CLK  19
#define GPIO_RESET 22

static const char* TAG = "GPIO_HEX_FLASH";

// Function that sends one byte over the ISP protocol
void send_byte(uint8_t byte) {
    //TODO:
    // add code that sends one byte over the ISP protocol
    // using the GPIO_MOSI, GPIO_CLK, and GPIO_RESET pins
}

void flash_hex(void)
{
    // Open the .hex file from SPIFFS
    FILE* f = fopen(HEX_FILE, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    //Read the hex file and send it via ISP
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            send_byte(line[i]);
        }
    }
    fclose(f);
}

void app_main()
{
    esp_err_t ret = esp_spiffs_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount SPIFFS (0x%x)", ret);
        return;
    }
    // Set the correct mode for the gpio pins
    gpio_set_direction(GPIO_MOSI,GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_CLK,GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_RESET,GPIO_MODE_OUTPUT);

    flash_hex();
}
