#pragma once
#include <array>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>

#include "..\utils\common.h"
//#include "common.h"
#define NUMCPP_NO_USE_BOOST // we don't need to define this, because we already include this definition in the build. But intelisense is confused so....
#undef NUMCPP_USE_MULTITHREAD // enables STL parallel execution policies throughout the library. Using multi-threaded algorithms can have negative performace impact for "small" array operations and should usually only be used when dealing with large array operations.
#include "NumCpp.hpp"
#include "Fastor.h"


using namespace nc;
namespace cyx {

	template<typename T>
	auto ortho(T left, T right, T bottom,T top, T near, T far ) -> NdArray<f32> {
		
		return {
			{ 2.0f/(f32)(right-left),  0.0f,  									0.0f, 										((f32)(-right - left))  / ((f32)(right - left))   },
			{ 0.0f,  									 2.0f/(f32)(top-bottom),  0.0f, 										((f32)(-top 	- bottom))/ ((f32)(top   - bottom)) },
			{ 0.0f,  									 0.0f,  									2.0f/(f32)(far-near),			((f32)(-far 	- near))  / ((f32)(far   - near))   },
			{ 0.0f,  							     0.0f,  									0.0f,  				   					 1.0f },
		};	
	}
	

	auto rotation2D(f32 angle) -> NdArray<f32> {
		return {
			{ cos(angle),-sin(angle)},
			{ sin(angle), cos(angle)}
		};	
	}

	
	auto scale2D(f32 scale) -> NdArray<f32> {
		return {
			{ scale,.0f},
			{ .0f, scale}
		};	
	}
	// using homogenous coordiantes
	auto translation(std::initializer_list<f32> translate) -> NdArray<f32> {
		Shape shape (translate.size() + 1,translate.size()+1);
		NdArray<f32> A(shape);

		A(shape.rows-1,shape.cols-1) = 1.0f;
		
		size_t i = 0;
		for (auto& value : translate) {
			A(i, shape.cols-1) = value;
			i =+ 1;
		}
		return A;
	}
}
