#include <iostream>	//gain access to std::cout (also std::endl)
#include <stdlib.h>	//gain access to atoi (for string conversion)

//include our timer header
#ifdef _WIN32
	#include "../Windows/performance_timer.h"
#else
	#include "../Linux/performance_timer.h"
#endif

using namespace std;

//#define DO8
#define DO_FLOATS
#define EXECUTIONS 800000000

int main(int argc, char* argv[])
{
	

	size_t iterations = EXECUTIONS;
		#ifdef DO8
			iterations /= 8;
		#endif
	while (true)
	{
		timer::time_t t0 = timer::now();

		#ifdef DO_FLOATS
			float var = 1.f;
		#else
			int var = 1;
		#endif
		for (volatile size_t i = 0; i < iterations; i++)
		{
			#ifdef DO_FLOATS
				var *= 1.0000001f;
				#ifdef DO8
					/*1*/	var += 1.0000001f;
					/*2*/	var += 1.0000001f;
					/*3*/	var += 1.0000001f;
					/*4*/	var += 1.0000001f;
					/*5*/	var += 1.0000001f;
					/*6*/	var += 1.0000001f;
					/*7*/	var += 1.0000001f;
				#endif
			#else
				var += 3;
				#ifdef DO8
					/*1*/	var += 3;
					/*2*/	var += 3;
					/*3*/	var += 3;
					/*4*/	var += 3;
					/*5*/	var += 3;
					/*6*/	var += 3;
					/*7*/	var += 3;
				#endif
			#endif
		}
		timer::time_t elapsed = timer::now() - t0;
		std::cout << "\r("<<(int)var<<") "<<iterations<<" iterations: "<<(unsigned long long)(float(EXECUTIONS) / timer::toSecondsf(elapsed)) << " operations per second"<<  std::endl;
	}
	
	return 0;	//signal that the program has completed correctly
}
