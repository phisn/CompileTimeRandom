#include <iostream>

#include "CompileTimeRandom.h"

int main()
{
	// just iterating over the same macro will always result in same
	// number because the internal state is only updated for each occurance
	// of the DYC_RAND_... macro

	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
	std::cout << DYC_RAND_NEXT_BETWEEN(1, 11) << std::endl;
}
