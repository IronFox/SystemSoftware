#ifndef performance_timerH
#define performance_timerH

#include <time.h>

namespace timer
{
	typedef unsigned long long	time_t;
	
	time_t	toNanoSeconds(const timespec&t)
	{
		return (unsigned long long)t.tv_sec * 1000000000ULL + t.tv_nsec;
	}
	
	time_t	now()
	{
		timespec result;
		clock_gettime(CLOCK_REALTIME,&result);
		return toNanoSeconds(result);
	}
	
	time_t	getFrequency()
	{
		timespec res;
		clock_getres(CLOCK_REALTIME, &res);
		return 1000000000ULL / toNanoSeconds(res);
	}
	
	double	toSecondsd(time_t t)
	{
		return double(t) / 1000000000.0;
	}

	float	toSecondsf(time_t t)
	{
		return float(t) / 1000000000.0f;
	}
	
}

#endif
