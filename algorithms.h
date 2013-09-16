#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iterator>
#include <future>


template<typename Iter> bool IsSorted(Iter first, Iter last)
{
	for (Iter i=first+1;i!=last;++i)
		if (*i < *(i-1)) return false;
	return true;
}

/*-----------------------------------------------------------------------------
Insertion sort (Cormen et al.)
-------------------------------------------------------------------------------*/
template <typename Iter> void InsertionSort(Iter l, Iter r)
{
	Iter tmp, back;
	tmp = r-1;
	do
	{
		--tmp;
		auto val = *tmp;
		for (back = tmp+1; r-back-1 >= 0 && *back < val; ++back)
		{
			*(back-1) = *back;
		}
		*(back-1) = val;
	}
	while (tmp > l);
}

// debug insertion sort



/*-----------------------------------------------------------------------------
Tail-recursive randomized quicksort implementation (Cormen et al.)
-------------------------------------------------------------------------------*/
template <typename T> inline void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

template <typename Iter> inline Iter Partition(Iter l, Iter r)
{
	size_t size = r - l;
	size_t med = size >> 1;
    
    if (*(r-1) < *l) std::swap(*l, *(r - 1));
    if (*(r-1) < *(l + med)) std::swap(*(r-1), *(l + med));
    if (*l < *(l + med)) std::swap(*l, *(l + med));
	
	Iter lt = l;
    auto val = *l;
	
	for(Iter gt = lt + 1; gt < r; ++gt)
	{
		if (*gt < val)
		{
			std::swap(*(++lt), *gt);
		}
	}

	std::swap(*l, *lt);

	return lt;
}


template <typename Iter> void QuickSort(Iter l, Iter r)
{
	while (l < r - 1)
	{
		Iter q = Partition(l, r);
		
		if (q - l > r - q + 1)
		{
			QuickSort(q + 1, r);
			r = q;
		}
		else
		{
			QuickSort(l, q);
			l = q + 1;
		}
	}
}

#define CHUNK_SIZE 16
#define PAR_CHUNK 4096


template <typename Iter> inline void HybridSort(Iter l, Iter r)
{
	if (l < r - 1)
	{
        Iter q = Partition(l, r);
        
        if (r - q + 1 < CHUNK_SIZE)
        {
            InsertionSort(q + 1, r);
        }
        else if (r - q + 1 > PAR_CHUNK)
        {
            auto future = std::async(std::launch::async, [&]()
                                            {
                                                HybridSort(q + 1, r);
                                            });
            
            if (q - l < CHUNK_SIZE)
            {
                InsertionSort(l, q);
            }
            else
            {
                HybridSort(l, q);
            }
            return;
        }
        else
        {
            HybridSort(q + 1, r);
        }
        
        if (q - l < CHUNK_SIZE)
        {
            InsertionSort(l, q);
        }
        else
        {
            HybridSort(l, q);
        }
    }
}



/*-----------------------------------------------------------------------------
Heap sort (Cormen at al.), RA iterators only
-------------------------------------------------------------------------------*/
template <typename Iter> class Heap
{
public:
	Heap(Iter first, Iter last);

	void Sort();
	bool CheckInvariant() { return CheckInvariant(0); }
	void BuildMaxHeap();

private:
	bool     IsLeaf(unsigned i) { return Child1(i) >= size_ && Child2(i) >= size_; }
	unsigned Child1(unsigned i) { return ((i << 1) + 1); }
	unsigned Child2(unsigned i) { return ((i << 1) + 2); }

	void Heapify (unsigned i);
	
	bool CheckInvariant(unsigned int i);


	Iter first_;
	size_t size_;
};

template <typename Iter> void HeapSort(Iter l, Iter r)
{
	Heap<Iter> heap(l, r);
	heap.Sort();
}


 template <typename Iter> inline Heap<Iter>::Heap(Iter first, Iter last)
	: first_(first)
	, size_(last - first)
{
	assert(size_ > 0);
}

template <typename Iter> inline void Heap<Iter>::Heapify (unsigned i)
{
	unsigned c1 = Child1(i);
	unsigned c2 = Child2(i);

	unsigned max = i;

	if (c1 < size_)
	{
		if (*(first_ + c1) > *(first_ + max))
			max = c1;	
	} 

	if (c2 < size_)
	{
		if (*(first_ + c2) > *(first_ + max))
			max = c2;
	}

	if (max != i)
	{
		std::swap(*(first_ + max), *(first_ + i));
		Heapify(max);
	}
}

template <typename Iter> inline void Heap<Iter>::BuildMaxHeap()
{
	size_t oldSize = size_;
	for (int i = (size_ >> 1)-1;i >= 0;--i)
	{
		Heapify(i);
	}
    size_ = oldSize;
}

template <typename Iter> inline void Heap<Iter>::Sort()
{
	unsigned oldSize = size_ ;
	BuildMaxHeap();

	for (; size_ > 1; --size_)
	{
		Heapify(0);
		std::swap(*(first_ + size_ - 1), *first_);
	}

	size_ = oldSize;
}

template <typename Iter> inline bool Heap<Iter>::CheckInvariant(unsigned int i)
{
	if (IsLeaf(i)) return true;
	
	bool isOK = true;
	unsigned c1 = Child1(i);
	unsigned c2 = Child2(i);
	
	if (c1 < size_)
	{
		isOK =isOK && *(first_ + c1)<=*(first_ + i) && CheckInvariant(c1);
	}

	if (c2 < size_)
	{
		isOK =isOK && *(first_ + c2)<=*(first_ + i) && CheckInvariant(c2);
	}

	return isOK;
}


#endif // ALGORITHMS_H