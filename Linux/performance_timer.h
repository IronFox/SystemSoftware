#ifndef performance_timerH
#define performance_timerH

#include <time.h>

/* link with librt.a (add -lrt to your link line) */

namespace timer
{
	typedef unsigned long long	time_t;
	
	inline time_t	toNanoSeconds(const timespec&t)
	{
		return (unsigned long long)t.tv_sec * 1000000000ULL + t.tv_nsec;
	}
	
	inline time_t	now()
	{
		timespec result;
		clock_gettime(CLOCK_REALTIME,&result);
		return toNanoSeconds(result);
	}
	
	inline time_t	getFrequency()
	{
		timespec res;
		clock_getres(CLOCK_REALTIME, &res);
		return 1000000000ULL / toNanoSeconds(res);
	}
	
	inline double	toSecondsd(time_t t)
	{
		return double(t) / 1000000000.0;
	}

	inline float	toSecondsf(time_t t)
	{
		return float(t) / 1000000000.0f;
	}
	
}

#endif
