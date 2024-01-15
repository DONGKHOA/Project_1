#ifndef __SSD1963_H__
#define __SSD1963_H__

#include "fonts.h"
#include <stdbool.h>


#define 	RS_PORT		GPIOA
#define		RS_PIN		GPIO_PIN_1

#define		WR_PORT		GPIOA
#define 	WR_PIN		GPIO_PIN_3

#define		RD_PORT		GPIOA
#define		RD_PIN		GPIO_PIN_2

#define		CS_PORT		GPIOA
#define		CS_PIN		GPIO_PIN_0

#define		REST_PORT	GPIOA
#define		REST_PIN	GPIO_PIN_5

#define		D0_PORT		GPIOA
#define		D0_PIN		GPIO_PIN_7

#define		D1_PORT		GPIOB
#define		D1_PIN		GPIO_PIN_0

#define		D2_PORT		GPIOB
#define		D2_PIN		GPIO_PIN_1

#define		D3_PORT		GPIOB
#define		D3_PIN		GPIO_PIN_10

#define		D4_PORT		GPIOB
#define		D4_PIN		GPIO_PIN_11

#define		D5_PORT		GPIOB
#define		D5_PIN		GPIO_PIN_14

#define		D6_PORT		GPIOB
#define		D6_PIN		GPIO_PIN_13

#define		D7_PORT		GPIOB
#define		D7_PIN		GPIO_PIN_12

#define		D8_PORT		GPIOB
#define		D8_PIN		GPIO_PIN_15

#define		D9_PORT		GPIOA
#define		D9_PIN		GPIO_PIN_8

#define		D10_PORT	GPIOA
#define		D10_PIN		GPIO_PIN_9

#define		D11_PORT	GPIOA
#define		D11_PIN		GPIO_PIN_10

#define		D12_PORT	GPIOA
#define		D12_PIN		GPIO_PIN_12

#define		D13_PORT	GPIOA
#define		D13_PIN		GPIO_PIN_11

#define		D14_PORT	GPIOB
#define		D14_PIN		GPIO_PIN_3

#define		D15_PORT	GPIOA
#define		D15_PIN		GPIO_PIN_15


 typedef struct { // Data stored PER GLYPH
 	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
 	uint8_t  width, height;    // Bitmap dimensions in pixels
 	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
 	int8_t   xOffset, yOffset; // Dist from cursor position to UL corner
 } GFXglyph;

 typedef struct { // Data stored for FONT AS A WHOLE:
 	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
 	GFXglyph *glyph;       // Glyph array
 	uint8_t   first, last; // ASCII extents
 	uint8_t   yAdvance;    // Newline distance (y axis)
 } GFXfont;

#define HUE_01 0x0000FF // 000, 000, 255 - BLUE
#define HUE_02 0x003FFF // 000, 063, 255 -
#define HUE_03 0x007FFF // 000, 127, 255 -
#define HUE_04 0x00BFFF // 000, 191, 255 -
#define HUE_05 0x00FFFF // 000, 255, 255 - CYAN
#define HUE_06 0x00FFBF // 000, 255, 191 -
#define HUE_07 0x00FF7F // 000, 255, 127 -
#define HUE_08 0x00FF00 // 000, 255, 063 -
#define HUE_09 0x00FF00 // 000, 255, 000 - GREEN
#define HUE_10 0x3FFF00 // 063, 255, 000 -
#define HUE_11 0x7FFF7F // 127, 255, 000 -
#define HUE_12 0xBFFF00 // 191, 255, 000 - LIME
#define HUE_13 0xFFFF00 // 255, 255, 000 - YELLOW
#define HUE_14 0xFFBF00 // 255, 191, 000 -
#define HUE_15 0xFF7F00 // 255, 127, 000 -
#define HUE_16 0xFF3F00 // 255, 063, 000 -
#define HUE_17 0xFF0000 // 255, 000, 000 - RED
#define HUE_18 0xFF003F // 255, 000, 063 -
#define HUE_19 0xFF007F // 255, 000, 127 -
#define HUE_20 0xFF00BF // 255, 000, 191 -
#define HUE_21 0xFF00FF // 255, 000, 255 - MAGENTA
#define HUE_22 0xBF00FF // 191, 000, 255 -
#define HUE_23 0x7F00FF // 127, 000, 255 -
#define HUE_24 0x3F00FF // 063, 000, 255 -


#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     HUE_17
#define BLUE    HUE_01
#define BLUE_D  0x0000A0 /*   0,   0, 160 */
#define CYAN    HUE_05
#define YELLOW  HUE_13 /* 255, 255,   0 */
#define MAGENTA HUE_21 /* 255,   0, 255 */
#define GREEN   HUE_09 /*   0, 255,   0 */
#define GREEN_D 0x007F00 /*   0, 128,   0 */
#define PURPLE  0x7F007F /* 128,   0, 128 */
#define TEAL    0x007F7F /*   0, 128, 128 */
#define NAVY    0x00007F /*   0,   0, 128 */
#define SILVER  0xBFBFBF /* 191, 191, 191 */
#define GRAY    0x7F7F7F /* 128, 128, 128 */
#define ORANGE  0xFFA500 /* 255, 165,   0 */
#define BROWN   0xA52A2A /* 165, 255,  42 */
#define MAROON  0x7F0000 /* 128,   0,   0 */
#define OLIVE   0x7F7F00 /* 128, 128,   0 */
#define LIME    HUE_12

/* Declare Private Macro */

