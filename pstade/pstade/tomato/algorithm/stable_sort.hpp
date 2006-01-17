#pragma once

/// \file stable_sort.hpp
/// tomato::stable_sort works around CRT.
/// std::stable_sort triggers the buffered merge-sort that seems to require CRT.

#include <algorithm>
#include <functional>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace pstade { namespace tomato {


/// \cond OUTPUT_DETAIL
namespace stable_sort_detail {

	template< class RandomAccessIter, class Predicate > inline
	void insertion_sort(RandomAccessIter first, RandomAccessIter last, Predicate pred)
	{
	#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
		std::__insertion_sort(first, last, pred);
	#else
		std::_Insertion_sort(first, last, pred);
	#endif
	}

} // namespace stable_sort_detail
/// \endcond


// iterator interface
template< class RandomAccessIter, class Predicate > inline
void stable_sort(RandomAccessIter first, RandomAccessIter last, Predicate pred)
{
	stable_sort_detail::insertion_sort(first, last, pred);
}

// range interface
template< class RandomAccessRange, class Predicate > inline
void stable_sort(RandomAccessRange& rng, Predicate pred)
{
	tomato::stable_sort(boost::begin(rng), boost::end(rng), pred);
}

// const-range interface
template< class RandomAccessRange, class Predicate > inline
void stable_sort(RandomAccessRange const& rng, Predicate pred)
{
	tomato::stable_sort(boost::begin(rng), boost::end(rng), pred);
}

// default less predicate

// iterator interface
template< class RandomAccessIter > inline
void stable_sort(RandomAccessIter first, RandomAccessIter last)
{
	typedef typename boost::iterator_value<RandomAccessIter>::type value_t;

	tomato::stable_sort(first, last, std::less<value_t>());
}

// range interface
template< class RandomAccessRange > inline
void stable_sort(RandomAccessRange& rng)
{
	typedef typename boost::range_value<RandomAccessRange>::type value_t;

	tomato::stable_sort(boost::begin(rng), boost::end(rng), std::less<value_t>());
}

// const-range interface
template< class RandomAccessRange > inline
void stable_sort(RandomAccessRange const& rng)
{
	typedef typename boost::range_value<RandomAccessRange>::type value_t;

	tomato::stable_sort(boost::begin(rng), boost::end(rng), std::less<value_t>());
}


} } // namespace pstade::tomato
