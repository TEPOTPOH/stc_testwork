/*
	This module for test findmax module.

	Autor: Eliseev R.V.
	Date: 2019

*/

#include <stdint.h>
#include "findmax_test.h"
#include "findmax.h"

#ifndef NULL
	#define NULL	0ul
#endif

#ifndef ARRAY_SIZE
	#define ARRAY_SIZE(a)	(sizeof(a)/sizeof(a[0]))
#endif

// tests debug info
#define TRACE_ON	1
#if TRACE_ON
	#include <stdio.h>
	#define TRACE(...)	printf(__VA_ARGS__)
#else
	#define TRACE(...)
#endif

typedef struct {
	float input_list[MAX_DIGITS_IN_ARRAY];
	uint8_t input_len;
	uint8_t limit_prcnt;
	uint8_t failed;
	
	uint8_t out_len;
	uint8_t out_list[MAX_DIGITS_IN_ARRAY];
} test_t;

static const test_t tests[] = {
	{ .input_list	= {3.0, 4.0, 3.58},
	  .input_len 	= 3,
	  .limit_prcnt	= 10,
	  .failed		= 0,
	  .out_len		= 1,
	  .out_list		= {1}
	},
	{ .input_list	= {3.0, 4.0, 4.05},
	  .input_len 	= 3,
	  .limit_prcnt	= 10,
	  .failed		= 0,
	  .out_len		= 2,
	  .out_list		= {1, 2}
	},
	{ .input_list	= {3.5, 3.1, 3.9, 4.0, 4.1},
	  .input_len 	= 5,
	  .limit_prcnt	= 10,
	  .failed		= 0,
	  .out_len		= 3,
	  .out_list		= {2, 3, 4}
	},
	// other tests
	{ .input_list	= {3.5, 3.1, 3.9, 4.0, 4.1},
	  .input_len 	= 5,
	  .limit_prcnt	= 1,
	  .failed		= 0,
	  .out_len		= 1,
	  .out_list		= {4}
	},
	{ .input_list	= {-2.5, 3.1, -3.9, 1.3, 0.0},
	  .input_len 	= 5,
	  .limit_prcnt	= 70,
	  .failed		= 0,
	  .out_len		= 2,
	  .out_list		= {1, 3}
	},
	{ .input_list	= {0.0, 0.0, 0.0},
	  .input_len 	= 3,
	  .limit_prcnt	= 5,
	  .failed		= 0,
	  .out_len		= 3,
	  .out_list		= {0, 1, 2}
	},
	{ .input_list	= {0xfffffff, 1342.2, 785.3},
	  .input_len 	= 3,
	  .limit_prcnt	= 65,
	  .failed		= 0,
	  .out_len		= 1,
	  .out_list		= {0}
	},
	// error tests
	{ .input_list	= {0},
	  .input_len 	= 10,	// wrong
	  .limit_prcnt	= 10,
	  .failed		= 1,
	  .out_len		= 0,
	},
	{ .input_list	= {0},
	  .input_len 	= 0,	// wrong
	  .limit_prcnt	= 10,
	  .failed		= 1,
	  .out_len		= 0, 
	},
	{ .input_list	= {0},
	  .input_len 	= 3,
	  .limit_prcnt	= 146,	// wrong
	  .failed		= 1,
	  .out_len		= 0,
	}
};


static uint8_t assert_result(const test_t* test, const list8_t* result_data)
{
	if (test->out_len != result_data->len)
		return 0;

	for(int i = 0; i < test->out_len; ++i)
		if (result_data->list[i] != test->out_list[i])
			return 0;

	// passed
	return 1;
}

static void show_result(const test_t* test, const list8_t* result_data)
{
	int i;
	TRACE("\ninput: ");
	for(i = 0; i < test->input_len; ++i)
		TRACE("[%.2f]",test->input_list[i]);
	TRACE(", %d\n", test->input_len);
	TRACE("K = %d %%\n", test->limit_prcnt);

	TRACE("result: ");
	for(i = 0; i < result_data->len; ++i)
		TRACE("[%d]",result_data->list[i]);
	TRACE(", %d", result_data->len);
}


// return 1 if all test passed, 0 - any failed
int findmax_test(void)
{
	int status, i, test_num;
	int ret = 1; // All passed
	list8_t result_data = {0};
	
	for(i = 0, test_num = 1; i < ARRAY_SIZE(tests); i++, test_num++) {
		status = find_max(tests[i].input_list,
						  tests[i].input_len, 
						  tests[i].limit_prcnt,
						  &result_data);
		// check status
		if (status == tests[i].failed) {
			uint8_t ok = 1;
			TRACE("\nTest %d", test_num);
			if (status)
				TRACE(": input data wrong");
			else {
				ok = assert_result(&tests[i], &result_data);
				show_result(&tests[i], &result_data);
			}			
			TRACE("\n%s\n", ok ? "Passed": "Failed");
			if (!ok) ret = 0;
		} else {
			TRACE("\nTest %d Failed: can't check wrong input data\n", test_num);
			ret = 0;
		}
	}
	
	status = find_max(tests[0].input_list,
					  tests[0].input_len,
					  tests[0].limit_prcnt,
					  NULL);
	TRACE("\nTest %d: input data wrong\n%s\n", test_num++, status ? "Passed": "Failed");
	if (!status) ret = 0;

	status = find_max(NULL,
					  tests[0].input_len, 
					  tests[0].limit_prcnt,
					  &result_data);
	TRACE("\nTest %d: input data wrong\n%s\n", test_num++, status ? "Passed": "Failed");
	if (!status) ret = 0;

	return ret;
}
