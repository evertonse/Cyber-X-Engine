#include "../src/utils/common.h"
#include "../src/math/vec.cpp"
#include <iostream>
#include <array>
#include <vector>
#include <cassert>

void test_vec_derived() {
	std::cout<<  "test_vec_derived" << '\n';
	cyx::vec3 v{1,2,3};
	
	std::cout << v.x << v.y << v.z << '\n';
	std::cout << v.r << v.g << v.b << '\n';
	std::cout << v * v<< '\n';
	std::cout << v.norm() << '\n';
	
	system("pause");
}

void test_vec_gerenic() {
	std::cout<< "test_vec_gerenic" << '\n';
	cyx::vec<int,9> v;
	for (auto& item : v) {
		item = 2; 
	}

	std::cout 
		<< "  v * 4.5 "		<<  v * 4.5				<< "\n"
		<< " -v"					<< -v 					<< "\n"
		<< " v + v"				<< v + v				 	<< "\n"
		<< " v - v"				<< v - v 				<< "\n"
		<< " v * v"				<< v * v					<< "\n"
		<< " v.dot(v)"			<< v.dot(v) 			<< "\n"
		<< " v.mag()"			<< v.mag()				<< "\n"
		<< " v.mag2()"			<< v.mag2()				<< "\n"
		<< " v.norm()"			<< v.norm() 			<< "\n"
		<< " v.norm().mag()"	<< v.norm().mag() 	<< "\n"
		<< " v.dim()"			<< v.dim() 				<< "\n";
	

		assert(-v == v * (-1));
		assert( v + v == v * 2);
		assert( (v - v)[0] == 0);
		//assert( v * v);
		assert( v.dot(v) == v.mag2());
		//assert( v.mag());
		assert( v.norm().mag() == 1);
		assert( v.dim() == 9);
	std::cout << "[TEST] passed !\n";
	system("pause");
}


int main() {
	test_vec_gerenic();
	test_vec_derived();

}