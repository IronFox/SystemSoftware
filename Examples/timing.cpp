#include <iostream>	//allow access to std::cout (also std::endl)

//include our timer header
#ifdef _WIN32
	#include "../Windows/performance_timer.h"
#else
	#include "../Linux/performance_timer.h"
#endif


/**
@brief Main entry point of our program
@param argc Number of runtime parameters passed to this program. Usually at least 1
@param argv Array of runtime parameters passed to this program.
 You may access up to argc number of parameters.
 Typically, the first parameter is the name of the program itself.
 
This function is automatically executed when the program is started.
Unless called from within this function, other functions are not executed.
@return 0, if the program executed correctly, any other integer otherwise.
*/
int main(int argc, char* argv[])
{
	int num_iterations = 100000000;
	std::cout << "starting loop over " << num_iterations << " iterations" << std::endl;
	volatile int dummy; //prevent optimization from removing the loop (since it does nothing)
	timer::time_t t0 = timer::now();	//measure time before our operation
	for (int i = 0; i < num_iterations; i++)
	{
		dummy = i;
	}
	float seconds = timer::toSecondsf(timer::now() - t0);	//measure time after our operation and convert it into seconds
	std::cout << "execution took "<<seconds<<" seconds to complete.\nprogram will exit now"<<std::endl;
	return 0;	//signal that the program has completet correctly
}
