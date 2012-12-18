#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "../Linux/performance_timer.h"

using namespace std;



class Calculator
{
public:
    static const int NumNumbers = 800000;
    static void* Process(void*)
    {
    
        int*primes = new int[NumNumbers];
        timer::time_t stared = timer::now();
        int found_primes = 0;
        for (int i = 2; i < NumNumbers; i++)
        {
            bool is_prime = true;
            for (int j = 0; j < found_primes / 2; j++)
                if ((i % primes[j]) == 0)
                {
                    is_prime = false;
                    break;
                }
            if (!is_prime)
                continue;
            primes[found_primes++] = i;
        }
        timer::time_t elapsed = timer::now() - stared;
		cout << "Calculator thread (thread " << pthread_self() << ") finished after " << timer::toSecondsf(elapsed) << " seconds"<<endl;
		delete[] primes;
		return NULL;
    }

};


class Writer
{
public:
	static const int NumChunks = 1000;
	static const int ChunkSize = 1000000;
	static void* Process(void*)
    {
		char buffer [L_tmpnam];

		tmpnam (buffer);		
		FILE*f = fopen(buffer,"wb+");

		char*chunk = new char[ChunkSize];
        for (int i = 0; i < ChunkSize; i++)
            chunk[i] = (char)i;

        timer::time_t stared = timer::now();

        for (int i = 0; i < NumChunks; i++)
        {
        	fwrite(chunk,ChunkSize,1,f);
        	fflush(f);
        }

		timer::time_t elapsed = timer::now() - stared;
		cout << "Writer thread (thread " << pthread_self() << ") finished after " << timer::toSecondsf(elapsed) << " seconds"<<endl;
		fclose(f);
		remove(buffer);
		delete[] chunk;
		return NULL;
    }

};






int main( int argc, const char* argv[] )
{
	if (argc != 2)
	{
		std::cout << "Program usage: "<<argv[0]<<" [calculator thread count]"<<std::endl;
		return -1;
	}
	const int num_calculators = atoi(argv[1]);

	static const int NumWriters = 1;
	//static const int NumCalculators = 4; 


	pthread_t	write_handle[NumWriters];
	pthread_t	*calc_handle = new 	pthread_t[num_calculators];
	
	for (int i = 0; i < num_calculators; i++)
		pthread_create(calc_handle+i,NULL,&Calculator::Process,NULL);
	for (int i = 0; i < NumWriters; i++)
		pthread_create(write_handle+i,NULL,&Writer::Process,NULL);


	for (int i = 0; i < num_calculators; i++)
        pthread_join(calc_handle[i],NULL);
	for (int i = 0; i < NumWriters; i++)
		pthread_join(write_handle[i],NULL);

	delete[] calc_handle;
}

