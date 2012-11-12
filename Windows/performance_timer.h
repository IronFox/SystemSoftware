#ifndef performance_timerH
#define performance_timerH

#include <Windows.h>

namespace timer
{
	typedef unsigned long long	time_t;

	inline time_t	now()
	{
		time_t result;
		QueryPerformanceCounter((LARGE_INTEGER*)&result);
		return result;
	}
	
	inline time_t	getFrequency()
	{
		static time_t frequency = 0;
		if (!frequency)
			QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return frequency;
	}
	
	inline double	toSecondsd(time_t t)
	{
		return double(t) / double(getFrequency());
	}

	inline float	toSecondsf(time_t t)
	{
		return float(t) / float(getFrequency());
	}
	
}

#endif
