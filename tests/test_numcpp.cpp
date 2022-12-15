#include <iostream>
#define NUMCPP_NO_USE_BOOST
#include "NumCpp.hpp"

/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
using namespace nc;
auto main(int argc, char *argv[]) -> int
{
	auto&& A = NdArray<int>({
		{1,2,3},
		{3,4,5},
		{7,8,9},
	}); 

	A = A + 1;
	std::cout << A << std::endl;
	A = A(A.rSlice(), 1) * 10;
	std::cout << A << std::endl;
	//A(A.rSlice(), {1}) += 1;

	return 0;
}