#define		pin_low(port,pin)			HAL_GPIO_WritePin(port,pin,GPIO_PIN_RESET)
#define		pin_high(port,pin)		HAL_GPIO_WritePin(port,pin,GPIO_PIN_SET)
#define		max(a,b)				(a>b)?a:b
#define		min(a,b)				(a<b)?a:b
#define		abs(a)					(a>=0)?a:(-a)



//  Orientation params
#define SSD1963_MADCTL_MY  0x80
#define SSD1963_MADCTL_MX  0x40
#define SSD1963_MADCTL_MV  0x20
#define SSD1963_MADCTL_ML  0x10
#define SSD1963_MADCTL_RGB 0x00
#define SSD1963_MADCTL_BGR 0x08
#define SSD1963_MADCTL_MH  0x04

/* Select a rotate direction for display */
#define SSD1963_SET_ROTATION 2
// default orientation
#if SSD1963_SET_ROTATION == 0
#define SSD1963_WIDTH  480
#define SSD1963_HEIGHT 272
    #define SSD1963_ROTATION 0x22


// rotate right
#elif SSD1963_SET_ROTATION == 1
    #define SSD1963_WIDTH  480
    #define SSD1963_HEIGHT 272
    #define SSD1963_ROTATION 0x21


// rotate left
#elif SSD1963_SET_ROTATION == 2
#define SSD1963_WIDTH  480
#define SSD1963_HEIGHT 272
    #define SSD1963_ROTATION 0x00

// upside down
#elif SSD1963_SET_ROTATION == 3
    #define SSD1963_WIDTH  480
    #define SSD1963_HEIGHT 272
    #define SSD1963_ROTATION 0x03
#endif

/****************************/

// Color definitions
#define	SSD1963_BLACK   0x0000
#define	SSD1963_BLUE    0xF800
#define	SSD1963_RED     0x001F
#define	SSD1963_GREEN   0x07E0
#define SSD1963_CYAN    0x07FF
#define SSD1963_MAGENTA 0xF81F
#define SSD1963_YELLOW  0xFFE0
#define SSD1963_WHITE   0xFFFF
#define SSD1963_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define ABS(x) ((x) > 0 ? (x) : -(x))

/**
 * @brief Initialize the SSD1963 controller
 * @param none
 * @return none
 */
void SSD1963_Init(void);

/**
 * @brief Draw a pixel on screen
 * @param x, y -> Coordinates to draw
 * @param color -> color to draw
 * @return none
 */
void SSD1963_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief Write string to screen
 * @param x, y -> Coordinates to write
 * @param str -> string to write
 * @param font -> font to use
 * @param color -> color of the string
 * @param bgcolor -> Background color of the string
 * @return none
 */
void SSD1963_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);

/**
 * @brief Fill a Rect-Area with single color
 * @param x, y -> Coordinates to start
 * @param w, h -> Width & Height of the Rect.
 * @param color -> color of the Rect.
 * @return none
 */
void SSD1963_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * @brief Fill screen with single color
 * @param color -> color to fill with
 * @return none
 */
void SSD1963_FillScreen(uint16_t color);

/**
 * @brief Draw a line with single color
 * @param x1&y1 -> coordinate of the start point
 * @param x2&y2 -> coordinate of the end point
 * @param color -> color of the line to Draw
 * @return none
 */
void SSD1963_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                      uint16_t color);
void SSD1963_DrawArc(uint16_t x, uint16_t y, uint16_t r, uint16_t startAngle, uint16_t endAngle, uint16_t thickness, uint16_t color);
/**
 * @brief Draw a circle with single color
 * @param x0&y0 -> coordinate of circle center
 * @param r -> radius of circle
 * @param color -> color of circle line
 * @return  none
 */
void SSD1963_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

/**
 * @brief Draw a Filled circle with single color
 * @param x0&y0 -> coordinate of circle center
 * @param r -> radius of circle
 * @param color -> color of circle
 * @return  none
 */
void SSD1963_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/**
 * @brief Draw a Triangle with single color
 * @param  xi&yi -> 3 coordinates of 3 top points.
 * @param color ->color of the lines
 * @return  none
 */
void SSD1963_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                            uint16_t x3, uint16_t y3, uint16_t color);

/**
 * @brief Draw a filled Triangle with single color
 * @param  xi&yi -> 3 coordinates of 3 top points.
 * @param color ->color of the triangle
 * @return  none
 */
void SSD1963_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                                uint16_t x3, uint16_t y3, uint16_t color);

/**
 * @brief Draw an image on the screen
 * @param x, y -> Coordinate of the image's top-left dot (where to start)
 * @param w, h -> Width & Height of the image
 * @param data -> Must be '(uint16_t *)data' ,the image data array
 * @return none
 */
void SSD1963_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);

/**
 * @brief Invert screen color
 * @param invert -> Invert or not
 * @return none
 */
void SSD1963_InvertColors(bool invert);

/**
 * @brief Simple test function for almost all functions
 * @param none
 * @return none
 */
void SSD1963_Test(void);

/**
 * @brief Simple FPS test function (not so reliable...)
 * @param none
 * @return none
 */
void FPS_Test(void);
void LCD_Rect_Fill1(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24);

void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);
void drawGauge1(int level,uint16_t cx,uint16_t cy);
void SSD1963_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void SSD1963_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, uint32_t color24);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24);
void LCD_Circle_Fill_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color24);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24);
void LCD_Bright(uint8_t bright);












//
//void LCD_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
//void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
//void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
//void LCD_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
//

#endif // __SSD1963_H__
