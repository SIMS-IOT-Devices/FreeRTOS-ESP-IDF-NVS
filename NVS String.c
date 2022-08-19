// Read/Write STRING to flash memory

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

void app_main(void)
{
    nvs_flash_init();
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    nvs_handle_t my_handle;
    nvs_open("storage", NVS_READWRITE, &my_handle);

    // Read data, key - "data", value - "read_data"
    size_t required_size = 0;
    nvs_get_str(my_handle, "data", NULL, &required_size);
    char *server_name = malloc(required_size);
    nvs_get_str(my_handle, "data", server_name, &required_size);
    printf("Read data: %s\n", server_name);

    // Write data, key - "data", value - "write_string"
    char *write_string = "Some string ...\0";
    nvs_set_str(my_handle, "data", write_string);
    printf("Write data: %s\n", write_string);
    nvs_commit(my_handle);

    nvs_close(my_handle);
}