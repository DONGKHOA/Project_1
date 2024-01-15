
/* vim: set ai et ts=4 sw=4: */
#include "main.h"
#include "SSD1963.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

GPIO_TypeDef* PORT_NAME_ARR[]={D0_PORT,D1_PORT,D2_PORT,D3_PORT,D4_PORT,D5_PORT,D6_PORT,D7_PORT,D8_PORT,D9_PORT,D10_PORT,D11_PORT,D12_PORT,D13_PORT,D14_PORT,D15_PORT};
uint16_t      PIN_NAME_ARR[]={D0_PIN,D1_PIN,D2_PIN,D3_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN,D8_PIN,D9_PIN,D10_PIN,D11_PIN,D12_PIN,D13_PIN,D14_PIN,D15_PIN};

//#define swap(a, b) { int16_t t = a; a = b; b = t; }
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
//#define min(a,b) (((a)<(b))?(a):(b))

#define MAXSIN 255

const uint8_t sinTab[91]= {
0,4,8,13,17,22,26,31,35,39,44,48,53,57,61,65,70,74,78,83,87,91,95,99,103,107,111,115,119,123,
127,131,135,138,142,146,149,153,156,160,163,167,170,173,177,180,183,186,189,192,195,198,200,203,206,208,211,213,216,218,
220,223,225,227,229,231,232,234,236,238,239,241,242,243,245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,
255
};


int cx,cy;
int sx,sy;
int xs0,ys0,xe0,ye0;
int xs1,ys1,xe1,ye1;
uint16_t bgCol;

inline static uint16_t H24_RGB565(uint8_t reverse, uint32_t color24)
{
	uint8_t b = (color24 >> 16) & 0xFF;
	uint8_t g = (color24 >> 8) & 0xFF;
	uint8_t r = color24 & 0xFF;
	if (reverse) return ((b / 8) << 11) | ((g / 4) << 5) | (r / 8);
	else return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}


void swap(uint16_t a, uint16_t b)
{
	uint16_t temp = 0x0000;

    temp = b;
    b = a;
    a = temp;
}
/* Static functions for fundamental instructions */
void tft_write_bus(uint8_t high_byte,uint8_t low_byte)
{
  uint8_t i;
  for(i=0;i<8;i++)
  {
    if(high_byte&(0x01<<i))
    {
      pin_high(PORT_NAME_ARR[i+8],PIN_NAME_ARR[i+8]);
    }
    else
    {
      pin_low(PORT_NAME_ARR[i+8],PIN_NAME_ARR[i+8]);
    }

		if(low_byte&(0x01<<i))
    {
      pin_high(PORT_NAME_ARR[i],PIN_NAME_ARR[i]);
    }
    else
    {
      pin_low(PORT_NAME_ARR[i],PIN_NAME_ARR[i]);
    }
  }
  pin_low(WR_PORT,WR_PIN);
  pin_high(WR_PORT,WR_PIN);
}


void tft_write_data8(uint8_t high_byte,uint8_t low_byte)
{
	pin_high(RS_PORT,RS_PIN);
	tft_write_bus(high_byte,low_byte);
}
void SSD1963_WriteData(uint16_t data)
{
  pin_high(RS_PORT,RS_PIN);
  tft_write_bus(data>>8,data&0x00ff);
}

void SSD1963_WriteCommand(uint16_t data)
{
  pin_low(RS_PORT,RS_PIN);
  tft_write_bus(data>>8,data&0x00ff);
}

//void tft_write_reg_data(uint16_t reg,uint16_t data)
//{
//  tft_write_reg(reg);
//  tft_write_data(data);
//}

//static void SSD1963_WriteCommand(uint16_t cmd) {
//    SSD1963_WRITE_REG = cmd;
//}

//static void SSD1963_WriteData(uint16_t data) {
//    SSD1963_WRITE_DATA = data;
//}
//
//static void SSD1963_WriteDataMultiple(uint16_t * datas, uint32_t dataNums) {
//    while (dataNums--)
//    {
////        SSD1963_WRITE_DATA = *datas++;
//    	SSD1963_WriteData(*datas++);
//    }
//}

