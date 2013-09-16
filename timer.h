#ifndef TIMER_H
#define TIMER_H

#if defined(MSVC_VERSION) && MSCV_VERSION < 1700

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

#else

#include <chrono>

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
	
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point stop_;
    
    float elapsed_;
};

inline CPUTimer::CPUTimer() :
elapsed_(0.f)
{
}

inline CPUTimer::~CPUTimer()
{
}

inline void CPUTimer::start()
{
    start_ = std::chrono::high_resolution_clock::now();
}

inline void CPUTimer::stop()
{
	stop_ = std::chrono::high_resolution_clock::now();
	elapsed_ = std::chrono::duration<float>(stop_ - start_).count();
}

inline float CPUTimer::elapsed() const
{
	return elapsed_;
}


#endif

#endif // TIMER_H