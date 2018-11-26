/* Author:   Alex St. Clair
 * Filename: circular_buffer.c
 * Created:  11-23-18
 * Targets:  Linux, FRDM-KL25Z
 * 
 * This file implements basic testing of the circular buffer
 * with C-Unit
 *
 * The test structure is based on the example found here:
 *   http://cunit.sourceforge.net/example.html
 */

#include "../inc/circular_buffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <CUnit/Basic.h>

int init_suite1(void)
{
	return 0;
}

int clean_suite1(void)
{
	return 0;
}

void test_init(void)
{
	ring_t * test_ring = NULL;

	/* ensure proper starting conditions */
	CU_ASSERT(test_ring == NULL);

	/* size too large */
	test_ring = ring_init(MAX_RING+1);
	CU_ASSERT(test_ring == NULL);

	/* size == 0 */
	test_ring = ring_init(0);
	CU_ASSERT(test_ring == NULL);

	/* size at max */
	test_ring = ring_init(MAX_RING);
	CU_ASSERT(test_ring != NULL);
	ring_destroy(test_ring);

	/* size at min */
	test_ring = ring_init(1);
	CU_ASSERT(test_ring != NULL);
	ring_destroy(test_ring);
}

void test_circle(void)
{
	char temp_char = '\0';

	ring_t * test_ring = NULL;

	/* ensure proper starting conditions */
	CU_ASSERT(test_ring == NULL);
	CU_ASSERT(0 == ring_size(test_ring));
	CU_ASSERT(NULL != (test_ring = ring_init(3)));

	/* fill buffer */
	CU_ASSERT(0 == ring_size(test_ring));
	CU_ASSERT(ring_push(test_ring,'1'));
	CU_ASSERT(ring_push(test_ring,'2'));
	CU_ASSERT(ring_push(test_ring,'3'));
	CU_ASSERT(3 == ring_size(test_ring));

	/* ensure no more adds */
	CU_ASSERT(0 == ring_push(test_ring,'4'));
	CU_ASSERT(3 == ring_size(test_ring));

	/* remove element and add another (requiring circular indexing) */
	CU_ASSERT(ring_pop(test_ring, &temp_char));
	CU_ASSERT('1' == temp_char);
	CU_ASSERT(ring_push(test_ring,'5'));

	/* empty buffer */
	CU_ASSERT(ring_pop(test_ring, &temp_char));
	CU_ASSERT('2' == temp_char);
	CU_ASSERT(ring_pop(test_ring, &temp_char));
	CU_ASSERT('3' == temp_char);
	CU_ASSERT(ring_pop(test_ring, &temp_char));
	CU_ASSERT('5' == temp_char);

	/* ensure empty */
	CU_ASSERT(0 == ring_size(test_ring));
	CU_ASSERT(~ring_pop(test_ring, &temp_char));

	ring_destroy(test_ring);
}

int main()
{
	CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
	{
		return CU_get_error();
	}

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "test of ring init", test_init)) ||
	    (NULL == CU_add_test(pSuite, "test of circular indexing", test_circle)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}