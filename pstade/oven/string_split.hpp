#ifndef PSTADE_OVEN_STRING_SPLIT_HPP
#define PSTADE_OVEN_STRING_SPLIT_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/algorithm/string/find_iterator.hpp> // split_iterator
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace string_split_detail {


    template< class Range >
    struct baby
    {
        typedef
            boost::algorithm::split_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        template< class FinderT >
        result_type operator()(Range& rng, FinderT f) const
        {
            return result_type(iter_t(rng, f), iter_t());
        }
    };


} // namespace string_split_detail


PSTADE_FUNCTION(make_string_split, (string_split_detail::baby<_>))
PSTADE_PIPABLE(string_split, (op_make_string_split))


} } // namespace pstade::oven


#endif