static void SSD1963_SetAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	swap(x1, y1);
	swap(x2, y2);
	SSD1963_WriteCommand(0x2a);
	SSD1963_WriteData(x1>>8);
	SSD1963_WriteData(x1);
	SSD1963_WriteData(x2>>8);
	SSD1963_WriteData(x2);
	SSD1963_WriteCommand(0x2b);
	SSD1963_WriteData(y1>>8);
	SSD1963_WriteData(y1);
	SSD1963_WriteData(y2>>8);
	SSD1963_WriteData(y2);
	SSD1963_WriteCommand(0x2c);
}

void SSD1289_Address_Set1(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)	/*Thiet lap vung lam viec cua man hinh*/
{
	/*Doi toa do ve toa do mong muon*/

//	swap(x1, y1);
//	swap(x2, y2);
	SSD1963_WriteCommand(0x2a);
	SSD1963_WriteData(x1>>8);
	SSD1963_WriteData(x1);
	SSD1963_WriteData(x2>>8);
	SSD1963_WriteData(x2);
	SSD1963_WriteCommand(0x2b);
	SSD1963_WriteData(y1>>8);
	SSD1963_WriteData(y1);
	SSD1963_WriteData(y2>>8);
	SSD1963_WriteData(y2);
	SSD1963_WriteCommand(0x2c);
}

void SSD1963_Init() {
		pin_high(CS_PORT,CS_PIN);
		pin_high(RD_PORT,RD_PIN);
		pin_high(WR_PORT,WR_PIN);
		pin_low(REST_PORT,REST_PIN);

		HAL_Delay(20);
		pin_high(REST_PORT,REST_PIN);
		HAL_Delay(20);
		pin_low(CS_PORT,CS_PIN);
		SSD1963_WriteCommand(0xE2);		//PLL multiplier, set PLL clock to 120M
		SSD1963_WriteData(0x23);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
		SSD1963_WriteData(0x02);
		SSD1963_WriteData(0x54);
		SSD1963_WriteCommand(0xE0);		// PLL enable
		SSD1963_WriteData(0x01);
		HAL_Delay(10);
		SSD1963_WriteCommand(0xE0);
		SSD1963_WriteData(0x03);
		HAL_Delay(10);
		SSD1963_WriteCommand(0x01);		// software reset
		HAL_Delay(100);
		SSD1963_WriteCommand(0xE6);		//PLL setting for PCLK, depends on resolution
		SSD1963_WriteData(0x01);
		SSD1963_WriteData(0x1F);
		SSD1963_WriteData(0xFF);

		SSD1963_WriteCommand(0xB0);		//LCD SPECIFICATION
		SSD1963_WriteData(0x20);
		SSD1963_WriteData(0x00);
		SSD1963_WriteData(0x01);		//Set HDP	479
		SSD1963_WriteData(0xDF);
		SSD1963_WriteData(0x01);		//Set VDP	271
		SSD1963_WriteData(0x0F);
		SSD1963_WriteData(0x00);

		SSD1963_WriteCommand(0xB4);		//HSYNC
		SSD1963_WriteData(0x02);		//Set HT	531
		SSD1963_WriteData(0x13);
		SSD1963_WriteData(0x00);		//Set HPS	8
		SSD1963_WriteData(0x08);
		SSD1963_WriteData(0x2B);		//Set HPW	43
		SSD1963_WriteData(0x00);		//Set LPS	2
		SSD1963_WriteData(0x02);
		SSD1963_WriteData(0x00);

		SSD1963_WriteCommand(0xB6);		//VSYNC
		SSD1963_WriteData(0x01);		//Set VT	288
		SSD1963_WriteData(0x20);
		SSD1963_WriteData(0x00);		//Set VPS	4
		SSD1963_WriteData(0x04);
		SSD1963_WriteData(0x0c);		//Set VPW	12
		SSD1963_WriteData(0x00);		//Set FPS	2
		SSD1963_WriteData(0x02);

		SSD1963_WriteCommand(0xBA);
		SSD1963_WriteData(0x0F);		//GPIO[3:0] out 1

		SSD1963_WriteCommand(0xB8);
		SSD1963_WriteData(0x07);	    //GPIO3=input, GPIO[2:0]=output
		SSD1963_WriteData(0x01);		//GPIO0 normal

		SSD1963_WriteCommand(0x36);		//rotation
		SSD1963_WriteData(SSD1963_ROTATION);

		SSD1963_WriteCommand(0xF0);		//pixel data interface
		SSD1963_WriteData(0x03);


		HAL_Delay(1);

		SSD1963_SetAddressWindow(0, 0, 479, 271);
		SSD1963_WriteCommand(0x29);		//display on

		SSD1963_WriteCommand(0xBE);		//set PWM for B/L
		SSD1963_WriteData(0x06);
		SSD1963_WriteData(0xf0);
		SSD1963_WriteData(0x01);
		SSD1963_WriteData(0xf0);
		SSD1963_WriteData(0x00);
		SSD1963_WriteData(0x00);

		SSD1963_WriteCommand(0xd0);
		SSD1963_WriteData(0x0d);

		SSD1963_WriteCommand(0x2C);
}


