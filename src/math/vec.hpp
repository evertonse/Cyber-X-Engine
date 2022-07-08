#include "..\utils\common.h"
#include <array>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>

namespace cyx {

	template <class T, u32 DIM>
	struct vec {
	
	public:
		std::array<T,DIM> numbers;
	
	public:
		vec() {}
		vec(std::initializer_list<T> values){
			size_t index = 0;
			for (auto& val : values) {
				numbers[index++] = val;
			}
		}
		vec& operator=(const vec& v) = default;
		
		/*==== vec operations ====*/
		f32 mag() const { return f32(std::sqrt(mag2())); }
		
		f32 mag2() const { 
			// just in case we donnst want a f32 here and instead use T, we'll leave the 
			// startic casting
			auto acc = static_cast<f32>(0.0f);
			for (auto& n : numbers) {
				acc += (n*n);
			}
			return static_cast<f32>(acc); 
		}

		vec<f32,DIM> norm() const { 
			// just in case we donnst want a f32 here and instead use T, we'll leave the 
			f32 scale = 1 / mag(); 
			vec<f32,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = static_cast<f32>((*this)[i]) * scale;
			}
			return new_vec;
		}
		//vec  perp() const { return vec(-y, x); }
		//vec  floor() const { return vec(std::floor(x), std::floor(y)); }
		//vec  ceil() const { return vec(std::ceil(x), std::ceil(y)); }
		//vec  max(const vec& v) const { return vec(std::max(x, v.x), std::max(y, v.y)); }
		//vec  min(const vec& v) const { return vec(std::min(x, v.x), std::min(y, v.y)); }
		//vec  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
		//vec  polar() { return { mag(), std::atan2(y, x) }; }
		
		T dot(const vec& other) const {
			auto acc = static_cast<T>(0);

			for (size_t i = 0; i < DIM; i++) {
				acc += other[i] * (*this)[i];
			}
			return acc; 
		}

		T& operator[]  (i32 index) { return numbers[index]; }
		const T& operator[]  (i32 index) const { return numbers[index]; }

		/*==== Operator Overloading for other vec ====*/
		vec  operator +  (const vec& other) const { 		
			vec new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = other[i] + (*this)[i];
			}
			return new_vec;
		}

		vec  operator -  (const vec& other) const { 		
			vec new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = other[i] - (*this)[i];
			}
			return new_vec; 
		}

		vec  operator *  (const vec& other) const { 		
			vec new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = other[i] * (*this)[i];
			}
			return new_vec; 
		}

		/*==== Operator Overloading for Integral Type ====*/
		vec<T,DIM>  operator +  (const T& rhs) const { 		
			vec<T,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = (*this)[i] + rhs;
			}
			return new_vec; 
		}
		vec<T,DIM>  operator -  (const T& rhs) const { 		
			vec<T,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = (*this)[i] - rhs;
			}
			return new_vec; 
		}

		vec<T,DIM>  operator *  (const T& rhs) { 		
			vec<T,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = (*this)[i] * rhs;
			}
			return new_vec; 
		}
		vec<T,DIM>  operator /  (const T& rhs) const { 		
			vec<T,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = (*this)[i] / rhs[i];
			}
			return new_vec; 
		}

		// identity operator
		vec  operator +  () const { 
			vec new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = +(*this)[i];
			}
			return new_vec; 
		}

		// negates operator
		vec  operator -  () const { 
			vec new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = -(*this)[i];
			}
			return new_vec; 
		}

		/*==== Operator Overloading for booleans ====*/
		bool operator==(const vec& other) {
			for (size_t i = 0; i < DIM; i++) {
				if((*this)[i] != other[i])
					return false;  
			}
			return true; 
		}
	
		bool operator != (const vec& other) const { return !this->operator==(other); }

		
		
		/*==== Utilities for vec ====*/
		friend std::ostream& operator << (std::ostream& os, const vec& rhs) {
			// TODO(Everton): change this to be string stream then pass to the ostream, ok??
			os << rhs.str(); return os; 
		}

		auto dim() const -> u32 {
			return DIM;
		}

		auto str() const -> const std::string  { 
			std::stringstream s;

			s << "vec" << DIM << "(";
			for (size_t i = 0; i < DIM-1; i++) {
				s << this->numbers[i] << ", ";
			}
			s << numbers[DIM-1] << ")";
			return s.str();
		}
		
		operator vec<f32,DIM>() const { 
			vec<f32,DIM> new_vec;
			for (size_t i = 0; i < DIM; i++) {
				new_vec[i] = static_cast<f32>((*this)[i]);
			}
			return new_vec; 
		}

		T* begin() { return (&numbers[0]); }
		T* end()   { return (&numbers[200]); } //
		
		T* data()  { return (numbers); }
	};

	struct vec2 : public vec<f32,2> {
		using MyBase   = vec<f32,2>;
		
		union {
			struct {	f32 &x,&y;};
			struct {	f32 &r,&g;};
		};
		
		vec2() :MyBase(),x(numbers[0]),y(numbers[1]){ };
		vec2(std::initializer_list<f32> vals) :MyBase(vals),x(numbers[0]),y(numbers[1]){ };
	};

	struct vec3 : public vec<f32,3> {
		using MyBase   = vec<f32,3>;
		
		union {
			struct {	f32 &x,&y,&z;};
			struct {	f32 &r,&g,&b;};
		};
		
		vec3() :MyBase(),x(numbers[0]),y(numbers[1]),z(numbers[2]){ };
		vec3(std::initializer_list<f32> vals) :MyBase(vals),x(numbers[0]),y(numbers[1]),z(numbers[2]){ };
	};

	struct vec4 : public vec<f32,4> {
		using MyBase   = vec<f32,4>;
		
		union {
			struct {f32 &x,&y,&z,&w;};
			struct {f32 &r,&g,&b,&a;};
		};
		
		vec4() :MyBase(),x(numbers[0]),y(numbers[1]),z(numbers[2]),w(numbers[2]){ };
		vec4(std::initializer_list<f32> vals) :MyBase(vals),x(numbers[0]),y(numbers[1]),z(numbers[2]),w(numbers[2]){ };
	};
}
