/*
	This module find maximal values of input array and output indexs of this array 
	if their values greater then K % from maximal.

	Autor: Eliseev R.V.
	Date: 2019

*/

#include <stdint.h>
#include "findmax.h"

#ifndef NULL
	#define NULL	0ul
#endif

// in_array[]: input array of float data
// in_N: num elements in input array
// in_K: limit value in % 
// out_presult: pointer on result struct
// return: 0 - OK, 1 - wrong input data
int find_max(const float in_array[], uint8_t in_N, uint8_t in_K, list8_t* out_list)
{
	int i;

	if ((in_N > MAX_DIGITS_IN_ARRAY) || (in_N == 0))
		return 1;
	
	if ((in_array == NULL) || (out_list == NULL))
		return 1;
	
	if (in_K > 100)
		return 1;

	float max = in_array[0];
	for (i = 1; i < in_N; ++i)
   		if (in_array[i] > max) max = in_array[i];	
	
	out_list->len = 0;
	float low_limit = max * (float)(100-in_K) / 100.0;
	for (i = 0; i < in_N; ++i)
  		if (in_array[i] >= low_limit)
			out_list->list[out_list->len++] = i;
	
	return 0;
}
