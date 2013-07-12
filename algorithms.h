#ifndef ALGORITHMS_H
#define ALGORITHMS_H

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

	for(Iter gt = lt + 1; gt < r; ++gt)
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
Heap sort (Cormen at al.)
-------------------------------------------------------------------------------*/




#endif // ALGORITHMS_H