
#include "GETime.h"
#include <chrono>
#include <thread>

int64 CGETime::GetTimeNow()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now =
		std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void CGETime::Sleep(int64 milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}