void SSD1963_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= SSD1963_WIDTH) || (y >= SSD1963_HEIGHT))
        return;
    SSD1963_SetAddressWindow(x, y, x+1, y+1);
    SSD1963_WriteData(color);
}
/*
 * Some problem occurred...Deserted temporarily
static void SSD1963_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;
    SSD1963_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);
    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if( (b << j) & 0x8000)  {
                SSD1963_WriteData(color);
            } else {
                SSD1963_WriteData(bgcolor);
            }
        }
    }
}
 */

static void SSD1963_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;
    SSD1963_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);
    for (i = 0; i < font.height; i++)
    {
        b = font.data[(ch-32) * font.height + i];
        for (j = 0; j < font.width; j++)
        {
            if ((b << j) & 0x8000)
                SSD1963_DrawPixel(x+j, y+i, color);

            else
                SSD1963_DrawPixel(x+j, y+i, bgcolor);
        }
    }
}


void SSD1963_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
    while(*str) {
        if(x + font.width >= SSD1963_WIDTH) {
            x = 0;
            y += font.height;
            if(y + font.height >= SSD1963_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        SSD1963_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}


void SSD1963_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= SSD1963_WIDTH) || (y >= SSD1963_HEIGHT)) return;
    if((x + w - 1) >= SSD1963_WIDTH) w = SSD1963_WIDTH - x;
    if((y + h - 1) >= SSD1963_HEIGHT) h = SSD1963_HEIGHT - y;

    SSD1963_SetAddressWindow(x, y, x+w-1, y+h-1);
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
            SSD1963_WriteData(color);
        }
    }
}

void SSD1963_FillScreen(uint16_t color) {
    SSD1963_FillRectangle(0, 0, SSD1963_WIDTH, SSD1963_HEIGHT, color);
}

