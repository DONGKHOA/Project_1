set(component_srcs "ili9341.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "."
                       REQUIRES "freertos" "esp_err"
                       )