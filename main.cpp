#include "algorithms.h"
#include "timer.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int const NUM_TEST = 5;
int const MIN_SIZE = 100;
int const MAX_SIZE = 100000;

#define RUN_TEST(func,first,last,timer) \
{ \
	generate(first, last, []() { return rand() % 1000; }); \
	timer.start(); \
	func(first, last); \
	timer.stop(); \
	if (!IsSorted(v.begin(), v.end()))\
	{\
		cout << "\nCATASTROPHE: incorrect output\n\n";\
		exit(-1); \
	}\
}



int main(int argc, char** argv)
{
	srand(12786324);

	CPUTimer timer;
	vector<int> v;

	int increment = (MAX_SIZE - MIN_SIZE)/NUM_TEST;

	for (int i=0;i<NUM_TEST;++i)
	{
		int size = MIN_SIZE + i*increment;
		v.resize(size);

		RUN_TEST(InsertionSort, v.begin(), v.end(), timer);

		cout << size << ";";
		cout << timer.elapsed() << ";" ;

		RUN_TEST(QuickSort, v.begin(), v.end(), timer);

		cout << timer.elapsed() << ";\n" ;
	}

	return 0;
}