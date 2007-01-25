#ifndef PSTADE_OVEN_MB_DECODED_HPP
#define PSTADE_OVEN_MB_DECODED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/wchar_from_mb.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_decoded_detail {


    template< class Range >
    struct baby
    {
        typedef
            boost::archive::iterators::wchar_from_mb<
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


} // namespace mb_decoded_detail


PSTADE_FUNCTION(make_mb_decoded, (mb_decoded_detail::baby<_>))
PSTADE_PIPABLE(mb_decoded, (op_make_mb_decoded))


} } // namespace pstade::oven


#endif
