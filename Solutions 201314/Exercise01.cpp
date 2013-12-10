// SyssoftConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "performance_timer.h"
#include <iostream>
//#include <alloca.h>

#define AUFGABE	2	//3

int _tmain(int argc, _TCHAR* argv[])
{
	#if AUFGABE == 3
		for (int i = 0; i < 1024*1024; i++)
		{
			void*data = _alloca(1024);
			std::cout << i*1024 << std::endl;
		}
	#endif

	#if AUFGABE == 2
		size_t max = 1ULL<<32;
		size_t k = max / 4096 * 2;
		for (size_t n = 2; n <= max; n<<= 1)
		{
			int *int_array = (int*)malloc(sizeof(int) * n);

			timer::time_t t = timer::now();

			size_t i = 0;
			size_t n_loops=k; // k sei die Anzahl der Zugriffe
			while (n_loops-- > 0) {
				int_array[i]++;
				i = (i+4096) % n;
			}

			float seconds = timer::toSecondsf(timer::now() - t) / float(k);

			free(int_array);

			std::cout << n << ';'<<seconds*1000000 << std::endl;
		}
	#endif
	
	return 0;
}

