#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_BUBBLE_SORT_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_BUBBLE_SORT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] http://www.s34.co.jp/cpptechdoc/article/sort/


#include <pstade/oven/prelude.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/oven/do_iter_swap.hpp>
#include <pstade/oven/read.hpp>


namespace pstade { namespace oven { namespace test {


// Iterator: Bidirectional Swappable
template< class Iterator, class Compare >
void iter_bubble_sort(Iterator first, Iterator last, Compare comp)
{
    bool swapped;
    do {
        Iterator curr = first;
        Iterator next = curr;
        ++next;
        swapped = false;
        while (next != last) {
            if (comp(read(next), read(curr))) {
                do_iter_swap(curr, next);
                swapped = true;
            }
            ++curr; ++next;
        }
        --last;
    } while (swapped);
}

template< class Iterator > inline
void iter_bubble_sort(Iterator first, Iterator last)
{
    test::iter_bubble_sort(first, last, less);
}


template< class Range, class Compare > inline
void bubble_sort(Range& rng, Compare comp)
{
    test::iter_bubble_sort(boost::begin(rng), boost::end(rng), comp);
}

template< class Range > inline
void bubble_sort(Range& rng)
{
    test::iter_bubble_sort(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::test


#endif
