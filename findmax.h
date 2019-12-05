/*
	This module find maximal values of input array and output indexs of this array 
	if their values greater then K % from maximal.

	Autor: Eliseev R.V.
	Date: 2019

*/

#ifndef FIND_MAX_H
#define FIND_MAX_H

#define MAX_DIGITS_IN_ARRAY	8

typedef struct {
	uint8_t list[MAX_DIGITS_IN_ARRAY];
	uint8_t len;
} list8_t;

int find_max(const float in_array[], uint8_t in_N, uint8_t in_K, list8_t* out_list);

#endif // FIND_MAX_H