void SSD1963_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                     uint16_t color) {
    uint16_t swap;
    uint16_t steep = ABS(y1 - y0) > ABS(x1 - x0);
    if (steep) {
        swap = x0;
        x0 = y0;
        y0 = swap;

        swap = x1;
        x1 = y1;
        y1 = swap;
        //_swap_int16_t(x0, y0);
        //_swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        swap = x0;
        x0 = x1;
        x1 = swap;

        swap = y0;
        y0 = y1;
        y1 = swap;
        //_swap_int16_t(x0, x1);
        //_swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = ABS(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            SSD1963_DrawPixel(y0, x0, color);
        } else {
            SSD1963_DrawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void SSD1963_DrawArc(uint16_t x, uint16_t y, uint16_t r, uint16_t startAngle, uint16_t endAngle, uint16_t thickness, uint16_t color)
{
	uint16_t rDelta = -(thickness/2);
	uint16_t px, py, cx, cy;

        startAngle -= 90;
        endAngle   -= 90;

        if (startAngle!=endAngle)
        {
                for (int i=0; i<thickness; i++)
                {
                        px = x + cos((startAngle*3.14)/180) * (r+rDelta+i);
                        py = y + sin((startAngle*3.14)/180) * (r+rDelta+i);
                        for (int d=startAngle+1; d<endAngle+1; d++)
                        {
                                cx = x + cos((d*3.14)/180) * (r+rDelta+i);
                                cy = y + sin((d*3.14)/180) * (r+rDelta+i);
                                SSD1963_DrawLine(px, py, cx, cy, color);
                                px = cx;
                                py = cy;
                        }
                }
        }
        else
        {
                px = x + cos((startAngle*3.14)/180) * (r+rDelta);
                py = y + sin((startAngle*3.14)/180) * (r+rDelta);
                cx = x + cos((startAngle*3.14)/180) * (r-rDelta);
                cy = y + sin((startAngle*3.14)/180) * (r-rDelta);
                SSD1963_DrawLine(px, py, cx, cy, color);
        }
}


void SSD1963_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    SSD1963_DrawPixel(x0, y0 + r, color);
    SSD1963_DrawPixel(x0, y0 - r, color);
    SSD1963_DrawPixel(x0 + r, y0, color);
    SSD1963_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SSD1963_DrawPixel(x0 + x, y0 + y, color);
        SSD1963_DrawPixel(x0 - x, y0 + y, color);
        SSD1963_DrawPixel(x0 + x, y0 - y, color);
        SSD1963_DrawPixel(x0 - x, y0 - y, color);

        SSD1963_DrawPixel(x0 + y, y0 + x, color);
        SSD1963_DrawPixel(x0 - y, y0 + x, color);
        SSD1963_DrawPixel(x0 + y, y0 - x, color);
        SSD1963_DrawPixel(x0 - y, y0 - x, color);
    }
}

void SSD1963_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    SSD1963_DrawPixel(x0, y0 + r, color);
    SSD1963_DrawPixel(x0, y0 - r, color);
    SSD1963_DrawPixel(x0 + r, y0, color);
    SSD1963_DrawPixel(x0 - r, y0, color);
    SSD1963_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SSD1963_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        SSD1963_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        SSD1963_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        SSD1963_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
}

void SSD1963_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                            uint16_t x3, uint16_t y3, uint16_t color)
{
    /* Draw lines */
    SSD1963_DrawLine(x1, y1, x2, y2, color);
    SSD1963_DrawLine(x2, y2, x3, y3, color);
    SSD1963_DrawLine(x3, y3, x1, y1, color);
}

void SSD1963_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                                uint16_t x3, uint16_t y3, uint16_t color)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1);
    deltay = ABS(y2 - y1);
    x = x1;
    y = y1;

    if (x2 >= x1) {
        xinc1 = 1;
        xinc2 = 1;
    }
    else {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1) {
        yinc1 = 1;
        yinc2 = 1;
    }
    else {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay) {
        xinc1 = 0;
        yinc2 = 0;
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;
    }
    else {
        xinc2 = 0;
        yinc1 = 0;
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        SSD1963_DrawLine(x, y, x3, y3, color);

        num += numadd;
        if (num >= den) {
            num -= den;
            x += xinc1;
            y += yinc1;
        }
        x += xinc2;
        y += yinc2;
    }
}

void SSD1963_DrawImage(uint16_t x_pos, uint16_t y_pos, uint16_t W, uint16_t H, const uint16_t* bitmap) {
    if((x_pos >= SSD1963_WIDTH) || (y_pos >= SSD1963_HEIGHT)) return;
    if((x_pos + W - 1) >= SSD1963_WIDTH) return;
    if((y_pos + H - 1) >= SSD1963_HEIGHT) return;
    uint16_t xp = 0;
    uint16_t yp = (y_pos + H);
    uint32_t index = 0;
    SSD1963_SetAddressWindow(x_pos, y_pos, x_pos+W-1, y_pos+H-1);
    while(yp > 0)
    {
        for(xp = x_pos; xp < (x_pos + W); xp++)
        {
        	SSD1963_DrawPixel(xp, yp, bitmap[index++]);
        }
        yp--;
    }
}

