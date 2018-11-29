/* Author:   Alex St. Clair
 * Filename: character_report.c
 * Created:  11-28-18
 * Target:   FRDM-KL25Z
 *
 * This file implements functions to report on the characters that
 * have been received over UART
 */

#include "character_report.h"
#include "uart_driver_nonblocking.h"
#include <stdint.h>
#include <stdio.h>

static uint16_t count[256] = {0};

/* checks if characters have been received, and updates the count when they have */
bool check_for_update(void)
{
	uint8_t char_index = 0;
	bool chars_found = false;

	/* while there are chars on the rx buffer, count them */
	while (rx_nonblocking((char *) &char_index))
	{
		count[char_index]++;
		chars_found = true;
	}

	return chars_found;
}

/* creates an updated report to transmit */
void transmit_update(void)
{
	char line_str[16] = {0};
	uint16_t index = 0;
	uint8_t strindex = 0;

	for (index = 0; index < 256; index++)
	{
		if (count[index] > 0)
		{
			/* format a string for this character */
			sprintf(line_str, "%c - %u\n\r", (char) (index & 0xff), count[index]);

			/* place the string on the buffer */
			strindex = 0;
			while (strindex < 15 && line_str[strindex] != '\0')
			{
				/* this function will block if the transmit buffer fills */
				if (tx_nonblocking(line_str[strindex])) strindex++;
			}
		}
	}

	tx_nonblocking('\n');
}

/* blocks until the transmitter can report an error, then reports it */
void transmit_error(void)
{
	char err_str[] = "\n\rRX Over-run!\n\r";
	uint8_t index = 0;

	/* send the error string */
	while (err_str[index] != '\0')
	{
		/* this loop will continue until the transmission can complete */
		if (tx_nonblocking(err_str[index])) index++;
	}

	rx_overrun = false;
}
