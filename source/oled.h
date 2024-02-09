/*
 * oled.h
 *
 *  Created on: 09.02.2019
 *      Author: daniel
 */

#ifndef OLED_H_
#define OLED_H_

#include "fsl_i2c.h"

#include <stdint.h>
#include <stdlib.h>

extern const unsigned char LogoKI [];

#define SSD_1306
//#define  SH_1106


//#define __SET_COL_START_ADDR() 	{OLED_Write_Byte(0x02, OLED_CMD); OLED_Write_Byte(0x10, OLED_CMD);}
#define __SET_COL_START_ADDR() 	{OLED_Write_Byte(0x00, OLED_CMD); OLED_Write_Byte(0x10, OLED_CMD);}

#define OLED_CMD    		 0
#define OLED_DAT    		 1

#define OLED_WIDTH    	     128
#define OLED_HEIGHT          64

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x3C


void OLED_Write_Byte(uint8_t chData, uint8_t chCmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void OLED_Clear_Screen(uint8_t chFill);
void OLED_Draw_Point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint);
uint8_t OLED_Get_Point(uint8_t chXpos, uint8_t chYpos);
void OLED_Draw_Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void OLED_Draw_Dotline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void OLED_Draw_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t chPoint);
void OLED_Draw_Fill_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t chPoint);
void OLED_Invert_Rect(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
void OLED_Draw_Circle(uint8_t x0, uint8_t y0, uint8_t radius);
void OLED_Draw_Bitmap(const uint8_t *pchBmp);
void OLED_Puts(uint8_t x, uint8_t y, char *text);
void OLED_Init(I2C_Type *base);

#endif /* OLED_H_ */
