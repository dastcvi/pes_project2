/* Author:   Alex St. Clair
 * Filename: uart_driver.h
 * Created:  11-25-18
 * Target:   FRDM-KL25Z
 *
 * This file declares functions to implement both a blocking
 * and a non-blocking driver for the UART module in the
 * MKL25Z128VLK4
 */

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdbool.h>

#define PORT_ALT_2		0b010
#define UART_CLK_OSC	0b10

/* initialize the uart in blocking mode */
void init_uart_blocking(void);

/* checks if the transmitter is available */
bool tx_available(void);

/* transmits a char assuming the transmitter is available */
void tx_char(char data);

/* waits until the transmitter is available and transmits a char */
void tx_blocking(char data);

/* checks if the receiver has data */
bool rx_available(void);

/* reads back the data from the receiver */
char rx_char(void);

/* blocks until the receiver has data, then returns the data */
char rx_blocking(void);

#endif
