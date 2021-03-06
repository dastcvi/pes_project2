/* Author:   Alex St. Clair
 * Filename: uart_driver_nonblocking.h
 * Created:  11-28-18
 * Target:   FRDM-KL25Z
 *
 * This file declares functions to implement a nonblocking driver for the
 * UART module in the MKL25Z128VLK4
 */

#ifndef UART_DRIVER_NONBLOCKING_H
#define UART_DRIVER_NONBLOCKING_H

#include <stdbool.h>

/* determine whether or not this driver echos chars as they're received */
#define ENABLE_ECHO

#define PORT_ALT_2		2
#define UART_CLK_PLL	1

#define TX_BUFFER_SIZE	1024
#define RX_BUFFER_SIZE	256

extern bool rx_overrun;

/* initialize the uart in nonblocking mode */
void init_uart_nonblocking(void);

/* transmit a char by pushing it onto the tx buffer and enabling the tx interrupt */
bool tx_nonblocking(char data);

/* check if a character is ready to be received it, and grab it if so */
bool rx_nonblocking(char * data);

/* function called by the UART0 ISR for tx */
void isr_tx(void);

/* function called by the UART0 ISR upon rx */
void isr_rx(void);

#endif
