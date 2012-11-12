#include <iostream>	//gain access to std::cout (also std::endl)
#include <stdlib.h>	//gain access to atoi (for string conversion)

//include our timer header
#ifdef _WIN32
	#include "../Windows/performance_timer.h"
#else
	#include "../Linux/performance_timer.h"
#endif

using namespace std;
/*
 This program should occupy and periodically update a number of memory pages.
 Time-measurement should be performed to detect changes in performance.
 It is adviced to keep an outer loop running indefinitely,
 using an endless loop (e.g. by using while(true) or for(;;))
*/
int main(int argc, char* argv[])
{
	size_t memory = 0;
	if (argc != 2)
	{
		std::cout << "Program usage: "<<argv[0]<<" [amount of memory]"<<std::endl;
		//return -1;
		memory = 1024ULL*1024ULL*1024ULL*6ULL;
	}
	else
		memory = atoi(argv[1]);
	if (memory == 0)
	{
		std::cout << "Invalid memory size. Must be a valid int >= 1";
		return -1;
	}
	
	char * data = new char[memory];

	size_t step = 1;
	while (true)
	{
		timer::time_t t0 = timer::now();

		for (size_t i = 0; i < memory; i+=step)
		{
			//if (0 == (i % (1024 * 1024*512)))
			//	std::cout << '.';
			data[i] = 0;
		}
		timer::time_t elapsed = timer::now() - t0;
		std::cout << "\rtime needed for "<<memory/1024/1024<<" MiB: " << timer::toSecondsf(elapsed)<<" seconds       "<<std::endl;
	}
	
	return 0;	//signal that the program has completed correctly
}
