#include "common.h"
#include <iostream>
#include <array>
#include <vector>


namespace std {
	ostream& operator<<(ostream& os, const vector<int> v)
	{
		os << "[";
		for (auto& i : v)
		{
			if (i == v.back())
				os << i << "";
			else 
				os << i << ", ";
		}
		os << "]";
		return os;
	}
}


constexpr int n = 20;

int main() {
	std::vector<int> v;
	std::array<int,n> a{};

	for (size_t i = 0; i <  n; i++)
	{
		v.emplace_back(i);
	}
	auto ve2 = v[2];
	auto ve9 = v[9];

	std::cout << v << "\n";
}