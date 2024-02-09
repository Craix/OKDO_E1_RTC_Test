#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

#include "oled.h"

#define I2C_OLED ((I2C_Type *)I2C1_BASE)

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

	PRINTF("Hello world \r\n");

	while(1)
	{
		RTC_GetDatetime(RTC_PERIPHERAL, &RTC_dateTimeStruct);

		sprintf(sbuff, "%2d:%02d:%02d", RTC_dateTimeStruct.hour, RTC_dateTimeStruct.minute, RTC_dateTimeStruct.second);
		OLED_Puts(0,0, sbuff);

		sprintf(sbuff, "%4d-%02d-%02d", RTC_dateTimeStruct.year, RTC_dateTimeStruct.month, RTC_dateTimeStruct.day);
		OLED_Puts(0,1, sbuff);

		OLED_Refresh_Gram();
	}

	return 0 ;
}
