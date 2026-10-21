#include "stm32f4xx.h"
#include <stdint.h>

#include "systic.h"
#include "led.h"

#define SYSTCLK_FREQ			(16000000U)



int main(void)
{

	led_init();
	while(1)
	{

		led_active();
		systic_delay_ms(1000,SYSTCLK_FREQ);
		led_diminish();
		systic_delay_ms(1000,SYSTCLK_FREQ);

	}


	return 0;
}

