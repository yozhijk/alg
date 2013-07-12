#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

class CPUTimer
{
public:
	CPUTimer();
	~CPUTimer();
	
	void start();
	void stop();
	float elapsed() const;
	
private:
	CPUTimer(CPUTimer const&);
	CPUTimer& operator=(CPUTimer const&);
	
	LARGE_INTEGER freq_;
	LARGE_INTEGER start_;
	float 		elapsed_;
}; 

inline CPUTimer::CPUTimer() : 
elapsed_(0.f)
{
	QueryPerformanceFrequency(&freq_);
}

inline CPUTimer::~CPUTimer()
{
	
}

inline void CPUTimer::start()
{
	QueryPerformanceCounter(&start_);
}

inline void CPUTimer::stop()
{
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	elapsed_ = float(end.QuadPart - start_.QuadPart)/(float(freq_.QuadPart));
}

inline float CPUTimer::elapsed() const
{
	return elapsed_;
}

#endif // TIMER_H