#include <iostream>	//allow access to std::cout (also std::endl)
#include <stdlib.h>	//allow access to atoi (for string conversion)

//include our timer header
#ifdef _WIN32
	#include "../Windows/performance_timer.h"
#else
	#include "../Linux/performance_timer.h"
#endif


/*
 This program should occupy and periodically update a number of memory pages.
 Time-measurement should be performed to detect changes in performance.
 It is adviced to keep an outer loop running indefinitely,
 using an endless loop (e.g. by using while(true) or for(;;))
*/
int main(int argc, char* argv[])
{
	int pages = 0;
	if (argc != 2)
	{
		std::cout << "Program usage: "<<argv[0]<<" [page count]"<<std::endl;
		return -1;
		//pages = 200000;	you may default to this value as well.
	}
	else
		pages = atoi(argv[1]);	//parse firts parameter to page count.
	if (pages <= 0)
	{
		std::cout << "Invalid page count. Must be a valid int >= 1";
		return -1;
	}
	
	
	your program here
	
	
	return 0;	//signal that the program has completed correctly
}
