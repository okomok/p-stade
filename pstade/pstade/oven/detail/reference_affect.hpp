#ifndef PSTADE_OVEN_DETAIL_REFERENCE_AFFECT_HPP
#define PSTADE_OVEN_DETAIL_REFERENCE_AFFECT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// The Note of "../transform_range.hpp".


#include <boost/mpl/apply.hpp>
#include <pstade/affect.hpp>
#include <pstade/remove_cvr.hpp>
#include "../range_reference.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range, class Lambda >
struct reference_affect
{
    typedef typename range_reference<Range>::type ref_t;

    typedef typename
        affect<
            ref_t,
            typename boost::mpl::apply1<Lambda, typename remove_cvr<ref_t>::type>::type
        >::type
    type;
};


} } } // namespace pstade::oven::detail


#endif
