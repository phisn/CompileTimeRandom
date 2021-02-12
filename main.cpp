#include <iostream>

#include "CompileTimeRandom.h"

int main()
{
	// just iterating over the same macro will always result in same
	// number because the internal state is only updated for each occurance
	// of the DYC_RAND_... macro

	int array[50];

	Dynlec::CTRandomStream<50>::Call([&array](uint64_t index, uint64_t n)
		{ 
			array[index] = n;
		});
}
