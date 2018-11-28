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

#include "uart_driver.h"
#include "MKL25Z4.h"

#define RUN_BLOCKING_DEMO
//#define RUN_NONBLOCKING_DEMO
//#define RUN_APPLICATION

volatile static char user_char = '\0';

int main(void)
{
#ifdef RUN_BLOCKING_DEMO
	init_uart_blocking();

	/* endlessly echo chars */
	while (1)
	{
		user_char = rx_blocking();
		tx_blocking(user_char);
	}
#endif

#ifdef RUN_NONBLOCKING_DEMO
	while (1);
#endif

#ifdef RUN_APPLICATION
	while (1);
#endif

    return 0;
}
