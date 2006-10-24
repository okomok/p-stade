#ifndef PSTADE_OVEN_SUB_RANGE_RESULT_HPP
#define PSTADE_OVEN_SUB_RANGE_RESULT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Same as:
//
// 'sub_range_base' with some workarounds


#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Range >
struct sub_range_result
{
    // 'const' works around "Forwarding Problem".
    typedef iter_range<
        typename range_iterator<Range>::type
    > const type;
};


template< class Range >
struct sub_range_result_const
{
    typedef iter_range<
        typename range_iterator_const<Range>::type
    > const type;
};


} } // namespace pstade::oven


#endif
