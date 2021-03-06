/* Author:   Alex St. Clair
 * Filename: main.c
 * Created:  11-25-18
 * Target:   FRDM-KL25Z
 *
 * This is the main file for the embedded uart application
 * and driver demos for ECEN 5813 Project 2.
 *
 * Updating the defines will change
 */

#include "uart_driver_blocking.h"
#include "uart_driver_nonblocking.h"
#include "character_report.h"
#include "MKL25Z4.h"

//#define RUN_BLOCKING_DEMO
//#define RUN_NONBLOCKING_DEMO
#define RUN_APPLICATION

#define RED_LED_PINB		18	/* red LED is on PB18 */

static char user_char = '\0';

void red_led_init(void)
{
	/* Enable PORTB clock */
	SIM->SCGC5 |= (uint32_t) SIM_SCGC5_PORTB_MASK;

	/* mux */
	PORTB->PCR[RED_LED_PINB] |= (uint32_t) 1 << PORT_PCR_MUX_SHIFT;

	/* set as output */
	GPIOB->PDDR |= (uint32_t) 1 << RED_LED_PINB;

	/* start low (LED on) */
	GPIOB->PCOR |= (uint32_t) 1 << RED_LED_PINB;
}

void red_led_toggle(void)
{
	GPIOB->PTOR |= (uint32_t) 1 << RED_LED_PINB;
}

int main(void)
{
#ifdef RUN_BLOCKING_DEMO
	init_uart_blocking();
	red_led_init();

	/* endlessly echo chars */
	while (1)
	{
		user_char = rx_blocking();
		tx_blocking(user_char);
		red_led_toggle();
	}
#endif

#ifdef RUN_NONBLOCKING_DEMO
	init_uart_nonblocking();
	red_led_init();

	while (1)
	{
		if (rx_nonblocking(&user_char))
		{
			tx_nonblocking(user_char);
		}
		red_led_toggle();

	}
#endif

#ifdef RUN_APPLICATION
	init_uart_nonblocking();
	red_led_init();

	while (1)
	{
		if (check_for_update())
		{
			transmit_update();
		}

		if (rx_overrun)
		{
			transmit_error();
		}

		red_led_toggle();
	}
#endif

    return 0;
}
