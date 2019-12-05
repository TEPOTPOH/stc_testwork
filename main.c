#include <stdio.h>
#include <stdint.h>
#include "findmax.h"
#include "findmax_test.h"

int main(void)
{
	int ok = findmax_test();
	
	printf("\n\nModule 'find_max' %s\n", ok ? "Passed": "Failed");

	return 0;
}