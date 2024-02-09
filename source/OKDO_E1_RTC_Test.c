#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "oled.h"

#include "arm_math.h"

#define I2C_OLED ((I2C_Type *)I2C1_BASE)

volatile bool alarm = false;

void Analog_Clock(uint8_t x, uint8_t y, uint8_t radius, rtc_datetime_t *datetime)
{

	uint8_t radius_s=radius;
	uint8_t radius_m=radius*0.95;
	uint8_t radius_h=radius*0.5;
	uint8_t radius_p=radius-4;

	float h, m, s, p;

	s=(2*PI*datetime->second)/60.0;
	m=(2*PI*datetime->minute)/60.0;
	h=(2*PI*((datetime->hour % 12)+(datetime->minute/60.)))/12.0;

	OLED_Clear_Screen(0);

	for(int i=0; i<60;i++)
	{
		p=(2*PI*i)/60.0;

		if(i % 5)
		{
			 OLED_Draw_Point(x+radius*sin(p), y-radius*cos(p), 1);
		}
		else
		{
			 OLED_Draw_Line(x+radius_p*sin(p), y-radius_p*cos(p), x+radius*sin(p), y-radius*cos(p));
		}
	}

	OLED_Draw_Line(x,y, x+radius_s*sin(s), y-radius_s*cos(s));
	OLED_Draw_Line(x,y, x+radius_m*sin(m), y-radius_m*cos(m));
	OLED_Draw_Line(x,y, x+radius_h*sin(h), y-radius_h*cos(h));

}

void RTC_IRQHANDLER()
{
	if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag)
	{
		alarm=true;
		/* Clear alarm flag */
		RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
	}
}

/*
 * @brief Application entry point.
 */

int main(void)
{
	char sbuff[32];

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	#endif

	/* Initialize OLED */
	OLED_Init(I2C_OLED);

	while(1)
	{
		RTC_GetDatetime(RTC_PERIPHERAL, &RTC_dateTimeStruct);

		Analog_Clock(96 , 32, 31 ,&RTC_dateTimeStruct);

		sprintf(sbuff, "%2d:%02d:%02d", RTC_dateTimeStruct.hour, RTC_dateTimeStruct.minute, RTC_dateTimeStruct.second);
		OLED_Puts(0,0, sbuff);

		sprintf(sbuff, "%4d-%02d-%02d", RTC_dateTimeStruct.year, RTC_dateTimeStruct.month, RTC_dateTimeStruct.day);
		OLED_Puts(0,1, sbuff);

		if(alarm)
		{
			OLED_Puts(0, 3, "ALARM!");
		}

		OLED_Refresh_Gram();
	}

	return 0 ;
}
