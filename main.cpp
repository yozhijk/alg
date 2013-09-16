#include "algorithms.h"
#include "timer.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int const NUM_ITER = 5;
int const NUM_TEST = 1;
int const MIN_SIZE = 10000000;
int const MAX_SIZE = 10000000;

#define RUN_TEST(func,first,last,timer,iters) \
{ \
    elapsed=0;\
    for (int i=0;i<iters;++i){\
	generate(first, last, []() { return rand(); }); \
	timer.start(); \
	func(first, last); \
	timer.stop(); \
    elapsed+=timer.elapsed();\
	if (!IsSorted(v.begin(), v.end()))\
	{\
		cout << "\nCATASTROPHE: incorrect output\n\n";\
		exit(-1); \
	}}\
    elapsed /= iters;\
}



int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	CPUTimer timer;
	vector<int> v;
    
    float elapsed = 0;
	
	int increment = (MAX_SIZE - MIN_SIZE)/NUM_TEST;
	for (int i=0;i<NUM_TEST;++i)
	{
		int size = MIN_SIZE + i*increment;
		v.resize(size);

		// This is too slow on large input
		//RUN_TEST(InsertionSort, v.begin(), v.end(), timer);

		//cout << size << ";";
		//cout << timer.elapsed() << ";" ;

		RUN_TEST(std::sort, v.begin(), v.end(), timer, NUM_ITER);

		cout << elapsed << ";" ;

		RUN_TEST(HybridSort, v.begin(), v.end(), timer, NUM_ITER);

		cout << elapsed << ";";
        
        RUN_TEST(QuickSort, v.begin(), v.end(), timer, NUM_ITER);
        
		cout << elapsed << ";";

		cout << "\n";
	}



	return 0;
}