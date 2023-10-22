/**
 * @file ili9341.h
 *
 */

#ifndef ILI9341_H
#define ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
#include "driver/spi_master.h"
#include "font.h"
#include "esp_err.h"

typedef enum
{
	DIRECTION_0 = 0,
	DIRECTION_1,
	DIRECTION_2,
	DIRECTION_3,
}DIRECTION_Data_t;

typedef struct {
	uint8_t _font_Rotation;
	uint8_t _font_background;
	uint16_t _font;
	uint16_t _font_color;
	uint16_t _font_background_color;
	uint16_t _width;
	uint16_t _height;
	uint16_t _offsetx;
	uint16_t _offsety;
	int16_t _dc;
	spi_device_handle_t _TFT_Handle;
} TFT_t;

/*********************
 *      DEFINES
 *********************/

#define ILI9341_ENABLE_BACKLIGHT_CONTROL CONFIG_LV_ENABLE_BACKLIGHT_CONTROL

#if CONFIG_LV_BACKLIGHT_ACTIVE_LVL
  #define ILI9341_BCKL_ACTIVE_LVL 1
#else
  #define ILI9341_BCKL_ACTIVE_LVL 0
#endif

#define ILI9341_INVERT_COLORS CONFIG_LV_INVERT_COLORS

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void ili9341_init(void);
void ili9341_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map);
void ili9341_enable_backlight(bool backlight);
void ili9341_sleep_in(void);
void ili9341_sleep_out(void);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ILI9341_H*/