void SSD1963_InvertColors(bool invert) {
    SSD1963_WriteCommand(invert ? 0x21 /* INVON */ : 0x20 /* INVOFF */);
}

void SSD1963_Test(void)
{
    SSD1963_FillScreen(SSD1963_WHITE);
    HAL_Delay(1000);
    SSD1963_WriteString(10, 10, "ISMAIL", Font_16x26, SSD1963_RED, SSD1963_WHITE);
    HAL_Delay(2000);
    SSD1963_FillScreen(SSD1963_RED);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_BLUE);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_GREEN);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_YELLOW);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_CYAN);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_MAGENTA);
    HAL_Delay(1000);
    SSD1963_FillScreen(SSD1963_BLACK);
    HAL_Delay(2000);

    SSD1963_FillRectangle(10, 10, 30, 20, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_BLACK);

    SSD1963_DrawLine(10, 10, 30, 30, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_BLACK);

    SSD1963_DrawCircle(100, 100, 50, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_BLACK);

    SSD1963_DrawFilledCircle(100, 100, 50, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_BLACK);

    SSD1963_DrawTriangle(10, 10, 50, 50, 100, 10, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_BLACK);

    SSD1963_DrawFilledTriangle(10, 10, 50, 50, 100, 10, SSD1963_WHITE);
    HAL_Delay(1500);
    SSD1963_FillScreen(SSD1963_WHITE);
    HAL_Delay(1000);
//    SSD1963_DrawImage(70, 57, 250, 182, (const uint16_t*)image);
    HAL_Delay(1000);

}

void FPS_Test(void)
{
    SSD1963_FillScreen(SSD1963_WHITE);

    uint32_t start = HAL_GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHJK";
    do {
        SSD1963_WriteString(10, 10, message, Font_11x18, SSD1963_RED, SSD1963_WHITE);

        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        fps++;
        end = HAL_GetTick();
    } while ((end - start) < 5000);

    HAL_Delay(1000);
    char buff[64];
    fps = (float) fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);

    SSD1963_FillScreen(SSD1963_WHITE);
    SSD1963_WriteString(10, 10, buff, Font_11x18, SSD1963_RED, SSD1963_WHITE);
    HAL_Delay(3000);
}


void LCD_Rect_Fill1(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24)
{
	uint32_t i = 0;
	uint32_t j = (uint32_t) w * (uint32_t) h;
	SSD1289_Address_Set1(x, y, x + w - 1, h + w - 1);
	for (i = 0; i < j; i++) SSD1963_WriteData(H24_RGB565(1, color24));
}


