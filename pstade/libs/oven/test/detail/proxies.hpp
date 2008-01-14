#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_PROXIES_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_PROXIES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/base_to_adaptor.hpp>
#include <pstade/oven/detail/prefix.hpp>
#include <pstade/oven/concepts.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "./proxy_iterator.hpp"


namespace pstade { namespace oven { namespace test {


template< class Range >
struct base_make_proxies
{
    typedef
        proxy_iterator<
            typename range_iterator<Range>::type
        >
    iter_t;

    typedef
        iter_range<iter_t> const
    result_type;

    result_type operator()(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return result_type(rng);
    }
};


PSTADE_OVEN_BASE_TO_ADAPTOR(proxies, (base_make_proxies<_>))


} } } // namespace pstade::oven::test


#endif
