#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_SELECTION_SORT_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_SELECTION_SORT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] http://www.s34.co.jp/cpptechdoc/article/sort/


#include <pstade/oven/detail/prefix.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/less.hpp> // less
#include <pstade/oven/do_iter_swap.hpp>
#include <pstade/oven/read.hpp>


namespace pstade { namespace oven { namespace test {


template< class Iterator, class Compare >
Iterator min_element_(Iterator first, Iterator last, Compare comp)
{
    if (first == last)
        return first;

    Iterator result = first;
    while (++first != last) {
        if (comp(read(first), read(result)))
            result = first;
    }

    return result;
}


// Iterator: Forward Swappable
template< class Iterator, class Compare >
void iter_selection_sort(Iterator first, Iterator last, Compare comp)
{
    while (first != last) {
        Iterator mid = test::min_element_(first, last, comp);
        if (first != mid) {
            do_iter_swap(first, mid);
        }
        ++first;
    }
}

template< class Iterator > inline
void iter_selection_sort(Iterator first, Iterator last)
{
    test::iter_selection_sort(first, last, egg::less);
}


template< class Range, class Compare > inline
void selection_sort(Range& rng, Compare comp)
{
    test::iter_selection_sort(boost::begin(rng), boost::end(rng), comp);
}

template< class Range > inline
void selection_sort(Range& rng)
{
    test::iter_selection_sort(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::test


#endif
