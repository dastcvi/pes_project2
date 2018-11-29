/* Author:   Alex St. Clair
 * Filename: character_report.h
 * Created:  11-28-18
 * Target:   FRDM-KL25Z
 *
 * This file declares functions to report on the characters that
 * have been received over UART
 */

#ifndef CHARACTER_REPORT_H
#define CHARACTER_REPORT_H

#include <stdbool.h>

/* checks if characters have been received, and updates the count when they have */
bool check_for_update(void);

/* creates an updated report to transmit */
void transmit_update(void);

/* blocks until the transmitter can report an error, then reports it */
void transmit_error(void);

#endif