void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24)
{
	uint8_t  *bitmap = font -> bitmap;
	uint16_t bo = glyph -> bitmapOffset;
	uint8_t bits = 0, bit = 0;
	uint16_t set_pixels = 0;
	uint8_t  cur_x, cur_y;
	for(cur_y = 0; cur_y < glyph -> height; cur_y++)
	{
		for(cur_x = 0; cur_x < glyph -> width; cur_x++)
		{
			if(bit == 0)
			{
				bits = (*(const unsigned char *)(&bitmap[bo++]));
				bit  = 0x80;
			}
			if(bits & bit)
			{
				set_pixels++;
			}
			else if (set_pixels > 0)
			{
				LCD_Rect_Fill1(x + (glyph -> xOffset + cur_x - set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0)
		{
			LCD_Rect_Fill1(x + (glyph -> xOffset + cur_x-set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
			set_pixels = 0;
		}
	}
}

void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font, uint8_t size, uint32_t color24)
{
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	GFXfont font;
	memcpy((&font), (p_font), (sizeof(GFXfont)));
	for(uint16_t text_pos = 0; text_pos < strlen(text); text_pos++)
	{
		char c = text[text_pos];
		if(c == '\n')
		{
			cursor_x = x;
			cursor_y += font.yAdvance * size;
		}
		else if(c >= font.first && c <= font.last && c != '\r')
		{
			GFXglyph glyph;
			memcpy((&glyph), (&font.glyph[c - font.first]), (sizeof(GFXglyph)));
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
			cursor_x += glyph.xAdvance * size;
		}
	}
}


int fastSin(int k)
{
  while(k<0) k+=360;
  while(k>=360) k-=360;
  if(k<90)  return(pgm_read_byte(&sinTab[k])); else
  if(k<180) return(pgm_read_byte(&sinTab[180-k])); else
  if(k<270) return(-pgm_read_byte(&sinTab[k-180])); else
            return(-pgm_read_byte(&sinTab[360-k]));
}


int fastCos(int p)
{
  return fastSin(p+90);
}


void drawGauge1(int level,uint16_t cx,uint16_t cy)
{
//  cx=cx/2;
//  cy=cy/2;
  int rx0=40, ry0=40;
  int rx1=63, ry1=63;
  int mina=-75;
  int maxa=180+75;
  for(int i=mina; i<maxa; i+=15) {
    sx = fastCos(i-180);
    sy = fastSin(i-180);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*ry0/MAXSIN;
    xe0 = cx+sx*rx1/MAXSIN;
    ye0 = cy+sy*ry1/MAXSIN;
    sx = fastCos(i-180+10);
    sy = fastSin(i-180+10);
    xs1 = cx+sx*rx0/MAXSIN;
    ys1 = cy+sy*ry0/MAXSIN;
    xe1 = cx+sx*rx1/MAXSIN;
    ye1 = cy+sy*ry1/MAXSIN;
    int l=100*(i-mina)/(maxa-mina);
    if(l<level) {
    	SSD1963_DrawFilledTriangle(xs0,ys0,xe0,ye0,xe1,ye1, SSD1963_GREEN);
    	SSD1963_DrawFilledTriangle(xs1,ys1,xe1,ye1,xs0,ys0, SSD1963_GREEN);
    } else {
    	SSD1963_DrawFilledTriangle(xs0,ys0,xe0,ye0,xe1,ye1, SSD1963_RED);
    	SSD1963_DrawFilledTriangle(xs1,ys1,xe1,ye1,xs0,ys0, SSD1963_RED);
    }
  }

}

void SSD1963_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	SSD1963_DrawLine(x, y, x+w-1, y, color);
}

void SSD1963_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	SSD1963_DrawLine(x, y, x, y+h-1, color);
}

//void LCD_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
//	int16_t f = 1 - r;
//	int16_t ddF_x = 1;
//	int16_t ddF_y = -2 * r;
//	int16_t x = 0;
//	int16_t y = r;
//
//	while (x < y) {
//		if (f >= 0) {
//			y--;
//			ddF_y += 2;
//			f += ddF_y;
//		}
//		x++;
//		ddF_x += 2;
//		f += ddF_x;
//		if (cornername & 0x4) {
//			SSD1963_DrawPixel(x0 + x, y0 + y, color);
//			SSD1963_DrawPixel(x0 + y, y0 + x, color);
//		}
//		if (cornername & 0x2) {
//			SSD1963_DrawPixel(x0 + x, y0 - y, color);
//			SSD1963_DrawPixel(x0 + y, y0 - x, color);
//		}
//		if (cornername & 0x8) {
//			SSD1963_DrawPixel(x0 - y, y0 + x, color);
//			SSD1963_DrawPixel(x0 - x, y0 + y, color);
//		}
//		if (cornername & 0x1) {
//			SSD1963_DrawPixel(x0 - y, y0 - x, color);
//			SSD1963_DrawPixel(x0 - x, y0 - y, color);
//		}
//	}
//}
//
//

//
//
//void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
//	// smarter version
//	Draw_H_Line(x + r, y, w - 2 * r, color); // Top
//	Draw_H_Line(x + r, y + h - 1, w - 2 * r, color); // Bottom
//	Draw_V_Line(x, y + r, h - 2 * r, color); // Left
//	Draw_V_Line(x + w - 1, y + r, h - 2 * r, color); // Right
//	// draw four corners
//	LCD_DrawCircleHelper(x + r, y + r, r, 1, color);
//	LCD_DrawCircleHelper(x + w - r - 1, y + r, r, 2, color);
//	LCD_DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
//	LCD_DrawCircleHelper(x + r, y + h - r - 1, r, 8, color);
//}
//
//void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
//	int16_t f = 1 - r;
//	int16_t ddF_x = 1;
//	int16_t ddF_y = -2 * r;
//	int16_t x = 0;
//	int16_t y = r;
//
//	while (x < y) {
//		if (f >= 0) {
//			y--;
//			ddF_y += 2;
//			f += ddF_y;
//		}
//		x++;
//		ddF_x += 2;
//		f += ddF_x;
//
//		if (cornername & 0x1) {
//			SSD1963_drawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
//			SSD1963_drawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
//		}
//		if (cornername & 0x2) {
//			SSD1963_drawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
//			SSD1963_drawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
//		}
//	}
//}
//
//
//void LCD_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
//	// smarter version
//	SSD1963_FillRectangle(x + r, y, w - 2 * r, h, color);
//
//	// draw four corners
//	LCD_FillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
//	LCD_FillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
//}
//
//










void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24)
{
	SSD1963_SetAddressWindow(x, y, x, y);
	SSD1963_WriteData(H24_RGB565(1, color24));
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24)
{
	uint32_t i = 0;
	SSD1963_SetAddressWindow(y, x, y + h - 1, x + w - 1);
	for (i = 0; i < w * h; i++) SSD1963_WriteData(H24_RGB565(0, color24));
}

void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = 0;
	for (;;)
	{
		LCD_Rect_Fill(x1, y1, size, size, color24);
		if (x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24)
{
	LCD_Line(x1, y1, x2, y2, size, color24);
	LCD_Line(x2, y2, x3, y3, size, color24);
	LCD_Line(x3, y3, x1, y1, size, color24);
}

void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24)
{
	LCD_Line(x, y, x + w, y, size, color24);
	LCD_Line(x, y + h, x + w, y + h, size, color24);
	LCD_Line(x, y, x, y + h, size, color24);
	LCD_Line(x + w, y, x + w, y + h, size, color24);
}

void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24)
{
	int16_t x, y;
	int32_t rx2 = rx * rx;
	int32_t ry2 = ry * ry;
	int32_t fx2 = 4 * rx2;
	int32_t fy2 = 4 * ry2;
	int32_t s;
	if (fill)
	{
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++)
		{
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1-2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0)
			{
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
	else
	{
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++)
		{
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0)
			{
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
}

void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24)
{
	int a_, b_, P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_)
	{
		if (fill == 1)
		{
			LCD_Rect_Fill(x - a_, y - b_, 2 * a_ + 1, 2 * b_ + 1, color24);
			LCD_Rect_Fill(x - b_, y - a_, 2 * b_ + 1, 2 * a_ + 1, color24);
		}
		else
		{
			LCD_Rect_Fill(a_ + x, b_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, a_ + y, size, size, color24);
			LCD_Rect_Fill(x - a_, b_ + y, size, size, color24);
			LCD_Rect_Fill(x - b_, a_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, y - a_, size, size, color24);
			LCD_Rect_Fill(a_ + x, y - b_, size, size, color24);
			LCD_Rect_Fill(x - a_, y - b_, size, size, color24);
			LCD_Rect_Fill(x - b_, y - a_, size, size, color24);
		}
		if (P < 0)
		{
			P = (P + 3) + (2 * a_);
			a_++;
		}
		else
		{
			P = (P + 5) + (2 * (a_ - b_));
			a_++;
			b_--;
		}
	}
}

