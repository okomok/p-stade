#ifndef PSTADE_OVEN_MB_ENCODED_HPP
#define PSTADE_OVEN_MB_ENCODED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/mb_from_wchar.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_encoded_detail {


    template< class Range >
    struct baby
    {
        typedef
            boost::archive::iterators::mb_from_wchar<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            return result(rng);
        }
    };


} // namespace mb_encoded_detail


PSTADE_FUNCTION(make_mb_encoded, (mb_encoded_detail::baby<_>))
PSTADE_PIPABLE(mb_encoded, (op_make_mb_encoded))


} } // namespace pstade::oven


#endif
