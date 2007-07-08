#ifndef PSTADE_OVEN_STRING_FOUND_HPP
#define PSTADE_OVEN_STRING_FOUND_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/algorithm/string/find_iterator.hpp>
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace string_found_detail {


    template< class Range >
    struct base
    {
        typedef
            boost::algorithm::find_iterator<
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


} // namespace string_found_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(string_found, (string_found_detail::base<_>))


} } // namespace pstade::oven


#endif