void LCD_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, uint32_t color24)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + y, y0 + x, size, size, color24);
		}
		if (cornername & 0x2) {
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 + y, y0 - x, size, size, color24);
		}
		if (cornername & 0x8) {
			LCD_Rect_Fill(x0 - y, y0 + x, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
		}
		if (cornername & 0x1) {
			LCD_Rect_Fill(x0 - y, y0 - x, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
		}
	}
}

void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24)
{
	LCD_Line(x + r, y, x + length + size - r, y, size, color24);
	LCD_Line(x + r, y + width - 1, x + length + size - r, y + width - 1, size, color24);
	LCD_Line(x, y + r, x, y + width - size - r, size, color24);
	LCD_Line(x + length - 1, y + r, x + length - 1, y + width - size - r, size, color24);

	LCD_Circle_Helper(x + r, y + r, r, 1, size, color24);
	LCD_Circle_Helper(x + length - r - 1, y + r, r, 2, size, color24);
	LCD_Circle_Helper(x + length - r - 1, y + width - r - 1, r, 4, size, color24);
	LCD_Circle_Helper(x + r, y + width - r - 1, r, 8, size, color24);
}

void LCD_Circle_Fill_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color24)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1) {
			LCD_Line(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y + delta, 1, color24);
			LCD_Line(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x + delta, 1, color24);
		}
		if (cornername & 0x2) {
			LCD_Line(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y + delta, 1, color24);
			LCD_Line(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x + delta, 1, color24);
		}
	}
}

