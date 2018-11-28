/* Author:   Alex St. Clair
 * Filename: uart_driver_blocking.c
 * Created:  11-25-18
 * Target:   FRDM-KL25Z
 *
 * This file implements functions to implement a blocking driver for the
 * UART module in the MKL25Z128VLK4
 */

#include "uart_driver_blocking.h"
#include "MKL25Z4.h"

void init_uart_blocking(void)
{
	/* Enable PORTA clock */
	SIM->SCGC5 |= (uint32_t) SIM_SCGC5_PORTA_MASK;

	/* UART0_RX: PTA1, ALT2 */
	PORTA->PCR[1] |= (uint32_t) PORT_ALT_2 << PORT_PCR_MUX_SHIFT;

	/* UART0_TX: PTA2, ALT2 */
	PORTA->PCR[2] |= (uint32_t) PORT_ALT_2 << PORT_PCR_MUX_SHIFT;

	/* set UART0 clock to MCGPLLCLK (48 MHz) */
	SIM->SOPT2 |= (uint32_t) UART_CLK_PLL << SIM_SOPT2_UART0SRC_SHIFT;

	/* enable MCGPLLCLK */
	MCG->C5 |= (uint8_t) 1 << MCG_C5_PLLCLKEN0_SHIFT;

	/* enable UART0 clock */
	SIM->SCGC4 |= (uint32_t) 1 << SIM_SCGC4_UART0_SHIFT;

	/* ensure receiver and transmitter not enabled */
	UART0->C2 &= ~((uint8_t) (UART_C2_TE_MASK | UART_C2_RE_MASK));

	/* baud_prescale = baud_clock / (OSR * baud)
	 * OSR = 16 (reset default)
	 * baud_clock = MCGPLLCLK / 2 = 48 MHz (startup code initializes MCGPLLCLK)
	 * for baud = 115200, then baud_prescale = 26.04
	 */
	UART0->BDH &= ~((uint8_t) UART_BDH_SBR_MASK); /* clear upper bits since 26 < 0xFF */
	UART0->BDL = (uint8_t) 26;

	/* module defaults to 8-bit, no parity, one stop bit */
	/* enable receiver and transmitter */
	UART0->C2 |= (uint8_t) (UART_C2_TE_MASK | UART_C2_RE_MASK);
}

/* checks if the transmitter is available */
bool tx_available(void)
{
	uint8_t status = UART0->S1;
	status &= UART_S1_TDRE_MASK;

	/* return the status of the transmit data register empty flag */
	return (status == UART_S1_TDRE_MASK);
}

/* transmits a char assuming the transmitter is available */
void tx_char(char data)
{
	UART0->D = (uint8_t) data;
}

/* waits until the transmitter is available and transmits a char */
void tx_blocking(char data)
{
	while (!tx_available());

	tx_char(data);
}

/* checks if the receiver has data */
bool rx_available(void)
{
	uint8_t status = UART0->S1;
	status &= UART_S1_RDRF_MASK;

	/* return the status of the read data ready flag */
	return (status == UART_S1_RDRF_MASK);
}

/* reads back the data from the receiver */
char rx_char(void)
{
	char data = (char) UART0->D;

	return data;
}

/* blocks until the receiver has data, then returns the data */
char rx_blocking(void)
{
	while (!rx_available());

	return rx_char();
}
