#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_COMB_SORT_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_COMB_SORT_HPP


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


// Iterator: Random Access Swappable
template< class Iterator, class Compare >
void iter_comb_sort(Iterator first, Iterator last, Compare comp)
{
    typedef typename boost::iterator_difference<Iterator>::type diff_t;

    diff_t gap = last - first;
    if ( gap < 1 )
        return;

    Iterator first2 = last;
    bool swapped = false;
    do {
        diff_t newgap = (gap * 10 + 3) / 13;
        if (newgap < 1)
            newgap = 1;

        first2 += newgap - gap;
        gap = newgap;
        swapped = false;
        for (Iterator target1 = first, target2 = first2; target2 != last; ++target1, ++target2) {
            if (comp(read(target2), read(target1))) {
                do_iter_swap(target1, target2);
                swapped = true;
            }
        }
    } while ((gap > 1) || swapped);
}

template< class Iterator > inline
void iter_comb_sort(Iterator first, Iterator last)
{
    test::iter_comb_sort(first, last, egg::less);
}


template< class Range, class Compare > inline
void comb_sort(Range& rng, Compare comp)
{
    test::iter_comb_sort(boost::begin(rng), boost::end(rng), comp);
}

template< class Range > inline
void comb_sort(Range& rng)
{
    test::iter_comb_sort(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::test


#endif
