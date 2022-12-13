
#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>  
#include <assert.h>  

#include <string>  
#include <iostream>  
#include <sstream>  

// I saw this typing in rust and casey's stream, i really like it
typedef float	  f32;
typedef double   f64;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef uint8_t  byte;


typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;


#define HEADER 	"\033[95m"
#define OKBLUE 	"\033[94m"
#define OKCYAN 	"\033[96m"
#define OKGREEN	"\033[92m"
#define WARNING	"\033[93m"
#define FAIL 		"\033[91m"
#define ENDC 		"\033[0m"
#define PRINTBOLD 		"\033[1m"
#define UNDERLINE "\033[4m"

#define RED(msg) 	FAIL 	msg ENDC
#define GREEN(msg)	OKGREEN msg ENDC

// To be used when inside function and the data "persists" trough multiple calls (makes it ease to find later)