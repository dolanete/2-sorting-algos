#pragma once

#include <functional> // std::less
#include <iterator> // std::iterator_traits

namespace sort {

	// This is C++ magic which will allows our function
	// to default to using a < b if the comparator arg
	// is unspecified. It uses defines std::less<T>
	// for the iterator's value_type.
	//
	// For example: if you have a vector<float>, the 
	// iterator's value type will be float. std::less 
	// will select the < for sorting floats as the 
	// default comparator.
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept { 
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
/* 		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
		using value_type      = typename _it::value_type;
		using reference       = typename _it::reference;
		using pointer         = typename _it::pointer;
 */
		for (RandomIter i = begin; i != end; ++i) { // Iterate through list
			for (RandomIter j = begin; j < i; ++j) { // Iterate through list from beginning to the i position
				if (comp(*i, *j)) {
					swap(*i, *j);
				}
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		RandomIter j, k;
		for (RandomIter i = begin+1; i < end; ++i) { //Loop thorugh vector
			j = std::move(i-1);
			k = std::move(i);
			//k = std::move(i);
			while(j >= begin) {
				if (comp(*k, *j)) {
					swap(*k, *j);
				} else {
					break;
				}
				--j;
				--k;
			}
			/* for (; *k < *j; j--, k--) {
				if (comp(*k, *j)) {
					swap(*k, *j);
				}
			} */
		}

	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		
		RandomIter min;
		for (RandomIter i = begin; i < end; ++i) {
			min = std::move(i);
			for (RandomIter j = i+1; j < end; ++j) {
				if (comp(*j, *min)) {
					min = std::move(j);
				}
			}
			if (*i != *min) {
				swap(*i, *min);
			}
			
    	} 
	}
}
