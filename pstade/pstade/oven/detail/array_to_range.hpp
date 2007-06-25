#ifndef PSTADE_OVEN_DETAIL_ARRAY_TO_RANGE_HPP
#define PSTADE_OVEN_DETAIL_ARRAY_TO_RANGE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include "../iter_range.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Array >
struct array_to_range_aux
{
    typedef typename
        boost::remove_extent<Array>::type *
    iter_t;

    typedef
        iter_range<iter_t> const
    type;
};


template< class MaybeArray >
struct array_to_range :
    boost::mpl::eval_if< boost::is_array<MaybeArray>,
        array_to_range_aux<MaybeArray>,
        boost::add_reference<MaybeArray>
    >
{ };


} } } // namespace pstade::oven::detail


#endif
