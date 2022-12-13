#include <iostream>
#include <chrono>
#include <ctime>

#if defined(CX_DEBUG_BUILD)
	#define CX_LOG(msg)

#else
	#define CX_LOG(msg)

#endif

struct Timer {
	Timer();
	~Timer();

	std::time_point _start,_end;
};

struct Log {
	Log(const char* msg = "");
};