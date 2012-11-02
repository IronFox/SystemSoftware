#include <Windows.h>

namespace timer
{
	typedef LARGE_INTEGER	time_t;
	
	time_t	now()
	{
		time_t result;
		VERIFY(QueryPerformanceCounter(&result));
		return result;
	}
	
	time_t	getFrequency()
	{
		static time_t frequency = 0;
		if (!frequency)
			VERIFY(QueryPerformanceFrequency(&frequency));
		return frequency;
	}
	
	double	toSecondsd(time_t t)
	{
		return double(t) / double(getFrequency());
	}

	float	toSecondsf(time_t t)
	{
		return float(t) / float(getFrequency());
	}
	
}
