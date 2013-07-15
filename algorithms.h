#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cassert>


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
	while (tmp != l);
}

// debug insertion sort



/*-----------------------------------------------------------------------------
Tail-recursive quicksort implementation (Cormen et al.)
-------------------------------------------------------------------------------*/
template <typename T> void Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

template <typename Iter> Iter Partition(Iter l, Iter r)
{
	Iter lt = l;

	for(Iter gt = lt + 1; gt != r; ++gt)
	{
		if (*gt < *l)
		{
			Swap(*(++lt), *gt);
		}
	}

	Swap(*l, *lt);
	return lt;
}

template <typename Iter> void QuickSort(Iter l, Iter r)
{
	while (l < r)
	{
		Iter q = Partition(l,r);
		QuickSort(l,q);
		l = q + 1;
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
	unsigned Parent(unsigned i) { return (i >> 1) - 1; }
	unsigned Child1(unsigned i) { return ((i << 1) + 1); }
	unsigned Child2(unsigned i) { return ((i << 1) + 2); }

	void Heapify (unsigned i);
	
	bool CheckInvariant(unsigned int i);


	Iter first_;
	unsigned size_; 
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
		Swap(*(first_ + max), *(first_ + i));
		Heapify(max);
	}
}

template <typename Iter> inline void Heap<Iter>::BuildMaxHeap()
{
	unsigned oldSize_ = size_;
	for (int i = (size_ >> 1)-1;i >= 0;--i)
	{
		Heapify(i);
	}
}

template <typename Iter> inline void Heap<Iter>::Sort()
{
	unsigned oldSize = size_ ;
	BuildMaxHeap();

	for (; size_ > 1; --size_)
	{
		Heapify(0);
		Swap(*(first_ + size_ - 1), *first_);
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