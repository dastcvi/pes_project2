/* Author:   Alex St. Clair
 * Filename: circular_buffer.c
 * Created:  11-23-18
 * Targets:  Linux, FRDM-KL25Z
 * 
 * This file implements basic testing of the circular buffer
 * without C-Unit
 */

#include "../inc/circular_buffer.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{
	bool success = true;

	ring_t * test_ring = NULL;
	test_ring = ring_init(3);

	if (test_ring == NULL) {
		printf("Init error\n");
		return -1;
	}
	
	printf("Alloc ok\n");

	char temp_char = '\0';

	success &= (0 == ring_size(test_ring));
	success &= ring_push(test_ring,'1');
	success &= ring_push(test_ring,'2');
	success &= (2 == ring_size(test_ring));
	success &= ring_push(test_ring,'3');
	success &= (3 == ring_size(test_ring));
	success &= ~ring_push(test_ring,'4');
	success &= (3 == ring_size(test_ring));
	success &= ring_pop(test_ring, &temp_char);
	success &= ('1' == temp_char);
	success &= ring_push(test_ring,'5');
	success &= (3 == ring_size(test_ring));
	success &= ring_pop(test_ring, &temp_char);
	success &= ('2' == temp_char);
	success &= ring_pop(test_ring, &temp_char);
	success &= ('3' == temp_char);
	success &= ring_pop(test_ring, &temp_char);
	success &= ('5' == temp_char);
	success &= (0 == ring_size(test_ring));
	success &= ~ring_pop(test_ring, &temp_char);
	success &= (0 == ring_size(test_ring));
	success &= ring_push(test_ring, '6');
	success &= ring_push(test_ring, '7');
	success &= ring_push(test_ring, '8');
	success &= ~ring_push(test_ring, '9');
	success &= ring_pop(test_ring, &temp_char);
	success &= ('6' == temp_char);
	success &= ring_push(test_ring, 'a');
	success &= ring_pop(test_ring, &temp_char);
	success &= ('7' == temp_char);
	success &= ring_pop(test_ring, &temp_char);
	success &= ('8' == temp_char);
	success &= ring_pop(test_ring, &temp_char);
	success &= ('a' == temp_char);

	if (success) {
		printf("Test cases ok\n");
	} else {
		printf("Tests failed\n");
	}

	ring_destroy(test_ring);

	printf("Freed allocated memory\n");

	return 1;
}