void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24)
{
	LCD_Rect_Fill(x + r, y, length - 2 * r, width, color24);
	LCD_Circle_Fill_Helper(x + length - r - 1, y + r, r, 1, width - 2 * r - 1, color24);
	LCD_Circle_Fill_Helper(x + r, y + r, r, 2, width - 2 * r - 1, color24);
}


void LCD_Bright(uint8_t bright)
{
	SSD1963_WriteCommand(0xBE);  // PWM configuration
	SSD1963_WriteData(0x08);     // set PWM signal frequency to 170Hz when PLL frequency is 100MHz
	SSD1963_WriteData(bright);   // PWM duty cycle
	SSD1963_WriteData(0x01);
}

//static void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24)
//{
//	uint8_t  *bitmap = font -> bitmap;
//	uint16_t bo = glyph -> bitmapOffset;
//	uint8_t bits = 0, bit = 0;
//	uint16_t set_pixels = 0;
//	uint8_t  cur_x, cur_y;
//	for(cur_y = 0; cur_y < glyph -> height; cur_y++)
//	{
//		for(cur_x = 0; cur_x < glyph -> width; cur_x++)
//		{
//			if(bit == 0)
//			{
//				bits = (*(const unsigned char *)(&bitmap[bo++]));
//				bit  = 0x80;
//			}
//			if(bits & bit)
//			{
//				set_pixels++;
//			}
//			else if (set_pixels > 0)
//			{
//				LCD_Rect_Fill(x + (glyph -> xOffset + cur_x - set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
//				set_pixels = 0;
//			}
//			bit >>= 1;
//		}
//		if (set_pixels > 0)
//		{
//			LCD_Rect_Fill(x + (glyph -> xOffset + cur_x-set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
//			set_pixels = 0;
//		}
//	}
//}
//
//void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24)
//{
//	int16_t cursor_x = x;
//	int16_t cursor_y = y;
//	GFXfont font;
//	memcpy((&font), (p_font), (sizeof(GFXfont)));
//	for(uint16_t text_pos = 0; text_pos < strlen(text); text_pos++)
//	{
//		char c = text[text_pos];
//		if(c == '\n')
//		{
//			cursor_x = x;
//			cursor_y += font.yAdvance * size;
//		}
//		else if(c >= font.first && c <= font.last && c != '\r')
//		{
//			GFXglyph glyph;
//			memcpy((&glyph), (&font.glyph[c - font.first]), (sizeof(GFXglyph)));
//			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
//			cursor_x += glyph.xAdvance * size;
//		}
//	}
//}
